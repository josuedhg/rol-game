#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "creature.h"
#include "scene.h"

struct attributes {
	int str;
	int dex;
	int con;
};

struct player {
	struct creature creature;
	char *name;
	int exp;
	int lvl;
	struct attributes *attributes;
	int direction;
	struct scene *scene;
};

void player_init(struct player *);
char *player_look_around(struct player *);
int get_modifier(int attribute);

#endif /* end of include guard: __PLAYER_H__ */
