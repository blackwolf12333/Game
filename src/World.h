/*
 * World.h
 *
 *  Created on: Jul 19, 2013
 *      Author: blackwolf12333
 */

#ifndef WORLD_H_
#define WORLD_H_

#include "Graphics.h"

#define STEP 30

typedef struct entity_t {
	SDL_Surface *surface;
	int x, y;
} Entity;

typedef struct world_t {
	SDL_Surface *landscape;
	Entity *player;
	SDL_Surface **environment;
} World;

int init_world();
void destroy_world();
void paint_world();

/**
 * This moves the player from his original coordinates to the original coordinates + the argument coordinates
 */
void move_player(int x, int y);

#endif /* WORLD_H_ */
