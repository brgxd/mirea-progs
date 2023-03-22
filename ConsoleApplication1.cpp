

#include <iostream>

using namespace std;

class BaseString
{
protected:
	char* p;
	int len;
	int capacity;
public:
	BaseString(char* ptr)
	{
		cout << "\nBase Constructor 1\n";
		int i = 0;
		for (; ptr[i] != '\0'; i++);
		len = i;

		capacity = (len > 256) ? len + 1 : 256;
		p = new char[capacity];

		for (i = 0; ptr[i] != '\0';p[i] = ptr[i], i++);
		p[len] = '\0';
	}

	BaseString(const char* ptr)
	{
		cout << "\nBase Constructor 1\n";
		int i = 0;
		for (; ptr[i] != '\0'; i++);
		len = i;

		capacity = (len > 256) ? len + 1 : 256;
		p = new char[capacity];

		for (i = 0; ptr[i] != '\0'; p[i] = ptr[i], i++);
		p[len] = '\0';
	}

	BaseString(int Capacity = 256)
	{
		cout << "\nBase Constructor 0\n";
		capacity = Capacity;
		p = new char[capacity];
		len = 0;
	}

	~BaseString()
	{
		cout << "\nBase Destructor\n";
		if (p != NULL)
			delete[] p;
		len = 0;
		p = NULL;
		capacity = 0;
	}

	int Length() { return len; }
	int Capacity() { return capacity; }
	//char* get() {return p;}
	char& operator[](int i) { return p[i]; }


	BaseString& operator=(BaseString& s)
	{
		cout << "\nBase Operator = \n";

		return *this;
	}

	BaseString(BaseString& s)
	{
		cout << "\nBase Copy Constructor\n";
		capacity = s.capacity;
		len = s.len;
		p = new char[s.capacity];
		for (int i = 0; i <= len; p[i] = s.p[i], i++);
	}

	virtual void print()
	{
		int i = 0;
		while (p[i] != '\0')
		{
			cout << p[i];
			i++;
		}
	}

	virtual int IndexOf(char c, int start = 0)
	{
		if (start > len || len == 0) return -1;
		for (int i = start; p[i] != '\0'; i++)
		{
			if (p[i] == c)return i;
		}
		return -1;
	}

};

class String : public BaseString
{
public:
	String(const char* str) : BaseString(str) {}
	~String() {}

	virtual int IndexOf(char c, int start = 0)
	{
		if (start == 0) start = len - 1;
		if (len == 0 || start >= len)return -1;
		for (int i = start; i > -1; i--)
			if (p[i] == c)return i;
		return -1;
	}
};


int main()
{
	if (true)
	{
		BaseString s("test");
		s.print();
		cout << "\n" << s.IndexOf('e');
		BaseString s1 = s;
		cout << "\n" << s1.IndexOf('t');
		/* BaseString s1 = s;
		s1.print();
		BaseString s2;
		s2 = s;
		s2 = s + s1;
		s2.print();
		s1 = s2 + s;
		s1.print();*/
	}
	char c; cin >> c;
	return 0;
}
