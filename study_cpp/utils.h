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

		Node* current; //현재 최상위 노드
		Node start; //최하위 노드 

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

	class Table
	{
	protected:
		int max_row_size, max_col_size;

		// 데이터를 보관하는 테이블
		// Cell*을 보관하는 2차원 배열 
		Cell*** data_table;

	public:
		Table(int max_row_size, int max_col_size);
		~Table();

		// 새로운 셀을 등록
		void reg_cell(Cell* c, int row, int col);

		//해당 셀의 정수값을 반환
		int to_numeric(const std::string& s);
		//행 및 열 번호로 셀을 호출
		int to_numeric(int row, int col);

		//해당 셀의 문자열을 반환
		std::string stringify(const std::string& s);
		std::string stringify(int row, int col);

		virtual std::string print_table() = 0;
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
