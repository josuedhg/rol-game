#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "creature.h"

#define PLAYER_HP_BASE 8
#define DRAGON_HP_BASE 16

static void test_creature_attack_fail(void **state)
{
	struct attack attack = {.name = "fire wave", .dice ={.dice_type = D4, .num_dices = 1}};
	struct creature dragon = {.hp = DRAGON_HP_BASE, .atk = 2, .def = 16, .attack = &attack};

	struct attack fist_attack = {.name = "fist attack", .dice ={.dice_type = D4, .num_dices = 1}};
	struct creature player = {.hp = PLAYER_HP_BASE, .atk = 0, .def = 13, .attack = &fist_attack};

	will_return(rand, 4);
	attack_creature(&dragon, &player);
	assert_int_equal(player.hp, PLAYER_HP_BASE);
}

static void test_creature_attack_success(void **state)
{
	struct attack attack = {.name = "fire wave", .dice ={.dice_type = D4, .num_dices = 1}};
	struct creature dragon = {.hp = DRAGON_HP_BASE, .atk = 2, .def = 16, .attack = &attack};

	struct attack fist_attack = {.name = "fist attack", .dice ={.dice_type = D4, .num_dices = 1}};
	struct creature player = {.hp = PLAYER_HP_BASE, .atk = 0, .def = 13, .attack = &fist_attack};

	will_return(rand, 19);
	will_return(rand, 2);
	attack_creature(&dragon, &player);
	assert_int_equal(player.hp, PLAYER_HP_BASE - 3);
}

static void test_creature_zero_hp(void **state)
{
	struct attack attack = {.name = "fire wave", .dice ={.dice_type = D20, .num_dices = 1}};
	struct creature dragon = {.hp = DRAGON_HP_BASE, .atk = 2, .def = 16, .attack = &attack};

	struct attack fist_attack = {.name = "fist attack", .dice ={.dice_type = D4, .num_dices = 1}};
	struct creature player = {.hp = PLAYER_HP_BASE, .atk = 0, .def = 13, .attack = &fist_attack};

	will_return(rand, 19);
	will_return(rand, 18);
	attack_creature(&dragon, &player);
	assert_int_equal(player.hp, 0);
}

int main()
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_creature_attack_fail),
		cmocka_unit_test(test_creature_attack_success),
		cmocka_unit_test(test_creature_zero_hp),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
