#include "gtest/gtest.h"
#include <math.h>

double squareRoot(const double a) {
    double b = sqrt(a);
    if(b != b) { // nan check
        return -1.0;
    }else{
        return sqrt(a);
    }
}


class TestSquareRoot : public ::testing::Test // This is a practice for the test fixture and setup procedures, it is not necessary
{
  protected:
  bool this_is_true;

  TestSquareRoot(){}
  virtual ~TestSquareRoot(){}

  virtual void SetUp()
  {
	this_is_true = true;
  }
};


TEST_F(TestSquareRoot, PositiveNos) 
{
	ASSERT_TRUE(this_is_true);
    ASSERT_EQ(6, squareRoot(36.0));
    ASSERT_EQ(18.0, squareRoot(324.0));
    ASSERT_EQ(25.4, squareRoot(645.16));
    ASSERT_EQ(0, squareRoot(0.0));
}


TEST_F(TestSquareRoot, NegativeNos) 
{
    ASSERT_EQ(-1.0, squareRoot(-15.0));
    ASSERT_EQ(-1.0, squareRoot(-0.2));
}
 

TEST(TestSquareRoot2, NegativeNos) // with the same test fixture name TestSquareRoot, we cannot mix TEST and TEST_F together
{
    ASSERT_EQ(-1.0, squareRoot(-15.0));
    ASSERT_EQ(-1.0, squareRoot(-0.2));
}
 
