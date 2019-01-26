#include <iostream>
#include <cstdlib>
#include "Game.h"
#include "Object.h"
#include "SDL_image.h"

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
		applySurface(0,0, background, screen);
		applySurface(112, 10, logo, screen);
		applySurface(112, 660, start, screen);
		applySurface(662, 660, end, screen);

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
			applySurface(112, 660, select, screen);
		}
		else if(selection == 1)
		{
			applySurface(662, 660, select, screen);
		}

		SDL_Flip(screen);
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
		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
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
    
    //Set up the screen
    screen = SDL_SetVideoMode( 1024, 768, 32, SDL_SWSURFACE );
    
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    
    
    //Set the window caption
    SDL_WM_SetCaption( "RENEGADE TOAST and the DEATH-y DUCKS of DOOM.", NULL );
    

	background = IMG_Load("background.png");
	toast = IMG_Load("toast.png");
	cat1 = IMG_Load("cat1.png");
	cat2 = IMG_Load("cat2.png");
	cat3 = IMG_Load("cat3.png");
	cat4 = IMG_Load("cat4.png");
	mama = IMG_Load("mama.png");
	baby = IMG_Load("baby.png");
	dragon = IMG_Load("dragon.png");
	bullet = IMG_Load("bullet.png");
	logo = IMG_Load("logo.png");
	start = IMG_Load("buttonStart.png");
	end = IMG_Load("buttonQuit.png");
	select = IMG_Load("buttonSelect.png");
	story = IMG_Load("storyScreenNoWeapons.png");
	fireball = IMG_Load("shoot.png");
	playAgain = IMG_Load("gameOver.png");
	music = Mix_LoadMUS("guerilla-Shrak-1146.wav");
	Quack = Mix_LoadWAV("duck-quack4.wav");
	flare = Mix_LoadWAV("fireball.wav");
	roar = Mix_LoadWAV("creature_snarl2.wav");
	laser = Mix_LoadWAV("Laser_ca-Intermed-563.wav");
	meow = Mix_LoadWAV("angry6.wav");


	applySurface(0, 0, background, screen);

	SDL_Flip(screen);




	Mix_PlayMusic(music, -1);

	try{
	mainMenu();
	}
	catch(...)
	{
	}

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

				SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
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
		if(!quit && gameOver() == false)
		{
			quit = true;
		}
		

	}
	if(leaveGame)
	{
		throw "ALLDONE";
	}
}

bool Game::gameOver()
{
	bool quit = false;
	bool keepPlaying = true;
	while(!quit)
	{
		applySurface(112, 10, playAgain, screen);
		SDL_Flip(screen);
		
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
			if(m == "DEADDUCK")
			{
				Mix_PlayChannel(-1, Quack, 0);
				delete stuff[i];
				stuff.erase(stuff.begin() + i);//Kill what you're dealing with.
			}
			else if(m == "DEADDRAGON")
			{
				Mix_PlayChannel(-1, roar, 0);
				delete stuff[i];
				stuff.erase(stuff.begin() + i);//Kill what you're dealing with.
			}
			else if(m == "DEADCAT")
			{
				Mix_PlayChannel(-1, meow, 0);
				delete stuff[i];
				stuff.erase(stuff.begin() + i);//Kill what you're dealing with.
			}
			else if(m == "DEAD")
			{
				delete stuff[i];
				stuff.erase(stuff.begin() + i);//Kill what you're dealing with.
			}
			else if(m == "FIRE")
			{
				Mix_PlayChannel(-1, flare, 0);
				Fireball* f = new Fireball(stuff[i]->x, stuff[i]->y+1);
				stuff.push_back(f);
			}
			else if(m == "KILL")
			{
				lives--;
			}
			else if(m == "QUACK")
			{
				Mix_PlayChannel(-1, Quack, 0);
			}
			
		}
	}
}


void Game::drawScreen()
{
	
	applySurface(0,0, background, screen);
	for(int y = 0; y < 19; y++)
	{
		for(int x = 0; x < 25; x++)
		{
			switch(drawMap[y][x])
			{
			case PLAYER: applySurface(x * 40, y * 40, toast, screen); break;
			case BULLET: applySurface(x * 40, y * 40, bullet, screen); break;
			case MAMA: applySurface(x * 40, y * 40, mama, screen); break;
			case BABY: applySurface(x * 40, y * 40, baby, screen); break;
			case KITTEN1: applySurface(x * 40, y * 40, cat1, screen); break;
			case KITTEN2: applySurface(x * 40, y * 40, cat2, screen); break;
			case KITTEN3: applySurface(x * 40, y * 40, cat3, screen); break;
			case KITTEN4: applySurface(x * 40, y * 40, cat4, screen); break;
			case DRAGON: applySurface(x * 40, y * 40, dragon, screen); break;
			case FIREBALL: applySurface(x * 40, y * 40, fireball, screen); break;
			default:  break;//do nothing
			}
		}
	}
	SDL_Flip(screen);
}

void Game::startMenu()
{
	bool quit = false;
	int choice = 0;
	while(!quit)
	{
		applySurface(0,0, background, screen);
		applySurface(112, 10, story, screen);

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
		SDL_Flip(screen);
		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
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


void Game::applySurface( int x, int y, SDL_Surface* start, SDL_Surface* finish )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    
    SDL_BlitSurface( start, NULL, finish, &offset );
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
	SDL_FreeSurface(screen);
	SDL_FreeSurface(toast);
	SDL_FreeSurface(bullet);
	SDL_FreeSurface(dragon);
	SDL_FreeSurface(mama);
	SDL_FreeSurface(baby);
	SDL_FreeSurface(cat1);
	SDL_FreeSurface(cat2);
	SDL_FreeSurface(cat3);
	SDL_FreeSurface(cat4);
	SDL_FreeSurface(story);
	SDL_FreeSurface(start);
	SDL_FreeSurface(end);
	SDL_FreeSurface(fireball);
	SDL_FreeSurface(logo);
	SDL_FreeSurface(background);
	SDL_FreeSurface(select);
	SDL_FreeSurface(playAgain);
}