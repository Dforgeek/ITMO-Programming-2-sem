#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

class Point {
private:
    double m_x, m_y;
public:
    explicit Point(double x = 0, double y = 0) : m_x(x), m_y(y) //Конструктор по умолчанию
    {
    }

    Point(const Point &p) : m_x(p.m_x), m_y(p.m_y) //Конструктор копирования
    {
    }

    Point &operator=(const Point &p) = default;

    void newCoords(double x, double y) {
        m_x = x;
        m_y = y;
    }

    [[nodiscard]] double getX() const { return m_x; };

    double getY() const { return m_y; };

    void printPoint() const {
        std::cout << "(" << m_x << ", " << m_y << ")\n";
    }

    double distanceTo(const Point &pnt) const {
        return sqrt(pow(pnt.getX() - m_x, 2) +
                    pow(pnt.getY() - m_y, 2));
    }

    double distanceFrom(const Point &pnt) const {
        return sqrt(pow(m_x - pnt.getX(), 2) +
                    pow(m_y - pnt.getY(), 2));
    }


};

class PolyLine {
protected:
    std::vector<Point> m_points;
public:
    explicit PolyLine(const std::vector<Point> &points = {}) {
        m_points = points;
    }

    PolyLine(const PolyLine &pln) : m_points(pln.m_points) {
    }

    PolyLine &operator=(const PolyLine &pln) {
        m_points = pln.m_points;
        return *this;
    }

    virtual double perimeter() {
        double sum = 0;
        for (int i = 1; i < m_points.size(); i++) {
            sum += m_points[i].distanceFrom(m_points[i - 1]);
        }
        return sum;
    }

};

class ChainedPolyLine : public PolyLine {
public:
    explicit ChainedPolyLine(const std::vector<Point> &points1 = {}) : PolyLine(points1) {
    }

    explicit ChainedPolyLine(const PolyLine &pln) : PolyLine(pln) {
    }

    ChainedPolyLine &operator=(const ChainedPolyLine &cpln) {
        m_points = cpln.m_points;
        return *this;
    }


    double perimeter() override {
        double sum = 0;
        for (int i = 1; i < m_points.size(); i++) {
            sum += m_points[i].distanceFrom(m_points[i - 1]);
        }
        sum += m_points[0].distanceFrom(m_points[m_points.size() - 1]);
        return sum;
    }
};

class Polygon : public ChainedPolyLine {
public:
    explicit Polygon(const std::vector<Point> &points = {}) : ChainedPolyLine(points) {
    }

    explicit Polygon(const ChainedPolyLine &cpln) : ChainedPolyLine(cpln) {
    }

    explicit Polygon(const PolyLine &polyLine):ChainedPolyLine(polyLine){

    }

    Polygon &operator=(const Polygon &plgn) {
        m_points = plgn.m_points;
        return *this;
    }

    double area() {
        double s = 0.0;
        int j = m_points.size() - 1;
        for (int i = 0; i < m_points.size(); i++) {
            s += (m_points[j].getX() + m_points[i].getX()) * (m_points[j].getY() - m_points[i].getY());
            j = i;
        }
        return std::abs(s / 2.0);
    }

    bool regularityCheck() {
        for (int i = 1; i < m_points.size() - 1; i++) {
            if (m_points[i].distanceFrom(m_points[i - 1])
                != m_points[i + 1].distanceFrom(m_points[i])) {
                return false;
            }
        }
        return true;
    };

};

class RegPolygon : Polygon {
public:
    explicit RegPolygon(const std::vector<Point> &points = {}) : Polygon(points) {
        assert(Polygon(points).regularityCheck() && "Дорогой друг нельзя так");
    }

    explicit RegPolygon(const Polygon &plgn) : Polygon(plgn) {
        assert(Polygon(plgn).regularityCheck());
    }

    RegPolygon &operator=(const RegPolygon &rplgn) {
        m_points = rplgn.m_points;
        return *this;
    }
};

class Triangle {
private:
    Point m_a, m_b, m_c;
public:
    Triangle(const Point &a, const Point &b, const Point &c) : m_a(a), m_b(b), m_c(c) {

    }

    Triangle(const Triangle &trgl) : m_a(trgl.m_a), m_b(trgl.m_b), m_c(trgl.m_c) {
    }

    Triangle &operator=(const Triangle &trgl) {
        m_a = trgl.m_a;
        m_b = trgl.m_b;
        m_c = trgl.m_c;
        return *this;
    }

    double perimeter() {
        double ab = m_a.distanceTo(m_b);
        double ac = m_a.distanceTo(m_c);
        double bc = m_b.distanceTo(m_c);
        return ab + ac + bc;
    }

    double area() {
        return 0.5 * std::abs(((m_a.getX() - m_c.getX()) * (m_b.getY() - m_c.getY()))
                              - ((m_a.getY() - m_c.getY()) * (m_b.getX() - m_c.getX())));
    }
};

class Trapezoid {
private:
    Point m_a, m_b, m_c, m_d;

    double m_AB{}, m_BC{}, m_CD{}, m_DA{};
public:
    Trapezoid(Point &a, Point &b, Point &c, Point &d) {
        m_a = a;
        m_b = b;
        m_c = c;
        m_d = d;
        Point m_vectorAB{m_b.getX() - m_a.getX(), m_b.getY() - m_a.getY()};
        Point m_vectorBC{m_c.getX() - m_b.getX(), m_c.getY() - m_b.getY()};
        Point m_vectorCD{m_d.getX() - m_c.getX(), m_d.getY() - m_c.getY()};
        Point m_vectorDA{m_a.getX() - m_d.getX(), m_a.getY() - m_d.getY()};
        if (m_vectorCD.getY() == 0 || m_vectorDA.getY() == 0) {
            assert(m_vectorCD.getY() == 0 && m_vectorAB.getY() == 0 ||
                   m_vectorBC.getY() == 0 && m_vectorDA.getY() == 0);
        } else {
            assert((m_vectorAB.getX() / m_vectorCD.getX() != m_vectorAB.getY() / m_vectorCD.getY())
                   || (m_vectorBC.getX() / m_vectorDA.getX() != m_vectorBC.getY() / m_vectorDA.getY()));
        }
        m_AB = m_a.distanceTo(m_b);
        m_BC = m_b.distanceTo(m_c);
        m_CD = m_c.distanceTo(m_d);
        m_DA = m_d.distanceTo(m_a);
    }

    Trapezoid(const Trapezoid &trpzd) : m_a(trpzd.m_a), m_b(trpzd.m_b), m_c(trpzd.m_c), m_d(trpzd.m_d) {
        m_AB = m_a.distanceTo(m_b);
        m_BC = m_b.distanceTo(m_c);
        m_CD = m_c.distanceTo(m_d);
        m_DA = m_d.distanceTo(m_a);
    }

    Trapezoid &operator=(const Trapezoid &trpzd) {
        m_a = trpzd.m_a;
        m_b = trpzd.m_b;
        m_c = trpzd.m_c;
        m_d = trpzd.m_d;
        return *this;
    }

    double perimeter() const {
        return m_AB + m_BC + m_CD + m_DA;
    }

    double area() {
        return std::abs(
                m_a.getX() * m_b.getY() + m_b.getX() * m_c.getY() + m_c.getX() * m_d.getY() + m_d.getX() * m_a.getY() -
                (m_b.getX() * m_a.getY() + m_c.getX() * m_b.getY() + m_d.getX() * m_c.getY() +
                 m_a.getX() * m_d.getY())) / 2.0;

    }

};