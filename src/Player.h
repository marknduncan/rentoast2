#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "Object.h"

using namespace std;
class Player : public Object
{
public:
	Player(int xpos, int ypos){
		x = xpos;
		y = ypos;
		HP = 1;
		IDNum = Object::objectCount;
		Object::objectCount++;
		isCentipede = false;
		direction = 0;
	}
	~Player()
	{
		Object::objectCount--;
	}
	int getx(){return x;}
	int gety(){return y;}
	virtual void update(int** &map)
	{
		if (direction == 1)
		{
			if(y > 16)
			{
				map[(int)y][(int)x] = EMPTY;
				y--;
				map[(int)y][(int)x] = PLAYER;
			
			}
			direction = 0;
		}
		else if (direction == 2)
		{
			if(y < 18)
			{
				map[(int)y][(int)x] = EMPTY;
				y++;
				map[(int)y][(int)x] = PLAYER;
			}
			direction = 0;
		}
		else if (direction == 3)
		{
			if(x > 0)
			{
				map[(int)y][(int)x] = EMPTY;
				x--;
				map[(int)y][(int)x] = PLAYER;
			}
			direction = 0;
		}
		else if (direction == 4)
		{
			if(x < 24)
			{
				map[(int)y][(int)x] = EMPTY;
				x++;
				map[(int)y][(int)x] = PLAYER;
			}	
			direction = 0;
		}
		else
		{
			map[(int)y][(int)x] = PLAYER;
			direction = 0;
		}
	}
	virtual Player& splitFront(int index){ return *this;}
	virtual Player& splitBack(int index){ return *this;}
	virtual void hitAction()
	{
		HP -= 1;
		if(HP == 0)
		{
			throw "KILL";
		}
	}
};
#endif
