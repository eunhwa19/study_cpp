#include <iostream>
#include "main.h"

int main()
{
	Marine* marines[100];
	
	marines[0] = new Marine(2, 3, "Marine 2"); // new는 객체를 동적으로 생성하면서 동시에 자동으로 생성자도 호출해준다.
	marines[1] = new Marine(3, 5, "Marine 1");

	marines[0]->show_status();
	marines[1]->show_status();

	std::cout << std::endl << "마린1이 마린2를 공격! " << std::endl;

	marines[0]->be_attacked(marines[1]->attack());

	marines[0]->show_status();
	marines[1]->show_status();

	delete marines[0];
	delete marines[1];
}
