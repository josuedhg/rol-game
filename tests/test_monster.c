#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "creature.h"
#include "monster.h"

static void test_monster_init(void **state)
{
	struct attack attack = {.name = "fire wave", .dice = {.dice_type = D4, .num_dices = 1}};
	struct attack *attacks[] = {&attack, NULL};
	struct monster dragon;

	will_return(rand, 3);
	will_return(rand, 6);
	monster_init(&dragon, 2, 12, attacks);

	assert_int_equal(dragon.creature.hp, 11);
	assert_int_equal(dragon.creature.atk, 2);
	assert_int_equal(dragon.creature.def, 12);
	assert_true(dragon.creature.attack == &attack);
}

static void test_monster_change_attack(void **state)
{
	struct attack fire_wave = {.name = "fire wave", .dice = {.dice_type = D6, .num_dices = 2}};
	struct attack claw = {.name = "claw", .dice = {.dice_type = D4, .num_dices = 1}};
	struct attack *attacks[] = {&fire_wave, &claw, NULL};
	struct monster dragon;

	will_return(rand, 3);
	will_return(rand, 6);
	monster_init(&dragon, 2, 12, attacks);

	monster_change_attack(&dragon, 1);

	assert_true(dragon.creature.attack == &claw);
}

int main()
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_monster_init),
		cmocka_unit_test(test_monster_change_attack),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
