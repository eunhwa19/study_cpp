#include "main.h"

#include <iostream>
#include <vector>
#include <algorithm>

struct n_ary_node
{
	std::string name;
	bool is_dir;
	std::vector<n_ary_node*> children;
};

struct file_system
{
	using node = n_ary_node;
	using node_ptr = node*;

private:
	node_ptr root;
	node_ptr cwd;

public:
	file_system()
	{
		root = new node{ "/", true, {} };
		cwd = root; //처음에는 루트를 현재 디렉토리로 설정
	}

	node_ptr find(const std::string& path) // 디렉토리/파일 을 찾는 함수
	{
		if (path[0] == '/')
		{
			return find_impl(root, path.substr(1));
		}
		else //상대 경로 
		{
			return find_impl(cwd, path);
		}
	}

private:
	node_ptr find_impl(node_ptr directory, const std::string& path)
	{
		if (path.empty())
			return directory;
		auto sep = path.find('/');
		std::string current_path = sep == std::string::npos ? path : path.substr(0, sep);
		std::string rest_path = sep == std::string::npos ? "" : path.substr(sep + 1);
		auto found = std::find_if(directory->children.begin(), directory->children.end(), 
			[&](const node_ptr child) {	
				return child->name == current_path;		
			});

		if (found != directory->children.end())
		{
			return find_impl(*found, rest_path);
		}

		return NULL;
	}

public:
	bool add(const std::string& path, bool is_dir)
	{
		if (path[0] == '/')
		{
			return add_impl(root, path.substr(1), is_dir);
		}
		else
		{
			return add_impl(cwd, path, is_dir);
		}
	}

private:
	bool add_impl(node_ptr directory, const std::string& path, bool is_dir)
	{
		if (!(directory->is_dir)) //not directory->is_dir
		{
			std::cout << directory->name << "은(는) 파일입니다." << std::endl;
			return false;
		}

		auto sep = path.find('/');

		//path에 '/'가 없는 경우
		if (sep == std::string::npos)
		{
			auto found = std::find_if(directory->children.begin(), directory->children.end(), 
				[&](const node_ptr child) {
					return child->name == path;
			});

			if (found != directory->children.end())
			{
				std::cout << directory->name << "에 이미" << path << " 이름의 파일/디렉토리가 있습니다." << std::endl;
				return false;
			}

			directory->children.push_back(new node{ path, is_dir, {} });
			return true;
		}

		//path에 '/'가 있는 경우, 즉, 디렉토리 이름을 포함하고 있는 경우 
		std::string next_dir = path.substr(0, sep);
		auto found = std::find_if(directory->children.begin(), directory->children.end(), [&](const node_ptr child)
			{
				return child->name == next_dir && child->is_dir;
			});

		if (found != directory->children.end())
		{
			return add_impl(*found, path.substr(sep + 1), is_dir);
		}

		//path에 디렉토리 이름이 포함되어 있지만, 해당 디렉토리가 없는 경우
		std::cout << directory->name << "에 " << next_dir << " 이름의 디렉토리가 없습니다. " << std::endl;
		return false;
	}

public: 
	bool change_dir(const std::string& path)
	{
		auto found = find(path);
		if (found && found->is_dir)
		{
			cwd = found;
			std::cout << "현재 디렉토리를 " << cwd->name << "로 이동합니다. " << std::endl;
			return true;
		}

		std::cout << path << " 경로를 찾을 수 없습니다. " << std::endl;
		return false;
	}

public:
	void show_path(const std::string& path)
	{
		auto found = find(path);
		if (!found)
		{
			std::cout << path << " 경로가 존재하지 않습니다." << std::endl;
			return;
		}

		if (found->is_dir)
		{
			for (auto child : found->children)
			{
				std::cout << (child->is_dir ? "d " : "- ") << child->name << std::endl;
			}
		}

		else
		{
			std::cout << "- " << found->name << std::endl;
		}
	}
};

int main()
{
	file_system fs;
	fs.add("usr", true); // "/"에 usr 디렉토리 추가
	fs.add("etc", true); // "/"에 etc 디렉토리 추가
	fs.add("var", true); // "/"에 var 디렉토리 추가
	fs.add("tmp_file", false); // "/"에 tmp_file 파일 추가

	std::cout << "\"/\"의 파일/디렉토리 목록:" << std::endl;
	fs.show_path("/");

	std::cout << std::endl;
	fs.change_dir("usr");
	fs.add("gilbut", true);
	fs.add("gilbut/Downloads", true);
	fs.add("gilbut/Downloads/newFile.cpp", false);

	std::cout << "현재 디렉토리에서 usr의 파일/디렉토리 목록: " << std::endl;
	fs.show_path("usr"); // 현재 디렉토리에는 usr 디렉토리가 없으므로 정상적으로 출력하지 못합니다. 

	std::cout << "\"/usr\"의 파일/디렉토리 목록:" << std::endl;
	fs.show_path("/usr");

	std::cout << "\"usr/gilbut/Downloads\"의 파일/디렉토리 목록" << std::endl;
	fs.show_path("/usr/gilbut/Downloads");
} 

