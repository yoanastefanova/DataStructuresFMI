#pragma once



template<class T>
struct StackNode 
{
	T data;
	StackNode<T>* next;
	StackNode(const T& _data, StackNode<T>* = nullptr);
};



template<class T>
class Stack 
{
private:

	StackNode<T>* topOfStack;
	StackNode<T>* last;
	size_t curSize;
	void copy(const Stack<T> &other);
	void destroy();
public:
	Stack();
	Stack(const Stack<T> &other);
	~Stack();
	Stack<T>& operator=(const Stack<T> &other);
	void push(const T &_data);
	void pop();
	T top() const;
	bool empty() const;
	size_t size() const;

};