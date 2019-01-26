#ifndef DUCKS_H
#define DUCKS_H

#include <iostream>
#include "Object.h"
#include <vector>
using namespace std;

struct DuckNode
{
	double x, y;
	int isHead;
	DuckNode()
	{
		isHead = 2;
		x = 0;
		y = 0;
	}
	DuckNode(int h, int xpos, int ypos)
	{
		isHead = h;
		x = xpos;
		y = ypos;
	}
	DuckNode& operator=(const DuckNode& other)
	{
		if(this != &other)
		{
			isHead = other.isHead;
			x = other.x;
			y = other.y;
		}
		return *this;
	}
};

class Ducks: public Object
{
	public:
		Ducks(int);
		Ducks(Ducks& );
		~Ducks();
		virtual void update(int** &map); // calls move function, calls collision, and updates coordinates
		virtual void hitAction(int index);
		vector<DuckNode> gaggle;
		
	private:
		
		//private function
		void move(int**); // moves the ducks
		
		
};

#endif