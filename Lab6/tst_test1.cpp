#include "Polynomial.h"
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <string.h>

using namespace testing;

TEST(PolynomialTest, GetValue_Test1)
{
    std::initializer_list<pair> members{pair{1, 0}, {0, 5}, {5, 2}, {100, 200}};
    Polynomial<4> pol(members);
    EXPECT_EQ(pol.getValue(4), 2053);

}

TEST(PolynomialTest, GetValue_Test2)
{
    std::initializer_list<pair> members{pair{1, 0}, {0, 5}, {5, 2}, {100, 200}};
    Polynomial<5> pol(members);
    EXPECT_EQ(pol.getValue(0), 5);
}

TEST(PolynomialTest, GetValue_Test3)
{
    std::initializer_list<pair> members{pair{1, 1}};
    Polynomial<1> pol(members);
    EXPECT_EQ(pol.getValue(165), 165);
}

TEST(PolynomialTest, GetValue_Test4)
{
    std::initializer_list<pair> members{pair{1, 1}};
    Polynomial<1> pol(members);
    EXPECT_EQ(pol.getValue(0), 0);
}

TEST(PolynomialTest, GetValue_Test5)
{
    std::initializer_list<pair> members{pair{4, 1}};
    Polynomial<1> pol(members);
    EXPECT_EQ(pol.getValue(2), 16);
}

TEST(PolynomialTest, cout_Test)
{
    std::initializer_list<pair> members{pair{2, 2}, pair{1, 2}, pair{3, 2}, pair{4, 2}, pair{0, 2}};
    Polynomial<5> pol(members);
    testing::internal::CaptureStdout();
    std::cout<<pol;
    std::string out=testing::internal::GetCapturedStdout();
    EXPECT_STREQ(out.c_str(), "+2x^2+2x^1+2x^3+2x^4+2x^0");
}

