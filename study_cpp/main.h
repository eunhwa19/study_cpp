#pragma once
#include <string.h>
#include <iostream>

class Photon_Cannon
{
private:
	int hp, shield;
	int coord_x, coord_y;
	int damage;

public:
	Photon_Cannon(int x, int y);
	Photon_Cannon(const Photon_Cannon& pc);

	void show_status();
};

Photon_Cannon::Photon_Cannon(const Photon_Cannon& pc) //다른 객체를 상수 레퍼런스로 받는다
{
	std::cout << "복사 생성자 호출 !" << std::endl;
	hp = pc.hp;
	shield = pc.shield;
	coord_x = pc.coord_x;
	coord_y = pc.coord_y;
	damage = pc.damage;
}

Photon_Cannon::Photon_Cannon(int x, int y)
{
	std::cout << "생성자 호출 !" << std::endl;
	hp = shield = 100;
	coord_x = x;
	coord_y = y;
	damage = 20;
}

void Photon_Cannon::show_status()
{
	std::cout << "Photon Cannon " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " 
		<< coord_y << " ) " << std::endl;
	std::cout << " HP : " << hp << std::endl;
}

//복사 생성자 공부 1/25