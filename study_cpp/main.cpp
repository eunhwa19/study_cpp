#include "main.h"

#include <iostream>
#include <array>

int main()
{
	std::array<int, 10> arr1;

	arr1[0] = 1;
	std::cout << "arr1 �迭�� ù ��° ����: " << arr1[0] << std::endl;
	
	std::array<int, 4> arr2 = { 1, 2, 3, 4 };
	
	std::cout << "arr2�� ��� ����: ";
	for (int i = 0; i < arr2.size(); i++)
	{
		std::cout << arr2[i] << " ";
	}

}
