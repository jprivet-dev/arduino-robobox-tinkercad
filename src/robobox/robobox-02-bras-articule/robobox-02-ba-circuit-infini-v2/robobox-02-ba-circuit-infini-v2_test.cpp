#include <math.h>
 
// Get the Square root of a number. 
double squareRoot(const double a) 
{
    double b = sqrt(a);
    if(b != b) // NaN check
        { return -1.0; }
    else
        { return sqrt(a); }
}

#include <gtest/gtest.h>
 
TEST(SquareRootTest, PositiveNos) 
    { 
    ASSERT_EQ(6, squareRoot(36.0));
    ASSERT_EQ(18.0, squareRoot(324.0));
    ASSERT_EQ(25.4, squareRoot(645.16));
    ASSERT_EQ(0, squareRoot(0.0));
    }
 
TEST(SquareRootTest, NegativeNos) 
    {
    ASSERT_EQ(-1.0, squareRoot(-15.0));
    ASSERT_EQ(-1.0, squareRoot(-0.2));
    }
 
int main(int argc, char **argv) 
    {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    }