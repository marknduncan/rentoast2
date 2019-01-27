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
	SDL_Window* screen;
	// SDL_Surface* screen;
	// SDL_Surface* cat1;
	// SDL_Surface* cat2;
	// SDL_Surface* cat3;
	// SDL_Surface* cat4;
	// SDL_Surface* toast;
	// SDL_Surface* bullet;
	// SDL_Surface* mama;
	// SDL_Surface* baby;
	// SDL_Surface* dragon;
	// SDL_Surface* fireball;
	// SDL_Surface* logo;
	SDL_Surface* backgroundSurface;
	SDL_Texture* backgroundTexture;
	// SDL_Surface* start;
	// SDL_Surface* end;
	// SDL_Surface* story;
	// SDL_Surface* select;
	// SDL_Surface* playAgain;
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
	int lives;


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
	void startGame();
	void updateMap();
	bool GameOver();
	void initialize(int level);
	bool checkWin();
	void checkInput();
	void drawScreen();
	SDL_Surface* load_image(string);
	void applySurface(int, int, SDL_Surface*, SDL_Window*,SDL_Texture*);
	void fire();
	void pause();
	bool checkPress();
	void cleanUp();

};
#endif