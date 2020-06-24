#pragma once
#include <iostream>

class DLL
{
	struct Node
	{

		Node() : next(nullptr), prev(nullptr)
		{}

		Node(const int _data, Node *_next, Node *_prev)
			: data(_data), next(_next), prev(_prev)
		{}
	
		Node *next, *prev;
		int data;

	} *first, *last;


public:

	void insertFront(int _data)
	{
		Node *newNode = new Node(_data, first, nullptr);

		//first = new Node(_data, first, nullptr);

		if (first->next)
		{
			first->prev = newNode;
			//first->next->prev = first;
		}

		else
			first = newNode;
			//last = first;
	}

	void insertLast(int _data)
	{
		last = new Node(_data, nullptr, last);

		if (last->prev)
		{
			last->prev->next = last;
		}

		else
			first = last;
	}

	void insertAfter(Node *prevBox, int _data)
	{
		if (prevBox == nullptr)
		{
			std::cout << "Previous node is required!\n";
		}

		Node *newNode = new Node(_data, prevBox->next, prevBox);//data, next, prev
		/* 
		 next �� newNode �� ���� ��� �������, ��� ����� � ������ next �� �������, ���� ����� ������ �� �������
		 prev �� newNode �� ���� ��� �������, ���� ����� ������ �� �������
		*/
		prevBox->next = newNode;//���� next �� �������, ���� ����� ������ �� ������� ���� ��� ������

		if (newNode->next != nullptr)
		{
			newNode->next->prev = newNode; //��� �������, ���� ����� ������ �� �������, �� � ����������, prev �� ���� ���� newNode ������ �� ���� ��� newNode
		}
	}

	void remove(Node *del)
	{
		if (del->next)
		{
			del->next->prev = del->prev;
		}

		else
			last = del->prev;

		if (del->prev)
		{
			del->prev->next = del->next;
		}

		else
			first = del->next;
	}


	void display()
	{
		Node* temp;
		temp = first;

		while (temp != nullptr)
		{
			std::cout << temp->data << " ";
			temp = temp->next;
		}
	}
};