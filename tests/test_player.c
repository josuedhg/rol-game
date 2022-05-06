#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

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

static void test_player_look_around_nothing_to_see(void **state)
{
	struct scene empty_room = {.things = { NULL }};
	struct attributes attributes = {.str = 16, .dex = 13, .con = 9};
	struct attack fist_attack = {.name = "fist attack", .dice = {.dice_type = D4, .num_dices = 1}};
	struct player player = {.direction = 1, .scene = &empty_room, .attributes = &attributes, .creature = {.attack = &fist_attack}};
	char *description = player_look_around(&player);
	assert_string_equal(description, "Nothing to see");
	free(description);
}

static void test_player_look_around_one(void **state)
{
	struct scene empty_room = {.things = { NULL, "a table", NULL, NULL}};
	struct attributes attributes = {.str = 16, .dex = 13, .con = 9};
	struct attack fist_attack = {.name = "fist attack", .dice = {.dice_type = D4, .num_dices = 1}};
	struct player player = {.direction = 1, .scene = &empty_room, .attributes = &attributes, .creature = {.attack = &fist_attack}};
	char *description = player_look_around(&player);
	assert_string_equal(description, "to the east you see a table");
	free(description);
}

static void test_player_look_around_two(void **state)
{
	struct scene empty_room = {.things = { NULL, "a table", "a mirror", NULL}};
	struct attributes attributes = {.str = 16, .dex = 13, .con = 9};
	struct attack fist_attack = {.name = "fist attack", .dice = {.dice_type = D4, .num_dices = 1}};
	struct player player = {.direction = 1, .scene = &empty_room, .attributes = &attributes, .creature = {.attack = &fist_attack}};
	char *description = player_look_around(&player);
	assert_string_equal(description, "to the east you see a table and "
					 "to the south you see a mirror");
	free(description);
}

static void test_player_look_around_three(void **state)
{
	struct scene empty_room = {.things = { "a basin", "a table", "a mirror", NULL}};
	struct attributes attributes = {.str = 16, .dex = 13, .con = 9};
	struct attack fist_attack = {.name = "fist attack", .dice = {.dice_type = D4, .num_dices = 1}};
	struct player player = {.direction = 1, .scene = &empty_room, .attributes = &attributes, .creature = {.attack = &fist_attack}};
	char *description = player_look_around(&player);
	assert_string_equal(description, "to the north you see a basin, "
					 "to the east you see a table and "
					 "to the south you see a mirror");
	free(description);
}

static void test_player_look_around_four(void **state)
{
	struct scene empty_room = {.things = { "a basin", "a table", "a mirror", "a door"}};
	struct attributes attributes = {.str = 16, .dex = 13, .con = 9};
	struct attack fist_attack = {.name = "fist attack", .dice = {.dice_type = D4, .num_dices = 1}};
	struct player player = {.direction = 1, .scene = &empty_room, .attributes = &attributes, .creature = {.attack = &fist_attack}};
	char *description = player_look_around(&player);
	assert_string_equal(description, "to the north you see a basin, "
					 "to the east you see a table, "
					 "to the south you see a mirror and "
					 "to the west you see a door");
	free(description);
}

int main()
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_player_init),
		cmocka_unit_test(test_player_get_modifier),
		cmocka_unit_test(test_player_look_around_nothing_to_see),
		cmocka_unit_test(test_player_look_around_one),
		cmocka_unit_test(test_player_look_around_two),
		cmocka_unit_test(test_player_look_around_three),
		cmocka_unit_test(test_player_look_around_four),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
