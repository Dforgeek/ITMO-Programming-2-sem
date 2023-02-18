#include <iostream>
#include "mallocator.h"
#include <vector>
#include <queue>
#include <list>
#include <map>



int main() {



    struct node{
        std::size_t size=0;
        //fsdsdsds
        //
    };



    std::vector<long long, Mollocator<long long, 20000>> v(5);

    for (int i = 0; i < 20; ++i) {
        v.push_back(i);
    }

    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i] << '\n';
    }



    std::list<long long, Mollocator<long long, 100>> lllllllll;

    for (int i = 0; i < 100; i++) {
        lllllllll.push_back(i);
    }
    for (int i = 0; i < 100; i++) {
        std::cout << lllllllll.front() << '\n';
        lllllllll.pop_front();
    }

    return 0;
}