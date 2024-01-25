#include "main.h"

#include <iostream>
#include <forward_list>
#include <vector>

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
