#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
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
		applySurface(0,0,titleBackground,sdlScreen);
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
	TTF_Init();

	//Set up the audio
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    
	SDL_CreateWindowAndRenderer(1024, 768, SDL_WINDOW_SHOWN, &sdlWindow, &sdlRenderer);
	// sdlWindow = SDL_CreateWindow(
	// 		"RENEGADE TOAST and the DEATH-Y DUCKS of DOOM 2",                  // window title
	// 		SDL_WINDOWPOS_UNDEFINED,           // initial x position
	// 		SDL_WINDOWPOS_UNDEFINED,           // initial y position
	// 		1024,                               // width, in pixels
	// 		768,                               // height, in pixels
	// 		SDL_WINDOW_OPENGL                  // flags - see below
	// 	);

	// //Set up the screen    
	// sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED );


	sdlScreen = SDL_CreateRGBSurface(0, 1024, 768, 32,
                                        0x00FF0000,
                                        0x0000FF00,
                                        0x000000FF,
                                        0xFF000000);

	sdlTexture = SDL_CreateTexture(sdlRenderer,
                                            SDL_PIXELFORMAT_ARGB8888,
                                            SDL_TEXTUREACCESS_STREAMING,
                                            1024, 768);

	SDL_SetWindowTitle(sdlWindow, "RENEGADE TOAST and the DEATH-Y DUCKS of DOOM 2");
	
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

	_arcadeFont = TTF_OpenFont("resources/ARCADECLASSIC.TTF", 24); //18PT SIZE
	_arcadeFontLarge = TTF_OpenFont("resources/ARCADECLASSIC.TTF", 50); //18PT SIZE

	//load backgrounds
	titleBackground = IMG_Load("resources/background.png");
	backgroundSurfaces[0] = IMG_Load("resources/background_2.jpg");
	backgroundSurfaces[1] = IMG_Load("resources/background_3.jpg");
	backgroundSurfaces[2] = IMG_Load("resources/background_4.jpg");

	toastSurface = IMG_Load("resources/toast.png");
	toastLivesSurface = IMG_Load("resources/toast_lives.png");
	cat1Surface = IMG_Load("resources/cat1.png");
	// cat2Surface = IMG_Load("resources/cat2.png");
	// cat3Surface = IMG_Load("resources/cat3.png");
	// cat4Surface = IMG_Load("resources/cat4.png");
	mamaSurface = IMG_Load("resources/mama.png");
	babySurface = IMG_Load("resources/baby.png");
	dragonSurface = IMG_Load("resources/dragon.png");
	bulletSurface = IMG_Load("resources/bullet.png");
	rocketSurface = IMG_Load("resources/rocket.png");

	logoSurface = IMG_Load("resources/rentoast2_logo.png");
	startSurface = IMG_Load("resources/buttonStart.png");
	endSurface = IMG_Load("resources/buttonQuit.png");
	selectSurface = IMG_Load("resources/buttonSelect.png");
	storySurface = IMG_Load("resources/storyScreen2.png");
	fireballSurface = IMG_Load("resources/shoot.png");
	playAgainSurface = IMG_Load("resources/GameOver.png");

	music = Mix_LoadMUS("resources/Battle-of-the-Ancients.wav");

	Quack = Mix_LoadWAV("resources/duck-quack4.wav");
	flare = Mix_LoadWAV("resources/fireball.wav");
	roar = Mix_LoadWAV("resources/creature_snarl2.wav");
	laser = Mix_LoadWAV("resources/LASRFIR2.wav");
	meow = Mix_LoadWAV("resources/angry6.wav");
	ow = Mix_LoadWAV("resources/ow2.wav");

	
	//If there is no music playing, play the music
	if( Mix_PlayingMusic() == 0 )
	{
		Mix_PlayMusic( music, -1 );	 
		Mix_VolumeMusic(MIX_MAX_VOLUME/1.5);
	}

	Mix_Volume(-1,MIX_MAX_VOLUME/3);

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
	score = 0; //initialize score
	activeWeapon = "LASER";
	weaponSurface = bulletSurface;

	while(!quit)
	{
		alive = true;
		won = false;
		lvl = 1;
		lives = 3;
		
		while(alive)
		{
			initialize(lvl);
			loadBackgroundSurface();

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
				drawScreen(lvl);

				if(checkWin() == true)
				{
					won = true;
				}

				if(lives == 0)
				{
					alive = false;
					won = true;
				}

				if( fps.get_ticks() < 40)
				{
                	SDL_Delay( ( 40 ) - fps.get_ticks() );
                }
			}
			won = false;
 			lvl++;
			lives++;
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

	int sum = 0;
    int x;
    ifstream inFile;

	//read high score file
	inFile.open("highscore.txt");

    while (inFile >> x) {
        sum = sum + x;
    }

    inFile.close();

	if(sum < score){
		//write out the current score to a text file for high score
		std::ofstream ofs ("highscore.txt", std::ofstream::out);
		ofs << score;
		ofs.close();
	}
	else{
		score = sum;
	}

	while(!quit)
	{
		printHighScore();
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
				score += 500;
			}
			else if(strncmp(m,"DEADDRAGON",10) == 0)
			{
				Mix_PlayChannel(-1, roar, 0);
				delete stuff[i];
				stuff.erase(stuff.begin() + i);//Kill what you're dealing with.
				score += 1000;
			}
			else if(strncmp(m,"DEADCAT",7) == 0)
			{
				Mix_PlayChannel(-1, meow, 0);
				delete stuff[i];
				stuff.erase(stuff.begin() + i);//Kill what you're dealing with.
				score += 100;
			}
			else if(strncmp(m,"DEAD",4) == 0) //fireball
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
				Mix_PlayChannel(-1, ow, 0);
			}
			else if(strncmp(m,"QUACK",5) == 0)
			{
				Mix_PlayChannel(-1, Quack, 0);
				score += 50;
			}
			
		}
	}
}


