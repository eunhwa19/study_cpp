#include "main.h"

#include <iostream>
#include <queue>

// 2.3.1 �������� 7: ȸ�� ������ ���� �����, 
struct node // binary tree
{
	std::string position;
	node* first;
	node* second;
};

struct org_tree
{
	node* root;

	//��Ʈ ���(ȸ�� ��ǥ) ����
	static org_tree create_org_structure(const std::string& pos)
	{
		org_tree tree;
		tree.root = new node{ pos, NULL, NULL };
		return tree;
	}

	static node* find(node* root, const std::string& value)
	{
		if (root == NULL)
			return NULL;

		if (root->position == value)
			return root;

		auto firstFound = org_tree::find(root->first, value);

		if (firstFound != NULL)
			return firstFound;

		return org_tree::find(root->second, value);
	}

	bool addSubordinate(const std::string& manager, const std::string& subordinate)
	{
		auto managerNode = org_tree::find(root, manager);

		if (!managerNode) //�Ŵ��� ��忡 �ƹ��͵� ������
		{
			std::cout << manager << "��(��) ã�� �� �����ϴ�: " << std::endl;
			return false;
		}

		if (managerNode->first && managerNode->second) //�ڽ� ��尡 �� ��������
		{
			std::cout << manager << " �Ʒ��� " << subordinate << "��(��) �߰��� �� �����ϴ�. " << std::endl;
			return false;
		}

		if (!managerNode->first)
			managerNode->first = new node { subordinate, NULL, NULL }; // ù ��°�� �߰� 

		else
			managerNode->second = new node { subordinate, NULL, NULL }; // �� ��°�� �߰� 

		std::cout << manager << " �Ʒ��� " << subordinate << "��(��) �߰��߽��ϴ�. " << std::endl;

		return true; // ���� �߰� ���� 
	}

	static void preOrder(node* start)
	{
		if (!start)
			return;

		std::cout << start->position << ", ";
		preOrder(start->first);
		preOrder(start->second);
	}

	static void inOrder(node* start)
	{
		if (!start)
			return;

		inOrder(start->first);
		std::cout << start->position << ", ";
		inOrder(start->second);
	}

	static void postOrder(node* start)
	{
		if (!start)
			return;

		postOrder(start->first);
		postOrder(start->second);
		std::cout << start->position << ", ";
	}

	//�������� 8: ���� ���� ��ȸ �����ϱ� 
	static void levelOrder(node* start)
	{
		if (!start)
			return;

		std::queue<node*> q;
		q.push(start);

		while (!q.empty())
		{
			int size = q.size();
			for (int i = 0; i < size; i++)
			{
				auto current = q.front();
				q.pop();

				std::cout << current->position << ", ";
				if (current->first)
					q.push(current->first);
				if (current->second)
					q.push(current->second);
			}

			std::cout << std::endl;
		}
	}
};

int main()
{
	auto tree = org_tree::create_org_structure("CEO");

	tree.addSubordinate("CEO", "�λ���");
	tree.addSubordinate("�λ���", "IT����");
	tree.addSubordinate("�λ���", "�����ú���");
	tree.addSubordinate("IT����", "��������");
	tree.addSubordinate("IT����", "�۰�������");
	tree.addSubordinate("�����ú���", "��������");
	tree.addSubordinate("�����ú���", "ȫ������");
	tree.addSubordinate("�λ���", "�繫����");

	std::cout << std::endl;

	org_tree::levelOrder(tree.root);
}

/*
//1.10.1 �ǽ� ���� 3: �繫�� ���� �������� �μ� ��� ��� �ùķ��̼�
class Job
{
private:
	int id;
	std::string user;
	int pages;

	static int count;

public:
	Job(const std::string& u, int p) : user(u), pages(p), id(++count) {}

	friend std::ostream& operator<<(std::ostream& os, const Job& j)
	{
		os << "id: " << j.id << ", �����: " << j.user << ", ������ ��: " << j.pages << "��";
		return os;
	}
};

int Job::count = 0;

template <size_t N>
class Printer
{
	std::queue<Job> jobs;

public:
	bool addNewJob(const Job& job)
	{
		if (jobs.size() == N)
		{
			std::cout << "�μ� ��⿭�� �߰� ����: " << job << std::endl;
			return false;
		}

		std::cout << "�μ� ��⿭�� �߰�: " << job << std::endl;
		jobs.push(job);
		return true;
	}

	void startPrinting()
	{
		while (!jobs.empty())
		{
			std::cout << "�μ� ��: " << jobs.front() << std::endl;
			jobs.pop();
		}
	}
};

int main()
{
	Printer<5> printer;

	Job j1("����", 10);
	Job j2("����", 4);
	Job j3("����", 5);
	Job j4("����", 7);
	Job j5("ä��", 8);
	Job j6("�ÿ�", 10);

	printer.addNewJob(j1);
	printer.addNewJob(j2);
	printer.addNewJob(j3);
	printer.addNewJob(j4);
	printer.addNewJob(j5);
	printer.addNewJob(j6);
	printer.startPrinting();

	printer.addNewJob(j6);
	printer.startPrinting();
}
*/

