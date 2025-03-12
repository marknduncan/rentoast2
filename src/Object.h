#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>

using namespace std;
const int EMPTY = 0;
const int PLAYER = 1;
const int BABY = 3;
const int MAMA = 4;
const int DRAGON = 5;
const int BULLET = 6;
const int FIREBALL = 7;
const int BOMB = 8;
const int MOLOTOV = 9;
const int EXPLOSION = 10;
const int FIRE = 11;
const int KITTEN1 = 12;
const int KITTEN2 = 13;
const int KITTEN3 = 14;
const int KITTEN4 = 15;


class Object 
{
public:
	int HP;
	static int objectCount;
	int IDNum;
	double x, y;
	bool isCentipede;

	int direction; //1 up, 2 down, 3 left, 4, right

	virtual void update(int** &map) = 0;

};


#endif