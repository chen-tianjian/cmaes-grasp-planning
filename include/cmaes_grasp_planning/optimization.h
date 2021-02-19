#ifndef _CMAES_GRASP_PLANNING_OPTIMIZATION_H_
#define _CMAES_GRASP_PLANNING_OPTIMIZATION_H_

#include <vector>


#define LATEST 0
#define SEEN 1

namespace cmaes_grasp_planning {


struct CMAESParams
{
    std::vector<double> x0;
    double sigma0;
    int lambda = -1;
    std::vector<double> lb;
    std::vector<double> ub;
    double xtol = 1e-6;
    double ftol = 1e-6;
    int max_iter = -1;
    int max_feval = -1;
    bool render = false;
    bool best_grasp = LATEST;
};


class CMAESGraspPlanningOptimization
{
protected:
    CMAESParams params_;
    std::vector<double> x_best_;
    
public:
    CMAESGraspPlanningOptimization(CMAESParams params): params_(params){}
    ~CMAESGraspPlanningOptimization(){}

    bool optimize();
    std::vector<double> const getXBest() {return x_best_;}
};


} //end of namespace cmaes_grasp_planning

#endif