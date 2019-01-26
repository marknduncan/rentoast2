#ifndef DRAGON_H
#define DRAGON_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Object.h"

using namespace std;
class Dragon : public Object{
public:
	double base;
	Dragon(int yPos)
	{
		srand(time(NULL));
		x = 24;
		y = yPos;
		HP = 2;
		IDNum = Object::objectCount;
		Object::objectCount++;
		isCentipede = false;
		base = 1.0 /(rand() % 10);

		direction = 3;
	}
	~Dragon()
	{
		Object::objectCount--;
	}
	virtual void update(int** &map)
	{
		if(map[(int)y+1][(int)x] == BULLET)
		{
			hitAction();
		}
		map[(int)y][(int)x] = 0;
		x -= base;
		if(x < 0 )
		{
			x = 24.0;
			y++;
		}
		if(y > 15)
		{
			y = 0;
		}
		map[(int)y][(int)x] = DRAGON;
		if(rand() % 35 == 0)
			fire();
	}
	void fire()
	{
		throw "FIRE";
	}
	virtual void hitAction()
	{
		HP -= 1;
		if(HP == 0)
		{
			throw "DEADDRAGON";
		}
	}

};

#endif