#pragma once
#include <iostream>

struct Node
{
	int data;
	Node *next;
};

class LinkedList
{
private:
	Node *head, *tail;

public:

	LinkedList()
	{
		head = nullptr;
		tail = nullptr;
	}

	void create(int _data)
	{
		Node *temp = new Node;
		temp->data = _data;
		temp->next = nullptr;

		if (head == nullptr)
		{
			head = temp;
			tail = temp;
			temp = nullptr; 
		}

		else
		{
			tail->next = temp;
			tail = temp;
		}
	}


	void display()
	{
		Node *temp = new Node;
		temp = head;

		while (temp != nullptr)
		{
			std::cout << temp->data << '\n';
			temp = temp->next;
		}
	}

	void insertFront(int _data)
	{
		Node *temp = new Node;
		temp->data = _data;
		temp->next = head;
		head = temp;
	}


	void insertPosition(int pos, int _data)
	{
		Node *prev = new Node;
		Node *cur = new Node;
		Node *temp = new Node;
		cur = head;

		for (int i = 1; i < pos; ++i)
		{
			prev = cur;
			cur = cur->next;
		}

		temp->data = _data;
		prev->next = temp;
		temp->next = cur;
	}

	// insertEnd би било същото като create

	void deleteFirst()
	{
		Node *temp = new Node;
		temp = head;
		head = head->next;
		delete temp;
	}

	void deleteLast()
	{
		Node *cur = new Node;
		Node *prev = new Node;
		cur = head;

		while (cur != nullptr)
		{
			prev = cur;
			cur = cur->next;
		}

		tail = prev;
		prev->next = nullptr;
		delete cur;
	}

	void deletePos(int pos)
	{
		Node *cur = new Node;
		Node *prev = new Node;
		cur = head;

		for (int i = 0; i < pos; ++i)
		{
			prev = cur;
			cur = cur->next;
		}

		prev->next = cur->next;
	}


};