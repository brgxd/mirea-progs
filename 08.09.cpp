#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class Element
{
	//элемент связного списка
private:
	//указатель на предыдущий и следующий элемент
	Element* next;
	Element* prev;

	//информация, хранимая в поле
	T field;
public:
	//доступ к полю *next
	virtual Element* getNext() { return next; }
	virtual void setNext(Element* value) { next = value; }

	//доступ к полю *prev
	virtual Element* getPrevious() { return prev; }
	virtual void setPrevious(Element* value) { prev = value; }

	//доступ к полю с хранимой информацией field
	virtual T getValue() { return field; }
	virtual void setValue(T value) { field = value; }

	template<class T> friend ostream& operator<< (ostream& ustream, Element<T>& obj);

	Element(T value) {field = value; next = prev = NULL;}
};

template<class T>
ostream& operator << (ostream& ustream, Element<T>& obj)
{
	ustream << obj.field;
	return ustream;
}

template <class T>
class LinkedListParent
{
protected:
	//достаточно хранить начало и конец
	Element<T>* head;
	Element<T>* tail;
	//для удобства храним количество элементов
	int num;
public:
	virtual int Number() { return num; }

	virtual Element<T>* getBegin() { return head; }

	virtual Element<T>* getEnd() { return tail; }

	LinkedListParent()
	{
		//конструктор без параметров
		cout << "\nParent constructor";
		head = NULL; tail = NULL;
		num = 0;
	}

	//чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать добавление
	virtual Element<T>* push(T value) = 0;

	//чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать удаление
	virtual Element<T>* pop() = 0;

	virtual ~LinkedListParent()
	{
		//деструктор - освобождение памяти
		cout << "\nParent destructor";
	}

	//получение элемента по индексу - какова асимптотическая оценка этого действия?
	virtual Element<T>* operator[](int i)
	{
		//индексация
		if (i<0 || i>num) return NULL;
		int k = 0;

		//ищем i-й элемент - вставем в начало и отсчитываем i шагов вперед
		Element<T>* cur = head;
		for (k = 0; k < i; k++)
		{
			cur = cur->getNext();
		}
		return cur;
	}

	template<class T> friend ostream& operator<< (ostream& ustream, LinkedListParent<T>& obj);
	template<class T> friend istream& operator>> (istream& ustream, LinkedListParent<T>& obj);
};

template<class T>
ostream& operator << (ostream& ustream, LinkedListParent<T>& obj)
{
	if (typeid(ustream).name() == typeid(ofstream).name())
	{
		ustream << obj.num << "\n";
		for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext())
			ustream << current->getValue() << " ";
		return ustream;
	}

	ustream << "\nLength: " << obj.num << "\n";
	int i = 0;
	for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext(), i++)
		ustream << "arr[" << i << "] = " << current->getValue() << "\n";

	return ustream;
}

template<class T>
istream& operator >> (istream& ustream, LinkedListParent<T>& obj)
{
	//чтение из файла и консоли совпадают
	int len;
	ustream >> len;
	//здесь надо очистить память под obj, установить obj.num = 0
	double v = 0;
	for (int i = 0; i < len; i++)
	{
		ustream >> v;
		obj.push(v);
	}
	return ustream;
}

//дописать класс итератора по списку
template<typename ValueType>
class ListIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
public:
	//конструкторы
	ListIterator() { ptr = NULL; }
	ListIterator(Element<ValueType>* p) { ptr = p; }
	ListIterator(const ListIterator& it) { ptr = it.ptr; }

	//методы работы с итераторами
	//присваивание
	ListIterator& operator=(const ListIterator& it) { ptr = it.ptr; return *this; }
	ListIterator& operator=(Element<ValueType>* p) { ptr = p; return *this; }

	//проверка итераторов на равенство
	bool operator!=(ListIterator const& other) const { return ptr != other }
	bool operator==(ListIterator const& other) const { return ptr == other }
	//получить значение
	Element<ValueType>& operator*()
	{
		return *ptr;
	}
	//перемещение с помощью итераторов
	ListIterator& operator++() 
	{  
	    if(ptr->getNext()==NULL) return *this;
	    ptr = ptr->getNext()
	    return *this;
	}
	ListIterator& operator++(int v) 
	{ 
	    if(ptr->getNext()==NULL) return *this;
	    ptr = ptr->getNext();
	    return *this;
	}
//private:
	//текущий элемент
	Element<ValueType>* ptr;
};

//класс итерируемый список - наследник связного списка, родитель для Очереди и Стека
template <class T>
class IteratedLinkedList : public LinkedListParent<T>
{
public:
	IteratedLinkedList() : LinkedListParent<T>() { cout << "\nIteratedLinkedList constructor"; }
	virtual ~IteratedLinkedList() { cout << "\nIteratedLinkedList destructor"; }

	ListIterator<T> iterator;

	ListIterator<T> begin() { ListIterator<T> it = LinkedListParent<T>::head; return it; }
	ListIterator<T> end() { ListIterator<T> it = LinkedListParent<T>::tail; return it; }
};

template<class T>
class Stack : public IteratedLinkedList<T>
{
public:
    Stack() : LinkedListParent<T>(){
        head = NULL;
        tail = NULL;
        num = 0;
        cout <<"n\STack default constructor"; 
    }
    virtual ~Stack() {
        cout << "n\Stack destructor"
        
    }
    
    Element<T> push(T value){
        Element<T>* newElement = new Element value;
        if(head == NULL){
            head = tail = newElement;
            return;
        }
        newElement->setPrevious(tail);
        tail->setNext(newElement);
        tail = newElement;
        return tail;
    }
    
    T pop(){
        if(num == 0){
            return;
        }
        //if(num == 1){
        if(head == tail)// учитывая что существует exception при head == NULL 
            T result = head->getValue();
            delete head;
            delete tail;
            head = tail = NULL;
            return result;
        }
        T result = tail->getValue();
        Element<T>* new_tail = tail->getPrevious();
        tail->setPrevious(NULL);
        new_tail->setNext(NULL);
        delete tail;
        tail = new_tail;
        return result;
    }
    
    ListIterator<T> insert(ListIterator<T> it, T value)
    {
        Element<T> newElement = new Element value;
        it++->setPrevious(newElement);
        it.ptr->setNext(newElement);
        it++;
        return it;//что вернется при return ++it;?
    }
    
};


int main()
{
	
	Stack<int> S;
	S.push(1);
	S.push(2);
	S.push(3);
	cout << S;
	cout << "\n";
	int e1 = S.pop();
	cout << "\nElement = " << e1->getValue();
	cout << S;
	cout<<"\nIndex in the Stack class: " << S[1]->getValue();

	cout << S;
	cout << "\nIterators:\n";
	S.iterator = S.begin();
	while (S.iterator != S.end())
	{
		cout << *S.iterator << " ";
		S.iterator++;
	}
	cout << *S.iterator << " ";
	
	char c; cin >> c;
	return 0;
}
