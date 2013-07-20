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

int init_opengl() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);

	//Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Initialize clear color
	glClearColor(0.f, 0.f, 0.f, 1.f);

	//Check for error
	GLenum error = glGetError();
	if(error != GL_NO_ERROR) {
		printf( "Error initializing OpenGL! %s\n", gluErrorString(error));
		return -1;
	}

	return 1;
}

int init_screen() {
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		fprintf(stderr, "SDL failed to initialize: %s\n", SDL_GetError());
		return -1;
	}

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, /*SDL_OPENGL | */SDL_HWSURFACE);
	if(screen == NULL) {
		fprintf(stderr, "failed to initialize the screen: %s\n", SDL_GetError());
		return -1;
	}

	/*if(init_opengl() == -1) {
		return -1;
	}*/

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
		fprintf(stderr, ERR_PREFIX "failed to load image: %s!\n", SDL_GetError());
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

void update() {

}

void render() {
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	//Reset modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, 0.f);

	//RYGB Mix
	glBegin( GL_QUADS );
	glColor3f(1.f, 0.f, 0.f); glVertex2f(-50.f, -50.f);
	glColor3f(1.f, 1.f, 0.f); glVertex2f(50.f, -50.f);
	glColor3f(0.f, 1.f, 0.f); glVertex2f(50.f, 50.f);
	glColor3f(0.f, 0.f, 1.f); glVertex2f(-50.f, 50.f);
	glEnd();

	//Update screen
	SDL_GL_SwapBuffers();
}
