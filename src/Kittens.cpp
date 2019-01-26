#include <iostream>
#include "SDL.h"
#include "Game.h"
#include "Object.h"
#include "Kittens.h"
#include "Player.h"
#include "Ducks.h"
#include "Dragon.h"
#include <vector>

using namespace std;

Kittens::Kittens(int xPos, int yPos)
{
	IDNum = Object::objectCount;
	Object::objectCount++;
	x = xPos;
	y = yPos;

	HP = 4;
	isCentipede = false;

	direction = 0;
}

Kittens::~Kittens()
{
	Object::objectCount--;
}

void Kittens::update(int** &map)
{	
	if(map[(int)y+1][(int)x] == BULLET)
	{
		hitAction();
	}
	if(HP == 4)
	{
		map[(int)y][(int)x] = EMPTY;
		map[(int)y][(int)x] = KITTEN1;
	}
	if(HP == 3)
	{
		map[(int)y][(int)x] = EMPTY;
		map[(int)y][(int)x] = KITTEN2;
	}
	if(HP == 2)
	{
		map[(int)y][(int)x] = EMPTY;
		map[(int)y][(int)x] = KITTEN3;
	}
	if(HP == 1)
	{
		map[(int)y][(int)x] = EMPTY;
		map[(int)y][(int)x] = KITTEN4;
	}


}

void Kittens::hitAction()
{
	HP -=1;
	if(HP == 0) throw "DEADCAT";
}