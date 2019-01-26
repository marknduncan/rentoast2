#ifndef FIREBALL_H
#define FIREBALL_H
#include <iostream>
#include "Object.h"
using namespace std;
class Fireball : public Object
{
public:
	
	Fireball(int xpos, int ypos)
	{
		x = xpos;
		y = ypos;
		HP = 1;
		IDNum = Object::objectCount;
		Object::objectCount++;
		isCentipede = false;
	}
	~Fireball()
	{
		Object::objectCount--;
	}
	virtual void update (int** &map)
	{
		map[(int)y][(int)x] = EMPTY;
		y += .2;		
		if(y > 19 || HP == 0)
		{
			throw "DEAD";
		}		
		if (map[(int)y][(int)x] == PLAYER)
		{
			hitAction();
		}

		map[(int)y][(int)x] = FIREBALL;


		
	}
	virtual void hitAction()
	{
		HP -=1;
		throw "KILL";
	}

};
#endif
	