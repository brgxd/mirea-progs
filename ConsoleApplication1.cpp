// FigureInherit.cpp: определяет точку входа для консольного приложения.
//

#include <math.h>
#include <iostream>
#include <fstream>

using namespace std;

class Figure
{
protected:
	double dim1, dim2, dim3;
public:
	virtual double Area() = 0;
	virtual void print() { cout << "\nFigure class"; }
	double Dim1() { return dim1; }
	double Dim2() { return dim2; }
	double Dim3() { return dim3; }
	Figure(double d1) { dim1 = d1; dim2 = 0; dim3 = 0; cout << "\nBase Constructor 1"; }
	Figure(double d1, double d2) { dim1 = d1; dim2 = d2; dim3 = 0; cout << "\nBase Constructor 2"; }
	Figure(double d1, double d2, double d3) { dim1 = d1; dim2 = d2; dim3 = d3; cout << "\nBase Constructor 3"; }
};

class Triangle : public Figure
{
public:
	Triangle(double d1, double d2, double d3) : Figure(d1, d2, d3) { cout << "\nTriangle Constructor"; }
	virtual double Area()
	{
		cout << "\nTriangle Area\n";
		double p = dim1 + dim2 + dim3; p /= 2;
		return sqrt(p * (p - dim1) * (p - dim2) * (p - dim3));
	}
	virtual void print() { cout << "\nTriangle class"; }
};

class Rectangle : public Figure
{
public:
	Rectangle(double d1, double d2) : Figure(d1, d2) { cout << "\nRectangle Constructor"; }
	virtual double Area()
	{
		cout << "\nRectangle Area\n";
		return dim1 * dim2;
	}
	virtual void print() { cout << "\nRectangle class"; }
};

class Square1 : public Figure
{
public:
	Square1(double d1) : Figure(d1) { cout << "\nSquare1 Constructor"; }
	virtual double Area()
	{
		cout << "\nSquare1 Area\n";
		return sqrt(dim1 * dim1);
	}
};

class Square2 : public Rectangle
{
public:
	Square2(double d1) : Rectangle(d1, d1) { cout << "\nSquare2 Constructor"; }
	virtual void print() { cout << "\nSquare class"; }
	void test() { cout << "\nNew function"; }
};


double f(double x)
{
	return sin(x);
}

double g(double x, double y)
{
	return x * x + y*y;
}

double Integral(double (*p)(double), double left, double right, double step = 0.001)
{
	double s = 0;
	double x = left;
	while (x < right)
	{
		s += p(x) * step;
		x += step;
	}
	return s;
}

double Integral(double (*p)(double, double), double x_left, double x_right, double y_left, double y_right, double step = 0.001)
{
	double v = 0;
	double x = x_left;
	double y = y_left;
	while (x < x_right)
	{
		while(y < y_right)
		{
			v += p(x, y) * step * step;
			y += step;
		}
		y = y_left;
		x += step;
	}
	return v;
}

double p(double x)
{
	return cos(x)-1;
}


double Dichotomy(double left, double right, double eps = 0.0001)
{
	double middle = p((left+right) / 2);
	double x = p(left);
	double y = p(right);
	while (middle > eps)
	{
		if (left * middle < 0)
		{
			right = middle;
		}
		else
		{
			left = middle;
		}
	}
	return middle;
}



int main()
{
	double (*p)(double, double); p = g;
	double s = Dichotomy(1, 10);
	cout << "\nDichotomy: " << s;
	Triangle T(3, 4, 5);
	cout << "\nTriangle area: " << T.Area();
	cout << "\nVariable T of class: "; T.print();
	cout << "\nSides: " << T.Dim1() << ", " << T.Dim2() << ", " << T.Dim3();
	Square2 Q(5);
	cout << "\nArea of square:" << Q.Area();
	Q.test();

	cout << "\nBase pointer:\n";
	Square2 S2(2);
	Square1 S1(3);
	Rectangle R(4, 3);
	Triangle T(5, 4, 3);
	Figure* ptr;
	ptr = &S2; cout << ptr->Area();
	ptr = &S1; cout << ptr->Area();
	ptr = &R; cout << ptr->Area();
	ptr = &T; cout << ptr->Area();

	char c; cin >> c;
	return 0;
}