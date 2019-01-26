//Main
#include <iostream>
#include "SDL.h"
#include "Game.h"
#include "Object.h"
#include "Player.h"
#include "Ducks.h"
#include "Kittens.h"
#include "Dragon.h"
#include <vector>

using namespace std;

int main( int argc, char* args[] )
{
	Game centipede;
	try
	{
	centipede.play();
	}
	catch(...)
	{
	}
	return 0;
}
