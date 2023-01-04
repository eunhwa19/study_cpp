#include <iostream>
#include "main.h"

int main()
{
	Marine* marines[100];
	
	marines[0] = new Marine(2, 3, "Marine 2"); // new�� ��ü�� �������� �����ϸ鼭 ���ÿ� �ڵ����� �����ڵ� ȣ�����ش�.
	marines[1] = new Marine(3, 5, "Marine 1");

	marines[0]->show_status();
	marines[1]->show_status();

	std::cout << std::endl << "����1�� ����2�� ����! " << std::endl;

	marines[0]->be_attacked(marines[1]->attack());

	marines[0]->show_status();
	marines[1]->show_status();

	delete marines[0];
	delete marines[1];
}
