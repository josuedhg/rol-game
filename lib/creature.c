#include "creature.h"
#include "dice.h"

static bool defend(struct creature *creature, int attack)
{
	return attack < creature->def;
}

static void get_damage(struct creature *creature, int damage)
{
	creature->hp -= (damage < creature->hp)? damage : creature->hp;
}

static int damage(struct creature *creature)
{
	return dice_roll(&creature->attack->dice);
}

void attack_creature(struct creature *creature, struct creature *enemy)
{
	struct dice d20 = {.num_dices = 1, .dice_type = D20};
	int attack = dice_roll(&d20);
	if (defend(enemy, attack + creature->atk))
		return;
	get_damage(enemy, damage(creature));
}
