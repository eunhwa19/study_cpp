#include "main.h"

/*
//실습문제 3: 사무실 공유 프린터의 인쇄 대기 목록 시뮬레이션 
#include <iostream>
#include <string>
#include <queue>

class Job
{
	int id;
	std::string user;
	int pages; 

	static int count;

public: 
	Job(const std::string& u, int p) : user(u), pages(p), id(++count) {} // constructor

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
		while (not jobs.empty())
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
	Job j3("수현", 5);
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
//실습문제 2: 카드 게임 시뮬레이션 
#include <iostream>
#include <string>
#include <random>
#include <sstream>
#include <array>
#include <vector>
#include <chrono>
#include <algorithm>

struct card
{
	int number;

	enum suit
	{
		HEART, SPADE, CLUB, DIAMOND
	}suit;
	
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
			os << "spade";
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
		{
			deck[i] = card{ i + 1, card::HEART };
		}
		for (int i = 0; i < 13; i++)
		{
			deck[i + 13] = card{ i + 1, card::SPADE };
		}
		for (int i = 0; i < 13; i++)
		{
			deck[i + 26] = card{ i + 1, card::CLUB };
		}
		for (int i = 0; i < 13; i++)
		{
			deck[i + 39] = card{ i + 1, card::DIAMOND };
		}
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
		return player1.empty() || player2.empty() || player3.empty() || player4.empty();
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
//실습문제 1: 음악 재생 목록 구현하기 
#include <iostream>
#include <string>
#include <initializer_list>

struct circular_linked_list_node
{
	std::string* data; // 문자열의 주소 저장 
	circular_linked_list_node* next;
	circular_linked_list_node* prev;
};

using node = circular_linked_list_node;
using node_ptr = node*;

struct circular_linked_list_iterator
{
private: 
	node_ptr ptr; 

public:
	circular_linked_list_iterator(node_ptr p) : ptr(p) {}

	std::string& operator*()
	{
		return *(ptr->data); // 역참조, 실제 문자열에 접근 
	}

	node_ptr get()
	{
		return ptr;
	}

	circular_linked_list_iterator& operator++()
	{
		ptr = ptr->next;
		return *this;
	}

	circular_linked_list_iterator operator++(int)
	{
		circular_linked_list_iterator it = *this;
		++(*this);
		return it;
	}

	circular_linked_list_iterator& operator--()
	{
		ptr = ptr->prev;
		return *this;
	}

	circular_linked_list_iterator operator--(int)
	{
		circular_linked_list_iterator it = *this;
		--(*this);
		return it;
	}

	friend bool operator==(const circular_linked_list_iterator& it1, const circular_linked_list_iterator& it2)
	{
		return it1.ptr == it2.ptr;
	}

	friend bool operator!=(const circular_linked_list_iterator& it1, const circular_linked_list_iterator& it2)
	{
		return it1.ptr != it2.ptr;
	}

};

class circular_linked_list
{
private:
	node_ptr head;
	size_t n;

public:
	circular_linked_list() : n(0) // default constructor 
	{
		head = new node { NULL, NULL, NULL};
		head->next = head;
		head->prev = head;
	}

	size_t size() const
	{
		return n;
	}

	void insert(const std::string &value)
	{
		node_ptr new_node = new node{ new std::string(value), nullptr, nullptr };
		n++;
		auto dummy = head->prev; // head의 이전 노드를 가리키는 포인터가 됨. 
		dummy->next = new_node;
		new_node->prev = dummy;
		if (head == dummy) // 노드가 한 개일 때
		{
			dummy->prev = new_node;
			new_node->next = dummy;
			head = new_node;
			return;
		}
		new_node->next = head;
		head->prev = new_node;
		head = new_node; // head 앞에 new_node를 넣는 것 
	}

	void erase(const std::string& value)
	{
		auto cur = head;
		auto dummy = head->prev;

		while (cur != dummy)
		{
			if (*(cur->data) == value)
			{
				cur->prev->next = cur->next;
				cur->next->prev = cur->prev;
				if (cur == head)
					head = head->next;
				delete cur;
				n--;
				return;
			}
			cur = cur->next;
		}
	}

	circular_linked_list(const circular_linked_list& other) : circular_linked_list() // copy construtor
	{
		for (const auto& i : other)
			insert(i);
	}

	circular_linked_list(const std::initializer_list<std::string>& il) : head(nullptr), n(0) // initialization list 
	{
		for (const auto& i : il)
			insert(i);
	}

	circular_linked_list_iterator begin() { return circular_linked_list_iterator{ head }; }
	circular_linked_list_iterator begin() const { return circular_linked_list_iterator{ head }; }
	circular_linked_list_iterator end() { return circular_linked_list_iterator{ head->prev }; }
	circular_linked_list_iterator end() const { return circular_linked_list_iterator{ head->prev }; }

	~circular_linked_list()
	{
		while (size())
		{
			erase(*(head->data));
		}

		delete head;
	}
};

struct playlist
{
	circular_linked_list list;

	void insert(const std::string& song)
	{
		list.insert(song);
	}

	void erase(const std::string& song)
	{
		list.erase(song);
	}

	void loop_once()
	{
		for (auto& song : list)
			std::cout << song << " ";
		std::cout << std::endl;
	}
};

int main()
{
	playlist pl;
	pl.insert("이 별로부터");
	pl.insert("26");

	std::cout << "playlist : ";
	pl.loop_once();

	playlist pl2 = pl;
	pl2.erase("이 별로부터");
	pl2.insert("Run to you");

	std::cout << "playlist2 : ";
	pl2.loop_once();
}
*/

