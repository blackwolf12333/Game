/*
 * WorldLoader.c
 *
 *  Created on: Jul 20, 2013
 *      Author: blackwolf12333
 */

#include "WorldLoader.h"
#include <string.h>

struct node {
	char *name;
	char *data[512];
};

struct parser_data {
	struct node nodes[512];
};

int get_file_size(FILE *fd) {
	int size;

	while(fgetc(fd) != '\n') {
		size++;
	}

	return size;
}

struct parser_data *parse(char *path) {
	struct parser_data *data = malloc(sizeof(*data));
	struct node *node = malloc(sizeof(*node));
	int nodes = 0;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;

	FILE *fd = fopen(path, "r");
	if(fd != NULL) {
		if((read = getline(&line, &len, fd)) != -1) {
			if(strncmp(line, "*", 1) == 0) {
				if((read = getline(&line, &len, fd)) != -1) {
					while (strncmp(line, "*", 1) != 0) { // read till the end of the file
						node->name = malloc(read - 2);
						node->name = strndup(line, read - 1);
						fprintf(stderr, "%s\n", node->name);
						if ((read = getline(&line, &len, fd)) != -1) {
							if (strncmp(line, "#", 1) == 0) {
								if ((read = getline(&line, &len, fd)) != -1) {
									int i = 0;
									node->data[i] = malloc(len);
									strncpy(node->data[i], line, read - 1);
									i++;

									if ((read = getline(&line, &len, fd)) != -1) {
										while (strncmp(line, "#", 1) != 0) {
											//data
											node->data[i] = malloc(len);
											strncpy(node->data[i], line, read - 1);
											i++;
											read = getline(&line, &len, fd);
										}
									}
									data->nodes[nodes++] = *node;
									memset(node, 0, sizeof(*node));
								}
							}
						}
						read = getline(&line, &len, fd);
					}
				}
			}
		}
		/*char buf[512]; // WINDOWS COMPATIBLE
		fgets(buf, 512, fd);
		if(strncmp(buf, "*", 1) == 0) {
			memset(buf, 0, 2);
			fgets(buf, 512, fd);
			while(strncmp(buf, "*", 1) != 0) {
				node->name = malloc(sizeof(buf));
				strncpy(node->name, buf, strlen(buf));
				fgets(buf, 512, fd);
				if(strncmp(buf, "#", 1) == 0) {
					fgets(buf, 512, fd);
					int i = 0;
					while(strncmp(buf, "#", 1) != 0) {
						node->data[i] = malloc(sizeof(buf));
						strncpy(node->data[i], buf, strlen(buf)); i++;
						fgets(buf, 512, fd);
					}
					data->nodes[nodes++] = *node;
					memset(node, 0, sizeof(*node));
				}
			}
		}*/
	}

	return data;
}

char *get_character_path(struct parser_data *data, char *path) {
	int i;
	for(i = 0; i < sizeof(data->nodes); i++) {
		if((data->nodes[i].data[0] == NULL) || (strcmp(data->nodes[i].name, "") == 0)) {
			break;
		}
		if((data->nodes[i].data[0] != NULL)) {
			if(strcmp(data->nodes[i].name, "characters") == 0) {
				char *name = data->nodes[i].name;
				strcat(name, "/player0.png");
				char *pathdup = malloc(strlen(path) + strlen(name));
				strcpy(pathdup, path);
				strcat(pathdup, name);
				return pathdup;
			}
		}
	}
	return NULL;
}

Entity *init_player(struct parser_data *data, char *path) {
	Entity *player = malloc(sizeof(*player));
	char *character_path = get_character_path(data, path);
	fprintf(stderr, "%s\n", character_path);
	player->surface = load_image(character_path);

	int i, j;
	for(i = 0; i < sizeof(data->nodes); i++) {
		if((data->nodes[i].data[0] == NULL) || (strcmp(data->nodes[i].name, "") == 0)) {
			break;
		}
		if((data->nodes[i].data[0] != NULL)) {
			if(strcmp(data->nodes[i].name, "characters")) {
				for(j = 0; j < sizeof(data->nodes[i].data); i++) {
					char *name = strtok(data->nodes[i].data[j], ":");

					if(strcmp(name, "player0") == 0) {
						player->x = (int) strtol(strtok(NULL, ":"), (char**)NULL, 10);
						player->y = (int) strtol(strtok(NULL, ":"), (char**)NULL, 10);
						break;
					}
				}
			}
		}
	}
	return player;
}

World *load_world(char *path) {
	World *world = malloc(sizeof(*world));

	struct parser_data *data = malloc(sizeof(*data));
	data = parse(path);

	/*int i;
	for(i = 0; i < sizeof(data->nodes); i++) {
		if((data->nodes[i].data[0] == NULL) || (strcmp(data->nodes[i].name, "") == 0)) {
			break;
		}
		if((data->nodes[i].data[0] != NULL)) {
			fprintf(stderr, "node: %d name: %s\n", i, data->nodes[i].name);
			int j;
			for(j = 0; j < sizeof(data->nodes[i].data); j++) {
				if((data->nodes[i].data[j] == NULL) || (strcmp(data->nodes[i].data[j], "") == 0)) {
					break;
				}
				fprintf(stderr, "data: %s\n", data->nodes[i].data[j]);
			}
		}
	}*/
	char *world_dir = malloc((strlen(path) - strlen("world_description.wd")) + strlen("landscape.png"));
	strncpy(world_dir, path, strlen(path) - strlen("world_description.wd"));
	strcat(world_dir, "landscape.png");
	world->landscape = load_image(world_dir);
	memset(world_dir, 0, strlen(world_dir));
	world_dir = malloc((strlen(path) - strlen("world_description.wd")) + strlen("landscape.png"));
	strncpy(world_dir, path, strlen(path) - strlen("world_description.wd"));
	world->player = init_player(data, world_dir);

	free(data);

	return world;
}