/*
//1.7.5 �ǽ� ���� 2: ī�� ���� �ùķ��̼� 
struct card
{
	int number;

	enum suit
	{
		HEART, SPADE, CLUB, DIAMOND
	} suit;

	std::string to_string() const
	{
		std::ostringstream os;

		if (number > 0 && number <= 10)
			os << number;
		else
		{
			switch (number)
			{
			case 1:
				os << "Ace";
				break;
			case 11:
				os << "Jack";
				break;
			case 12:
				os << "Queen";
				break;
			case 13:
				os << "King";
				break;
			default:
				return "Invalid card";
			}
		}

		os << " of ";

		switch (suit)
		{
		case HEART:
			os << "hearts";
			break;
		case SPADE:
			os << "spades";
			break;
		case CLUB:
			os << "clubs";
			break;
		case DIAMOND:
			os << "diamonds";
			break;
		}

		return os.str();
	}
};

struct game
{
	std::array<card, 52> deck;
	std::vector<card> player1, player2, player3, player4;

	void buildDeck()
	{
		for (int i = 0; i < 13; i++)
			deck[i] = card{ i + 1, card::HEART };
		for (int i = 0; i < 13; i++)
			deck[i + 13] = card{ i + 1, card::SPADE };
		for (int i = 0; i < 13; i++)
			deck[i + 26] = card{ i + 1, card::CLUB };
		for (int i = 0; i < 13; i++)
			deck[i + 39] = card{ i + 1, card::DIAMOND };
	}

	void dealCards()
	{
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
		player1 = { deck.begin(), deck.begin() + 13 };
		player2 = { deck.begin() + 13, deck.begin() + 26 };
		player3 = { deck.begin() + 26, deck.begin() + 39 };
		player4 = { deck.begin() + 39, deck.end() };
	}

	bool compareAndRemove(std::vector<card>& p1, std::vector<card>& p2)
	{
		if (p1.back().number == p2.back().number)
		{
			p1.pop_back();
			p2.pop_back();
			return true;
		}
		return false;
	}

	void playOneRound()
	{
		if (compareAndRemove(player1, player2))
		{
			compareAndRemove(player3, player4);
			return;
		}
		else if (compareAndRemove(player1, player3))
		{
			compareAndRemove(player2, player4);
			return;
		}
		else if (compareAndRemove(player1, player4))
		{
			compareAndRemove(player2, player3);
			return;
		}
		else if (compareAndRemove(player2, player3))
		{
			return;
		}
		else if (compareAndRemove(player2, player4))
		{
			return;
		}
		else if (compareAndRemove(player3, player4))
		{
			return;
		}

		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(player1.begin(), player1.end(), std::default_random_engine(seed));
		std::shuffle(player2.begin(), player2.end(), std::default_random_engine(seed));
		std::shuffle(player3.begin(), player3.end(), std::default_random_engine(seed));
		std::shuffle(player4.begin(), player4.end(), std::default_random_engine(seed));
	}

	bool isGameComplete() const
	{
		return (player1.empty() || player2.empty() || player3.empty() || player4.empty());
	}

	void playGame()
	{
		while (!isGameComplete())
		{
			playOneRound();
		}
	}

	int getWinner() const
	{
		if (player1.empty())
			return 1;
		if (player2.empty())
			return 2;
		if (player3.empty())
			return 3;
		if (player4.empty())
			return 4;
	}
};

int main()
{
	game newGame;
	newGame.buildDeck();
	newGame.dealCards();
	newGame.playGame();
	auto winner = newGame.getWinner();
	std::cout << winner << "�� �÷��̾ �̰���ϴ�!" << std::endl;
}
*/

/*
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
*/

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
