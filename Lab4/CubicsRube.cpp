//
// Created by Dforgeek on 04.06.2022.
//
#include "CubicsRube.h"
#include <cassert>
#include <iostream>
//Part::Part(const Vector &position, colour c1, colour c2, colour c3) {
//    for (int i = 0; i < 3; ++i) {
//        assert(!(position[i] != -1 && position[i] != 0 && position[i] != 1) && "Wrong position");
//    }
//    assert(c1 != NONE && "First colour can't be NONE");
//    m_pos = position;
//    m_colours[0] = c1;
//    m_colours[1] = c2;
//    m_colours[2] = c3;
//    if (m_colours[1] == NONE && m_colours[2] == NONE) {
//        m_type = FACE;
//    } else if (m_colours[2] == NONE) {
//        m_type = EDGE;
//    } else {
//        m_type = CORNER;
//    }
//
//}

char colourToChar(colour c) {
    if (c == W) return 'W';
    if (c == Y) return 'Y';
    if (c == B) return 'B';
    if (c == O) return 'O';
    if (c == R) return 'R';
    if (c == G) return 'G';
    assert(true && "Попытка вывести несущетсвующий цвет");
}

//Edge::Edge(std::initializer_list<colour> colours) : m_squares(colours) {
//    assert(m_squares.size() == 9 && "Wrong edge size");
//}

//Edge::Edge(colour c) {
//
//    std::fill(m_squares.begin(), m_squares.end(), c);
//}
Edge::Edge() {
    for (int i = 0; i < 9; i++) {
        m_squares.push_back(W);
    }

}

void Edge::fillUp(colour c) {
    std::fill(m_squares.begin(), m_squares.end(), c);
}

Edge &Edge::operator=(const Edge &other) = default;

colour &Edge::operator[](int index) {
    return this->m_squares[index];
}

bool Edge::isOneColored() {
    for (int i = 1; i < 9; i++) {
        if (m_squares[i] != m_squares[i - 1]) return false;
    }
    return true;
}


CubicsRube::CubicsRube() {
    front.fillUp(B);
    up.fillUp(W);
    down.fillUp(Y);
    back.fillUp(G);
    left.fillUp(R);
    right.fillUp(O);

}

void CubicsRube::printCube() {
    std::cout << "\nCubics Rube condition:\n";
    //the back one is upside down
    for (int i = 2; i > -1; --i) {
        std::cout << "   ";
        for (int j = 2; j > -1; --j) {
            char k = colourToChar(back[i * 3 + j]);
            std::cout << k;
        }
        std::cout << "   \n";
    }

    //up

    for (int i = 0; i < 3; i++) {
        std::cout << "   ";
        for (int j = 0; j < 3; j++) {
            char k = colourToChar(up[i * 3 + j]);
            std::cout << k;
        }
        std::cout << "   \n";
    }
    //left front right
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << colourToChar(left[i * 3 + j]);
        }
        for (int j = 0; j < 3; ++j) {
            std::cout << colourToChar(front[i * 3 + j]);
        }
        for (int j = 0; j < 3; ++j) {
            std::cout << colourToChar(right[i * 3 + j]);
        }
        std::cout << '\n';
    }

    for (int i = 0; i < 3; i++) {
        std::cout << "   ";
        for (int j = 0; j < 3; j++) {
            char k = colourToChar(down[i * 3 + j]);
            std::cout << k;
        }
        std::cout << "   \n";
    }
}




bool CubicsRube::isSolved() {
    return up.isOneColored() && down.isOneColored() && left.isOneColored() && right.isOneColored() &&
        front.isOneColored() && back.isOneColored();
}

void CubicsRube::rotateTo(destination dest) {
    Edge temp;
    if (dest==UP){
        temp=down;
        down=up


    }
}