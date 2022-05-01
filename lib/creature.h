#ifndef __CREATURE_H__
#define __CREATURE_H__

#include <stdbool.h>

#include "dice.h"

struct creature;

struct attack {
	char *name;
	struct dice dice;
};

struct creature {
	int hp;
	int atk;
	int def;
	struct attack *attack;
};

void attack_creature(struct creature *, struct creature *);

#endif /* end of include guard: __CREATURE_H__ */
