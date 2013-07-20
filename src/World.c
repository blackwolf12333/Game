/*
 * World.c
 *
 *  Created on: Jul 19, 2013
 *      Author: blackwolf12333
 */

#include <stdio.h>
#include <stdlib.h>
#include "World.h"
#include "WorldLoader.h"

#define WORLD_DIR "/home/blackwolf12333/workspace/Game/world"

World *world = NULL;

int world_border_detection(SDL_Rect *offset) {
	int detected = 0;
	if((offset->x + SCREEN_WIDTH) > world->landscape->w) {
		offset->x = (world->landscape->w / 2) - (get_screen()->w / 2);
		world->player->x -= 30;
		detected = 1;
	}
	if((offset->y + SCREEN_HEIGHT) > world->landscape->h) {
		offset->y = (world->landscape->h/ 2) - (get_screen()->h / 2);
		world->player->y -= 30;
		detected = 1;
	}
	if(offset->x < 0) {
		offset->x = 0;
		world->player->x += 30;
		detected = 1;
	}
	if(offset->y < 0) {
		offset->y = 0;
		world->player->y += 30;
		detected = 1;
	}
	return detected;
}

void paint_world() {
	SDL_FillRect(get_screen(), &get_screen()->clip_rect, SDL_MapRGB( get_screen()->format, 0xFF, 0xFF, 0xFF ) );
	SDL_Rect offset;

	offset.x = (world->landscape->w / 2) - (get_screen()->w / 2) + world->player->x;
	offset.y = (world->landscape->h / 2) - (get_screen()->h / 2) + world->player->y;
	int border_detected = world_border_detection(&offset);
	offset.w = SCREEN_WIDTH;
	offset.h = SCREEN_HEIGHT;

	apply_surface(&offset, NULL, world->landscape, get_screen());

	if(border_detected) {
		/*offset.x = world->player->x / STEP;
		offset.y = world->player->y / STEP;*/
		// make this so that the player can move to the edge of the screen/world
		offset.x = (get_screen()->w / 2) - (world->player->surface->w / 2);
		offset.y = (get_screen()->h / 2) - (world->player->surface->h / 2);
	} else {
		offset.x = (get_screen()->w / 2) - (world->player->surface->w / 2);
		offset.y = (get_screen()->h / 2) - (world->player->surface->h / 2);
	}

	apply_surface(NULL, &offset, world->player->surface, get_screen());

	SDL_Flip(get_screen());
}

int init_world() {
	world = malloc(sizeof(*world));

	if(world == NULL) {
		fprintf(stderr, "THE UNIVERSE HAS COLLAPSED :O");
		return -1;
	}

	world->landscape = NULL;
	world->player = NULL;

	/*world->landscape = load_image(WORLD_DIR "/landscape.png");
	world->player = malloc(sizeof(*world->player));
	world->player->surface = load_image(WORLD_DIR "/characters/player0.png");
	world->player->x = 320;
	world->player->y = 240;*/

	world = load_world(WORLD_DIR "/world_description.wd");

	return 0;
}

void destroy_world() {
	SDL_FreeSurface(world->landscape);
	SDL_FreeSurface(world->player->surface);
	free(world);
}

void move_player(int x, int y) {
	world->player->x += x;
	world->player->y += y;
}
