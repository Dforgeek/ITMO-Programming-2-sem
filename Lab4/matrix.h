//
// Created by Dforgeek on 04.06.2022.
//

#ifndef INC_4_LAB_MATRIX_H
#define INC_4_LAB_MATRIX_H

#include <cassert>
#include <array>

class Vector {
private:
    int m_x, m_y, m_z;
public:
    Vector();

    explicit Vector(int x, int y, int z);

    Vector(const Vector &v) = default;

    Vector &operator=(const Vector &v) = default;

    Vector operator+=(const Vector &v);

    Vector operator+(const Vector &v);

    Vector operator*=(int c);

    Vector operator*(int c);

    [[nodiscard]] int getDot(const Vector &v) const;

    //CROSS
    Vector operator*(const Vector &v) const;

    int operator[](int index) const;

    void setCoords(int x, int y, int z);
};


// 3 на 3 матрица
//class Matrix {
//private:
//    std::array<int, 9> mtrx{};
//public:
//    explicit Matrix(std::array<int, 9> values) {}
//
//    Vector
//};


#endif //INC_4_LAB_MATRIX_H
