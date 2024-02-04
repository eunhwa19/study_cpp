#include "main.h"

#include <iostream>

//1.6.3 �ǽ� ���� 1: ���� ������ �����ϱ�
// 1. �ϴ� �⺻ �����̳ʸ� ����� 
// 2. ���� ������ ǥ�� -> ������ ���� ������ ù ��° ���Ұ� �;���. 
// 3. next(), previous(), printall(), insert(), remove() �Լ� �ʿ�
// 4. �ݺ��� �ۼ� (begin(), end() ����) 

template <typename T>
struct cir_list_node
{
	T* data; 
	cir_list_node* next; 
	cir_list_node* prev;

	~cir_list_node()
	{
		delete data;
	}
};

template <typename T>
class cir_list
{
public:
	using node = cir_list_node<T>;
	using node_ptr = node*;

	cir_list() : n(0)
	{
		head = new node{ NULL, NULL, NULL }; // ��� NULL�� ������ ���� ���
		head->next = head;
		head->prev = head;
	}

	size_t size() const
	{
		return n;
	}

	void insert(const T& value) //insert beginning
	{
		node_ptr newNode = new node{ new T(value), NULL, NULL };
		n++;
		auto dummy = head->prev; 
		dummy->next = newNode; 
		newNode->prev = dummy; 

		if (head == dummy)
		{
			dummy->prev = newNode;
			newNode->next = dummy;
			head = newNode;
			return;
		}

		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}

	void erase(const T& value)
	{
		auto cur = head, dummy = head->prev;
		while (cur != dummy)
		{
			if (*(cur->data) == value)
			{
				cur->prev->next = cur->next;
				cur->next->next = cur->prev;

				if (cur == head)
					head = head->next;
				delete cur;
				n--;
				return;
			}
			cur = cur->next;
		}
	}

	struct cir_list_iterator
	{
	private:
		node_ptr ptr;
	public:
		cir_list_iterator(node_ptr p) : ptr(p) {} //������

		T& operator*()
		{
			return *(ptr->data);
		}

		node_ptr get()
		{
			return ptr;
		}

		cir_list_iterator& operator++()
		{
			ptr = ptr->next;
			return *this;
		}

		cir_list_iterator& operator++(int)
		{
			cir_list_iterator it = *this;
			++(*this);
			return it;
		}

		cir_list_iterator& operator--()
		{
			ptr = ptr->prev;
			return *this;
		}

		cir_list_iterator& operator--(int)
		{
			cir_list_iterator it = *this;
			--(*this);
			return it;
		}

		friend bool operator==(const cir_list_iterator& it1, const cir_list_iterator& it2)
		{
			return it1.ptr == it2.ptr;
		}

		friend bool operator!=(const cir_list_iterator& it1, const cir_list_iterator& it2)
		{
			return it1.ptr != it2.ptr;
		}

	};

	cir_list_iterator begin() { return cir_list_iterator{ head }; }
	cir_list_iterator begin() const { return cir_list_iterator{ head }; }
	cir_list_iterator end() { return cir_list_iterator{ head->prev }; }
	cir_list_iterator end() const { return cir_list_iterator{ head->prev }; }

	cir_list(const cir_list<T>& other) : cir_list()
	{
		for (const auto& i : other) //�������� ���������� ���� ����Ʈ�� ���� ����
			insert(i);
	}

	cir_list(const std::initializer_list<T>& il) : head(NULL), n(0)
	{
		for (const auto& i : other)
			insert(i);
	}

	~cir_list()
	{
		while (size())
		{
			erase(*(head->data));
		}

		delete head;
	}

private:
	node_ptr head;
	size_t n;
};

struct playlist
{
	cir_list<int> list;

	void insert(int song)
	{
		list.insert(song);
	}

	void erase(int song)
	{
		list.erase(song);
	}

	void loopOnce()
	{
		for (auto& song : list)
			std::cout << song << " ";
		std::cout << std::endl;
	}
};

int main()
{
	playlist pl;
	pl.insert(1);
	pl.insert(2);
	std::cout << "��� ��� : ";
	pl.loopOnce();

	playlist pl2 = pl;
	pl2.erase(2);
	pl2.insert(3);
	std::cout << "�� ��° ������ : ";
	pl2.loopOnce();
}

