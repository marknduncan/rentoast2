#ifndef BULLET_H
#define BULLET_H
#include <iostream>
#include "Object.h"
using namespace std;
class Bullet : public Object
{
public:
	bool bouttaDie;
	Bullet(int xpos, int ypos)
	{
		x = xpos;
		y = ypos;
		HP = 1;
		IDNum = Object::objectCount;
		Object::objectCount++;
		isCentipede = false;
		bouttaDie = false;

		direction = 1;
	}
	~Bullet()
	{
		Object::objectCount--;
	}
	virtual void update (int** &map)
	{
		
		map[(int)y][(int)x] = EMPTY;
		if(bouttaDie) throw "DEAD";
		y -= 1.0;		
		if(y < 0)
		{
			throw "DEAD";
		}		
		if (map[(int)y][(int)x] != EMPTY)
		{
			hitAction();
		}

		map[(int)y][(int)x] = BULLET;

	}
	virtual void hitAction()
	{
		HP -=1;
		if(HP == 0)	bouttaDie = true;
	}

};
#endif
	