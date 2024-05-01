#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>

#include "player.h"

static void test_player_init(void **state)
{
	struct attributes attributes = {.str = 16, .dex = 13, .con = 9};
	struct attack fist_attack = {.name = "fist attack", .dice = {.dice_type = D4, .num_dices = 1}};
	struct player player = {.attributes = &attributes, .creature = {.attack = &fist_attack}};
	player_init(&player);

	assert_int_equal(player.lvl, 1);
	assert_int_equal(player.exp, 0);
	assert_int_equal(player.creature.max_hp, 10);
	assert_int_equal(player.creature.max_hp, player.creature.hp);
	assert_int_equal(player.creature.atk, 1);
	assert_int_equal(player.creature.def, 10);
	assert_true(player.creature.attack == &fist_attack);
}

static void test_player_get_modifier(void **state)
{
	assert_int_equal(get_modifier(3), -2);
	assert_int_equal(get_modifier(18), 2);
	assert_int_equal(get_modifier(4), -1);
	assert_int_equal(get_modifier(17), 1);
	assert_int_equal(get_modifier(10), 0);
}

int main()
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_player_init),
		cmocka_unit_test(test_player_get_modifier),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
