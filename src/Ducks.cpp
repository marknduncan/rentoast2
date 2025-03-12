#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Object.h"
#include "Ducks.h"

using namespace std;

int Object::objectCount = 0;
//default constructor
Ducks::Ducks(int length)
{
	for(int i = length; i >= 0; i--)
	{
		DuckNode ducklist(3, i, 0);
		gaggle.push_back(ducklist);

	}

	gaggle[0].isHead = 1;

	direction = 4; // 4 = right

	HP  =  1;
	isCentipede = true;
	IDNum = Object::objectCount;
	Object::objectCount++;

}

//class copy constructor
Ducks::Ducks(Ducks& d)
{
		direction = d.direction;
		HP = d.HP;

		for(int i = 0; i < d.gaggle.size(); i++)
			gaggle.push_back(d.gaggle[i]);
		IDNum = Object::objectCount;
		Object::objectCount++;
}

Ducks::~Ducks()
{
	Object::objectCount--;
}

//move function
void Ducks::move(int** map) // changes the duck's coordinates
{
	double Ax, Ay, Bx, By;
	gaggle[0].isHead = 1;
	if(direction == 1) //up
	{

		for(int i = 0; i < gaggle.size(); i++)
		{
			Bx = gaggle[i].x;
			By = gaggle[i].y;
			if(i == 0)
			{
				map[(int)gaggle[i].y][(int)gaggle[i].x] = EMPTY;
				gaggle[i].y -= .2;
				if((int)gaggle[i].y - (int)By == 0) 
				{
					if(gaggle[i].isHead !=0)
					{
						map[(int)gaggle[i].y][(int)gaggle[i].x] = MAMA;
					}
					break;
				}
	
				if(gaggle[i].y < 0)
				{
					srand(time(NULL));
					gaggle[i].y = 18;
					gaggle[i].x = rand() % 25;
				}
				if(gaggle[i].isHead !=0)
				{
					map[(int)gaggle[i].y][(int)gaggle[i].x] = MAMA;
				}
			}
			if(i != 0)
			{
				map[(int)gaggle[i].y][(int)gaggle[i].x] = EMPTY;
				gaggle[i].x = Ax;
				gaggle[i].y = Ay;
				if(gaggle[i].isHead !=0)
				{
					map[(int)gaggle[i].y][(int)gaggle[i].x] = BABY;
				}
			}				
			Ax = Bx;
			Ay = By;

		}
	
	}

	if(direction == 2) // down
	{
		

		for(int i = 0; i < gaggle.size(); i++)
		{
			Bx = gaggle[i].x;
			By = gaggle[i].y;
			if(i == 0)
			{
				map[(int)gaggle[i].y][(int)gaggle[i].x] = EMPTY;
				gaggle[i].y += .2;	
				if((int)gaggle[i].y - (int)By == 0)  
				{
					if(gaggle[i].isHead !=0)
					{
						map[(int)gaggle[i].y][(int)gaggle[i].x] = MAMA;
					}
					break;
					
				}
	
				if(gaggle[i].y > 18)
				{
					srand(time(NULL));
					gaggle[i].y = 0;
					gaggle[i].x = rand() % 25;
				}
			
				if(gaggle[i].isHead !=0)
				{
					map[(int)gaggle[i].y][(int)gaggle[i].x] = MAMA;
				}
			}

			if(i != 0)
			{
				map[(int)gaggle[i].y][(int)gaggle[i].x] = EMPTY;
				gaggle[i].x = Ax;
				gaggle[i].y = Ay;
				if(gaggle[i].isHead !=0)
				{
					map[(int)gaggle[i].y][(int)gaggle[i].x] = BABY;
				}
			}
			Ax = Bx;
			Ay = By;

		}

	}

	if(direction == 3) //left
	{
		for(int i = 0; i < gaggle.size(); i++)
		{
			Bx = gaggle[i].x;
			By = gaggle[i].y;
			if(i == 0)
			{
				map[(int)gaggle[i].y][(int)gaggle[i].x] = EMPTY;
				gaggle[i].x -= .2;
				if((int)gaggle[i].x - (int)Bx == 0) 
				{
					if(gaggle[i].isHead !=0)
					{
						map[(int)gaggle[i].y][(int)gaggle[i].x] = MAMA;
						
					}
					break;
				}
	
				if(gaggle[i].x < 0)
				{
					srand(time(NULL));
					gaggle[i].x = 25;
					gaggle[i].y = rand() % 19;
				}
				if(gaggle[i].isHead !=0)
				{
					map[(int)gaggle[i].y][(int)gaggle[i].x] = MAMA;
				}
			}
			
			if(i != 0)
			{
				map[(int)gaggle[i].y][(int)gaggle[i].x] = EMPTY;
				gaggle[i].x = Ax;
				gaggle[i].y = Ay;
				if(gaggle[i].isHead !=0)
				{
					map[(int)gaggle[i].y][(int)gaggle[i].x] = BABY;
				}
			}
			Ax = Bx;
			Ay = By;

		}
	}

	if(direction == 4) //right
	{
		for(int i = 0; i < gaggle.size(); i++)
		{
			Bx = gaggle[i].x;
			By = gaggle[i].y;
			if(i == 0)
			{
				map[(int)gaggle[i].y][(int)gaggle[i].x] = EMPTY;
				gaggle[i].x += .2;
				if((int)gaggle[i].x - (int)Bx == 0)
				{
					if(gaggle[i].isHead !=0)
					{
						map[(int)gaggle[i].y][(int)gaggle[i].x] = MAMA;
						
					}
					break;
				}
	
				if(gaggle[i].x > 25)
				{
					srand(time(NULL));
					gaggle[i].x = 0;
					gaggle[i].y = rand() % 19;
				}
				if(gaggle[i].isHead !=0)
				{
					map[(int)gaggle[i].y][(int)gaggle[i].x] = MAMA;
				}
			}
			if(i != 0)
			{
				map[(int)gaggle[i].y][(int)gaggle[i].x] = EMPTY;
				gaggle[i].x = Ax;
				gaggle[i].y = Ay;
				if(gaggle[i].isHead !=0)
				{
					map[(int)gaggle[i].y][(int)gaggle[i].x] = BABY;
				}
			}
			Ax = Bx;
			Ay = By;

		}

	}


}

