#include <iostream>
#include <cstdlib>
#include "Game.h"
#include "Object.h"
#include "SDL_image.h"
#define SHAPE_SIZE 16

using namespace std;

Game::Game()
{	
	drawMap = new int*[19];
	for(int i = 0; i < 24; i++)
	{
		drawMap[i] = new int[25];
	}
}

Game::~Game()
{
	cleanUp();
}

void Game::mainMenu()
{
	bool quit = false;
	int choice = 0;
	int selection = 0;

	while(!quit)
	{
		applySurface(0,0,backgroundSurface,sdlScreen);
		applySurface(112, 10, logoSurface, sdlScreen);
		applySurface(112, 660, startSurface, sdlScreen);
		applySurface(662, 660, endSurface, sdlScreen);

		if(SDL_PollEvent(&Done))
		{
			if(Done.type == SDL_KEYDOWN)
			{
				switch( Done.key.keysym.sym )
				{
					case SDLK_LEFT: selection++; 
						if(selection > 1)
						{
							selection = 0;
						}
						break;
					case SDLK_RIGHT: selection--; 
						if(selection < 0)
						{
							selection = 1;
						}
						break;
					case SDLK_ESCAPE: choice = 2; break;
					case SDLK_SPACE: choice = selection + 1; break;
					default: break;
				}
					
			}
			else if (Done.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		if(selection == 0)
		{
			applySurface(112, 660, selectSurface, sdlScreen);
		}
		else if(selection == 1)
		{
			applySurface(662, 660, selectSurface, sdlScreen);
		}

		SDL_RenderPresent(sdlRenderer);

		try
		{
			switch(choice)
			{
				case 1: startMenu(); choice = 0; break;
				case 2: quit = true;
				default: break;
			}
		}
		catch(const char*)
		{
			quit = true;
		}

		SDL_FillRect( sdlScreen, &sdlScreen->clip_rect, SDL_MapRGB( sdlScreen->format, 0xFF, 0xFF, 0xFF ) );
	}

}

void Game::optionMenu()
{
	int choice = 0;
	while(true)
	{
		//show logo
		//show buttons
		switch(choice)
		{
		case 1: toggleGore(); break;
		case 2: toggleSound(); break;
		case 3: toggleSFX(); break;
		case 4: return;
		default: break;
		}
	}

}

void Game::rollCredits()
{
	bool quit = false;
	while(!quit)
	{
		//show credits
		//if enter pressed, set quit to true.
	}

}

void Game::highScore()
{
	bool quit = false;
	while(!quit)
	{
		//show highscores
		//if enter pressed, set quit to true.
	}
}

void Game::toggleSound()
{
	//SDL stuff to switch if music is on or off.
}

void Game::toggleGore()
{
	//SDL stuff to switch Gore on or off.
}

void Game::toggleSFX()
{
	//same thing, but with Sound FX
}

void Game::instructions()
{
	bool quit = false;
	while(!quit)
	{
		//show instructions
		//if enter pressed, set quit to true.
	}
}

void Game::play()
{
	//Initialize all SDL subsystems
    SDL_Init( SDL_INIT_EVERYTHING );
    
	//Set up the audio
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    
	//Set up the screen    
	SDL_CreateWindowAndRenderer(1024, 768, SDL_WINDOW_SHOWN, &sdlWindow, &sdlRenderer);

	sdlScreen = SDL_CreateRGBSurface(0, 1024, 768, 32,
                                        0x00FF0000,
                                        0x0000FF00,
                                        0x000000FF,
                                        0xFF000000);

	sdlTexture = SDL_CreateTexture(sdlRenderer,
                                            SDL_PIXELFORMAT_ARGB8888,
                                            SDL_TEXTUREACCESS_STREAMING,
                                            1024, 768);

	//Set the window caption		 
    SDL_SetWindowTitle(sdlWindow, "RENEGADE TOAST and the DUCKS of DEATH-Y DOOM.");
	
	//Set the app icon
	SDL_Surface *iconSurface;
  	iconSurface = IMG_Load("resources/toast.png");
 	SDL_SetWindowIcon(sdlWindow, iconSurface);
 	SDL_FreeSurface(iconSurface);//free the surface

	//Necessary to fix a bug with the SDL2 rendering
	SDL_PumpEvents();
	SDL_SetWindowSize(sdlWindow, 1024, 768);

	// Blank out the renderer with all black
    SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 0);
    SDL_RenderClear(sdlRenderer);

	//replace with textures like above
	backgroundSurface = IMG_Load("resources/background.png");
	toastSurface = IMG_Load("resources/toast.png");
	cat1Surface = IMG_Load("resources/cat1.png");
	cat2Surface = IMG_Load("resources/cat2.png");
	cat3Surface = IMG_Load("resources/cat3.png");
	cat4Surface = IMG_Load("resources/cat4.png");
	mamaSurface = IMG_Load("resources/mama.png");
	babySurface = IMG_Load("resources/baby.png");
	dragonSurface = IMG_Load("resources/dragon.png");
	bulletSurface = IMG_Load("resources/bullet.png");
	logoSurface = IMG_Load("resources/logo.png");
	startSurface = IMG_Load("resources/buttonStart.png");
	endSurface = IMG_Load("resources/buttonQuit.png");
	selectSurface = IMG_Load("resources/buttonSelect.png");
	storySurface = IMG_Load("resources/storyScreenNoWeapons.png");
	fireballSurface = IMG_Load("resources/shoot.png");
	playAgainSurface = IMG_Load("resources/GameOver.png");

	music = Mix_LoadMUS("resources/guerilla-Shrak-1146.wav");

	Quack = Mix_LoadWAV("resources/duck-quack4.wav");
	flare = Mix_LoadWAV("resources/fireball.wav");
	roar = Mix_LoadWAV("resources/creature_snarl2.wav");
	laser = Mix_LoadWAV("resources/Laser_ca-Intermed-563.wav");
	meow = Mix_LoadWAV("resources/angry6.wav");

	
	//If there is no music playing, play the music
	if( Mix_PlayingMusic() == 0 )
	{
		Mix_PlayMusic( music, -1 );	 
	}

	mainMenu();

}

void Game::startGame()
{
	bool quit = false;
	bool leaveGame = false;
	bool alive = true;
	int lvl = 1;
	bool won = false;
	lives = 3;
	
	while(!quit)
	{
		alive = true;
		won = false;
		lvl = 1;
		lives = 3;
		while(alive)
		{
			initialize(lvl);
			while(!won)
			{
				fps.start();
				try{
				checkInput();
				}
				catch(const char*)
				{
					won = true;
					quit = true;
					alive = false;
					leaveGame = true;
				}
				updateMap();

				SDL_FillRect( sdlScreen, &sdlScreen->clip_rect, SDL_MapRGB( sdlScreen->format, 0xFF, 0xFF, 0xFF ) );
				drawScreen();

				if(checkWin() == true)
				{
					won = true;
				}
				if(lives == 0)
				{
					alive = false;
					won = true;
				}
				if( fps.get_ticks() < 20)
				{
                SDL_Delay( ( 20 ) - fps.get_ticks() );
                }
			}
			won = false;
 			lvl++;
		}
		if(!quit && GameOver() == false)
		{
			quit = true;
		}
		

	}
	if(leaveGame)
	{
		throw "ALLDONE";
	}
}

bool Game::GameOver()
{
	bool quit = false;
	bool keepPlaying = true;
	while(!quit)
	{
		applySurface(112, 10, playAgainSurface, sdlScreen);
		SDL_RenderPresent(sdlRenderer);

		if(SDL_PollEvent(&Done))
		{
			if(Done.type == SDL_KEYDOWN)
			{
				switch( Done.key.keysym.sym )
				{
					case SDLK_RETURN:
					case SDLK_y:  
						keepPlaying = true;
						quit = true;
						break;
					case SDLK_ESCAPE:
					case SDLK_n: 
						keepPlaying = false;
						quit = true;
						break;
					default: break;
				}
				
			}
		}
	}
	return keepPlaying;
}

void Game::updateMap()
{
	for(int i = 0; i < stuff.size(); i++)
	{
		try{
			stuff[i]->update(drawMap);
		}
		catch(const char* m)
		{
			if(strncmp(m,"DEADDUCK",8) == 0)
			{
				Mix_PlayChannel(-1, Quack, 0);
				delete stuff[i];
				stuff.erase(stuff.begin() + i);//Kill what you're dealing with.
			}
			else if(strncmp(m,"DEADDRAGON",10) == 0)
			{
				Mix_PlayChannel(-1, roar, 0);
				delete stuff[i];
				stuff.erase(stuff.begin() + i);//Kill what you're dealing with.
			}
			else if(strncmp(m,"DEADCAT",7) == 0)
			{
				Mix_PlayChannel(-1, meow, 0);
				delete stuff[i];
				stuff.erase(stuff.begin() + i);//Kill what you're dealing with.
			}
			else if(strncmp(m,"DEAD",4) == 0)
			{
				delete stuff[i];
				stuff.erase(stuff.begin() + i);//Kill what you're dealing with.
			}
			else if(strncmp(m,"FIRE",4) == 0)
			{
				Mix_PlayChannel(-1, flare, 0);
				Fireball* f = new Fireball(stuff[i]->x, stuff[i]->y+1);
				stuff.push_back(f);
			}
			else if(strncmp(m,"KILL",4) == 0)
			{
				lives--;
			}
			else if(strncmp(m,"QUACK",5) == 0)
			{
				Mix_PlayChannel(-1, Quack, 0);
			}
			
		}
	}
}


void Game::drawScreen()
{
	
	applySurface(0,0, backgroundSurface, sdlScreen);
	for(int y = 0; y < 19; y++)
	{
		for(int x = 0; x < 25; x++)
		{
			switch(drawMap[y][x])
			{
			case PLAYER: applySurface(x * 40, y * 40, toastSurface, sdlScreen); break;
			case BULLET: applySurface(x * 40, y * 40, bulletSurface, sdlScreen); break;
			case MAMA: applySurface(x * 40, y * 40, mamaSurface, sdlScreen); break;
			case BABY: applySurface(x * 40, y * 40, babySurface, sdlScreen); break;
			case KITTEN1: applySurface(x * 40, y * 40, cat1Surface, sdlScreen); break;
			case KITTEN2: applySurface(x * 40, y * 40, cat2Surface, sdlScreen); break;
			case KITTEN3: applySurface(x * 40, y * 40, cat3Surface, sdlScreen); break;
			case KITTEN4: applySurface(x * 40, y * 40, cat4Surface, sdlScreen); break;
			case DRAGON: applySurface(x * 40, y * 40, dragonSurface, sdlScreen); break;
			case FIREBALL: applySurface(x * 40, y * 40, fireballSurface, sdlScreen); break;
			default:  break;//do nothing
			}
		}
	}
	SDL_RenderPresent(sdlRenderer);
}

void Game::startMenu()
{
	bool quit = false;
	int choice = 0;
	while(!quit)
	{
		applySurface(0,0, backgroundSurface, sdlScreen);
		applySurface(112, 10, storySurface, sdlScreen);

		try
		{
			if(SDL_PollEvent(&Done))
			{
				if(Done.type == SDL_KEYDOWN)
				{
					switch( Done.key.keysym.sym )
						{
							case SDLK_SPACE:
							case SDLK_RETURN: 
								startGame(); 
								break;
							case SDLK_ESCAPE: quit = true; break;
							default: break;
						}
				}
				else if(Done.type == SDL_QUIT)
				{
					
				}
			}
		}
		catch(const char*)
		{
			throw "ALLDONE";
		}

		SDL_RenderPresent(sdlRenderer);

		SDL_FillRect( sdlScreen, &sdlScreen->clip_rect, SDL_MapRGB( sdlScreen->format, 0xFF, 0xFF, 0xFF ) );
	}
}

void Game::checkInput()
{
		
	if(SDL_PollEvent(&Done))
		{
			if(Done.type == SDL_KEYDOWN)
			{
				switch( Done.key.keysym.sym )
				{
					case SDLK_LEFT:
						stuff[0]->direction = 3;
						break;
					case SDLK_RIGHT: 
						stuff[0]->direction = 4;
						break;
					case SDLK_UP:
						stuff[0]->direction = 1;
						break;
					case SDLK_DOWN:
						stuff[0]->direction = 2;
						break;
					case SDLK_ESCAPE: 
						pause();
						break;
					case SDLK_SPACE: 
						fire();
						break;
					default: break;
				}
				
			}
			else if(Done.type == SDL_QUIT)
			{
				throw "ALLDONE";
			}
		}
			
}

bool Game::checkWin()
{
	bool won = true;
	for(int i = 0; i < stuff.size(); i++)
	{
		if(stuff[i]->isCentipede)
			won = false;
	}
	return won;
}

void Game::initialize(int level)
{
	stuff.erase(stuff.begin(), stuff.end());
	Player* P1 = new Player(11, 18);
	stuff.push_back(P1);	
	srand(time(NULL));
	int xPos = rand() % 25;
	int yPos = rand() % 19 + 1;
	for(int y = 0; y < 19; y++)
	{
		for(int x = 0; x < 25; x++)
		{
			kittenMap[y][x] = 0;
			drawMap[y][x] = 0;
		}
	}
	for(int i = 0; i <= 5 * level; i++)
	{
		xPos = rand() % 19 + 1;
		yPos = rand() % 12;
		while(kittenMap[yPos][xPos])
		{
			xPos = rand() % 25;
			yPos = rand() % 15 + 1;
		}
		Kittens* temp = new Kittens(xPos, yPos);
		stuff.push_back(temp);
		kittenMap[yPos][xPos] = 1;
	}
	Ducks* Quack = new Ducks(5 + level);
	stuff.push_back(Quack);
	for(int i = 0; i < level; i++)
	{
		Dragon* boom = new Dragon(rand() % 8);
		stuff.push_back(boom);
	}

}


void Game::applySurface(int x, int y, SDL_Surface* sdlSurface,SDL_Surface* sdlScreen)
{
 	SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    
	//blit surface to the screen surface
    SDL_BlitSurface( sdlSurface, NULL, sdlScreen, &offset );

	SDL_UpdateTexture(sdlTexture, NULL, sdlScreen->pixels, sdlScreen->pitch);
	SDL_RenderClear(sdlRenderer);
    SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL);
}

