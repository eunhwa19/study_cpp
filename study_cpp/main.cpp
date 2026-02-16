#include "main.h"

#include <iostream>
#include <array>
#include <type_traits>

//연습문제 2: 빠르고 범용적인 데이터 저장 컨테이너 만들기 
template<typename ... Args>
auto build_array(Args&&... args) -> std::array<typename std::common_type<Args...>::type, sizeof...(args)>
// 후행 리턴 타입(trailing return type) : 함수의 반환 타입을 함수 매개변수 목록 뒤에 명시하는 방법
{
	using commonType = typename std::common_type<Args...>::type;
	return { std::forward<commonType>((Args&&)args)... };
}

int main()
{
	auto data = build_array(1, 0u, 'a', 3.2f, false);

	for (auto i : data)
		std::cout << i << " ";
	std::cout << std::endl;
}

/*
//연습문제1 : 동적 크기 배열 구현
template <typename T>
class dynamic_array
{
	T* data;
	size_t n;

public:
	dynamic_array(int n) //constructor
	{
		this->n = n; //this: 호출된 객체의 주소를 가리키는 상수 포인터 
		data = new T[n]; //dynamic memory allocation 
	}

	dynamic_array(const dynamic_array<T>& other) //copy constructor 
	{
		n = other.n;
		data = new T[n];

		for (int i = 0; i < n; i++)
			data[i] = other[i]; //전달 받은 객체와 동일하게 객체를 복사
	}

	T& operator[] (int index) //Operator overloading
	{
		return data[index]; 
	}

	const T& operator[](int index) const //const 멤버 함수
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

	~dynamic_array() //destructor
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
	std::cout << "1반을 복사하여 2반 생성: " << class2.to_string() << std::endl;

	auto class3 = class1 + class2;
	std::cout << "1반과 2반을 합쳐 3반 생성: " << class3.to_string() << std::endl;

	return 0;
}
*/
