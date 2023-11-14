#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace MyExcel
{
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

	// stack ��ü ����
	class Stack
	{
		struct Node
		{
			Node* prev;
			std::string s;

			Node(Node* prev, std::string s) : prev(prev), s(s) {}
		};

		Node* current; //���� �ֻ��� ���
		Node start; //������ ��� 

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

		// �����͸� �����ϴ� ���̺�
		// Cell*�� �����ϴ� 2���� �迭 
		Cell*** data_table;

	public:
		Table(int max_row_size, int max_col_size);
		~Table();

		// ���ο� ���� ���
		void reg_cell(Cell* c, int row, int col);

		//�ش� ���� �������� ��ȯ
		int to_numeric(const std::string& s);
		//�� �� �� ��ȣ�� ���� ȣ��
		int to_numeric(int row, int col);

		//�ش� ���� ���ڿ��� ��ȯ
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
