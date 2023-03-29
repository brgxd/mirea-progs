// Matrices1.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>

using namespace std;

class Exception : public exception
{
protected:
	//сообщение об ошибке
	char* str;
public:
	Exception(const char* s)
	{
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}
	Exception(const Exception& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy_s(str, strlen(e.str) + 1, e.str);
	}
	~Exception()
	{
		delete[] str;
	}

	//функцию вывода можно будет переопределить в производных классах, когда будет ясна конкретика
	virtual void print()
	{
		cout << "Exception: " << str << "; " << what();
	}
};


class InvalidSizeException : public Exception
{
protected:
	int w, h;
public:
	InvalidSizeException(const char* s, int Width, int Height) :Exception(s) { w = Width; h = Height; }
	InvalidSizeException(const InvalidSizeException& e) : Exception(e) { w = e.w; h = e.h; }



	//функцию вывода можно будет переопределить в производных классах, когда будет ясна конкретика
	virtual void print()
	{
		cout << "InvalidSizeException: " << str << "; columns" << w << "\t" <<"rows:" <<h<<"; "<< what();
	}
};


class IndexOutOfBoundsException : public Exception
{
protected:
	int row, col;
public:
	IndexOutOfBoundsException(const char* s, int r, int c) :Exception(s) { r = row; c = col; }
	IndexOutOfBoundsException(const IndexOutOfBoundsException& e) : Exception(e) { row = e.row; col = e.col; }

	virtual void print()
	{
		cout << "IndexOutOfBoundsException: " << str << "; columns" << col << "\t" << "rows:" << row << "; " << what();
	}
};

class WrongSizeException : public Exception
{
protected:
	int w, h;
public:
	WrongSizeException(const char* s, int Width, int Height) :Exception(s) { w = Width; h = Height; }
	WrongSizeException(const WrongSizeException& e) : Exception(e) { w = e.w; h = e.h; }
	WrongSizeException(const char* s) : Exception(s){}

	virtual void print()
	{
		cout << "WrongSizeException: " << str << "; columns" << w << "\t" << "rows:" << h << "; " << what();
	}
};

class NonPositiveSizeException : public WrongSizeException
{
public:
	NonPositiveSizeException(const char* s, int r, int c) : WrongSizeException(s) {}
	NonPositiveSizeException(const NonPositiveSizeException& e) : WrongSizeException(e) {}
};

class TooLargeSizeException : public WrongSizeException
{
public:
	TooLargeSizeException(const char* s, int Width, int Height) : WrongSizeException(s) {}
	TooLargeSizeException(const TooLargeSizeException& e) : WrongSizeException(e) {}
};

class BaseMatrix
{
protected:
	double** ptr;
	int height;
	int width;
public:
	BaseMatrix(int Height = 2, int Width = 2)
	{
		//конструктор
		/*if (Height > 10000 || Width > 10000)
			throw TooLargeSizeException()*/
		height = Height;
		width = Width;
		ptr = new double* [height];
		for (int i = 0; i < height; i++)
			ptr[i] = new double[width];
		cout << "\nBase Matrix constructor";
	}

	BaseMatrix(const BaseMatrix& M)
	{
		//конструктор копий
		height = M.height;
		width = M.width;
		ptr = new double* [height];
		for (int i = 0; i < height; i++)
		{
			ptr[i] = new double[width];
			for (int n = 0; n < width; n++)
				ptr[i][n] = M.ptr[i][n];
		}
		cout << "\nBase Matrix copy constructor";
	}

	BaseMatrix(double** arr, int w, int h)
	{
		height = h;
		width = w;
		for (int i = 0; i < height; i++)
		{
			ptr[i] = new double[width];
			for (int n = 0; n < width; n++)
				ptr[i][n] = arr[i][n];
		}
		cout << "\nBase Matrix uconstructor";
	}




	~BaseMatrix()
	{
		//деструктор
		if (ptr != NULL)
		{
			for (int i = 0; i < height; i++)
				delete[] ptr[i];
			delete[] ptr;
			ptr = NULL;
		}
	}

	void print()
	{
		//вывод
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
				cout << ptr[i][j] << " ";
			cout << "\n";
		}
	}

	double* operator[](int row)
	{
		if (row < 0 || row >= height)
			throw IndexOutOfBoundsException("Index out of bounds in operator []", row, -1);
		return ptr[row];
	}

	double& operator()(int row, int column)
	{
		if (row < 0 || row >= height || column >= width)
			throw IndexOutOfBoundsException("Index out of bounds in operator []", row, column);
		return ptr[row][column];
	}

};



class Matrix : public BaseMatrix
{
public:
	Matrix(int Height = 2, int Width = 2) : BaseMatrix(Height, Width) {}
	Matrix(double** arr, int w, int h) :BaseMatrix(arr, w, h) {}
	Matrix(const Matrix& M): BaseMatrix((BaseMatrix&)M) { cout << "\nMatrix copy constructor"; }

	Matrix operator*(double d)
	{
		Matrix s(height, width);
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
				s(i, j) = ptr[i][j] * d;
		}
		return s;
	}

	double operator+()
	{
		if (width != height)
			throw InvalidSizeException("Rows != columns in operator +()", width, height);
		double sum = 0;
		for (int i = 0; i < height; i++)
			sum += ptr[i][i];
		return sum;

	}
};


int main()
{
	try 
	{
		Matrix M(2, 3);
		Matrix S(2, 2);
		M(0, 0) = 1; M(0, 1) = 2; M(1, 0) = 4; M(1, 1) = 10;
		M(3, 3) = 10;
		(M * 4.2).print();
		cout << +(M * 2);
	}
	catch (IndexOutOfBoundsException e)
	{
		cout << "\nCught:IndexOutOfBoundsException"; e.print();
	}
	catch (Exception e)
	{
		cout << "\nCaught:Exception"; e.print();
	}
	catch (InvalidSizeException e)
	{
		cout << "\nCaught:InvalidSizeException"; e.print();
	}
	char c; cin >> c;

	return 0;
}
