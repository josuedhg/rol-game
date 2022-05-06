#include "scene.h"

const char *direction_text[DIRECTIONS] = {"north", "east", "south", "west"};

const char *direction_to_string(int direction)
{
	return direction_text[direction];
}
