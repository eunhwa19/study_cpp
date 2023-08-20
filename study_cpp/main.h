#pragma once
#include <string>
#include <iostream>

// Vector ��ü ����
class Vector
{
	std::string* data; //������ ����
	int capacity; // ���� �Ҵ�� ũ�� 
	int length; // ���� ������ ����ϴ� ��

public:
	Vector(int n = 1); //������

	void push_back(std::string s); // �� ���� �߰�
	std::string operator[](int i); // i��° ���ҿ� ����
	void remove(int x); // x��° ��ġ�� ���� ����
	int size(); // ���� ũ��

	~Vector(); //�Ҹ���
};

void Vector::push_back(std::string s)
{
	if (capacity <= length) //�Ҵ�� ũ�Ⱑ ���� ����ϴ� �纸�� ������
	{
		std::string* temp = new std::string[capacity * 2]; // ���� ũ���� �� ���� ���ο� string ����
		for (int i = 0; i < length; i++) 
		{
			temp[i] = data[i]; // data�� �ִ� ���Ҹ� �״�� temp�� �������
		}
		delete[] data; 
		data = temp;
		capacity = capacity * 2;
	}

	data[length] = s;
	length++;
}

std::string Vector::operator[](int i) 
{ 
	return data[i]; 
}

void Vector::remove(int x)
{
	for (int i = x + 1; i < length; i++)
	{
		data[i - 1] = data[i];
	}
	length--;
}

int Vector::size()
{
	return length;
}

Vector::~Vector()
{
	if (data)
	{
		delete[] data;
	}
}

// stack ��ü ����
class Stack 
{
	struct Node
	{

		Node* prev;
		std::string s;

		Node(Node* prev, std::string s) : prev(prev), s(s) {}
	};

	Node* current;
	Node start;

public:
	Stack(); 

	void push(std::string s);
	std::string pop();
	std::string peek();
	bool is_empty();

	~Stack();
};

Stack::Stack() : start(NULL, "") 
{ 
	current = &start; 
}

void Stack::push(std::string s)
{
	Node* n = new Node(current, s);
	current = n;
}

std::string Stack::pop()
{	
	if (current == &start) 
		return "";

	std::string s = current->s;
	Node* prev = current;
	current = current->prev;

	delete prev;
	return s;
}

std::string Stack::peek()
{
	return current->s;
}

bool Stack::is_empty()
{
	if (current == &start) return true;
	return false;
}

Stack::~Stack()
{
	while (current != &start)
	{
		Node* prev = current;
		current = current->prev;
		delete prev;
	}
}

// ������ ���� ����� (��ó : https://modoocode.com/217)
