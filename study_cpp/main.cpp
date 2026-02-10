#include "main.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <array>

template <typename T>
class dynamic_array
{
	T* data;
	size_t n;

public:
	dynamic_array(int n) //constructor
	{
		this->n = n;
		data = new T[n];
	}

	dynamic_array(const dynamic_array<T>& other) //copy constructor 
	{
		n = other.n;
		data = new T[n];

		for (int i = 0; i < n; i++)
			data[i] = other[i];
	}

	T& operator[] (int index)
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

	size_t size(const)
	{
		return n;
	}
};

int main()
{
	
	return 0;
}

