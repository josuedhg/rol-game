#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "scene.h"

const char *direction_text[DIRECTIONS] = {"north", "east", "south", "west"};

const char *direction_to_string(int direction)
{
	return direction_text[direction];
}

char *scene_look(struct scene *scene, int direction)
{
	char * description = NULL;
	if (scene->things[direction] != NULL)
		asprintf(&description, "to the %s you see %s",
			direction_to_string(direction),
			scene->things[direction]);

	return description;
}

char *scene_look_around(struct scene *scene)
{
	char *descriptions[DIRECTIONS];
	int to_see_count = 0;
	char *full_description = NULL;

	for (int i = 0; i < DIRECTIONS; i++) {
		descriptions[i] = scene_look(scene, i);
		if (descriptions[i] != NULL) to_see_count++;
	}

	if (to_see_count > 0) {
		for (int i = 0, item = 0; i < DIRECTIONS; i++) {
			if (descriptions[i] == NULL) continue;
			char *tmp_desc = full_description;
			asprintf(&full_description, "%s%s%s",
				(full_description)? full_description: "",
				descriptions[i],
				(item < to_see_count - 1)? ((item < to_see_count - 2)?", ": " and "): "");
			free(tmp_desc);
			item++;
		}
	} else {
		full_description = strdup("Nothing to see");
	}

	for (int i = 0; i < DIRECTIONS; i++) free(descriptions[i]);

	return full_description;
}
