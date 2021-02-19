#include "cmaes_grasp_planning/optimization.h"
#include "graspit/graspitCore.h"
#include "graspit/world.h"
#include "graspit/robot.h"
#include "graspit/grasp.h"
#include "graspit/contact/contact.h"
#include "graspit/ivmgr.h"
#include "graspit/quality/quality.h"
#include "cmaes.h"

using namespace libcmaes;

double LOWEST_SCORE = -5.0;
namespace cmaes_grasp_planning {

bool CMAESGraspPlanningOptimization::optimize()
{
    World *world = graspitCore->getWorld();
    if (!world)
    {
        std::cerr << "No world" << std::endl; 
        return false;
    }

    Hand* hand = world -> getCurrentHand();
    if (!hand)
    {
        std::cerr << "No hand" << std::endl; 
        return false;
    }

    int n_hand_dof = hand->getNumDOF();
    if (params_.lb.size() != 6 + n_hand_dof || (params_.ub.size() != 6 + n_hand_dof) || (params_.x0.size() != 6 + n_hand_dof)) 
    {
        std::cerr << "Dimension mismatch: lower bound dimension: "<< params_.lb.size() << ", upper bound dimension: " << params_.ub.size() << ", x0 dimension: " << params_.x0.size() << ", hand (and wrist) number of DoF: " << 6 + n_hand_dof << std::endl; 
        return false;
    }

    for (int i = 0; i < 6 + n_hand_dof; i++)
    {
        if (params_.lb[i] > params_.ub[i])
        {
            std::cerr << "Lower bound " << params_.lb[i] << " larger than upper bound " << params_.ub[i] << std::endl; 
            return false;
        }
        if ((params_.x0[i] < params_.lb[i]) || (params_.x0[i] > params_.ub[i]))
        {
            std::cerr << "x0 entry " << params_.x0[i] << " not in the lower - upper bound interval" << std::endl; 
            return false;
        }
    }
    


    Grasp *grasp = hand->getGrasp();
    GraspableBody* object = grasp->getObject();
    if (!object) 
    {
        std::cerr << "No object" << std::endl; 
        return false;
    }

    QualityMeasure *quality = grasp->getQM(0); // always use the first qm
    if (!quality) 
    {
        std::cerr << "No quality metric" << std::endl; 
        return false;
    }

    FitFunc calcNegQualityMetric = [world, hand, grasp, quality, this](const double *x, const int & N)
    {
        double quality_metric = 0;
        // x: palm XYZ (in mm) RPY (in rad) and finger joint values (in rad)
        transf palm_trans = transf::TRANSLATION(vec3(x[0], x[1], x[2])) % transf::RPY(x[3], x[4], x[5]); // % means multiplication  
        hand->setTran(palm_trans);
        double * hand_dof_val_ptr = const_cast<double *>(x)+6; //x is a pointer
        hand->checkSetDOFVals(hand_dof_val_ptr); // change the val if out of joint limits
        hand->forceDOFVals(hand_dof_val_ptr); 
        world->updateGrasps();
        if (world->noCollision() == false)
        {
            quality_metric = LOWEST_SCORE + 1.0; // no-force closure has a qm -1, this is worse
            return -quality_metric; // convert to minimization
        }
        hand->autoGrasp(this->params_.render);
        world->updateGrasps();
        quality_metric = quality->evaluate();
        if (quality_metric < 0) // no force closure
        {
            int n_contacts = grasp->getNumContacts();
            quality_metric = std::min(LOWEST_SCORE + n_contacts, 0.0); // no contact is the worst, more contact is better, but should not be better than force-closure (0)
        }
        return -quality_metric; // convert to minimization
    };

    GenoPheno<pwqBoundStrategy, linScalingStrategy> gp(&params_.lb.front(), &params_.ub.front(), 6+n_hand_dof); // genotype / phenotype transform associated to bounds.
    CMAParameters<GenoPheno<pwqBoundStrategy, linScalingStrategy>> cmaparams(params_.x0, params_.sigma0, params_.lambda, 0, gp); // 0 is for random seeding of the internal generator.           
    cmaparams.set_max_iter(params_.max_iter);
    cmaparams.set_max_fevals(params_.max_feval);
    cmaparams.set_xtolerance(params_.xtol);
    cmaparams.set_ftolerance(params_.ftol);
    cmaparams.set_algo(aCMAES);
    cmaparams.set_quiet(false);
    CMASolutions cmasols = cmaes<GenoPheno<pwqBoundStrategy, linScalingStrategy>>(calcNegQualityMetric, cmaparams);
    std::cout << cmasols.status_msg() << std::endl;
    Eigen::VectorXd x_best_eigen;
    if (params_.best_grasp == SEEN)
    {
        x_best_eigen = gp.pheno(cmasols.get_best_seen_candidate().get_x_dvec());
    }
    else
    {
        x_best_eigen = gp.pheno(cmasols.best_candidate().get_x_dvec());
    }
    x_best_ = std::vector<double>(x_best_eigen.data(), x_best_eigen.data() + x_best_eigen.size());
    double fmin = calcNegQualityMetric(&x_best_.front(), x_best_.size());
    std::cout << "Best grasp quality:" << -fmin << std::endl;

    return true;

}



} //end of namespace cmaes_grasp_planning
