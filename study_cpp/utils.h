#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace MyExcel
{
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

	class NumStack
	{
		struct Node
		{
			Node* prev;
			double s;

			Node(Node* prev, double s) : prev(prev), s(s) {}
		};

		Node* current;
		Node start;

	public: 
		NumStack();
		void push(double s);
		double pop();
		double peek();
		bool is_empty();

		~NumStack();
	};

	class Cell
	{
	protected:
		int x, y;
		Table* table;

		std::string data;

	public:
		virtual std::string stringify();
		virtual int to_numeric();

		Cell(std::string data, int x, int y, Table* table);
	};
}

#endif 
