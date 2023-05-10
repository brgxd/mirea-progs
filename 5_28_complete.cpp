#include <iostream>
#include <fstream>
#include <typeinfo>

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

class WrongSizeException : public Exception
{
protected:
	int w, h;
public:
	WrongSizeException(const char* s, int Width, int Height) : Exception(s) { w = Width; h = Height; }
	WrongSizeException(const WrongSizeException& e) : Exception(e) { w = e.w; h = e.h; }

	//функцию вывода можно будет переопределить в производных классах, когда будет ясна конкретика
	virtual void print()
	{
		cout << "WrongSizeException: " << str << "; columns: " << w << "\t" << "rows: " << h << "; " << what();
	}
};

class NonPositiveSizeException : public WrongSizeException
{
public:
	NonPositiveSizeException(const char* s, int Width, int Height) : WrongSizeException(s, Width, Height) { }
	NonPositiveSizeException(const NonPositiveSizeException& e) : WrongSizeException(e) {}
};

class TooLargeSizeException : public WrongSizeException
{
public:
	TooLargeSizeException(const char* s, int Width, int Height) : WrongSizeException(s, Width, Height) { }
	TooLargeSizeException(const TooLargeSizeException& e) : WrongSizeException(e) {}
};

class IndexOutOfBoundsException : public Exception
{
protected:
	int row, col;
public:
	IndexOutOfBoundsException(const char* s, int Row, int Column) : Exception(s) { row = Row; col = Column; }
	IndexOutOfBoundsException(const IndexOutOfBoundsException& e) : Exception(e) { row = e.row; col = e.col; }

	//функцию вывода можно будет переопределить в производных классах, когда будет ясна конкретика
	virtual void print()
	{
		cout << "IndexOutOfBoundsException: " << str << "; row: " << row << "\t" << "column: " << col << "; " << what();
	}
};

class InvalidOperationException : public Exception
{
protected:
	int row, col;
public:
	InvalidOperationException(const char* s, int Row, int Column) : Exception(s) { row = Row; col = Column; }
	InvalidOperationException(const InvalidOperationException& e) : Exception(e) { row = e.row; col = e.col; }
	virtual void print()
	{
		cout << "InvalidOperationException" << str << "; row: " << row << "\t" << "column: " << col << "; " << what();
	}
};

class InvalidVarFunctionException : public InvalidOperationException
{
public:
	InvalidVarFunctionException(const char* s, int Row, int Column) : InvalidOperationException(s, Row, Column) {}
	InvalidVarFunctionException(const InvalidOperationException& e) : InvalidOperationException(e) {}
	virtual void print()
	{
		cout << "InvalidVarFunctionException" << str << "; row: " << row << "\t" << "column: " << col << "; " << what();
	}
};

template <class T = double>
class BaseMatrix
{
protected:
	T** ptr;
	int height;
	int width;
public:
	BaseMatrix(int Height = 2, int Width = 2)
	{
		if (Height <= 0 || Width <= 0)
			throw NonPositiveSizeException("NonPositive size of matrix in BaseMatrix(int, int)", Width, Height);
		if (Height > 20 || Width > 20)
			throw TooLargeSizeException("Matrix size is too large in BaseMatrix(int, int)", Width, Height);
		cout << "\nBaseMatrix constructor int, int";
		//конструктор
		height = Height;
		width = Width;
		ptr = new T * [height];
		for (int i = 0; i < height; i++)
			ptr[i] = new T[width];
	}

	BaseMatrix(const BaseMatrix& M)
	{
		//конструктор копий
		cout << "\nBaseMatrix copy constructor";
		height = M.height;
		width = M.width;
		ptr = new T * [height];
		for (int i = 0; i < height; i++)
		{
			ptr[i] = new T[width];
			for (int j = 0; j < width; j++)
				ptr[i][j] = M.ptr[i][j];
		}
	}

