#include <cassert>
#include <iostream>

//#include "Stack.h"


template<class T>
struct StackNode
{
	T data;
	StackNode<T>* next;
	StackNode(const T&, StackNode<T>* = nullptr);
	StackNode();
};



template<class T>
class Stack
{
public:
	Stack();
	Stack(const Stack<T> &other);
	~Stack();
	Stack<T>& operator=(const Stack<T> &other);
	void push(const T &_data);
	void pop();
	T top();
	bool empty() const;
	size_t size() const;

private:

	StackNode<T>* topOfStack;
	StackNode<T>* last;
	size_t curSize;
	void copy(const Stack<T> &other);
	void destroy();
};



template<class T>
StackNode<T>::StackNode(const T & _data, StackNode<T>* _next) : data(_data), next(_next)
{}

template<class T>
StackNode<T>::StackNode() 
{
	data = 0;
	next = NULL;
}


template<class T>
Stack<T>::Stack()
{
	topOfStack = last = nullptr;
	curSize = 0;
}

template<class T>
void Stack<T>::copy(const Stack<T> &other)
{
	topOfStack = last = nullptr;
	curSize = 0;

	if (other.topOfStack)
	{
		StackNode<T> otherIter = other.topOfStack;
		while (otherIter)
		{
			StackNode<T>* newElement = new StackNode<T>(otherIter->data);
				
			if (!topOfStack)
			{
				topOfStack = last = newElement;
			}

			
			{
				last->next = newElement;
				last = last->next;
			}

			curSize++;
			otherIter = otherIter->next;
		}
	}
}

template<class T>
void Stack<T>::destroy() 
{
	while (topOfStack)
	{
		StackNode<T>* toDelete = topOfStack;
		topOfStack = topOfStack->next;
		delete toDelete;
	}
	topOfStack = last = nullptr;
}


template<class T>
Stack<T>::Stack(const Stack<T>& other) 
{
	copy(other);
}


template<class T>
Stack<T>::~Stack() 
{
	destroy();
}



template<class T>
Stack<T>& Stack<T>::operator= (const Stack<T>& other)
{
	if (this != &other) 
	{
		destroy();
		copy(other);
	}
	return *this;
}


template<class T>
void Stack<T>::push(const T& _data) 
{
	StackNode<T>* toAdd = new StackNode<T>;
	toAdd->data = _data;
	toAdd->next = topOfStack;
	topOfStack = toAdd;

	if (curSize == 0)
	{
		last = topOfStack;
	}
	curSize++;
}


template<class T>
void Stack<T>::pop()
{
	if (empty())
	{
		std::cout << "Stack is empty!\n";
	}

	else
	{
		if (topOfStack == last) 
		{
			delete topOfStack;
			topOfStack = last = nullptr;
			return;
		}
		StackNode<T>* toDelete = topOfStack;
		topOfStack = topOfStack->next;
		delete toDelete;
		curSize--;
	}
}

template<class T>
T Stack<T>::top()  
{
	if (empty())
	{
		std::cout << "Stack is empty!\n";
	}

	else
	{
		return topOfStack->data;
		//std::cout << topOfStack->data;
	}
	/*
	T ret = topOfStack->data;

	StackNode<T>* tmp = topOfStack;
	topOfStack = topOfStack->next;

	delete tmp;
	return ret;
	*/
}


template<class T>
size_t Stack<T>::size() const 
{
	return curSize;
}


template<class T>
bool Stack<T>::empty() const 
{
	if (topOfStack == NULL)
	{
		return true;
	}

	else return false;
}
