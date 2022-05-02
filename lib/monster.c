#include <stddef.h>

#include "dice.h"
#include "monster.h"

void monster_init(struct monster *monster, int lvl, int def, struct attack **attacks)
{
	monster->lvl = lvl;
	monster->attacks = attacks;
	monster->creature.attack = monster->attacks[0];
	monster->creature.def = def;
	monster->creature.atk = lvl;

	struct dice hp_dice = {.dice_type = D8, .num_dices = lvl};
	monster->creature.hp = dice_roll(&hp_dice);
}

void monster_change_attack(struct monster *monster, int index)
{
	monster->creature.attack = monster->attacks[index];
}
