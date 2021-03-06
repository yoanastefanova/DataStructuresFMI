#pragma once
#include "pch.h"
#include <iostream>
#include <fstream>



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


	void push(const T _newEl)
	{
		/*
		Node* temp = new Node;
		temp->data = _newEl;

		if (isEmpty())
		{
			top = temp;
			temp->next = nullptr;
		}

		else
		{
			temp->next = top;
			top = temp;
		}
		*/
		top = new Node(_newEl, top);
		++size;
	}


	void pop()
	{
		/*
		if (isEmpty())
		{
			std::cout << "Stack is empty!\n";			
		}
		*/

		if (top)
		{
			Node* temp = top;
			top = top->next;
			delete temp;
			--size;
		}
	}

	T& topStack()
	{
		/*
		if (isEmpty())
			return ;
			std::cout<<"Stack is empty!\n";
			*/

		if(top)
			return top->data;
	}

	const size_t getSize() const
	{
		return size;
	}

	void print() 
	{
		if (isEmpty())
			return;

		Node* temp = top;
		while (temp)
		{
			std::cout << temp->data <<" ";
			temp = temp->next;
		}

		std::cout << '\n';
	}

	bool isEmpty() const
	{
		return size == 0;
	}

private:

	struct Node
	{
		T data;
		Node* next;
		Node(const T& _data, Node* _next = nullptr) 
		{
			data = _data;
			next = _next;
		}
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
		top = 0;
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



bool areBalanced(char* arr)
{
	bool flag = true;
	Stack<char> temp;
	char x;
	//fromFileToArr(comp, arr);

	int len = strlen(arr);


	for (int i = 0; i < len; ++i)
	{
		if (arr[i] == ')' && arr[i-1] != '\\')
		{
			temp.push(arr[i]);
			continue;
		}

		else if (arr[i] == '(' && arr[i-1] != '\\')
		{
			x = temp.topStack();
			temp.pop();
			if (x == '(')
			{
				flag = false;
			}
		}

		else if (!temp.isEmpty())
		{
			flag = false;
		}

		else
			temp.pop();
	}

	return flag;

	/*
	---------only with stack

	while (!_st.isEmpty())
	{
		T tempEl = _st.top();

		if (tempEl == '(')//
		{
			temp.push(tempEl);
			temp.pop();
		}

		else if (tempEl == ')')
		{
			x = temp.top();
			temp.pop();
			if (x != '(')
			{
				flag = false;
			}
		}

		else
			temp.pop();
	}

	return flag;
	*/
}


bool balancedQuotes(char* arr)
{
	int len = strlen(arr);
	int counter = 0;

	for (int i = 0; i < len; i++)
	{
		if (arr[i] == '\"' && arr[i - 1] != '\\')
		{
			counter++;
		}
	}

	if (counter % 2 != 1)
	{
		return true;
	}

	else
		return false;
}


void inputNames()
{
	std::cout << "Input name of compressed file: ";
	char* comp = new char[30];
	std::cin>>comp;

	std::cout << "Input name of decompressed file: ";
	char* decomp = new char[30];
	std::cin >> decomp;
}


//информацията от компресирания файл се вкарва в масив
void fromFileToArr(const char* comp, char* arr)//, Stack<char> st)
{	
	std::ifstream file1(comp);

	size_t j = 0;

	if (file1)
	{
		while (file1)//>>arr[i])
		{
			arr[j] = file1.get();//всеки символ от низа се записва в масива 123---->123
			j++;//минава на следващата позиция в масива
		}
	}

	file1.close();	
}

void fromStackToArr(Stack<char> st, char* arr)
{
	size_t i = 0;

	while (!st.isEmpty())
	{
		arr[i] = st.topStack();//всяка позиция на масива се попълва с най-горния елемент от стека
		st.pop();
		++i;//минава на следващата позиция в масива
	}
}

void fromArrToStack(char* arr, Stack<char> st)
{
	size_t len = strlen(arr);

	for (size_t i = 0; i < len; ++i)//обикаля масива
	{
		st.push(arr[i]);//записва всеки елемент от масива в стека 123 ----> 321
		//file1.get(arr[i]);
		//ch = file1.get();
		//st.push(ch);
	}
}

bool isLetter(char el)
{
	if ((el >= 'a' && el <= 'z') || (el >= 'A' && el <= 'Z'))
	{
		return true;
	}

	return false;
}

bool isNum(char el)
{

	if (el >= 1 && el <= 9)
	{
		return true;
	}

	return false;
}

bool isOperator(char el)
{
	if (isNum(el) || (el == '\"') || (el == '\\'))
	{
		return true;
	}

	return false;
}

size_t getPriority(char el)
{
	if (isNum(el))
	{
		return 1;
	}

	if (el == ')')
	{
		return 2;
	}

	if (el == '(')
	{
		return 3;
	}

	if (el == '\"')
	{
		return 4;
	}

	if (el == '\\')
	{
		return 5;
	}

	else
		return 0;
}

void addElementToArr(const char el, char* arr)
{
	int len = strlen(arr) - 1;

	for (int i = len; i > 0; ++i)
	{
		arr[i] = arr[i - 1];
	}
}

bool isValid(char* arr)
{
	int len = strlen(arr) - 1;

	bool bracket = (arr[len] == '(' && arr[len - 1] != '\\');
	bool slash = (arr[len] == '\\' && arr[len - 1] != '\\');
	bool num = (isNum(arr[len]) && arr[len - 1] != '\\');

	if(bracket || slash || num)
	{
		return false;
	}

	else 
		return true;
}

void decode(char* arr, char* arrPrint)
{
	Stack<char> st1;
	int len = strlen(arr);
	int lenPrint = strlen(arrPrint);


	if (isValid(arr))
	{
		for (int i = len; i >= 0; --i)
		{
			if (arr[i] == ')')
			{
				st1.push(arr[i]);
			}

			else if (arr[i] == '\"')
			{
				for (int j = i - 1; j >= 0; --j)
				{
					if (arr[j] == '\"' && arr[j - 1] != '\\')
					{
						st1.push(arr[i]);
					}

					else
						std::cout << "Invalid input!\n";
				}
			}

			if (st1.topStack() == '\"')
			{
				while (arr[i] != '\"' && arr[i - 1] != '\\')//докато не срещнем вторите кавички и ако пред тях няма '\'
				{
					addElementToArr(arr[i], arrPrint);//елементите между кавичките се добавят в масива с резултата
					++i;
				}

				st1.pop();// махаме кавичките от стека, след като вече сме ги използвали
			}

			else if (isLetter(arr[i]))
			{
				addElementToArr(arr[i], arrPrint);
			}

			else if (isNum(arr[i]) && arr[i + 1] == '(')
			{
				int tempLen = lenPrint;
				int num = arr[i] - '0';

				for (int i = 0; i < num; ++i)
				{
					for (int j = 0; j < tempLen; ++j)
					{
						addElementToArr(arrPrint[j], arrPrint);
					}
				}
			}

			if (arr[i] != '\\' && arr[i - 1] == '\\')
			{
				addElementToArr(arr[i], arrPrint);
			}

			else if (arr[i] == '(')
			{
				st1.pop();
			}
		}
	}

	else
		std::cout << "Invalid input!\n";
}


/*
//-------------- 2(ab\") ----> ab"ab"

if (isNum(st1.top()))
{
	char temp = st1.top();
	size_t len = strlen(arrTemp);
	for (size_t i = 0; i < temp; ++i)
	{
		for (size_t j = 0; j < len; ++j)
		{
			st2.push(arrTemp[j]);
		}
	}
}
*/


int main()//int argc, char* argv[])
{
	/*
	std::ifstream in(argv[1]);
	std::ofstream out(argv[2]);
	char arr[100];
	char arr1[200];
	char ch;
	int length = strlen(arr1);

	while (in.get(ch))
	{
		if (in.eof()) break;
		addElementToArr(ch, arr);
	}

	for (int i = 0; i < length; ++i)
	{
		char temp = arr[i];
		out << temp;
	}
	*/


	Stack<int> s;
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	s.push(5);

	
	s.print();
	s.pop();

	Stack<char> s1;
	
	s1.push(')');
	s1.push(')');
	s1.push(')');
	s1.push('(');
	s1.push('(');
	s1.push('(');

	s1.print();

	char temp[20];

	fromStackToArr(s1, temp);


	//std::cout << areBalanced(temp);


	Stack<char> s2;
	s1.push('a');
	s1.push('b');
	s1.push('c');
	s1.push('d');

	

	
    return 0; 
}

	