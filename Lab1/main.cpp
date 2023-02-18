#include <iostream>
#include "geometry.h"
#include "polynomial.h"


int main() {
    Point p1{0, 0};
    Point p2{4, 0};
    Point p3{4, 3};
    Point p4{0, 3};
    PolyLine polyline{{p1, p2, p3, p4}};
    ChainedPolyLine chpolyline{polyline};
    std::cout << "Polyline perimeter: " << polyline.perimeter() << std::endl;
    std::cout << "Chained Polyline perimeter: " << chpolyline.perimeter() << std::endl;
    Trapezoid trapezoid{p1, p2, p3, p4};
    std::cout << "Perimeter and area of trapezoid: " << trapezoid.perimeter() << ", " << trapezoid.area() << std::endl;
    Triangle triangle{p1, p2, p3};
    std::cout << "Triangle perimeter and area of triangle: " << triangle.perimeter() << ", " << triangle.area()<<std::endl;
    Polygon polygon{polyline};
    std::cout<<"Polygon perimeter and it's area: " << polygon.perimeter()<<", "<<polygon.area()<<std::endl;

    Polynomial p, p10{{{1, 2,}, {5, 6}, {0,100}, {3, -10}}};
    std::cin>> p;
    p+=p10;
    std::cout<<p<<std::endl;
    Polynomial pp{{{2, 10}, {45, 8}, {3, -9}}}, ppp{{{3, 80}, {2, 5}, {12, 14}}}, pppp;
    pppp=pp*ppp;
    std::cout<<pppp;
    return 0;
}
