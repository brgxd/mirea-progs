﻿#include <iostream>

using namespace std;

template<class T>
class Node
{
protected:
	//закрытые переменные Node N; N.data = 10 вызовет ошибку
	T data;

	//не можем хранить Node, но имеем право хранить указатель
	Node* left;
	Node* right;
	Node* parent;

	//переменная, необходимая для поддержания баланса дерева
	int height;

	virtual Node<T>* Min(Node<T>* current)
	{
		while (current->getLeft() != NULL)
			current = current->getLeft();
		return current;
	}

	virtual Node<T>* Max(Node<T>* current)
	{
		while (current->getRight() != NULL)
			current = current->getRight();
		return current;
	}
public:
	//доступные извне переменные и функции
	virtual void setData(T d) { data = d; }
	virtual T getData() { return data; }
	int getHeight() { return height; }

	virtual Node* getLeft() { return left; }
	virtual Node* getRight() { return right; }
	virtual Node* getParent() { return parent; }

	virtual void setLeft(Node* N) { left = N; }
	virtual void setRight(Node* N) { right = N; }
	virtual void setParent(Node* N) { parent = N; }

	//Конструктор. Устанавливаем стартовые значения для указателей
	Node<T>(T n)
	{
		data = n;
		left = right = parent = NULL;
		height = 1;
	}

	Node<T>()
	{
		left = NULL;
		right = NULL;
		parent = NULL;
		data = 0;
		height = 1;
	}


	virtual void print()
	{
		cout << "\n" << data;
	}

	virtual void setHeight(int h)
	{
		height = h;
	}

	template<class T> friend ostream& operator<< (ostream& stream, Node<T>& N);

	Node* successor()
	{
		if (right != NULL)
			return Min(right);
		Node* current = parent;
		while (current != NULL && current->getData()<data)
			current = current->parent;
		return current;
	}
	Node* predecessor()
	{
		if (left != NULL)
			return Max(left);
		Node* current = parent;
		while (current->parent->right != current && current != NULL)
			current = current->parent;
		return current;


		/*Node* current = parent;
		Node* previous = this;
		while (current != NULL && current->right != previous)
		{
			previous = current;
			current = current->parent;
		}
		return current;*/
	}
};

template<class T>
ostream& operator<< (ostream& stream, Node<T>& N)
{
	stream << "\nNode data: " << N.data << ", height: " << N.height;
	return stream;
}
template<class T>
void print(Node<T>* N) { cout << "\n" << N->getData(); }

template<class T>
class Tree
{
protected:
	//корень - его достаточно для хранения всего дерева
	Node<T>* root;
public:
	//доступ к корневому элементу
	virtual Node<T>* getRoot() { return root; }

	//конструктор дерева: в момент создания дерева ни одного узла нет, корень смотрит в никуда
	Tree<T>() { root = NULL; }

	//функция добавления узла в дерево
	virtual Node<T>* push_R(Node<T>* N)
	{
		return push_R(N, root);
	}

	//рекуррентная функция добавления узла. Интерфейс аналогичен (добавляется корень поддерева, 
	//куда нужно добавлять узел), но вызывает сама себя - добавление в левое или правое поддерево
	virtual Node<T>* push_R(Node<T>* N, Node<T>* Current)
	{
		//не передан добавляемый узел
		if (N == NULL) return NULL;

		if (Current == NULL) Current = root;

		//пустое дерево - добавляем в корень
		if (root == NULL)
		{
			root = N;
			return root;
		}

		if (Current->getData() > N->getData())
		{
			//идем влево
			if (Current->getLeft() != NULL) return push_R(N, Current->getLeft());
			else
			{
				Current->setLeft(N);
				N->setParent(Current);
			}
		}
		if (Current->getData() < N->getData())
		{
			//идем вправо
			if (Current->getRight() != NULL) return push_R(N, Current->getRight());
			else
			{
				Current->setRight(N);
				N->setParent(Current);
			}
		}
		return N;
	}

	//функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
	virtual Node<T>* push(T value)
	{
		Node<T>* N = new Node<T>(value);
		return push_R(N);
	}

	//удаление узла
	virtual void Remove(Node<T>* N)
	{ }

	//поиск минимума и максимума в дереве
	virtual Node<T>* Min(Node<T>* Current = NULL)
	{
		if (root == NULL)
			return NULL;

		Node<T>* current = root;

		while (current->getLeft() != NULL)
			current = current->getLeft();

		return current;
	}

	virtual Node<T>* Max(Node<T>* Current = NULL)
	{
		if (root == NULL)
			return NULL;

		Node<T>* current = root;

		while (current->getRight() != NULL)
			current = current->getRight();

		return current;
	}

	//поиск узла в дереве
	virtual Node<T>* Find(T data)
	{
		if (root == NULL) return NULL;
		return Find_R(data, root);
	}

	//поиск узла в дереве. Второй параметр - в каком поддереве искать, первый - что искать
	virtual Node<T>* Find_R(T data, Node<T>* Current)
	{
		//база рекурсии
		if (Current == NULL || Current->getData() == data) return Current;
		//рекурсивный вызов
		if (Current->getData() > data) return Find_R(data, Current->getLeft());
		if (Current->getData() < data) return Find_R(data, Current->getRight());
	}