void Ducks::update(int** &map) // calls move function
{
	switch(direction)
	{
	case 1: //up
		if(map[(int)gaggle[0].y - 1][(int)gaggle[0].x] == KITTEN1 || map[(int)gaggle[0].y - 1][(int)gaggle[0].x] == KITTEN2 || map[(int)gaggle[0].y - 1][(int)gaggle[0].x] == KITTEN3 || map[(int)gaggle[0].y - 1][(int)gaggle[0].x] == KITTEN4)
		{
			if(map[(int)gaggle[0].y][(int)gaggle[0].x + 1] != KITTEN1 ||map[(int)gaggle[0].y][(int)gaggle[0].x + 1] != KITTEN2 || map[(int)gaggle[0].y][(int)gaggle[0].x + 1] != KITTEN3 || map[(int)gaggle[0].y][(int)gaggle[0].x + 1] != KITTEN4)
				direction = 4;
			else if(map[(int)gaggle[0].y][(int)gaggle[0].x -1] != KITTEN1 || map[(int)gaggle[0].y][(int)gaggle[0].x -1] != KITTEN2 || map[(int)gaggle[0].y][(int)gaggle[0].x -1] != KITTEN3 || map[(int)gaggle[0].y][(int)gaggle[0].x -1] != KITTEN4)
				direction = 3;
			else
			{
				gaggle[0].isHead = false;
				gaggle[gaggle.size() -1].isHead = true;
				direction = 2;
			}
		}
		if(map[(int)gaggle[0].y - 1][(int)gaggle[0].x] == PLAYER)
		{
			direction = 4;
			throw "KILL";
		}
		break;
	case 2: //down
		if(map[(int)gaggle[0].y + 1][(int)gaggle[0].x] == KITTEN1 || map[(int)gaggle[0].y + 1][(int)gaggle[0].x] == KITTEN2 || map[(int)gaggle[0].y + 1][(int)gaggle[0].x] == KITTEN3 || map[(int)gaggle[0].y + 1][(int)gaggle[0].x] == KITTEN4)
		{
			if(map[(int)gaggle[0].y][(int)gaggle[0].x + 1] != KITTEN1 || map[(int)gaggle[0].y][(int)gaggle[0].x + 1] != KITTEN2 || map[(int)gaggle[0].y][(int)gaggle[0].x + 1] != KITTEN3 || map[(int)gaggle[0].y][(int)gaggle[0].x + 1] != KITTEN4)
				direction = 4;
			else if(map[(int)gaggle[0].y][(int)gaggle[0].x -1] != KITTEN1 || map[(int)gaggle[0].y][(int)gaggle[0].x -1] != KITTEN2 || map[(int)gaggle[0].y][(int)gaggle[0].x -1] != KITTEN3 || map[(int)gaggle[0].y][(int)gaggle[0].x -1] != KITTEN4)
				direction = 3;
			else
			{
				gaggle[0].isHead = false;
				gaggle[gaggle.size() -1].isHead = true;
				direction = 1;
			}
		}
		if(map[(int)gaggle[0].y + 1][(int)gaggle[0].x] == PLAYER)
		{
			direction = 3;
			throw "KILL";
		}
		break;
	case 3://left
		if(map[(int)gaggle[0].y][(int)gaggle[0].x - 1] == KITTEN1 || map[(int)gaggle[0].y][(int)gaggle[0].x - 1] == KITTEN2 || map[(int)gaggle[0].y][(int)gaggle[0].x - 1] == KITTEN3 || map[(int)gaggle[0].y][(int)gaggle[0].x - 1] == KITTEN4)
		{
			if(map[(int)gaggle[0].y + 1][(int)gaggle[0].x] != KITTEN1 || map[(int)gaggle[0].y + 1][(int)gaggle[0].x] != KITTEN2 || map[(int)gaggle[0].y + 1][(int)gaggle[0].x] != KITTEN3 || map[(int)gaggle[0].y + 1][(int)gaggle[0].x] != KITTEN4)
				direction = 2;
			else if(map[(int)gaggle[0].y - 1][(int)gaggle[0].x] != KITTEN1 || map[(int)gaggle[0].y - 1][(int)gaggle[0].x] != KITTEN2 || map[(int)gaggle[0].y - 1][(int)gaggle[0].x] != KITTEN3 || map[(int)gaggle[0].y - 1][(int)gaggle[0].x] != KITTEN4)
				direction = 1;
			else
			{
				gaggle[0].isHead = false;
				gaggle[gaggle.size() -1].isHead = true;
				direction = 2;
			}
		}
		if(map[(int)gaggle[0].y][(int)gaggle[0].x - 1] == PLAYER)
		{
			direction = 1;
			throw "KILL";
		}
		break;
	case 4:
		if(map[(int)gaggle[0].y][(int)gaggle[0].x + 1] == KITTEN1 || map[(int)gaggle[0].y][(int)gaggle[0].x + 1] == KITTEN2 || map[(int)gaggle[0].y][(int)gaggle[0].x + 1] == KITTEN3 || map[(int)gaggle[0].y][(int)gaggle[0].x + 1] == KITTEN4)
		{	
			if(map[(int)gaggle[0].y + 1][(int)gaggle[0].x] != KITTEN1 || map[(int)gaggle[0].y + 1][(int)gaggle[0].x] != KITTEN2 || map[(int)gaggle[0].y + 1][(int)gaggle[0].x] != KITTEN3 || map[(int)gaggle[0].y + 1][(int)gaggle[0].x] != KITTEN4)
				direction = 2;
			else if(map[(int)gaggle[0].y - 1][(int)gaggle[0].x] != KITTEN1 || map[(int)gaggle[0].y - 1][(int)gaggle[0].x] != KITTEN2 || map[(int)gaggle[0].y - 1][(int)gaggle[0].x] != KITTEN3 || map[(int)gaggle[0].y - 1][(int)gaggle[0].x] != KITTEN4)
				direction = 1;
			else
			{
				gaggle[0].isHead = false;
				gaggle[gaggle.size() -1].isHead = true;
				direction = 2;
			}
		}
		if(map[(int)gaggle[0].y][(int)gaggle[0].x + 1] == PLAYER)
		{
			direction = 2;
			throw "KILL";
		}
			break;
	default: break;
	}

	for(int i = 0; i < gaggle.size(); i++)
	{
		if(map[(int)gaggle[i].y +1][(int)gaggle[i].x] == BULLET)
		{
			hitAction(i);
		}
	}
	move(map);
}


void Ducks::hitAction(int index)
{
	int doIQuack = gaggle[index].isHead;
	gaggle[index].isHead = 0;		
	bool temp = false;
	for(int i = 0; i < gaggle.size() ; i++)
	{

		if(gaggle[i].isHead != 0)
			temp = true;

	}

	if(temp == false)
		throw "DEADDUCK";
	if(doIQuack != 0)
		throw "QUACK";
}

