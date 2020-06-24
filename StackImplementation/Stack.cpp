#include <iostream>
#include "Stack.h"


template<class T>
StackNode<T>::StackNode(const T & _data, StackNode<T>* _next) : data(_data), next(_next)
{}


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

			else
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
Stack<T>& Stack<T>::operator = (const Stack<T>& other)
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
	StackNode<T>* toAdd = new StackNode<T>(_data, topOfStack);
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
	if (topOfStack) 
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
T Stack<T>::top() const 
{
	if (empty())
	{
		std::cout << "Empty Stack!\n";
	}

	return topOfStack->data;
}


template<class T>
size_t Stack<T>::size() const 
{
	return curSize;
}


template<class T>
bool Stack<T>::empty() const 
{
	return topOfStack == nullptr;
}