void Game::drawScreen(int lvl)
{
	
	applySurface(0,0,currentBackground,sdlScreen);
	printLevel(lvl);
	printScore();
	printLives();

	for(int y = 0; y < 19; y++)
	{
		for(int x = 0; x < 25; x++)
		{
			switch(drawMap[y][x])
			{
				case PLAYER: applySurface(x * 40, y * 40, toastSurface, sdlScreen); break;
				case BULLET: applySurface(x * 40, y * 40, weaponSurface, sdlScreen); break;
				case MAMA: applySurface(x * 40, y * 40, mamaSurface, sdlScreen); break;
				case BABY: applySurface(x * 40, y * 40, babySurface, sdlScreen); break;
				case KITTEN1: applySurface(x * 40, y * 40, cat1Surface, sdlScreen); break;
				// case KITTEN2: applySurface(x * 40, y * 40, cat2Surface, sdlScreen); break;
				// case KITTEN3: applySurface(x * 40, y * 40, cat3Surface, sdlScreen); break;
				// case KITTEN4: applySurface(x * 40, y * 40, cat4Surface, sdlScreen); break;
				case DRAGON: applySurface(x * 40, y * 40, dragonSurface, sdlScreen); break;
				case FIREBALL: applySurface(x * 40, y * 40, fireballSurface, sdlScreen); break;
				default:  break;//do nothing
			}
		}
	}
	SDL_RenderPresent(sdlRenderer);
}

//loads a random background to the currentBackground surface
void Game::loadBackgroundSurface(){
	int RandIndex = rand() % 3; //generates a random number between 0 and 2
	currentBackground = backgroundSurfaces[RandIndex];
}

void Game::startMenu()
{
	bool quit = false;
	int choice = 0;
	while(!quit)
	{
		applySurface(0,0,titleBackground,sdlScreen);
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
					case SDLK_RETURN: 
						pause();
						break;
					case SDLK_SPACE: 
						fire();
						break;
					case SDLK_z:
						toggleWeapon();
						break;
					case SDLK_x:
						toggleWeapon();
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

void Game::printScore(){

	SDL_Color white = {255, 255, 255};
	char scoreString[32];

	sprintf(scoreString, "%d", score);

  	textSurface = TTF_RenderText_Blended(_arcadeFont, scoreString, white);

	applySurface(900,725,textSurface,sdlScreen);
}

void Game::printLives(){

	SDL_Color white = {255, 255, 255};
	char livesString[32];

	sprintf(livesString, "%d", lives);

  	textSurface = TTF_RenderText_Blended(_arcadeFont, livesString, white);

	applySurface(900,700,textSurface,sdlScreen);
	applySurface(875,700,toastLivesSurface,sdlScreen);

}

void Game::printHighScore(){

	SDL_Color white = {255, 255, 255};
	char scoreString[32];
	char finalScoreString[64] = "High  Score ";

	sprintf(scoreString, "%d", score);
	strcat(finalScoreString,scoreString);

  	textSurface = TTF_RenderText_Blended(_arcadeFontLarge, finalScoreString, white);

	applySurface(315,650,textSurface,sdlScreen);
}

void Game::printLevel(int level){

	SDL_Color white = {255, 255, 255};
	char levelString[32];
	char finalLevelString[64] = "Level ";

	sprintf(levelString, "%d", level);
	strcat(finalLevelString,levelString);

  	textSurface = TTF_RenderText_Blended(_arcadeFont, finalLevelString, white);

	applySurface(20,725,textSurface,sdlScreen);
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

void Game::toggleWeapon(){
	if(strncmp(activeWeapon,"LASER",5) == 0 ){
		weaponSurface = rocketSurface;
		activeWeapon = "ROCKET";
	}
	else{
		weaponSurface = bulletSurface;
		activeWeapon = "LASER";
	}
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

	// When we exit the loop clean up and exit Audio
	if (Mix_PlayingMusic()) {
		Mix_HaltMusic();
	}

	Mix_FreeMusic(music);

	Mix_FreeChunk(ow);
	Mix_FreeChunk(flare);
	Mix_FreeChunk(roar);
	Mix_FreeChunk(laser);
	Mix_FreeChunk(meow);

	Mix_CloseAudio();

  	TTF_CloseFont(_arcadeFont);

  	SDL_FreeSurface(textSurface);
	SDL_FreeSurface(sdlScreen);
	SDL_FreeSurface(toastSurface);
	SDL_FreeSurface(bulletSurface);
	// SDL_FreeSurface(weaponSurface);
	SDL_FreeSurface(rocketSurface);
	SDL_FreeSurface(dragonSurface);
	SDL_FreeSurface(mamaSurface);
	SDL_FreeSurface(babySurface);
	SDL_FreeSurface(cat1Surface);
	// SDL_FreeSurface(cat2Surface);
	// SDL_FreeSurface(cat3Surface);
	// SDL_FreeSurface(cat4Surface);
	SDL_FreeSurface(storySurface);
	SDL_FreeSurface(startSurface);
	SDL_FreeSurface(endSurface);
	SDL_FreeSurface(fireballSurface);
	SDL_FreeSurface(logoSurface);

	for(SDL_Surface* backgroundSurface : backgroundSurfaces){
		SDL_FreeSurface(backgroundSurface);
	}

	SDL_FreeSurface(selectSurface);
	SDL_FreeSurface(playAgainSurface);
 
    SDL_DestroyWindow(sdlWindow);
 	TTF_Quit();
	// Always be sure to clean up
	SDL_Quit();
	exit(0);

}