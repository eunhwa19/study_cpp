#pragma once
#include <iostream>

class Marine
{
	int hp;
	int coord_x, coord_y;
	int damage; //���ݷ�
	bool is_dead;
	char* name; //���� �̸� 

public:
	Marine(); //�⺻ ������
	Marine(int x, int y, const char* marine_name); //�̸����� ����
	Marine(int x, int y); //x, y ��ǥ�� ���� ����
	~Marine();

	int attack(); //������ ����
	void be_attacked(int damage_earn); //�Դ� ������
	void move(int x, int y); //���ο� ��ġ

	void show_status();
};

Marine::Marine()
{
	hp = 50;
	coord_x = coord_y = 0;
	damage = 5;
	is_dead = false;
	name = NULL;
}

Marine::Marine(int x, int y, const char* marine_name)
{
	name = new char[strlen(marine_name) + 1]; //���� �̸� ���� + 1 ��ŭ �Ҵ�
	strcpy_s(name, sizeof(marine_name), marine_name);

	coord_x = x;
	coord_y = y;
	hp = 50;
	damage = 5;
	is_dead = false;
	name = NULL;
}

Marine::Marine(int x, int y)
{
	coord_x = x;
	coord_y = y;
	hp = 50;
	damage = 5;
	is_dead = false;
	name = NULL;
}

void Marine::move(int x, int y)
{
	coord_x = x;
	coord_y = y;
}

int Marine::attack()
{
	return damage;
}

void Marine::be_attacked(int damage_earn)
{
	hp = hp - damage_earn;

	if (hp <= 0)
		is_dead = true;
}

void Marine::show_status()
{
	std::cout << " *** Marine *** " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) " << std::endl;
	std::cout << " HP : " << hp << std::endl;
}

Marine::~Marine()
{
	std::cout << name << " �� �Ҹ��� ȣ��!" << std::endl;
	if (name != NULL)
	{
		delete[] name;
	}
}
