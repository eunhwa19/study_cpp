#include "main.h"

#include <iostream>
#include <array>
#include <type_traits>

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
