/*
code.c

  A simple collision simulator that uses the SDL library.

  This file is written by Jagger Fifield and may use external software.
  Please read all block comments to find more information.
*/

/*
Simple DirectMedia Layer
Copyright (C) 1997-2020 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
       claim that you wrote the original software. If you use this software
       in a product, an acknowledgment in the product documentation would be
       appreciated but is not required. 
    2. Altered source versions must be plainly marked as such, and must not be
       misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.
*/

/*
  SDL_image:  An example image loading library for use with SDL
  Copyright (C) 1997-2019 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

bool init(void);
bool loadMedia(void);
SDL_Surface* loadSurface(char* path);
void _close(void);

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gBall = NULL;
SDL_Surface* gPNG_Ball = NULL;

int main(int argc, char *argv[]){
	if(!init()){
		printf("Failed to initalize!\n");
	}else{
		if(!loadMedia()){
			printf("Failed to load media!\n");
		}else{

			bool quit = false;
			SDL_Event e;

    		SDL_BlitSurface(gBall, NULL, gScreenSurface, NULL);

			SDL_Rect dest;
			dest.x = 400;
			dest.y = 100;
    		
    		SDL_BlitSurface(gPNG_Ball, NULL, gScreenSurface, &dest);
    		SDL_UpdateWindowSurface(gWindow);

			while(!quit){
				while(SDL_PollEvent(&e) !=0){
					if(e.type == SDL_QUIT){
						quit = true;
						printf("Exiting!\n");
					}
				}
			}
		}
	}

	_close();
	
	return 0;
}

bool init(void){
	bool success = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL could not init! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}else{
		gWindow = SDL_CreateWindow("collisions", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920/2, 1080/2, SDL_WINDOW_SHOWN);
		if(gWindow == NULL){
			printf("SDL could not init! SDL_Error: %s\n", SDL_GetError());	
			success = false;
		}else{
			int imgFlags = IMG_INIT_PNG;
			if(!(IMG_Init(imgFlags) & imgFlags)){
				printf("SDL_image cound not init! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}else{
				gScreenSurface = SDL_GetWindowSurface(gWindow);
			}
		}
	}
	return success;
}

SDL_Surface* loadSurface(char* path){
	SDL_Surface* optimisedSurface = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path);
	if(loadedSurface == NULL){
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	}else{
		optimisedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
		if(optimisedSurface == NULL){
			printf("Unable to optimse image %s! SDL Error: %s\n", path, SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}
	return optimisedSurface;
}

bool loadMedia(void){
	bool success = true;

	gPNG_Ball = loadSurface("./ball.png");
	if(gPNG_Ball == NULL){
		printf("Unable to load image %s! SDL_Error: %s\n", "./ball.png", SDL_GetError());
		success = false;
	}

	gBall = SDL_LoadBMP("./ball.bmp");
	if(gBall == NULL){
		printf("Unalbe to load image %s! SDL_Error: %s\n", "./ball.bmp", SDL_GetError());
		success = false;
	}
	return success;
}

void _close(void){
	SDL_FreeSurface(gBall);
	gBall = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
	return;
}
