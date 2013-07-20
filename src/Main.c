/*
 ============================================================================
 Name        : SDLTut0.c
 Author      : blackwolf12333
 Version     :
 Copyright   : Copyleft under GPLv3
 Description : A game
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "Graphics.h"
#include "World.h"

int main(void) {
	SDL_Event event;
	int quit = 0;

	if(init_screen() == -1) {
		return EXIT_FAILURE;
	}

	if(init_world() == -1) {
		return EXIT_FAILURE;
	}

	while(!quit) {
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
				quit = 1;
				break;
			case SDL_KEYDOWN:
				if(SDL_GetKeyState(NULL)[SDLK_UP]) {
					move_player(0, -STEP);
				}
				if(SDL_GetKeyState(NULL)[SDLK_RIGHT]) {
					move_player(STEP, 0);
				}
				if(SDL_GetKeyState(NULL)[SDLK_DOWN]) {
					move_player(0, STEP);
				}
				if(SDL_GetKeyState(NULL)[SDLK_LEFT]) {
					move_player(-STEP, 0);
				}
				if(SDL_GetKeyState(NULL)[SDLK_ESCAPE]) {
					quit = 1;
					break;
				}
				break;
			}
		}
		paint_world();
		/*update();
		render();*/
	}

	destroy_world();
	SDL_Quit();
	return EXIT_SUCCESS;
}
