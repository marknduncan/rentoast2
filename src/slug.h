#ifndef SLUG_H
#define SLUG_H

#include "Object.h"

using namespace std;

class Slug: public Object
{
public:
	int HP;
	static int objectCount;
	int IDNum;
	double x, y;
	bool isCentipede;

	int direction; //1 up, 2 down, 3 left, 4, right

	Slug()
	{
		HP = 1;
		IDNum = Object::objectCount;
		Object::objectCount++;
		x = 0;
		y = 0;
		isCentipede = false;
		direction = 0;
	}
	~Slug()
	{
		Object::objectCount--;
	}

	virtual void update(int** &map){ }

};

#endif
