//
// Created by Dforgeek on 03.06.2022.
//

#ifndef INC_4_LAB_CUBICSRUBE_H
#define INC_4_LAB_CUBICSRUBE_H

#include <initializer_list>
#include <vector>

//class Part {
//private:
//    Vector m_pos;
//    enum colour {
//        W, Y, B, O, R, G, NONE
//    };
//    enum typee{FACE, EDGE, CORNER};
//    typee m_type;
//    colour m_colours[3];
//public:
//
//    Part(const Vector &position, colour c1, colour c2, colour c3);
//
//
//
//};
enum colour {
    B, G, O, R, W, Y
};

enum destination{
    UP, DOWN, RIGHT, LEFT, FRONT, BACK
};

class Edge {
private:
    std::vector<colour> m_squares;
public:
    Edge();

    void fillUp(colour c);

    Edge &operator=(const Edge& other);

    colour &operator[](int index);

    bool isOneColored();
};


class CubicsRube {
private:
    Edge back, front, right, left, up, down;
public:
    CubicsRube();

    void printCube();

    bool isSolved();

    void rotateTo(destination dest);
};


#endif //INC_4_LAB_CUBICSRUBE_H
