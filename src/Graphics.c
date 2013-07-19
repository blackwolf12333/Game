/*
 * Graphics.c
 *
 *  Created on: Jul 19, 2013
 *      Author: blackwolf12333
 */

#include <stdio.h>
#include "Graphics.h"

#define ERR_PREFIX "[SDLTut] "

SDL_Surface *screen = NULL;

int init_screen() {
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		fprintf(stderr, "SDL failed to initialize: %s\n", SDL_GetError());
		return -1;
	}

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE);
	if(screen == NULL) {
		fprintf(stderr, "failed to initialize the screen: %s\n", SDL_GetError());
		return -1;
	}

	SDL_WM_SetCaption("Hello world!", NULL);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY - 300, SDL_DEFAULT_REPEAT_INTERVAL);

	return 0;
}

SDL_Surface *load_image(char *path) {
	SDL_Surface *loadedImage = NULL;
	SDL_Surface *optimizedImage = NULL;

	loadedImage = IMG_Load(path);
	if(loadedImage != NULL) {
		optimizedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
	} else {
		fprintf(stderr, ERR_PREFIX "failed to load image!");
	}

	return optimizedImage;
}

void apply_surface(SDL_Rect *offset_src, SDL_Rect *offset_dest, SDL_Surface *surface, SDL_Surface *destination) {
	if (surface->format->palette && screen->format->palette) {
		SDL_SetColors(screen, surface->format->palette->colors, 0,
				surface->format->palette->ncolors);
	}

	SDL_SetColorKey(surface, SDL_SRCCOLORKEY, SDL_MapRGB(surface->format, 248, 248, 248));
	SDL_BlitSurface(surface, offset_src, destination, offset_dest);
}

SDL_Surface *get_screen() {
	return screen;
}