/*
//1.6.2 ���� ���� 5: �⺻���� ����� ���� �����̳� �����
struct singly_ll_node
{
	int data;
	singly_ll_node* next;
};

class singly_ll
{
public:
	using node = singly_ll_node;
	using node_ptr = node*;

	void push_front(int val)
	{
		auto new_node = new node{ val, NULL };
		if (head != NULL)
			new_node->next = head;
		head = new_node;
	}

	void pop_front()
	{
		auto first = head;
		if (head)
		{
			head = head->next;
			delete first;
		}
	}

	//�⺻ �ݺ���
	struct singly_ll_iterator
	{
	private:
		node_ptr ptr;

	public:
		singly_ll_iterator(node_ptr p) : ptr(p) {} //������

		int& operator*() { return ptr->data; } //������

		node_ptr get() { return ptr; }

		singly_ll_iterator& operator++()
		{
			ptr = ptr->next;
			return *this;
		}

		singly_ll_iterator& operator++(int)
		{
			singly_ll_iterator result = *this;
			++(*this);
			return result;
		}

		friend bool operator==(const singly_ll_iterator& left, const singly_ll_iterator& right)
		{
			return left.ptr == right.ptr;
		}

		friend bool operator!=(const singly_ll_iterator& left, const singly_ll_iterator& right)
		{
			return left.ptr != right.ptr;
		}

	};

	singly_ll_iterator begin() { return singly_ll_iterator(head); }
	singly_ll_iterator end() { return singly_ll_iterator(NULL); }
	singly_ll_iterator begin() const { return singly_ll_iterator(head); }
	singly_ll_iterator end() const { return singly_ll_iterator(NULL); }

	singly_ll() = default; //������

	singly_ll(const singly_ll& other) : head(NULL)
	{
		if (other.head)
		{
			head = new node{ 0, NULL };
			auto cur = head;
			auto it = other.begin();
			while (true)
			{
				cur->data = *it;

				auto tmp = it;
				++tmp;
				if (tmp == other.end())
					break;

				cur->next = new node{ 0, NULL };
				cur = cur->next;
				it = tmp;
			}
		}
	}

	singly_ll(const std::initializer_list<int>& ilist) : head(NULL)
	{
		for (auto it = std::rbegin(ilist); it != std::rend(ilist); it++)
			push_front(*it);
	}

private:
	node_ptr head;
};

int main()
{
	singly_ll sll = { 1, 2, 3 };
	sll.push_front(0); //0, 1, 2, 3

	std::cout << "ù ��° ����Ʈ : ";
	for (auto i : sll)
		std::cout << i << " ";
	std::cout << std::endl;

	auto sll2 = sll; //���� ���� 
	sll2.push_front(-1); // -1, 0, 1, 2, 3
	std::cout << "ù ��° ����Ʈ�� ������ ��, �� �տ� -1�� �߰�: ";
	for (auto i : sll2)
		std::cout << i << ' ';
	std::cout << std::endl;

	std::cout << "���� ���� �� ù ��° ����Ʈ: ";

	for (auto i : sll) //0, 1, 2, 3 
		std::cout << i << ' ';
	std::cout << std::endl;

}
*/

/*
//1.6.4 ���� ���� 4: �پ��� �ݺ��ڿ��� �̵��ϱ�
// - ���� �ݺ��ڸ� ����Ͽ� �����ͷκ��� ������ ������ �˻�
int main()
{
	std::vector<std::string> vec = {
		"Lewis Hamilton", "Lewis Hamilton", "Nico Roseberg",
		"Sebastian Vettel", "Lewis Hamilton", "Sebastian Vettel",
		"Sebastian Vettel", "Sebastian Vettel", "Fernando Alonso"
	};

	auto it = vec.begin(); //��� �ð�
	std::cout << "���� �ֱ� �����: " << *it << std::endl;
	
	it += 8;
	std::cout << "8�� �� �����: " << *it << std::endl;

	advance(it, -3); //��� �ð�
	std::cout << "�� �� 3�� �� �����: " << *it << std::endl;

	std::forward_list<std::string> fwd(vec.begin(), vec.end());

	auto it1 = fwd.begin();
	std::cout << "���� �ֱ� �����: " << *it1 << std::endl;

	advance(it1, 5);
	std::cout << "5�� �� �����: " << *it1 << std::endl;

}
*/

