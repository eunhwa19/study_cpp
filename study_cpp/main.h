#pragma once
#include <string>
#include <iostream>

// Vector 자체 제작
class Vector
{
	std::string* data; //데이터 보관
	int capacity; // 현재 할당된 크기 
	int length; // 현제 실제로 사용하는 양

public:
	Vector(int n = 1); //생성자

	void push_back(std::string s); // 새 원소 추가
	std::string operator[](int i); // i번째 원소에 접근
	void remove(int x); // x번째 위치한 원소 제거
	int size(); // 벡터 크기

	~Vector(); //소멸자
};

void Vector::push_back(std::string s)
{
	if (capacity <= length) //할당된 크기가 실제 사용하는 양보다 작으면
	{
		std::string* temp = new std::string[capacity * 2]; // 원래 크기의 두 배인 새로운 string 생성
		for (int i = 0; i < length; i++) 
		{
			temp[i] = data[i]; // data에 있는 원소를 그대로 temp에 집어넣음
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

// stack 자체 제작
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

// 간단한 엑셀 만들기 (출처 : https://modoocode.com/217)
