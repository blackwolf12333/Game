/*
 * Graphics.h
 *
 *  Created on: Jul 19, 2013
 *      Author: blackwolf12333
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>

int init_screen();

SDL_Surface *load_image(char *path);
void apply_surface(SDL_Rect *offset_src, SDL_Rect *offset_dest, SDL_Surface *surface, SDL_Surface *destination);

SDL_Surface *get_screen();

void update();
void render();

#endif /* GRAPHICS_H_ */