	BaseMatrix(T** arr, int h, int w)
	{
		cout << "\nBaseMatrix constructor double**";
		height = h;
		width = w;
		ptr = new T * [height];
		for (int i = 0; i < height; i++)
		{
			ptr[i] = new T[width];
			for (int j = 0; j < width; j++)
				ptr[i][j] = arr[i][j];
		}
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

	BaseMatrix operator=(BaseMatrix m)
	{
		if (height != m.height || width != m.width)
		{
			for (int i = 0; i < height; i++)
				delete[] ptr[i];
			if (height != m.height)
			{
				delete[] ptr;
				ptr = new T * [m.height];
			}
			for (int i = 0; i < m.height; i++)
			{
				ptr[i] = new T[m.width];
				for (int j = 0; j < m.width; j++)
					ptr[i][j] = m.ptr[i][j];
			}
			width = m.width;
			height = m.height;
			return *this;
		}
		for (int i = 0; i < m.height; i++)
			for (int j = 0; j < width; j++)
				ptr[i][j] = m.ptr[i][j];
		width = m.width;
		height = m.height;
		return *this;
	}

	T* operator[](int row)
	{
		if (row < 0 || row >= height)
			throw IndexOutOfBoundsException("Index out of bounds in operator[]", row, -1);
		return ptr[row];
	}

	T& operator()(int row, int column)
	{
		if (row < 0 || row >= height || column < 0 || column >= width)
			throw IndexOutOfBoundsException("Index out of bounds in operator()", row, column);
		return ptr[row][column];
	}
	template <class T1>
	friend ostream& operator<<(ostream& s, BaseMatrix<T1> M);
	template <class T2>
	friend istream& operator>>(istream& s, BaseMatrix<T2>& M);
};

template <class T1 = double>
ostream& operator<<(ostream& s, BaseMatrix<T1> M)
{
	if (typeid(s) == typeid(ofstream))
	{
		s << M.height << " " << M.width << " ";
		for (int i = 0; i < M.height; i++)
			for (int j = 0; j < M.width; j++)
				s << M.ptr[i][j] << " ";
		s << "\n";
	}
	else
	{
		for (int i = 0; i < M.height; i++)
		{
			for (int j = 0; j < M.width; j++)
				s << M.ptr[i][j] << " ";
			s << "\n";
		}
	}
	return s;
}

template <class T2 = double>
istream& operator>>(istream& s, BaseMatrix<T2>& M)
{
	if (typeid(s) == typeid(ifstream))
	{
		int h, w;
		s >> h >> w;
		if (h != M.height || w != M.width)
		{
			BaseMatrix<T2> M1(h, w);
			for (int i = 0; i < M1.height; i++)
				for (int j = 0; j < M1.width; j++)
					s >> M1.ptr[i][j];
			M = M1;
			return s;
		}
	}
	for (int i = 0; i < M.height; i++)
		for (int j = 0; j < M.width; j++)
			s >> M.ptr[i][j];
	return s;
}

template <class T = double>
class Matrix : public BaseMatrix<T>
{
public:
	Matrix<T>(int Height = 2, int Width = 2) : BaseMatrix<T>(Height, Width) {}
	Matrix<T>(T** arr, int w, int h) : BaseMatrix<T>(arr, w, h) {}
	Matrix<T>(const Matrix<T>& M) : BaseMatrix<T>((BaseMatrix<T>&)M) { cout << "\nMatrix copy constructor\n"; }
	Matrix<T>(istream& s)
	{
		int h, w;
		s >> h >> w;
		if (h <= 0 || w <= 0)
			throw NonPositiveSizeException("NonPositive size of matrix in BaseMatrix(int, int)", w, h);
		if (h > 20 || w > 20)
			throw TooLargeSizeException("Matrix size is too large in BaseMatrix(int, int)", w,h);
		height = h;
		width = w;
		ptr = new T * [height];
		for (int i = 0; i < height; i++)
			ptr[i] = new T[width];
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				s >> ptr[i][j];
		cout << "\nMatrix istream constructor";
	}

	using BaseMatrix<T>::ptr;
	using BaseMatrix<T>::height;
	using BaseMatrix<T>::width;