/*
// 2.4.3 연습문제 9: binary search tree 구현 
struct node
{
	int data;
	node* left;
	node* right;
};

struct bst
{
	node* root = nullptr;
	
	node* find(int value)
	{
		//원소 검색은 재귀적으로 동작하기 때문에 실제 구현은 find_impl()에 따로 작성하고 
		//private으로 지정하여 외부에서 직접 지정하지 못하게 함 
		return find_impl(root, value); 
	}

private: 
	node* find_impl(node* current, int value) //value를 찾아줘라 
	{
		if (!current) 
		{
			std::cout << std::endl;
			return NULL;
		}

		if (current->data == value)
		{
			std::cout << value << "을(를) 찾았습니다." << std::endl;
			return current;
		}

		if (value < current->data) //value값이 현재 노드의 왼쪽에 있는 경우 
		{
			std::cout << current->data << "에서 왼쪽으로 이동 ";
			return find_impl(current->left, value);
		}

		//value값이 현재 노드 오른쪽에 있는 경우 
		std::cout << current->data << "에서 오른쪽으로 이동 ";
		return find_impl(current->right, value);
	}

public:
	void insert(int value) //삽입 함수
	{
		if (!root)
			root = new node{ value, NULL, NULL };
		else
			insert_impl(root, value);
	}

private:
	void insert_impl(node* current, int value)
	{
		if (value < current->data)
		{
			if (!current->left) //값을 삽입해야하는 쪽이 비어있으면 
				current->left = new node { value, NULL, NULL }; //새로 노드를 추가한다. 
			else
				insert_impl(current->left, value);
		}
		else
		{
			if (!current->right)
				current->right = new node { value, NULL, NULL };
			else
				insert_impl(current->right, value);
		}
	}

public:
	void inorder() //중위 순회 함수 
	{
		inorder_impl(root);
	}

private: 
	void inorder_impl(node* start)
	{
		if (!start)
			return;

		inorder_impl(start->left);
		std::cout << start->data << " ";
		inorder_impl(start->right);
	}

public:
	node* successor(node* start) // 후속 노드를 찾는 함수
	{
		auto current = start->right;
		while (current && current->left)
			current = current->left;
		return current;
	}

	void deleteValue(int value)
	{
		root = delete_impl(root, value);
	}

private:
	node* delete_impl(node* start, int value)
	{
		if (!start)
			return NULL;
		
		if (value < start->data)
			start->left = delete_impl(start->left, value);
		else if (value > start->data)
			start->right = delete_impl(start->right, value);
		else //value == start->data
		{
			if (!start->left) //자식 노드가 전혀 없거나, 왼쪽 자식 노드만 없는 경우 
			{
				auto tmp = start->right; //오른쪽으로 이동
				delete start;
				return tmp;
			}

			if (!start->right) //오른쪽 자식 노드만 없는 경우 
			{
				auto tmp = start->left; //왼쪽으로 이동 
				delete start;
				return tmp;
			}
			
			//자식 노드가 둘 다 있는 경우
			auto succNode = successor(start); 
			start->data = succNode->data; 

			//오른쪽 서브 트리에서 후속(successor)을 찾아 삭제 
			start->right = delete_impl(start->right, succNode->data);
		}

		return start;
	}
};

int main()
{
	bst test_tree;
	test_tree.insert(12);
	test_tree.insert(10);
	test_tree.insert(20);
	test_tree.insert(8);
	test_tree.insert(11);
	test_tree.insert(15);
	test_tree.insert(28);
	test_tree.insert(4);
	test_tree.insert(2);

	std::cout << "중위 순회: ";
	test_tree.inorder();
	std::cout << std::endl;

	test_tree.deleteValue(12);
	std::cout << "12를 삭제한 후 중위 순회: ";
	test_tree.inorder();
	std::cout << std::endl;

	if (test_tree.find(12))
		std::cout << "원소 12는 트리에 있습니다. " << std::endl;
	else
		std::cout << "원소 12는 트리에 없습니다. " << std::endl;
}
*/

