#include "main.h"

#include <iostream>
#include <array>

int main()
{
	std::array<int, 10> arr1;

	arr1[0] = 1;
	std::cout << "arr1 배열의 첫 번째 원소: " << arr1[0] << std::endl;
	
	std::array<int, 4> arr2 = { 1, 2, 3, 4 };
	
	std::cout << "arr2의 모든 원소: ";
	for (int i = 0; i < arr2.size(); i++)
	{
		std::cout << arr2[i] << " ";
	}

}
