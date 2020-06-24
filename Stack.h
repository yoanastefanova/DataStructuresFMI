#pragma once
#pragma once

template<typename T>


class Stack
{

public:
	Stack()
	{
		top = 0;
		size = 0;
	}

	Stack(const Stack &other)
	{
		copy(other);
	}

	Stack &operator=(const Stack &other)
	{
		if (this != &other)
		{
			destroy();
			copy(other);
		}

		return *this;
	}

	~Stack()
	{
		destroy();
	}


	void push(const T& _newEl)
	{
		top = new Node(_newEl, top);
		++size;
	}


	T pop()
	{
		if (isEmpty())
		{
			std::cout << "Stack is empty!\n";
			return;
		}

		Node* temp = top;
		top = top->next;
		T el = temp->data;
		delete temp;
		return el;
	}



	bool isEmpty()
	{
		size == 0;
	}

private:

	struct Node
	{
		T data;
		Node* next;
		Node(const T& _data, Node* _next = nullptr) : data(_data), next(_next)
		{}
	};

	void destroy()
	{
		Node* temp;

		while (top)
		{
			temp = top;
			top = temp->next;
			delete temp;
		}

		size = 0;
		top = nullptr;
	}

	void copy(const Stack &other)
	{
		if (other.isEmpty())
			return;

		Node *temp1, *temp2;


		top = new Node(other.top->data);
		temp1 = top;
		temp2 = other.top->next;

		while (temp2)
		{
			temp1->next = new Node(temp2->data);
			temp1 = temp1->next;
			temp2 = temp2->next;
		}

		size = other.size;
	}

private:

	Node* top;
	size_t size;
};


