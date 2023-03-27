#include <iostream>
using namespace std;

class MyArrayParent
{
protected:

	int capacity;
	int count;

public:
	double* ptr;

	MyArrayParent(int Dimension = 100)
	{
		cout << "\nMyArrayParent constructor";
		ptr = new double[Dimension];
		capacity = Dimension;
		count = 0;
	}

	MyArrayParent(double* arr, int len)
	{
		cout << "\nMyArrayParent constructor";
		capacity = len + 1;
		count = len;
		ptr = new double[capacity];
		for (int i = 0; i < len; i++)
			ptr[i] = arr[i];
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
		cout << "\noperator=";
		if (capacity < P.capacity)
		{
			delete[] ptr;
			capacity = P.capacity;
			ptr = new double[capacity];
		}
		count = P.count;
		for (int i = 0; i < count; i++)
			ptr[i] = P.ptr[i];

		return *this;
	}

	~MyArrayParent()
	{
		cout << "\nMyArrayParent destructor";
		delete[] ptr;
		ptr = NULL;
		count = 0;
		capacity = 0;
	}

	int Capacity() { return capacity; }
	int Size() { return count; }
	double GetComponent(int index)
	{
		if (index >= 0 && index < count)
			return ptr[index];
		return -1;
	}
	void SetComponent(int index, double value)
	{
		if (index >= 0 && index < count)
			ptr[index] = value;
	}

	virtual void push(double value)
	{
		if (count < capacity)
		{
			ptr[count] = value;
			count++;
		}
	}

	void RemoveLastValue()
	{
		if (count > 0)
		{
			ptr[count - 1] = 0;
			count--;
		}
	}

	double& operator[](int index)
	{
		return ptr[index];
	}

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

	int IndexOf(int a)
	{
		for (int i = 0; i <= count; i++)
		{
			if (ptr[i] = a)return i;
		}
		return -1;
	}
};

class MyArrayChild : public MyArrayParent
{
public:
	MyArrayChild(int Dimension = 100) : MyArrayParent(Dimension) { cout << "\nMyArrayChild constructor"; }

	MyArrayChild(double* arr, int len) : MyArrayParent(arr, len) { cout << "nMyArrayChild constructor"; }

	~MyArrayChild() { cout << "\nMyArrayChild destructor\n"; }

	int IndexOf(double value, bool bFindFromStart = true)
	{
		int i = 0;
		if (bFindFromStart == true)
		{
			for (i = 0; i < count; i++)
			{
				if (ptr[i] == value)
					return i;
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

	void RemoveAt(int index = -1)
	{
		if (count == 0 || index > count) return;
		if (index == -1)
		{
			RemoveLastValue();
			return;
		}
		for (int i = index; i < count - 1; i++)
			ptr[i] = ptr[i + 1];
		RemoveLastValue();
		count--;
	}

	void InsertAt(double value, int index = -1)
	{
		if (index == -1 || index == count)
			push(value);
		if (index<0 || index>count) return;

		for (int i = count; i > index; i--)
			ptr[i] = ptr[i - 1];

		ptr[index] = value;
		count++;
	}

	int max()
	{
		double max = 0;
		for (int i = 0; i < count; i++)
			max = (max > ptr[i]) ? max : ptr[i];
		return max;
	}

	bool operator<(MyArrayChild a)
	{
		return (max() < a.max()) ? true : false;
	}


};

class MySortedArray : public MyArrayChild
{
protected:
	

public:

	MySortedArray(int Dimension = 100) : MyArrayChild(Dimension) { cout << "\nMySortedArray constructor"; }
	~MySortedArray() { cout << "\nMySortedArray destructor\n"; }

	int BinSearch(double value, int left, int right)
	{
		int middle = (left + right) / 2;

		//база рекурсии
		if (ptr[middle] == value)
			return middle;
		if (count == 1) return -1;
		if (left + 1 == right)
		{
			if (ptr[right] == value) return right;
			return -1;
		}

		if (ptr[middle] > value) return BinSearch(value, left, middle);
		if (ptr[middle] < value) return BinSearch(value, middle, right);
	}

	int BinSearch_insert(double value, int left, int right)
	{
		int middle = (left + right) / 2;

		//база рекурсии
		if (ptr[middle] == value)
			return middle;
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

		if (ptr[middle] > value) return BinSearch_insert(value, left, middle);
		if (ptr[middle] < value) return BinSearch_insert(value, middle, right);
	}

	bool operator<(MySortedArray a)
	{
		return ptr[count-1] < a.ptr[a.count-1] ? true : false;
	}

	int IndexOf(double value, bool bFindFromStart = true)
	{
		return BinSearch(value, 0, count - 1);
	}

	void push(double value)
	{
		if (value < ptr[0])
		{
			for(int i = count; i > 0; i--)
			{
				ptr[i] = ptr[i - 1];
			}
			ptr[0] = value;
			count++;
			return;
		}
		if (value > ptr[count - 1])
		{
			ptr[count] = value;
			count++;
			return;
		}
		int a = BinSearch_insert(value, 0, count - 1);
		for (int i = count; i > a; i--)
			ptr[i] = ptr[i - 1];
		ptr[a] = value;
		count++;
	}
};