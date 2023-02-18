#include <iostream>
#include <gtest/gtest.h>
#include "Polynomial.h"

int main(int argc, char *argv[]){

    std::initializer_list<pair> members{pair{1, 0}, {0, 5}, {5, 2}, {100, 200}};
    Polynomial<4> pol(members);
    long long res = pol.getValue(4);
    long long res2 = pol.getValue(0);
    std::cout << res << std::endl;
    std::cout << res2<< std::endl;
    std::cout << pol<<std::endl;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