/*
//연습문제 5: 기본적인 사용자 정의 컨테이너 만들기 
#include <iostream>
#include <algorithm>
#include <initializer_list>

struct singly_linked_list_node
{
	int data;
	singly_linked_list_node* next;
};

using node = singly_linked_list_node;
using node_ptr = node*;

struct singly_linked_list_iterator
{
private:
	node_ptr ptr;

public:
	singly_linked_list_iterator(node_ptr p) : ptr(p) {}
	int& operator*() { return ptr->data; }
	node_ptr get() { return ptr; }

	singly_linked_list_iterator& operator++() // 선행 증가
	{
		ptr = ptr->next; // it 이동
		return *this; //  이동한 it 반환
	}

	singly_linked_list_iterator operator++(int) // 후행 증가 
	{
		singly_linked_list_iterator result = *this; // 현재 it의 값을 복사해놓는 것
		++(*this); // it 이동 
		return result; // 이동하기 전의 복사본 반환
	}

	friend bool operator==(const singly_linked_list_iterator& left, const singly_linked_list_iterator& right)
	{
		return left.ptr == right.ptr;
	}

	friend bool operator!=(const singly_linked_list_iterator& left, const singly_linked_list_iterator& right)
	{
		return left.ptr != right.ptr;
	}
};

class singly_linked_list
{
private:
	node_ptr head;

public: 
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

	singly_linked_list_iterator begin() { return singly_linked_list_iterator(head); }
	singly_linked_list_iterator end() { return singly_linked_list_iterator(NULL); }
	singly_linked_list_iterator begin() const { return singly_linked_list_iterator(head); }
	singly_linked_list_iterator end() const { return singly_linked_list_iterator(NULL); }

	singly_linked_list() = default; // default constructor 
	singly_linked_list(const singly_linked_list& other) : head(NULL) // copy constructor
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

	singly_linked_list(const std::initializer_list<int>& ilist) : head(NULL) // initialization list
	{
		for (auto it = std::rbegin(ilist); it != std::rend(ilist); it++)
			push_front(*it);
	}
};

int main()
{
	singly_linked_list sll = { 1, 2, 3 };
	sll.push_front(0);

	std::cout << "첫 번째 리스트 ";
	for (auto i : sll)
		std::cout << i << " ";
	std::cout << std::endl; 

	auto sll2 = sll; 
	sll2.push_front(-1);
	std::cout << "첫 번째 리스트를 복사한 후, 맨 앞에 -1을 추가: ";
	for (auto i : sll2)
		std::cout << i << ' ';
	std::cout << std::endl; 
	
	std::cout << "깊은 복사 후 첫 번째 리스트: ";

	for (auto i : sll)
		std::cout << i << ' ';
	std::cout << std::endl; 
}
*/

/*
//연습문제 4: 다양한 반복자에서 이동하기 
#include <iostream>
#include <forward_list>
#include <vector>
#include <string>

int main()
{
	std::vector<std::string> vec = { "Lewis Hamilton", "Lewis Hamilton", "Nico Roseberg",
									 "Sebastian Vettel", "Lewis Hamilton", "Sebastian Vettel",
									 "Sebastian Vettel", "Sebastian Vettel", "Fernando Alonso" };

	auto it = vec.begin();
	std::cout << "가장 최근 우승자: " << *it << std::endl;

	it += 8;
	std::cout << "8년 전 우승자: " << *it << std::endl; 

	advance(it, -3);
	std::cout << "그 후 3년 뒤 우승자: " << *it << std::endl; 

	std::forward_list<std::string> fwd(vec.begin(), vec.end());

	auto it1 = fwd.begin();
	std::cout << "가장 최근 우승자: " << *it1 << std::endl; 

	advance(it1, 5);
	std::cout << "5년 전 우승자: " << *it1 << std::endl;
}
*/

