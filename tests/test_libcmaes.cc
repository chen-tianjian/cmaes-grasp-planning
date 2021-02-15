#include "cmaes.h"
#include "gtest/gtest.h"

using namespace libcmaes;


FitFunc fsphere_lambda_expr = [](const double *x, const int & N)
{
    double val = 0.0;
    for (int i=0;i<N;i++)
    val += x[i]*x[i];
    return val;
};


double fsphere_reg_func(const double *x, const int N)
{
    double val = 0.0;
    for (int i=0;i<N;i++)
    val += x[i]*x[i];
    return val;
}



class TestLIBCMAES : public ::testing::Test
{
    protected:
    std::vector<double> x0;
    double sigma;
    CMAParameters<> cmaparams;

    public:
    TestLIBCMAES(){}
    virtual ~TestLIBCMAES() {}

    protected:
    virtual void SetUp()
    {
        int dim = 10;
        x0 = std::vector<double>(dim, 10.0);
        sigma = 0.1;
    }

    void printResult(const CMASolutions & cmasols)
    {
        std::cout << "best solution: " << cmasols << std::endl;
        std::cout << "optimization took " << cmasols.elapsed_time() / 1000.0 << " seconds\n";
        std::cout << cmasols.run_status(); // the optimization status, failed if < 0
    }
};



class TestLIBCMAESBasic : public TestLIBCMAES
{
    public:
    TestLIBCMAESBasic():TestLIBCMAES(){}
    virtual ~TestLIBCMAESBasic() {}

    protected:
    virtual void SetUp()
    {
        TestLIBCMAES::SetUp();
        cmaparams = CMAParameters<>(x0, sigma);
    }

};


// TEST(TestLIBCMAES_nofixture, test_fsphere_lambda_expr) 
// {
//     int dim = 10;
//     std::vector<double> x0(dim, 10.0);
//     double sigma = 0.1;
//     CMAParameters<> cmaparams(x0, sigma);
//     CMASolutions cmasols = cmaes<>(fsphere_lambda_expr, cmaparams);
//     std::cout << "best solution: " << cmasols << std::endl;
//     std::cout << "optimization took " << cmasols.elapsed_time() / 1000.0 << " seconds\n";
//     Candidate bcand = cmasols.best_candidate();
//     double fmin = bcand.get_fvalue(); // min objective function value the optimizer converged to
//     ASSERT_NEAR(fmin, 0, 1e-3);
// }


TEST_F(TestLIBCMAESBasic, test_fsphere_lambda_expr) 
{
    CMASolutions cmasols = cmaes<>(fsphere_lambda_expr, cmaparams);
    printResult(cmasols);
    Candidate bcand = cmasols.best_candidate();
    double fmin = bcand.get_fvalue(); // min objective function value the optimizer converged to
    ASSERT_NEAR(fmin, 0, 1e-3);
}


TEST_F(TestLIBCMAESBasic, test_fsphere_reg_func) 
{
    FitFunc fsphere_fitfunc = fsphere_reg_func;
    CMASolutions cmasols = cmaes<>(fsphere_fitfunc, cmaparams);
    printResult(cmasols);
    Candidate bcand = cmasols.best_candidate();
    double fmin = bcand.get_fvalue(); // min objective function value the optimizer converged to
    ASSERT_NEAR(fmin, 0, 1e-3);
}


TEST_F(TestLIBCMAESBasic, test_cmaparams) 
{
    cmaparams.set_max_fevals(10000); // limits the number of function evaluations to 10000
    cmaparams.set_max_iter(100000); // limits the number of iterations of the algorithms to 1000000
    cmaparams.set_ftarget(1e-6); // stops the optimization whenever the objective function values gets below 1e-6
    cmaparams.set_fplot("tests/test_output.dat");
    cmaparams.set_mt_feval(true); // activates the parallel evaluation

    CMASolutions cmasols = cmaes<>(fsphere_lambda_expr, cmaparams);
    printResult(cmasols);
    Candidate bcand = cmasols.best_candidate();
    double fmin = bcand.get_fvalue(); // min objective function value the optimizer converged to
    ASSERT_NEAR(fmin, 0, 1e-3);
}


TEST_F(TestLIBCMAES, test_bounds)
{
    int dim = x0.size();
    double lb[dim], ub[dim]; 
    for (int i = 0; i < dim; i++)
    {
        lb[i] = -2.0;
        ub[i] = 2.0;
    }
    GenoPheno<pwqBoundStrategy, linScalingStrategy> gp(lb, ub, dim); // genotype / phenotype transform associated to bounds.
    CMAParameters<GenoPheno<pwqBoundStrategy, linScalingStrategy>> cmaparams(dim,&x0.front(),sigma,-1,0,gp); // -1 for automatically decided lambda, 0 is for random seeding of the internal generator.           
    // cmaparams.set_algo(aCMAES);
    CMASolutions cmasols = cmaes<GenoPheno<pwqBoundStrategy, linScalingStrategy>>(fsphere_lambda_expr,cmaparams);
    printResult(cmasols);
    cmasols.run_status();

    Eigen::VectorXd bestx = gp.pheno(cmasols.get_best_seen_candidate().get_x_dvec());
    std::cout << "best x:" << bestx << std::endl;
    double fmin = fsphere_lambda_expr(bestx.data(), bestx.size());
    ASSERT_NEAR(fmin, 0, 1e-3);

}