/*
// 2.3.1 연습문제 7: 회사 조직도 구조 만들기
struct node // binary tree
{
	std::string position;
	node* first;
	node* second;
};

struct org_tree
{
	node* root;

	//루트 노드(회사 대표) 생성
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

		if (!managerNode) //매니저 노드에 아무것도 없으면
		{
			std::cout << manager << "을(를) 찾을 수 없습니다: " << std::endl;
			return false;
		}

		if (managerNode->first && managerNode->second) //자식 노드가 다 차있으면
		{
			std::cout << manager << " 아래에 " << subordinate << "을(를) 추가할 수 없습니다. " << std::endl;
			return false;
		}

		if (!managerNode->first)
			managerNode->first = new node { subordinate, NULL, NULL }; // 첫 번째에 추가 

		else
			managerNode->second = new node { subordinate, NULL, NULL }; // 두 번째에 추가 

		std::cout << manager << " 아래에 " << subordinate << "을(를) 추가했습니다. " << std::endl;

		return true; // 원소 추가 성공 
	}

	static void preOrder(node* start) // 전위 순회
	{
		if (!start)
			return;

		std::cout << start->position << ", ";
		preOrder(start->first);
		preOrder(start->second);
	}

	static void inOrder(node* start) // 중위 순회
	{
		if (!start)
			return;

		inOrder(start->first);
		std::cout << start->position << ", ";
		inOrder(start->second);
	}

	static void postOrder(node* start) // 후위 순회
	{
		if (!start)
			return;

		postOrder(start->first);
		postOrder(start->second);
		std::cout << start->position << ", ";
	}

	//연습문제 8: 레벨 순서 순회 구현하기 
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
				std::cout << current->position << ", ";
				
				if (current->first)
					q.push(current->first);
				if (current->second)
					q.push(current->second);

				q.pop();
			}

			std::cout << std::endl;
		}
	}
};

int main()
{
	auto tree = org_tree::create_org_structure("CEO");

	tree.addSubordinate("CEO", "부사장");
	tree.addSubordinate("부사장", "IT부장");
	tree.addSubordinate("부사장", "마케팅부장");
	tree.addSubordinate("IT부장", "보안팀장");
	tree.addSubordinate("IT부장", "앱개발팀장");
	tree.addSubordinate("마케팅부장", "물류팀장");
	tree.addSubordinate("마케팅부장", "홍보팀장");
	tree.addSubordinate("부사장", "재무부장");

	std::cout << std::endl;

	org_tree::levelOrder(tree.root);
}
*/

/*
//1.10.1 실습 문제 3: 사무실 공유 프린터의 인쇄 대기 목록 시뮬레이션
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
		os << "id: " << j.id << ", 사용자: " << j.user << ", 페이지 수: " << j.pages << "장";
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
			std::cout << "인쇄 대기열에 추가 실패: " << job << std::endl;
			return false;
		}

		std::cout << "인쇄 대기열에 추가: " << job << std::endl;
		jobs.push(job);
		return true;
	}

	void startPrinting()
	{
		while (!jobs.empty())
		{
			std::cout << "인쇄 중: " << jobs.front() << std::endl;
			jobs.pop();
		}
	}
};

int main()
{
	Printer<5> printer;

	Job j1("광희", 10);
	Job j2("정다", 4);
	Job j3("현수", 5);
	Job j4("유미", 7);
	Job j5("채원", 8);
	Job j6("시원", 10);

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
//1.7.5 실습 문제 2: 카드 게임 시뮬레이션 
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
	std::cout << winner << "번 플레이어가 이겼습니다!" << std::endl;
}
*/

/*
//1.6.3 실습 문제 1: 음악 재생목록 구현하기
// 1. 일단 기본 컨테이너를 만든다 
// 2. 원형 데이터 표현 -> 마지막 원소 다음에 첫 번째 원소가 와야함. 
// 3. next(), previous(), printall(), insert(), remove() 함수 필요
// 4. 반복자 작성 (begin(), end() 포함) 

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
		head = new node{ NULL, NULL, NULL }; // 모두 NULL로 구성된 더미 노드
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
		cir_list_iterator(node_ptr p) : ptr(p) {} //생성자

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
		for (const auto& i : other) //역순으로 삽입하지만 원형 리스트라서 문제 없음
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
	std::cout << "재생 목록 : ";
	pl.loopOnce();

	playlist pl2 = pl;
	pl2.erase(2);
	pl2.insert(3);
	std::cout << "두 번째 재생목록 : ";
	pl2.loopOnce();
}
*/

/*
//1.6.2 연습 문제 5: 기본적인 사용자 정의 컨테이너 만들기
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

	//기본 반복자
	struct singly_ll_iterator
	{
	private:
		node_ptr ptr;

	public:
		singly_ll_iterator(node_ptr p) : ptr(p) {} //생성자

		int& operator*() { return ptr->data; } //접근자

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

	singly_ll() = default; //생성자

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

	std::cout << "첫 번째 리스트 : ";
	for (auto i : sll)
		std::cout << i << " ";
	std::cout << std::endl;

	auto sll2 = sll; //깊은 복사 
	sll2.push_front(-1); // -1, 0, 1, 2, 3
	std::cout << "첫 번째 리스트를 복사한 후, 맨 앞에 -1을 추가: ";
	for (auto i : sll2)
		std::cout << i << ' ';
	std::cout << std::endl;

	std::cout << "깊은 복사 후 첫 번째 리스트: ";

	for (auto i : sll) //0, 1, 2, 3 
		std::cout << i << ' ';
	std::cout << std::endl;

}
*/

