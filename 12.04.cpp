using namespace std;

#include <iostream>

template<class T> class LinkedList;
template<class T> class DoubleSideStack;
template<class T> class Stack;

template<class T>
class Element
{
protected:
	Element* next;
	Element* prev;
	T info;
public:
	friend class LinkedList<T>;
	friend class DoubleSideStack<T>;
	friend class Stack<T>;
	
	Element(T data)
	{
		next = prev = NULL;
		info = data;
	}

	Element(Element* Next, Element* Prev, T data)
	{
		next = Next;
		prev = Prev;
		info = data;
	}

	/*Element(const Element& el)
	{
		next = el.next;
		prev = el.prev;
		info = el.info;
	}*/

	template<class T1>
	friend ostream& operator<<(ostream& s, Element<T1>& el);

};

template<class T1>
ostream& operator<<(ostream& s, Element<T1>& el)
{
	s << el.info;
	return s;
}

template<class T>
class LinkedList
{
protected:
	Element<T>* head;
	Element<T>* tail;
	int count;
public:


	LinkedList()
	{
		head = tail = NULL;
		count = 0;
	}

	virtual ~LinkedList()
	{
		cout << "\nLinkedList Destructor";

		Element<T>* previous = NULL;
		for (Element<T>* current = head; current != NULL; current = current->next)
		{
			previous = current;
			current = curent->next;
			delete previous;
		}
	}

	//удалить первый/последний элемент и вернуть удаленное значение
	virtual Element<T>* pop() = 0;
	//добавить элемент в список
	virtual Element<T>* push(T value) = 0;

	//доступ по индексу
	virtual Element<T>& operator[](int index) = 0
	{
		//if(index <0 || index >= count) throw ...;
		Element<T>* current = head;
		for (int i = 0; current != NULL && i < index; current = current->Element::next, i++);
		return *current;
	}

	template<class T1>
	friend ostream& operator<<(ostream& s, LinkedList<T1>& el);

	//доработать деструктор
	~LinkedList()
	{

	}
};

template<class T1>
ostream& operator<<(ostream& s, LinkedList<T1>& el)
{
	Element<T2>* current = el.head;
	for (; current != NULL; current = current->next)
		s << *current << " ";
	return s;
}

template<class T>
class Stack : public LinkedList<T>
{
public:
	Stack<T>() : LinkedList<T>() {}
	virtual ~Stack() { cout << "\nStack Destructor"; }

	virtual Element<T>* pop() 
	{
		if (LinkedList<T>::tail == NULL)return NULL;

		Element<T>* res = LinkedList<T>::tail;

		if (LinkedList<T>::head == LinkedList<T>::tail)
		{
			LinkedList<T>::head = LinkedList<T>::tail = NULL;
			LinkedList<T>::count = 0;
			return res;
		}

		Element<T>* current = LinkedList<T>::head;
		for (; current->next != LinkedList<T>::tail; current = current->next);
		current->next = NULL;
		LinkedList<T>::tail = current;
		LinkedList<T>::count--;
		return res;

	}
	virtual Element<T>* push(T value) 
	{
		Element<T>* newElem = new Element<T>(value);
		if (this->tail != NULL)
		{
			this->tail->next = newElem;
			this->tail = this->tail->next;
		}
		else
			this->head = this->tail = newElem;
		this->count++;
		return this->tail;
	}

	virtual Element<T>* insert(T value, Element<T>* previous = NULL)
	{
		if (previous == NULL) 
			return push(value);

		Element<T>* inserted = new Element<T>(value);
		Element<T>* next = previous->next;
		previous->next = inserted;
		inserted->next = next;
		LinkedList<T>::count++;
		return inserted;
	}

};


class my_class
{
public:
	int x;
	my_class() { x = 0; cout << "\nmy_class constructor 0"; }
	~my_class() { cout << "\nmy_class destructor"; }
	my_class(int a) { x = a; cout << "\nmy_class constructor 1"; }
	my_class(const my_class& m) { x = m.x; cout << "\nmy_class copy constructor"; }
};

template<class T>
class DoubleSideStack : public Stack<T>
{
public:
	DoubleSideStack<T>() : Stack<T>() {}
	virtual ~DoubleSideStack<T>() { cout << "\ndoublesidestack destructor"; }

	using LinkedList<T>::head;
	using LinkedList<T>::tail;
	using LinkedList<T>::count;

	virtual Element<T>* push(T value)
	{
		Element<T>* tail_before = tail;
		Stack<T>::push(value);
		tail->prev = tail_before;
		return tail;
	}

	virtual Element<T>* pop()
	{
		if (LinkedList<T>::head == LinkedList<T>::tail)
			return Stack<T>::pop();
		Element<T>* newTail = tail->prev;
		newTail->next = NULL;
		tail->prev = NULL;
		tail = newTail;
		count--;
		return res;
	}

	virtual Element<T>* insert(T value, Element<T>* previous = NULL)
	{
		if (previous == NULL)
			return push(value);

		Element<T>* inserted = Stack<T>::insert(value, previous);
		inserted->next->prev = inserted;
		inserted->prev = previous;
		return inserted;
	}


	friend ostream& operator<<(ostream& s, DoubleSideStack<T1>& el)
};

template<class T1>
ostream& operator<<(ostream& s, DoubleSideStack<T1>& el)
{
	Element<T1>* current = el.tail;
	for (; current != NULL; current = current->prev)
		s << *current << " ";
	return s;
}

int main()
{
	LinkedList<double> S;
	/*for (int i = 0; i < 100; i += 10)
		S.push(i);
	cout << S;
	Element<int>* current = S.pop();
	while (current != NULL)
	{
		cout << *current << " ";
		current = S.pop();
	}*/

	LinkedList<my_class>* ptr = new Stack<my_class>;
	for (int i = 0; i < 100; i += 10)ptr->push(my_class(i));
	delete ptr;

}
