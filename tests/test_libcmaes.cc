#include "cmaes.h"
#include "gtest/gtest.h"

using namespace libcmaes;


FitFunc fsphere = [](const double *x, const int N)
{
  double val = 0.0;
  for (int i=0;i<N;i++)
    val += x[i]*x[i];
  return val;
};


TEST(TestLIBCMAES, fsphere) {
    int dim = 10;
    std::vector<double> x0(dim, 10.0);
    double sigma = 0.1;
    CMAParameters<> cmaparams(x0, sigma);
    CMASolutions cmasols = cmaes<>(fsphere, cmaparams);
    std::cout << "best solution: " << cmasols << std::endl;
    std::cout << "optimization took " << cmasols.elapsed_time() / 1000.0 << " seconds\n";
    Candidate bcand = cmasols.best_candidate();
    double fmin = bcand.get_fvalue(); // min objective function value the optimizer converged to
    ASSERT_NEAR(fmin, 0, 1e-3);
}
