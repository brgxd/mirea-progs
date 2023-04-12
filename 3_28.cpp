#include <iostream>

using namespace std;

class A1
{
protected:
	int a1;
public:
	A1() { a1 = 0; cout << "\nA1 default constructor " << a1 << "\n"; }
	A1(int A) { a1 = A; cout << "\nA1 constructor " << a1 << "\n"; }
	~A1() { cout << "\nA1 destructor"; }

	void print()
	{
		cout << "A1";
	}
};

class A2
{
protected:
	int a2;
public:
	A2() { a2 = 0; cout << "\nA2 default constructor " << a2 << "\n"; }
	A2(int B) { a2 = B; cout << "\nA2 constructor " << a2 << "\n"; }
	~A2() { cout << "\nA2 destructor"; }

	void print()
	{
		cout << "A2";
	}
};

class A3
{
protected:
	int a3;
public:
	A3() { a3 = 0; cout << "\nA3 default constructor " << a3 << "\n"; }
	A3(int B) { a3 = B; cout << "\nA3 constructor " << a3 << "\n"; }
	~A3() { cout << "\nA3 destructor"; }

	void print()
	{
		cout << "A3";
	}
};

class B1 : virtual public A1, virtual public A2, virtual public A3
{
protected:
	int b1;
public:
	B1() : A1(), A2(), A3() { b1 = 0; cout << "\nB1 default constructor"; }
	B1(int B, int A1 = 0, int A2 = 0, int A3 = 0) : A1(A1), A2(A2), A3(A3) { b1 = B; cout << "\nB1 constructor" << b1 << "\n"; }
	~B1() { cout << "\nB1 destructor"; }
};

class B2 : virtual public A1, virtual public A2, virtual public A3
{
protected:
	int b2;
public:
	B2() : A1(), A2(), A3() { b2 = 0; cout << "\nB2 default constructor"; }
	B2(int B, int A1 = 0, int A2 = 0, int A3 = 0) : A1(A1), A2(A2), A3(A3) { b2 = B; cout << "\nB2 constructor" << b2 << "\n"; }
	~B2() { cout << "\nB2 destructor"; }
};

class B3 : virtual public A1, virtual public A2, virtual public A3
{
protected:
	int b3;
public:
	B3() : A1(), A2(), A3() { b3 = 0; cout << "\nB3 default constructor"; }
	B3(int B, int A1 = 0, int A2 = 0, int A3 = 0) : A1(A1), A2(A2), A3(A3) { b3 = B; cout << "\nB3 constructor" << b3 << "\n"; }
	~B3() { cout << "\nB3 destructor"; }
};

class C1 : virtual public B1, virtual public B2, virtual public B3
{
protected:
	int c1;
public:
	C1() : B1(), B2(), B3() { c1 = 0; cout << "\nC1 default constructor"; }
	C1(int C, int B1, int B2, int B3, int A1, int A2, int A3) : B1(B1), B2(B2) , B3(B3) , A1(A1), A2(A2) , A3(A3) { c1 = C; cout << "\nC1 constructor" << c1 << "\n"; }
	void print()
	{
		cout << "\nC1: " << c1 << "\nB1: " << b1 << "\nB2: " << b2 << "\nB3: " << b3 << "\nA1: " << a1 << "\nA2: " << a2 << "\nA3: " << a3;
	}
};

int main()
{
	C1 c(10 , 7 , 9 , 12, 44, 56, 12);
	c.print();
}