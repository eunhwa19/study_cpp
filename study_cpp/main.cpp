#include "main.h"

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