/*
//1.6.4 연습 문제 4: 다양한 반복자에서 이동하기
// - 벡터 반복자를 사용하여 데이터로부터 유용한 정보를 검색
int main()
{
	std::vector<std::string> vec = {
		"Lewis Hamilton", "Lewis Hamilton", "Nico Roseberg",
		"Sebastian Vettel", "Lewis Hamilton", "Sebastian Vettel",
		"Sebastian Vettel", "Sebastian Vettel", "Fernando Alonso"
	};

	auto it = vec.begin(); //상수 시간
	std::cout << "가장 최근 우승자: " << *it << std::endl;
	
	it += 8;
	std::cout << "8년 전 우승자: " << *it << std::endl;

	advance(it, -3); //상수 시간
	std::cout << "그 후 3년 뒤 우승자: " << *it << std::endl;

	std::forward_list<std::string> fwd(vec.begin(), vec.end());

	auto it1 = fwd.begin();
	std::cout << "가장 최근 우승자: " << *it1 << std::endl;

	advance(it1, 5);
	std::cout << "5년 전 우승자: " << *it1 << std::endl;

}
*/

/*
//1.5.3 연습 문제 3: 연결 리스트에서 remove_if() 함수를 이용한 조건부 원소 삭제
// - 일부 시민들의 정보를 이용하여 선거권이 없는 사람을 가려내기
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

	std::cout << "전체 시민들: ";
	for (const auto& c : citizens)
		std::cout << c << " ";
	std::cout << std::endl;

	citizens.remove_if([](const citizen &c) //람다 표현식
	{
		return (c.age < 19);
	});

	std::cout << "투표권이 있는 시민들: ";
	for (const auto& c : citizens)
		std::cout << c << " ";
	std::cout << std::endl;

	citizens_copy.remove_if([](const citizen& c)
	{
		return (c.age != 18);
	});

	std::cout << "내년에 투표권이 생기는 시민들: ";
	for (const auto& c : citizens_copy)
		std::cout << c << " ";
	std::cout << std::endl;
}
*/

/*
//1.3.2 연습 문제2: 빠르고 범용적인 데이터 저장 컨테이너 만들기
template<typename ... Args> //가변 템플릿 //점 세 개는 가변 인자
auto build_array(Args&&... args)->std::array<typename std::common_type<Args...>::type, sizeof...(args)>
{
	using commonType = typename std::common_type<Args...>::type;
	return { std::forward<commonType>((Args&&)args)... };
}

int main()
{
	auto data = build_array(1, 0u, 'a', 3.2f, false);
	//auto data2 = build_array(1, "Packet", 2.0); //문자열과 숫자를 모두 표현할 수 있는 공통 자료형이 없음.

	for (auto i : data)
		std::cout << i << " ";
	std::cout << std::endl;
}
*/

/*
//1.3.1 연습 문제1: 동적 크기 배열 구현하기 - 학생 정보 관리 프로그램
template <typename T>
class dynamic_array
{
	T* data;
	size_t n; 

public: 
	dynamic_array(int n) //생성자
	{
		this->n = n;
		data = new T[n];
	}

	dynamic_array(const dynamic_array<T>& other) //복사 생성자 
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
	int standard; //학급
};

std::ostream& operator<<(std::ostream& os, const student& s)
{
	return (os << "[" << s.name << ", " << s.standard << "]");
}

int main()
{
	int nStudents;
	std::cout << "1반 학생 수를 입력하세요: ";
	std::cin >> nStudents;

	dynamic_array<student> class1(nStudents);
	for (int i = 0; i < nStudents; i++)
	{
		std::string name;
		int standard;
		std::cout << i + 1 << "번째 학생의 이름과 나이를 입력하세요: ";
		std::cin >> name >> standard;
		class1[i] = student{ name, standard };
	}

	try
	{
		class1.at(nStudents) = student{ "John", 8 };
	}
	catch (...)
	{
		std::cout << "예외 발생!" << std::endl;
	}

	//deep copy
	auto class2 = class1;
	std::cout << "1반을 복사에서 2반 생성: " << class2.to_string() << std::endl;

	//두 학급을 합쳐서 새로운 큰 학급을 생성
	auto class3 = class1 + class2;
	std::cout << "1반과 2반을 합쳐서 3반 생성: " << class3.to_string() << std::endl;

	return 0;
}
*/
