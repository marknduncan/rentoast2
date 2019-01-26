#ifndef KITTENS_H
#define KITTENS_H

#include <iostream>
#include "Object.h"

using namespace std;

class Kittens : public Object{
public:
	Kittens(int xPos, int yPos);
	~Kittens();
	virtual void update(int** &map);
	virtual void hitAction();

};

#endif