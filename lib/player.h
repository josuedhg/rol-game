#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "creature.h"

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
};

void player_init(struct player *);
int get_modifier(int attribute);

#endif /* end of include guard: __PLAYER_H__ */
