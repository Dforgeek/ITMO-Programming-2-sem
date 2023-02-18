#include <iostream>

#include "CubicsRube.h"

enum cuu {
    a, b, c
};

int main() {
    CubicsRube buba;
    cuu g = c;
    std::cout << char('a' + g);
    buba.printCube();
    if (buba.isSolved()) {
        std::cout << "SOLVED";
    } else {
        std::cout << "NOT SOLVED";
    }
    return 0;
}
