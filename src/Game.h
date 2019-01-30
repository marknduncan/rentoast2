#ifndef Game_H
#define Game_H
//Compiler stufff
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
//SDL stuff
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
//Our stuff.
#include "Object.h"
#include "Player.h"
#include "Ducks.h"
#include "Bullet.h"
#include "Kittens.h"
#include "Dragon.h"
#include "Fireball.h"
#include "slug.h"


using namespace std;

//The timer
class Timer
{
    private:
    //The clock time when the timer started
    int startTicks;
    
    //The ticks stored when the timer was paused
    int pausedTicks;
    
    //The timer status
    bool paused;
    bool started;
    
    public:
    
    Timer()
	{
		//Initialize the variables
		startTicks = 0;
		pausedTicks = 0;
		paused = false;
		started = false;    
	}

    
    //The various clock actions
    void start()
	{
    //Start the timer
    started = true;
    
    //Unpause the timer
    paused = false;
    
    //Get the current clock time
    startTicks = SDL_GetTicks();    
	}

    void stop()
	{
    //Stop the timer
    started = false;
    
    //Unpause the timer
    paused = false;    
	}

    void pause()
	{
		//If the timer is running and isn't already paused
		if( ( started == true ) && ( paused == false ) )
		{
			//Pause the timer
			paused = true;
    
			//Calculate the paused ticks
		     pausedTicks = SDL_GetTicks() - startTicks;
	    }
	}

    void unpause()
	{
	    //If the timer is paused
		if( paused == true )
		{
			//Unpause the timer
			paused = false;
    
			//Reset the starting ticks
			startTicks = SDL_GetTicks() - pausedTicks;
			
			//Reset the paused ticks
			pausedTicks = 0;
		}
	}

    
    //Gets the timer's time
    int get_ticks()
	{
		//If the timer is running
		if( started == true )
		{
			//If the timer is paused
			if( paused == true )
			{
				 //Return the number of ticks when the timer was paused
			    return pausedTicks;
			}
			else
			{
			    //Return the current time minus the start time
			    return SDL_GetTicks() - startTicks;
			}    
		}
    
	  //If the timer isn't running
		return 0;    
	}

    
    //Checks the status of the timer
    bool is_started()
	{
		return started;
	}
    bool is_paused()
	{
		return paused;
	}
};


class Game
{
private:
	SDL_Renderer* sdlRenderer;
	SDL_Window* sdlWindow;
	SDL_Texture* sdlTexture;
	
	SDL_Surface* currentBackground;

	SDL_Surface* sdlScreen;

	SDL_Surface* cat1Surface;

	SDL_Surface* cat2Surface;

	SDL_Surface* cat3Surface;

	SDL_Surface* cat4Surface;

	SDL_Surface* toastSurface;

	SDL_Surface* bulletSurface;

	SDL_Surface* mamaSurface;

	SDL_Surface* babySurface;

	SDL_Surface* dragonSurface;

	SDL_Surface* fireballSurface;

	SDL_Surface* logoSurface;

	SDL_Surface* startSurface;

	SDL_Surface* endSurface;

	SDL_Surface* storySurface;

	SDL_Surface* selectSurface;

	SDL_Surface* playAgainSurface;

	SDL_Surface* textSurface;

	TTF_Font* _arcadeFont;

	SDL_Event Done;
	Timer fps;

	Mix_Music* music;
	Mix_Chunk* Quack;
	Mix_Chunk* flare;
	Mix_Chunk* roar;
	Mix_Chunk* laser;
	Mix_Chunk* meow;
	
	int** drawMap;
	int kittenMap[19][25];
	vector<Object*> stuff;
	SDL_Surface* backgroundSurfaces[4];
	int lives;
	int score;

public:
	Game();
	~Game();
	void mainMenu();
	void startMenu();
	void optionMenu();
	void rollCredits();
	void highScore();
	void toggleSound();
	void toggleGore();
	void toggleSFX();
	void instructions();
	void play();
	void loadBackgroundSurface();
	void startGame();
	void updateMap();
	bool GameOver();
	void initialize(int level);
	bool checkWin();
	void checkInput();
	void drawScreen(int);
	void applySurface(int x, int y, SDL_Surface* sdlSurface,SDL_Surface* sdlScreen);
	void fire();
	void pause();
	bool checkPress();
	void cleanUp();
	void printLevel(int);
	void printScore(int);

};
#endif