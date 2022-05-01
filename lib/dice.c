#include <stdlib.h>
#include <time.h>

#include "dice.h"

int dice_roll(struct dice *dice)
{
	srand((unsigned)time(NULL));
	int result = 0;
	for (int i = 0; i < dice->num_dices; i++)
		result += (rand() % dice->dice_type) + 1;
	return result;
}