	T operator+()
	{
		if (typeid(T) != typeid(int) || typeid(T) != typeid(double))
			throw InvalidOperationException("operator+() can operate only with ints or doubles", width, height);
		if (width != height)
			throw WrongSizeException("Quantity of rows and columns isn't equal in operator+()", width, height);
		T sum = 0;
		for (int i = 0; i < height; i++)
			sum += ptr[i][i];
		return sum;
	}
	Matrix operator*(T d)
	{
		if (typeid(T) != typeid(int) || typeid(T) != typeid(double))
			throw InvalidOperationException("operator*() can operate only with ints or doubles", width, height);
		Matrix s(height, width);
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				s(i, j) = ptr[i][j] * d;

		return s;
	}

	Matrix operator=(Matrix m)
	{
		if (height != m.height || width != m.width)
		{
			for (int i = 0; i < height; i++)
				delete[] ptr[i];
			if (height != m.height)
			{
				delete[] ptr;
				ptr = new T * [m.height];
			}
			for (int i = 0; i < m.height; i++)
			{
				ptr[i] = new T[m.width];
				for (int j = 0; j < m.width; j++)
					ptr[i][j] = m.ptr[i][j];
			}
			width = m.width;
			height = m.height;
			return *this;
		}
		for (int i = 0; i < m.height; i++)
			for (int j = 0; j < width; j++)
				ptr[i][j] = m.ptr[i][j];
		width = m.width;
		height = m.height;
		return *this;
	}

	Matrix DeleteMostlyEmptyLines()
	{
		T empty;
		if (typeid(T) == typeid(int) || typeid(T) == typeid(double))
			empty = 0;
		if (typeid(T) == typeid(char))
			empty = ' ';
		T* IndexsOfNotEmptLines = new T[height];
		int k = 0;
		for (int i = 0; i < height; i++)
		{
			int a = 0;
			T* p = ptr[i];
			for (int j = 0; j < width; j++)
			{
				*p == empty ? a -= 1 : a++;
				p++;
			}
			if (a >= 0)
			{
				IndexsOfNotEmptLines[k] = i;
				k++;
			}
		}
		if (k <= 0)
			throw InvalidVarFunctionException(" Most lines are empty in functions DeleteMostlyEmptyLines operand", k, width);
		Matrix result(k, width);
		k = 0;
		for (int i = 0; i < height; i++)
		{
			;
			if (i == IndexsOfNotEmptLines[k])
			{
				for (int j = 0; j < width; j++)
					result.ptr[k][j] = ptr[i][j];
				k++;
			}
		}
		return result;
	}
};

int main()
{
	try
	{
		ifstream fin("Matrices.txt");
		Matrix<> M(1, 2);
		//Matrix<> M1(fin);
		fin >> M;
		//M = M1;
		cout << M;
		/*cout << "Amount of Matrices:";
		int n = 0;
		cin >> n;
		if (n <= 0)
			return 0;
		Matrix<>* m = new Matrix<>[n];
		for (int i = 0; i < n; i++)
		{
			Matrix<> M(cin);
			m[i] = M;
		}
		ofstream fout("Matrices.txt");
		if (fout)
		{
			for (int i = 0; i < n; i++)
				fout << m[i];
			fout.close();
		}
		Matrix<>* m2 = new Matrix<>[n];
		ifstream fin("Matrices.txt");
		if (fin.is_open())
		{
			for (int i = 0; i < n; i++)
			{
				Matrix<> M(fin);
				m2[i] = M;
			}
			fin.close();
		}
		for (int i = 0; i < n; i++)
		{
			cout << "\n" << m[i];
			cout << "\n" << m2[i];
		}


		Matrix<> M1(cin);
		Matrix<> M2(2,2);
		M2 = M1.DeleteMostlyEmptyLines();
		cout << M2;*/
	}

	catch (WrongSizeException e)
	{
		cout << "\nCaught WrongSizeException: "; e.print();
	}
	catch (IndexOutOfBoundsException e)
	{
		cout << "\nCaught IndexOutOfBoundsException: "; e.print();
	}
	catch (InvalidOperationException e)
	{
		cout << "\nCaught InvalidOperationException: "; e.print();
	}
	catch (InvalidVarFunctionException e)
	{
		cout << "\nCaught InvalidVarFunctionException: "; e.print();
	}
	catch (Exception e)
	{
		cout << "\nCaught Exception: "; e.print();
	}
	catch (exception e)
	{
		cout << "\nCaught Exception: "; cout << e.what();
	}
	return 0;
}