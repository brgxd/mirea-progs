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

		for (i = 0; ptr[i] != '\0'; p[i] = ptr[i], i++);
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

		for (i = 0; ptr[i] != '\0'; i++)
			p[i] = ptr[i];
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
		capacity = 0;
		p = NULL;
	}

	int Length() { return len; }
	int Capacity() { return capacity; }
	//char* get() {return p;}
	char& operator[](int i) { return p[i]; }


	BaseString& operator=(BaseString& s)
	{
		cout << "\nBase Operator = \n";
		len = s.len;
		capacity = s.capacity;
		if (capacity < s.capacity)
		{
			delete[] p;
			p = NULL;
			p = new char[s.capacity];
		}
		for (int i = 0; i <= len; i++)
			p[i] = s.p[i];
		return *this;
	}

	BaseString(BaseString& s)
	{
		cout << "\nBase Copy Constructor\n";
		capacity = s.capacity;
		len = s.len;
		p = new char[capacity];
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
		/*for (int i = start; p[i] != '\0'; i++)
			if (p[i] == c)
				return i;*/
		for (char* p1 = p; *p1; p1++)
			if (*p1 == c)
				return p1 - p;
		return -1;
	}

	
};

class String : public BaseString
{
public:
	String(int capacity = 256) : BaseString(capacity) {}
	String(const char* str) : BaseString(str) {}
	~String() {}

	virtual int IndexOf(char c, int start = 0)
	{
		if (start == 0) start = len - 1;
		if (len == 0 || start >= len) return -1;

		char* p1 = &p[len - 1];
		for (; p1 >= p; p1--)
			if (*p1 == c)
				break;
		return p1 - p;
		//if (*p1 == c)
			//return p1-p;
	//return -1;
	}

	bool IsPalindrome()
	{
		char* p1 = p;
		char* p2 = &p[len - 1];
		while (p1 < p2)
		{
			if (*p1 != *p2) return false;
			p1++;
			p2--;
		}
		return true;
	}

	bool aaa()
	{
		char* p1 = p;
		int n = 0;
		while (*p1 != '\0')
		{
			if (*p1 == '(')n++;
			if (*p1 == ')')n--;
			if (n < 0)return false;
			p1++;
		}
		return (n == 0 ? true : false);
		/*int n = 0;
		int k = 0;
		while (n < len)
		{
			if (p[n] == '(')k++;
			if (p[n] == ')')k--;
			n++;
			if (k < 0)return false;
		}
		return k == 0 ? true : false;*/
	}
};

int main()
{
	String s1("AAAAAAAA");
	String s2("ff");
	String s3("12345");
	cout << "\n" << s1.IsPalindrome() << "\n" << s3.IsPalindrome();
	s1 = s2 = s3;
	cout << "\n";
	s1.print();
	cout << "\n" << s3.IndexOf('3', 0);
	String s("(abcd)");
	cout << "\n" << s.aaa();
}