/*
//연습문제 3: 연결 리스트에서 remove_if() 함수를 이용한 조건부 원소 삭제 
#include <string>
#include <iostream>
#include <forward_list>

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
	std::forward_list<citizen> citizens = {
		{"Kim", 22}, {"Lee", 25}, {"Park", 18}, {"Jin", 16}
	}; 

	auto citizens_copy = citizens;

	std::cout << "전체 시민들: ";
	for (const auto& c : citizens)
		std::cout << c << " ";
	std::cout << std::endl;

	citizens_copy.remove_if([](const citizen& c) { return (c.age < 19); }); // [](const citizens& c) : 람다식 

	std::cout << "투표권이 있는 시민들: "; 
	for (const auto& c : citizens_copy)
		std::cout << c << " ";
	std::cout << std::endl;
}
*/

/*
//연습문제 2: 빠르고 범용적인 데이터 저장 컨테이너 만들기 
#include <array>
#include <iostream>
#include <type_traits>
#include <utility>

template<typename ... Args> // ... : 여러 개의 타입을 받을 수 있음 
std::array< typename std::common_type<Args...>::type, sizeof...(Args) > build_array(Args&&...args); // &&: rvalue reference 

template<typename ... Args>
auto build_array(Args&&... args) -> std::array<typename std::common_type<Args...>::type, sizeof...(Args) >
{
	using commonType = typename std::common_type<Args...>::type; // 여러 타입을 하나로 통일 
	return { std::forward<commonType>((Args&&)args)... };
}

int main()
{
	auto data = build_array(1, 0u, 'a', 3.2f, false);

	for (auto i : data)
		std::cout << i << " ";
	std::cout << std::endl;
	
	return 0;
}
*/

/*
//연습문제 1: 동적 크기 배열 구현하기 
#include <iostream>
#include <sstream>
#include <algorithm>

template <typename T> // 타입을 일단 T라고 하고 나중에 결정
class dynamic_array
{
	// 멤버 변수 
	T* data; // 배열의 시작 주소를 가리키는 포인터 
	size_t n; // 배열의 사이즈 

public: 
	dynamic_array(int n) // constructor 
	{
		this->n = n; // this : 현재 객체 자신을 가리키는 포인터, 여기서는 dynamic_array 객체 
		data = new T[n]; 
	}

	dynamic_array(const dynamic_array<T>& other) // copy constructor
	{
		n = other.n;
		data = new T[n];

		for (int i = 0; i < n; i++)
			data[i] = other[i];
	}

	T& operator[](int index) // T&(reference) 를 써서 값을 직접 수정할 수 있게 함
	{
		return data[index];
	}

	const T& operator[](int index) const // const 객체를 위해 만든 함수, 값을 읽을 수만 있고 수정은 안 됨.  
	{
		return data[index];
	}

	T& at(int index)
	{
		if (index >= 0 && index < n) 
			return data[index];
		throw "Index out of range";
	}

	size_t size() const 
	{
		return n;
	}

	~dynamic_array() // destructor 
	{
		delete[] data; // 메모리 누수 방지 
	}

	// 배열 내 원소 순회 
	T* begin() { return data; }
	const T* begin() const { return data; }
	T* end() { return data + n; }
	const T* end() const { return data + n; }

	friend dynamic_array<T> operator+(const dynamic_array<T>& arr1, const dynamic_array<T>& arr2) //operator overloading
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

		std::ostringstream os; // ostringstream : 여러 데이터를 << 연산자로 넣어서 하나의 문자열로 만들 때 쓰는 클래스 
		os << data[0];

		for (int i = 1; i < n; i++)
			os << sep << data[i];

		return os.str();
	}
};

struct student
{
	std::string name;
	int standard; 
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
		std::cout << i + 1 << "번째 학생 이름과 나이를 입력하세요: ";
		std::cin >> name >> standard;
		class1[i] = student{ name, standard };
	}

	auto class2 = class1;
	std::cout << "1반을 복사해서 2반 생성: " << class2.to_string() << std::endl;

	auto class3 = class1 + class2;
	std::cout << "1반과 2반을 합쳐 3반 생성: " << class3.to_string() << std::endl;

	return 0;
}
*/
