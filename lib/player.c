#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>

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

struct thing_desc {
	char *thing;
	int direction;
};

static int get_direction_ocupied(struct scene *scene, struct thing_desc *things, int size)
{
	int amount = 0;
	for (int i = 0; i < size; i++) {
		if (scene->things[i]) {
			things[amount].thing = scene->things[i];
			things[amount].direction = i;
			amount++;
		}
	}
	return amount;
}

static char *creating_description(char **descriptions, int size)
{
	char *description = NULL;
	for (int i = 0; i < size; i++) {
		char *tmp = description;
		asprintf(&description, "%s%s", (tmp)? tmp : "", descriptions[i]);
		free(tmp);
	}
	return description;
}

static void get_descriptions(struct thing_desc *things, char ***descriptions, int size)
{
	*descriptions = calloc(1, sizeof(char *) * size);
	char **descriptions_ptr = *descriptions;
	for (int i = 0; i < size; i++)
		asprintf(&descriptions_ptr[i],
			"to the %s you see %s%s",
			direction_to_string(things[i].direction),
			things[i].thing,
			(i < size - 1)? ((i < size - 2)?", ": " and "): "");

}

static void free_descriptions(char ***descriptions, int size)
{
	for (int i = 0; i < size; i++)
		free((*descriptions)[i]);
	free(*descriptions);
	*descriptions = NULL;
}

char *player_look_around(struct player *player)
{
	struct thing_desc things[DIRECTIONS] = { 0 };
	struct scene *scene = player->scene;
	char **descriptions = NULL;
	char *description = NULL;
	int amount = 0;

	amount = get_direction_ocupied(scene, things, DIRECTIONS);
	get_descriptions(things, &descriptions, amount);

	if (amount)
		description = creating_description(descriptions, amount);
	else
		asprintf(&description, "%s", "Nothing to see");

	free_descriptions(&descriptions, amount);
	return description;
}
