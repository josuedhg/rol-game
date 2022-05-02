#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "creature.h"

struct monster {
	struct creature creature;
	int lvl;
	struct attack **attacks;
};

void monster_init(struct monster *, int, int, struct attack **);
void monster_change_attack(struct monster *, int);

#endif /* end of include guard: __MONSTER_H__ */
