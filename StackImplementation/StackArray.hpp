#include<assert.h>
#include <iostream>

template<typename T>
class ArrStack
{
private:
	int size, capacity;
	T *arr;
	void copy(const ArrStack& other)
	{
		size = other.size;
		capacity = other.capacity;
		arr = new T[capacity];
		for (int i = 0; i < size; ++i)
		{
			arr[i] = other.arr[i];
		}
	}

	void destroy()
	{
		delete[] arr;
	}

	void extend()
	{
		T* temp = arr;
		capacity *= 2;
		arr = new T[capacity];
		for (int i = 0; i < size; ++i)
		{
			arr[i] = temp[i];
		}
		delete[] temp;
	}

	void downsize()
	{
		T* temp = arr;
		capacity /= 2;
		arr = new T[capacity];
		for (int i = 0; i < size; ++i)
		{
			arr[i] = temp[i];
		}

		delete[] temp;
	}
public:

	ArrStack(unsigned _capacity = 4) : capacity(_capacity), size(0)
	{
		assert(capacity > 0);
		arr = new T[capacity];
	}

	ArrStack(const ArrStack& other)
	{
		copy(other);
	}

	ArrStack& operator=(const ArrStack& other)
	{
		if (this != &other)
		{
			destroy();
			copy(other);
		}

		return *this;
	}

	~ArrStack()
	{
		destroy();
	}

	void push(const T& element)
	{
		if (size == capacity)
		{
			extend();
		}

		arr[size++] = element;
	}

	T top() const
	{
		assert(size);
		return arr[size - 1];
	}

	void pop()
	{
		assert(size);
		if (size < capacity / 4)
		{
			downsize();
		}
		size--;
	}

	bool empty()
	{
		return !size;
	}

	void toString(char* compr) 
	{
		ArrStack<char> temp;
		
		for (int i = 0; i < size; ++i)
		{
			temp.push(top());
			pop();
		}

		int j = 0;

		for (j; j < temp.size; ++j)
		{
			compr[j] = temp.top();
			temp.pop();
		}

		compr[j] = '\0';
	}

};