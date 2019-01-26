//Main
#include <iostream>
#include "SDL.h"
#include "Game.cpp"
#include "Object.h"
#include "Player.h"
#include "Ducks.cpp"
#include "Kittens.cpp"
#include "Dragon.cpp"
#include <vector>

using namespace std;

int main( int argc, char* args[] )
{
	Game rentoast;
	try
	{
	rentoast.play();
	}
	catch(...)
	{
	}
	return 0;
}
