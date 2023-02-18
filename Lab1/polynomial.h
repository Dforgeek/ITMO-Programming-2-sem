#include <iostream>
#include <unordered_map>
#include <utility>

class Polynomial {
protected:
    std::unordered_map<int, int> m_coefficients;
public:
    Polynomial() = default;

    Polynomial(const Polynomial &p) = default;

    explicit Polynomial(std::unordered_map<int, int> p) : m_coefficients(std::move(p)) {
    }

    Polynomial &operator=(const Polynomial &p) = default;

    bool operator==(const Polynomial &p) const {
        return (this->m_coefficients == p.m_coefficients);
    };

    Polynomial operator+=(const Polynomial &p) {
        for (std::pair<const int, int> i: p.m_coefficients) {
            if (this->m_coefficients.contains(i.first)) {
                this->m_coefficients[i.first] += i.second;
            } else {
                this->m_coefficients[i.first] = i.second;
            }
        }
        return *this;
    }

    Polynomial operator+(const Polynomial &newP) {
        Polynomial oldP(*this);
        return oldP += newP;
    }

    Polynomial operator-=(const Polynomial &p) {
        return *this += p;
    }

    Polynomial operator-(const Polynomial &newP) {
        Polynomial oldP(*this);
        return oldP -= newP;
    }

    Polynomial &operator*=(const int a) {
        for (auto &i: this->m_coefficients)
            i.second *= a;
        return *this;
    }

    Polynomial operator*(const int a) {
        Polynomial y(*this);
        return y *= a;
    }

    Polynomial &operator/=(const int a) {
        for (auto &i: this->m_coefficients)
            i.second /= a;
        return *this;
    }

    Polynomial operator/(const int a) {
        Polynomial y(*this);
        return y /= a;
    }

    Polynomial &operator*=(const Polynomial &p) {
        for (auto i: this->m_coefficients)
            for (auto j: this->m_coefficients)
                this->m_coefficients[i.first + j.first] += i.second * j.second;
        return *this;
    }

    Polynomial operator*(const Polynomial &newP) {
        Polynomial oldP(*this);
        return oldP *= newP;
    }

    int &operator[](int a) {
        return this->m_coefficients[a];
    }

    friend std::ostream &operator<<(std::ostream &o, const Polynomial &p);

    friend std::istream &operator>>(std::istream &in, Polynomial &p);

    void add(int pow, int coef) {
        if (m_coefficients.contains(pow)) {
            m_coefficients[pow] += coef;
        } else {
            m_coefficients[pow] = coef;
        }
    }

    ~Polynomial() = default;
};

std::ostream &operator<<(std::ostream &o, const Polynomial &p) {
    std::vector<int> keys;

    keys.reserve (p.m_coefficients.size());
    for (auto& it : p.m_coefficients) {
        keys.push_back(it.first);
    }
    std::sort (keys.begin(), keys.end());
    bool firstC = true;
    for (auto i: keys) {
        int sec=p.m_coefficients.find(i)->second;
        if (sec < 0) {
            o << sec << "x^" << i;
            firstC = false;
        } else if (sec > 0 && firstC) {
            o << sec << "x^" << i;
            firstC = false;
        } else if (sec > 0 && !firstC) {
            o << "+" << sec << "x^" << i;
            firstC = false;
        }
    }
    return o;
}

std::istream &operator>>(std::istream &in, Polynomial &p) {
    bool iscoef = true;
    std::string str, coef, pow;
    in >> str;
    for (char i: str) {

        if (i == '+' || i == '-') {
            if (!coef.empty() && !pow.empty()) {
                p.add(stoi(pow), stoi(coef));
                coef = "";
                pow = "";
            } else if (!coef.empty() && pow.empty()) {
                p.add(0, stoi(coef));
            }
            iscoef = true;
            coef += i;
        } else if (i == 'x' || i == '^') {
            iscoef = false;
        } else if (iscoef) {
            coef += i;
        } else {
            pow += i;
        }
    }
    if (!coef.empty() && !pow.empty()) {
        p.add(stoi(pow), stoi(coef));
        coef = "";
        pow = "";
    } else if (!coef.empty() && pow.empty()) {
        p.add(0, stoi(coef));
    }
    return in;
}