	//три обхода дерева
	virtual void PreOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL)
			f(N);
		if (N != NULL && N->getLeft() != NULL)
			PreOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)
			PreOrder(N->getRight(), f);
	}

	//InOrder-обход даст отсортированную последовательность
	virtual void InOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL && N->getLeft() != NULL)
			InOrder(N->getLeft(), f);
		if (N != NULL)
			f(N);
		if (N != NULL && N->getRight() != NULL)
			InOrder(N->getRight(), f);
	}

	virtual void PostOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL && N->getLeft() != NULL)
			PostOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)
			PostOrder(N->getRight(), f);
		if (N != NULL)
			f(N);
	}
};

template<class T>
class AVL_Tree : public Tree<T>
{
protected:
	//определение разности высот двух поддеревьев
	int bfactor(Node<T>* p)
	{
		int hl = 0;
		int hr = 0;
		if (p->getLeft() != NULL)
			hl = p->getLeft()->getHeight();
		if (p->getRight() != NULL)
			hr = p->getRight()->getHeight();
		return (hr - hl);
	}

	//при добавлении узлов в них нет информации о балансе, т.к. не ясно, куда в дереве они попадут
	//после добавления узла рассчитываем его высоту (расстояние до корня) и редактируем высоты в узлах, где это
	//значение могло поменяться
	void fixHeight(Node<T>* p)
	{
		int hl = 0;
		int hr = 0;
		if (p->getLeft() != NULL)
			hl = p->getLeft()->getHeight();
		if (p->getRight() != NULL)
			hr = p->getRight()->getHeight();
		p->setHeight((hl > hr ? hl : hr) + 1);
	}

	//краеугольные камни АВЛ-деревьев - процедуры поворотов
	Node<T>* RotateRight(Node<T>* p) // правый поворот вокруг p
	{
		Node<T>* q = p->getLeft();
		p->setLeft(q->getLeft());
		q->setRight(p);

		if (p == Tree<T>::root) Tree<T>::root = q;
		else
		{
			p->getParent()->getData() > p->getData() ? p->getParent()->setLeft(q) : p->getParent()->setRight(q);
		}
		if(p->getLeft() != NULL) p->getLeft()->setParent(p);
		q->setParent(p->getParent());
		p->setParent(q);
		
		fixHeight(p);
		fixHeight(q);
		return q;
	}

	Node<T>* RotateLeft(Node<T>* q) // левый поворот вокруг q
	{
		Node<T>* p = q->getRight();
		q->setRight(p->getLeft());
		p->setLeft(q);

		if (q == Tree<T>::root) Tree<T>::root = p;
		else
		{
			q->getParent()->getRight() == q ? q->getParent()->setRight(p) : q->getParent()->setLeft(p);
		}
		if (q->getLeft() != NULL) q->getRight()->setParent(q);
		p->setParent(q->getParent());
		q->setParent(p);

		fixHeight(q);
		fixHeight(p);
		return p;
	}

	//балансировка поддерева узла p - вызов нужных поворотов в зависимости от показателя баланса
	Node<T>* Balance(Node<T>* p) // балансировка узла p
	{
		fixHeight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->getRight())<0)RotateRight(p->getRight());
			return RotateLeft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->getLeft()) > 0)RotateLeft(p->getLeft());
			return RotateRight(p);
		}

		return p; // балансировка не нужна
	}

public:
	//конструктор AVL_Tree вызывает конструктор базового класса Tree
	AVL_Tree<T>() : Tree<T>() {}

	virtual Node<T>* push_R(Node<T>* N)
	{
		return push_R(N, Tree<T>::root);
	}

	//рекуррентная функция добавления узла. Устроена аналогично, но вызывает сама себя - добавление в левое или правое поддерево
	virtual Node<T>* push_R(Node<T>* N, Node<T>* Current)
	{
		//вызываем функцию push_R из базового класса
		Node<T>* pushedNode = Tree<T>::push_R(N, Current);
		//применяем к добавленному узлу балансировку
		if (Current != NULL)
			return Balance(Current);
		return pushedNode;
	}

	//функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
	virtual Node<T>* push(T n)
	{
		Node<T>* N = new Node<T>;
		N->setData(n);
		return push_R(N);
	}

	//удаление узла (с учетом балансировки)
	virtual void Remove(Node<T>* N)
	{ }
};

int main()
{
	AVL_Tree<double> T;
	int arr[15];
	int i = 0;
	for (i = 0; i < 15; i++) arr[i] = (int)(100 * cos(15 * double(i)));
	for (i = 0; i < 15; i++) T.push(arr[i]);

	Node<double>* M = T.Min();
	cout << "\nMin = " << M->getData() << "\tFind " << arr[3] << ": " << T.Find(arr[3]);
	//Node<double>* node_52 = T.Find(arr[3]);
	//cout << "\nSuccessor(52) = " << *(node_52->successor());
	//cout << "\n52 = " << *(node_52->successor()->predecessor());
	/*while (M != NULL)
	{
		cout << *M; M = M->successor();
	}
	M = T.Max();
	cout << "\n-----\n";
	while (M != NULL)
	{
		cout << *M; M = M->predecessor();
	}*/

	void (*f_ptr)(Node<double>*); f_ptr = print;
	/*cout << "\n-----\nPreorder:";
	T.PreOrder(T.getRoot(), f_ptr);*/
	cout << "\n-----\nInorder:";
	T.InOrder(T.getRoot(), f_ptr);
	/*cout << "\n-----\nPostorder:";
	T.PostOrder(T.getRoot(), f_ptr);*/


	char c; cin >> c;
	return 0;
}