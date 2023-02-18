//
// Created by Dforgeek on 04.06.2022.
//
#include "matrix.h"

Vector::Vector() {
    m_x=0;
    m_y=0;
    m_z=0;
};

Vector::Vector(int x, int y, int z) {
    m_x = x;
    m_y = y;
    m_z = z;
}

Vector Vector::operator+=(const Vector &v) {
    m_x += v.m_x;
    m_y += v.m_y;
    m_z += v.m_z;

    return *this;
}

Vector Vector::operator+(const Vector &v) {
    Vector oldV(*this);
    return oldV += v;

}

Vector Vector::operator*=(int c) {
    m_x *= c;
    m_y *= c;
    m_z *= c;
    return *this;
}

Vector Vector::operator*(int c) {
    Vector oldV(*this);
    return oldV *= c;
}

int Vector::getDot(const Vector &v) const {
    return m_x * v.m_x + m_y * v.m_y + m_z * v.m_z;
}

Vector Vector::operator*(const Vector &v) const {
    return Vector(m_y * v.m_z - m_z * m_y, m_z * v.m_x - m_x * v.m_z, m_x * v.m_y - m_y * v.m_x);
}

int Vector::operator[](int index) const {
    assert((index >= 0 && index < 3) && "Wrong index");
    if (index == 0) {
        return m_x;
    } else if (index == 1) {
        return m_y;
    } else {
        return m_z;
    }
}

void Vector::setCoords(int x, int y, int z) {
    m_z = z;
    m_y = y;
    m_x = x;
}
//
//Matrix::Matrix(std::array<int, 9> values) {
//
//}