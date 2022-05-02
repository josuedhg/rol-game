#include "player.h"

#define PLAYER_DEF_BASE 10
#define PLAYER_HP_BASE 10

int get_modifier(int attribute)
{
	if (attribute == 3)
		return -2;
	if (attribute <= 6)
		return -1;
	if (attribute == 18)
		return 2;
	if (attribute >= 15)
		return 1;
	return 0;
}

static int get_def(struct attributes *attr)
{
	return PLAYER_DEF_BASE + get_modifier(attr->dex);
}

void player_init(struct player *player)
{
	player->exp = 0;
	player->lvl = 1;
	player->creature.max_hp = PLAYER_HP_BASE + get_modifier(player->attributes->con);
	player->creature.hp = player->creature.max_hp;
	player->creature.def = get_def(player->attributes);
	player->creature.atk = get_modifier(player->attributes->str);
}
