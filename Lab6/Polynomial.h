#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <unordered_map>
#include <utility>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

struct pair{
    int power, coef;
};

template <int S>
class Polynomial{
protected:
    int m_size=S;
    pair m_coefficients[S];
public:
    constexpr Polynomial()=default;

    constexpr Polynomial (std::initializer_list<pair> &p){
        int cnt=0;
        for (auto &i:p){
            m_coefficients[cnt++]=i;
        }

    };

    constexpr Polynomial(const Polynomial &p)=default;

    constexpr long long getValue(int x){
        long long sum=0;

        for (pair i: m_coefficients){
            sum+=(long long)std::pow(x, i.power)*i.coef;

        }
        return sum;
    }

    friend std::ostream &operator<<(std::ostream &o, const Polynomial &p) {
        for (pair i: p.m_coefficients){
            if (i.coef<0){
                o<<'-'<<i.coef<<"x^"<<i.power;
            }else if (i.coef>0){
                o<<'+'<<i.coef<<"x^"<<i.power;
            }
        }
        return o;
    }
};



#endif // POLYNOMIAL_H