/*
//1.5.3 ���� ���� 3: ���� ����Ʈ���� remove_if() �Լ��� �̿��� ���Ǻ� ���� ����
// - �Ϻ� �ùε��� ������ �̿��Ͽ� ���ű��� ���� ����� ��������
struct citizen
{
	std::string name;
	int age;
};

std::ostream& operator<<(std::ostream& os, const citizen& c)
{
	return (os << "[" << c.name << ", " << c.age << "]");
}

int main()
{
	std::forward_list<citizen> citizens =
	{
		{"kim", 22}, {"lee", 25}, {"park", 18}, {"jin", 16}
	};

	auto citizens_copy = citizens; //deep copy

	std::cout << "��ü �ùε�: ";
	for (const auto& c : citizens)
		std::cout << c << " ";
	std::cout << std::endl;

	citizens.remove_if([](const citizen &c) //���� ǥ����
	{
		return (c.age < 19);
	});

	std::cout << "��ǥ���� �ִ� �ùε�: ";
	for (const auto& c : citizens)
		std::cout << c << " ";
	std::cout << std::endl;

	citizens_copy.remove_if([](const citizen& c)
	{
		return (c.age != 18);
	});

	std::cout << "���⿡ ��ǥ���� ����� �ùε�: ";
	for (const auto& c : citizens_copy)
		std::cout << c << " ";
	std::cout << std::endl;
}
*/

/*
//1.3.2 ���� ����2: ������ �������� ������ ���� �����̳� �����
template<typename ... Args> //���� ���ø� //�� �� ���� ���� ����
auto build_array(Args&&... args)->std::array<typename std::common_type<Args...>::type, sizeof...(args)>
{
	using commonType = typename std::common_type<Args...>::type;
	return { std::forward<commonType>((Args&&)args)... };
}

int main()
{
	auto data = build_array(1, 0u, 'a', 3.2f, false);
	//auto data2 = build_array(1, "Packet", 2.0); //���ڿ��� ���ڸ� ��� ǥ���� �� �ִ� ���� �ڷ����� ����.

	for (auto i : data)
		std::cout << i << " ";
	std::cout << std::endl;
}
*/

/*
//1.3.1 ���� ����1: ���� ũ�� �迭 �����ϱ� - �л� ���� ���� ���α׷�
template <typename T>
class dynamic_array
{
	T* data;
	size_t n; 

public: 
	dynamic_array(int n) //������
	{
		this->n = n;
		data = new T[n];
	}

	dynamic_array(const dynamic_array<T>& other) //���� ������ 
	{
		n = other.n;
		data = new T[n];

		for (int i = 0; i < n; i++)
			data[i] = other[i];
	}

	T& operator[](int index)
	{
		return data[index];
	}

	const T& operator[](int index) const
	{
		return data[index];
	}

	T& at(int index)
	{
		if (index < n)
			return data[index];
		throw "Index out of range";
	}

	size_t size() const
	{
		return n;
	}

	~dynamic_array()
	{
		delete[] data;
	}
	
	T* begin() { return data; }
	const T* begin() const { return data; }
	T* end() { return data + n; }
	const T* end() const { return data + n; }

	friend dynamic_array<T> operator+(const dynamic_array<T>& arr1, dynamic_array<T>& arr2)
	{
		dynamic_array<T> result(arr1.size() + arr2.size());
		std::copy(arr1.begin(), arr1.end(), result.begin());
		std::copy(arr2.begin(), arr2.end(), result.begin() + arr1.size());

		return result;
	}

	std::string to_string(const std::string& sep = ", ")
	{
		if (n == 0)
			return "";

		std::ostringstream os;
		os << data[0];

		for (int i = 1; i < n; i++)
			os << sep << data[i];

		return os.str();
	}

	
};

struct student
{
	std::string name;
	int standard; //�б�
};

std::ostream& operator<<(std::ostream& os, const student& s)
{
	return (os << "[" << s.name << ", " << s.standard << "]");
}

int main()
{
	int nStudents;
	std::cout << "1�� �л� ���� �Է��ϼ���: ";
	std::cin >> nStudents;

	dynamic_array<student> class1(nStudents);
	for (int i = 0; i < nStudents; i++)
	{
		std::string name;
		int standard;
		std::cout << i + 1 << "��° �л��� �̸��� ���̸� �Է��ϼ���: ";
		std::cin >> name >> standard;
		class1[i] = student{ name, standard };
	}

	try
	{
		class1.at(nStudents) = student{ "John", 8 };
	}
	catch (...)
	{
		std::cout << "���� �߻�!" << std::endl;
	}

	//deep copy
	auto class2 = class1;
	std::cout << "1���� ���翡�� 2�� ����: " << class2.to_string() << std::endl;

	//�� �б��� ���ļ� ���ο� ū �б��� ����
	auto class3 = class1 + class2;
	std::cout << "1�ݰ� 2���� ���ļ� 3�� ����: " << class3.to_string() << std::endl;

	return 0;
}
*/
