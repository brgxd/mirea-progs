#include <iostream>
#include <fstream>


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
	InvalidSizeException(const char* s, int Width, int Height) : Exception(s) { w = Width; h = Height; }
	InvalidSizeException(const InvalidSizeException& e) : Exception(e) { w = e.w; h = e.h; }

	//функцию вывода можно будет переопределить в производных классах, когда будет ясна конкретика
	virtual void print()
	{
		cout << "InvalidSizeException: " << str << "; columns: " << w << "\t" << "rows: " << h << "; " << what();
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

class BaseMatrix
{
protected:
	double** ptr;
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
		ptr = new double* [height];
		for (int i = 0; i < height; i++)
			ptr[i] = new double[width];
	}

	BaseMatrix(const BaseMatrix& M)
	{
		//конструктор копий
		cout << "\nBaseMatrix copy constructor";
		height = M.height;
		width = M.width;
		ptr = new double* [height];
		for (int i = 0; i < height; i++)
		{
			ptr[i] = new double[width];
			for (int j = 0; j < width; j++)
				ptr[i][j] = M.ptr[i][j];
		}
	}

	BaseMatrix(double** arr, int w, int h)
	{
		cout << "\nBaseMatrix constructor double**";
		height = h;
		width = w;
		ptr = new double* [height];
		for (int i = 0; i < height; i++)
		{
			ptr[i] = new double[width];
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

	double* operator[](int row)
	{
		if (row < 0 || row >= height)
			throw IndexOutOfBoundsException("Index out of bounds in operator[]", row, -1);
		return ptr[row];
	}

	double& operator()(int row, int column)
	{
		if (row < 0 || row >= height || column < 0 || column >= width)
			throw IndexOutOfBoundsException("Index out of bounds in operator()", row, column);
		return ptr[row][column];
	}
	friend ostream& operator<<(ostream& s, BaseMatrix M);
	friend istream& operator>>(istream& s, BaseMatrix& M);
};

ostream& operator<<(ostream& s, BaseMatrix M)
{
	if (typeid(s) == typeid(ofstream))
	{
		s << M.height << " " << M.width << " ";
		for (int i = 0; i < M.height; i++)
			for (int j = 0; j < M.width; j++)
				s << M.ptr[i][j] << " ";
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

istream& operator>>(istream& s, BaseMatrix& M)
{
	if (typeid(s) == typeid(ifstream))
	{
		int w, h;
		s >> h >> w;
		if (h != M.height || w != M.width)throw WrongSizeException("Matrix size in file and in code arent equal", w, h);
	}
	for (int i = 0; i < M.height; i++)
		for (int j = 0; j < M.width; j++)
			s >> M.ptr[i][j];
	return s;
}

class Matrix : public BaseMatrix
{
public:
	Matrix(int Height = 2, int Width = 2) : BaseMatrix(Height, Width) {}
	Matrix(double** arr, int w, int h) : BaseMatrix(arr, w, h) {}
	Matrix(const Matrix& M) : BaseMatrix((BaseMatrix&)M) { cout << "\nMatrix copy constructor\n"; }

	double operator+()
	{
		if (width != height)
			throw InvalidSizeException("Quantity of rows and columns isn't equal in operator+()", width, height);
		double sum = 0;
		for (int i = 0; i < height; i++)
			sum += ptr[i][i];
		return sum;
	}
	Matrix operator*(double d)
	{
		Matrix s(height, width);
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				s(i, j) = ptr[i][j] * d;

		return s;
	}

	Matrix operator=(Matrix m)
	{
		if (ptr == NULL)
		{
			ptr = new double* [m.height];
			for (int i = 0; i < m.height; i++)
			{
				ptr[i] = new double[m.width];
				for (int j = 0; j < m.width; j++)
					ptr[i][j] = m.ptr[i][j];
			}
			width = m.width;
			height = m.height;
			return *this;
		}
		if (height != m.height || width != m.width)
		{
			for (int i = 0; i < height; i++)
				delete[] ptr[i];
			if (height != m.height)
			{
				delete[] ptr;
				ptr = new double* [m.height];
			}
			for (int i = 0; i < m.height; i++)
			{
				ptr[i] = new double[m.width];
				for (int j = 0; j < width; j++)
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
		/*Matrix result(height, width);
		int k = 0;
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				result.ptr[i][j] = 0;
		for (int i = 0; i < height; i++)
		{
			int a = 0;
			double* p = ptr[i];
			for (int j = 0; j < width; j++)
			{
				*p == 0 ? a -= 1 : a += 1;
				p++;
			}
			if (a >= 0)
			{
				for (int j = 0; j < width; j++)
					result.ptr[k][j] = ptr[i][j];
				k += 1;
			}
		}
		return result;*/
		double* IndexsOfNotEmptLines = new double[height];
		int k = 0;
		for (int i = 0; i < height; i++)
		{
			int a = 0;
			double* p = ptr[i];
			for (int j = 0; j < width; j++)
			{
				*p == 0 ? a -= 1 : a += 1;
				p++;
			}
			if (a >= 0)
			{
				IndexsOfNotEmptLines[k] = i;
				k += 1;
			}
		}
		Matrix result(k, width);
		k = 0;
		for (int i = 0; i < height; i++)
		{;
			if (i == IndexsOfNotEmptLines[k])
			{
				for (int j = 0; j < width; j++)
					result.ptr[k][j] = ptr[i][j];
				k += 1;
			}
		}
		return result;
	}
};

int main()
{
	try
	{
		Matrix a(3, 3);
		a(0, 0) = 0; a(0, 1) = 2; a(0, 2) = 15;
		a(1, 0) = 0; a(1, 1) = 0; a(1, 2) = 54;
		a(2, 0) = 12; a(2, 1) = 90; a(2, 2) = 1;
		Matrix b(1, 4);
		Matrix c(2,2);
		c = a;
		//b = a.DeleteMostlyEmptyLines();
		//b.print();
		//Matrix* prr = new Matrix[2];
		//prr[0] = a;
		//prr[1] = b;
		//a.print();
		//prr[0].print();
		//b.print();
		//a.DeleteMostlyEmptyLines();
		/*Matrix* arr = new Matrix[10];
		for (int i = 0; i < 10; i++)
		{
			arr[i](0, 0) = i;
			arr[i](0, 1) = i+1;
			arr[i](1, 0) = i-1;
			arr[i](1, 1) = i*2;
		}
		//M1(0, 0) = 1; M1(0, 1) = 2; M1(1, 0) = 3; M1(1, 1) = 4; M1(1, 5) = 5;
		//Matrix M2 = M1;
		//cin >> M1;
		//cout << "\n";
		//cout << +(M2 * 5);
		//cout << "\n"<< M1;
		//M2.print();

		ofstream fout("test.txt");
		if (fout)
		{
			for (int i = 0; i < 10; i++)
				fout << arr[i] << "\n";
			fout.close();
		}
		ifstream fin("test.txt");
		if (fin)
		{
			// int n; fin >> n;
			//for (int i = 0; i < n; i++)
			while (!fin.eof())
			{
				try
				{
					Matrix M2;
					fin >> M2;
					cout << "\n" << M2;
				}
				catch (exception e) { cout << "\nCaught exception: " << e.what(); }
			}
			fin.close();
		}*/
	}

	catch (WrongSizeException e)
	{
		cout << "\nCaught WrongSizeException: "; e.print();
	}
	catch (InvalidSizeException e)
	{
		cout << "\nCaught InvalidSizeException: "; e.print();
	}
	catch (IndexOutOfBoundsException e)
	{
		cout << "\nCaught IndexOutOfBoundsException: "; e.print();
	}
	catch (InvalidOperationException e)
	{
		cout << "\nCaught InvalidOperationException: "; e.print();
	}
	catch (Exception e)
	{
		cout << "\nCaught Exception: "; e.print();
	}
	catch (exception e)
	{
		cout << "\nCaught Exception: "; cout << e.what();
	}
	char c; cin >> c;

	return 0;
}
	
