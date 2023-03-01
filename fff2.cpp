// Inhearitance_Array.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

using namespace std;

class MyArrayParent
{
private:
	//сколько памяти выделено?
	int capacity;
	//количество элементов - сколько памяти используем
	int count;
	//массив
	double* ptr;
public:
	//конструкторы и деструктор
	MyArrayParent(int Dimension = 100)
	{
		cout << "\nMyArrayParent constructor";
		//выделить память под массив ptr, заполнить поля
		ptr = new double[Dimension];
		capacity = Dimension;
		count = 0;
	}
	//конструктор принимает существующий массив
	MyArrayParent(double* arr, int len)
	{
		cout << "\nMyArrayParent constructor";
		//заполнить массив ptr, заполнить поля
	}
	//деструктор
	~MyArrayParent()
	{
		cout << "\nMyArrayParent destructor";
		//освободить память, выделенную под ptr
		delete[] ptr;
	}

	MyArrayParent(const MyArrayParent& P)
	{
		cout << "\nCopy constructor";
		count = P.count;
		capacity = P.capacity;
		ptr = new double[capacity];
		for (int i = 0; i < count; i++)
			ptr[i] = P.ptr[i];
	}

	MyArrayParent& operator=(const MyArrayParent& P)
	{
		cout << "\nCopy constructor";
		// почистить ptr
		if (capacity < P.capacity)
		{
			delete[] ptr;
			ptr = new double[capacity];
		}

		// delete[] ptr;
		count = P.count;
		for (int i = 0; i < count; i++)
			ptr[i] = P.ptr[i];

		return *this;
	}


	//обращение к полям
	int Capacity() { return capacity; }
	int Size() { return count; }
	double GetComponent(int index)
	{
		if (index >= 0 && index < count)
			return ptr[index];
		//сгенерировать исключение, если индекс неправильный
		return -1;
	}
	void SetComponent(int index, double value)
	{
		if (index >= 0 && index < count)
			ptr[index] = value;
		//сгенерировать исключение, если индекс неправильный
	}

	//добавление в конец нового значения
	void push(double value)
	{
		if (count < capacity)
		{
			ptr[count] = value;
			count++;
		}
	}

	//удаление элемента с конца
	void RemoveLastValue()
	{
		if (count >= 0)
		{
			ptr[count - 1] = 0;
			count--;
		}
		//что делаем, если пуст?
	}

	double& operator[](int index)
	{
		//перегрузка оператора []
		return ptr[index];
	}

	/*MyArrayParent& operator=(const Vector& V)
	{
		//оператор =
		//arr1 = arr2 = arr3; где arr_i - объекты нашего класса
	}

	MyArrayParent(const Vector& V)
	{
		//создание копии объекта - в основном, при возвращении результата из функции / передаче параметров в функцию
	}*/

	void print()
	{
		cout << "\nMyArrParent, size: " << count << ", values: {";
		int i = 0;
		for (i = 0; i < count; i++)
		{
			cout << ptr[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "}";
	}



};

class MyArrayChild : public MyArrayParent
{
public:
	//используем конструктор родителя. Нужно ли что-то ещё?
	MyArrayChild(int Dimension = 100) : MyArrayParent(Dimension) { cout << "\nMyArrayChild constructor"; }

	~MyArrayChild() { cout << "\nMyArrayChild destructor\n"; }

	//удаление элемента
	void RemoveAt(int index = -1)
	{
		if (count == 0) return;
		if (index == -1)
		{
			RemoveLastValue();
			return;
		}
		for (int i = index; i)
	}

	//поиск элемента
	int IndexOf(double value, bool bFindFromStart = true)
	{
		if (bFindFromStart == true)
		{
			{
				for (i = 0; i < count; i++)
				{
					if (ptr[i] == value)
						return i;
				}
			}
		}
		else
		{
			for (i = count - 1; i >= 0; i--)
			{
				if (ptr[i] == value)
					return i;
			}
		}
		return -1;
	}
	//вставка элемента
	void InsertAt(double value, int index = -1)
	{
		if (index == -1 || index == count)
			push(value)
		if (index<0 || index>count) return;

		for (int i = count; i > index; i--)
		{
			ptr[i] = ptr[i - 1];
		}
		ptr[index] = value;
		count++;
	}

	//выделение подпоследовательности
	//MyArrayChild SubSequence(int StartIndex = 0, int Length = -1)

	//добавление элемента в конец
	//operator + ?

};


class MySortedArray : public MyArrayChild
{

protected:
	int BinSearch(double value, int left, int right)
	{
		int middle = (left + right) / 2;
		if (count == 1) return -1;
		if (prt[middle] == value) return middle;

		if (left + 1 == right) {
			if (prt[middle] > value) return BinSearch(value, left, middle);
			if (prt[middle] < value) return BinSearch(value, middle, right);
		}
		if (prt[left] == value) return left;
		if (prt[right] == value) return right;
	}

	int BinSearch_insert(double value , int left , int right)
	{
		int middle = (left + right) / 2;

		if (ptr[middle] == value) return middle;
		if (count == 1)
		{
			if (ptr[0] > value) return 0;
			return 1;
		}
		if (left + 1 == right)
		{
			if (ptr[left] > value) return left;
			if (ptr[right] < value) return right + 1;
			return right;
		}

		if (ptr[middle] > value)return BinSearch_insert(value, left, middle);
		if (ptr[middle] < value)return BinSearch_insert(value, middle, right);
	}




public:
	MySortedArray(int Dimension = 100) : MyArrayChild(Dimension) { cout << "\nMySortedArray constructor"; }
	~MySortedArray() { cout << "\nMySortedArray destructor\n"; }

	int IndexOf(double value, 0, count - 1)
	{
		return BinSearch(value, 0, count - 1);
	}

	void push(double value)
	{
		if (count == 0)
		{
			MyArrayParent::push(value);
			return;
		}
		int index = BinSearch_insert(value , 0 , count - 1);
		InsertAt(value, index);
	}
};

void f(MyArrayParent s)
{
	cout << "\nIn f():"; 
	cout << s.ptr;
	s.print();
}

void g(int t)
{
	t = 10;
}


void HandleArray(double* arr int len, double min, double max, double& mean)
{
	//ДЗ!
}

int main()
{
	MyArrayParent arr;
	if (true)
	{
		//MyArrayChild arr;
		int i = 0;
		for (i = 0; i < 10; i++)
		{
			arr.push(i + 1);
		}
		arr.print();
		cout << "\n";
		//cout << "\n" << sp << "\n";
	}
	char c; cin >> c;
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл