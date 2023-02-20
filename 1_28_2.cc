#include <iostream>
#include <math.h>

using namespace std;

class Point
{
private:
    double xaxis;
    double yaxis;
public:
    void print()
    {
        cout << "("<< xaxis << "," << yaxis << ")";
    }

    Point() {xaxis = 0; yaxis = 0;}
    Point(double x, double y) {xaxis = x; yaxis = y;}

    double getX() { return xaxis; }
    double getY() { return yaxis; }

    void SetX(double x) { xaxis = x; }
    void SetY(double y) { yaxis = y; }

    Point operator+(double a)
    {
        return Point(xaxis,yaxis + a);
    }

    Point operator-()
    {
        return Point(xaxis,yaxis * -1);
    }
    friend Point operator+(double a,Point b);
};

Point operator+(double a, Point b)
{
    return Point(b.xaxis,b.yaxis + a);
}

int main()
{
    Point a(1,3);
    Point b = 10 + a;
    b.print();
    Point c = -b;
    c.print();
};
