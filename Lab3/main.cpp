#include <iostream>
#include "ringbuffer.h"
#include "algorythms.h"

template<class T>
bool isFirstBiggerThanSecond(T first, T second) {
    return first > second;
}

template<class T>
bool isSecondBiggerThanFirst(T first, T second) {
    return second > first;
}

int main() {
    RingBuffer<int> boba(6);

    for (int i = 0; i < 1000; i++) {
        boba.push_back(i);
        for (int j = 0; j < 6; j++) {
            std::cout << boba[j] << ' ';
        }
        std::cout << std::endl;
    }

    std::cout << "ОБРАТНО\n";

    for (int i = 1000; i != 0; i--) {
        boba.push_front(i);
        for (int j = 0; j < 6; j++) {
            std::cout << boba[j] << ' ';
        }
        std::cout << std::endl;
    }
    if (is_sorted(boba.begin(), boba.end(), std::greater())) {
        std::cout << "Buffer is sorted\n";
    }

    boba.pop_front();
    boba.pop_front();
    boba.pop_front();
    boba.pop_front();
    boba.pop_back();
    boba.pop_back();
    boba.pop_back();
    boba.pop_back();
    boba.pop_back();
    for (int j = 0; j < 6; j++) {
        std::cout << boba[j] << ' ';
    }
    std::cout << '\n';
    boba.push_front(4);
    boba.push_front(3);
    boba.push_back(5);
    boba.push_back(6);
    for (int j = 0; j < 6; j++) {
        std::cout << boba[j] << ' ';
    }
    std::cout << '\n';
    for (auto j: boba) {
        std::cout << j << ' ';
    }
    std::cout << '\n';
    return 0;
}