void Game::fire()
{
	Mix_PlayChannel(-1, laser, 0);
	Bullet* p = new Bullet(stuff[0]->x, stuff[0]->y-1);
	stuff.push_back(p);
}

void Game::pause()
{
	bool quit = false;
	while(!quit)
	{
		if(SDL_PollEvent(&Done))
		{
			if(Done.type == SDL_KEYDOWN)
			{
				switch( Done.key.keysym.sym )
				{
					case SDLK_ESCAPE: 
						quit = true;
						break;
					default: break;
				}
				
			}
			else if(Done.type == SDL_QUIT)
			{

			}
		}
	}
}

void Game::cleanUp()
{
	SDL_DestroyTexture(sdlTexture);
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);

	// When we exit the loop clean up and exit Audio
	if (Mix_PlayingMusic()) {
		Mix_HaltMusic();
	}

	Mix_FreeMusic(music);
	Mix_CloseAudio();

	SDL_FreeSurface(sdlScreen);
	SDL_FreeSurface(toastSurface);
	SDL_FreeSurface(bulletSurface);
	SDL_FreeSurface(dragonSurface);
	SDL_FreeSurface(mamaSurface);
	SDL_FreeSurface(babySurface);
	SDL_FreeSurface(cat1Surface);
	SDL_FreeSurface(cat2Surface);
	SDL_FreeSurface(cat3Surface);
	SDL_FreeSurface(cat4Surface);
	SDL_FreeSurface(storySurface);
	SDL_FreeSurface(startSurface);
	SDL_FreeSurface(endSurface);
	SDL_FreeSurface(fireballSurface);
	SDL_FreeSurface(logoSurface);
	SDL_FreeSurface(backgroundSurface);
	SDL_FreeSurface(selectSurface);
	SDL_FreeSurface(playAgainSurface);

	// Always be sure to clean up
	SDL_Quit();
	exit(0);

}