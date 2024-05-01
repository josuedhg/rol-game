#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>

#include "scene.h"

char *scene_look(struct scene *, int /* dirrection */);

static void test_scene_direction_to_string_north(void **state)
{
	assert_string_equal(direction_to_string(NORTH_DIRECTION), "north");
}

static void test_scene_direction_to_string_east(void **state)
{
	assert_string_equal(direction_to_string(EAST_DIRECTION), "east");
}

static void test_scene_direction_to_string_south(void **state)
{
	assert_string_equal(direction_to_string(SOUTH_DIRECTION), "south");
}

static void test_scene_direction_to_string_west(void **state)
{
	assert_string_equal(direction_to_string(WEST_DIRECTION), "west");
}

static void test_scene_direction_to_string_wrong(void **state)
{
	assert_ptr_equal(direction_to_string(4), NULL);
}

/////////////////////////////////////////////////////////

static void test_scene_look_around_nothing_to_see(void **state)
{
	struct scene empty_room = {.things = { NULL }};
	char *description = scene_look_around(&empty_room);
	assert_string_equal(description, "Nothing to see");
	free(description);
}

static void test_scene_look_around_one(void **state)
{
	struct scene room = {.things = { NULL, "a table", NULL, NULL}};
	char *description = scene_look_around(&room);
	assert_string_equal(description, "to the east you see a table");
	free(description);
}

static void test_scene_look_around_two(void **state)
{
	struct scene room = {.things = { NULL, "a table", "a mirror", NULL}};
	char *description = scene_look_around(&room);
	assert_string_equal(description, "to the east you see a table and "
					 "to the south you see a mirror");
	free(description);
}

static void test_scene_look_around_three(void **state)
{
	struct scene room = {.things = { "a basin", "a table", "a mirror", NULL}};
	char *description = scene_look_around(&room);
	assert_string_equal(description, "to the north you see a basin, "
					 "to the east you see a table and "
					 "to the south you see a mirror");
	free(description);
}

static void test_scene_look_around_four(void **state)
{
	struct scene room = {.things = { "a basin", "a table", "a mirror", "a door"}};
	char *description = scene_look_around(&room);
	assert_string_equal(description, "to the north you see a basin, "
					 "to the east you see a table, "
					 "to the south you see a mirror and "
					 "to the west you see a door");
	free(description);
}

int main()
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_scene_direction_to_string_north),
		cmocka_unit_test(test_scene_direction_to_string_east),
		cmocka_unit_test(test_scene_direction_to_string_south),
		cmocka_unit_test(test_scene_direction_to_string_west),
		cmocka_unit_test(test_scene_direction_to_string_wrong),
		cmocka_unit_test(test_scene_look_around_nothing_to_see),
		cmocka_unit_test(test_scene_look_around_one),
		cmocka_unit_test(test_scene_look_around_two),
		cmocka_unit_test(test_scene_look_around_three),
		cmocka_unit_test(test_scene_look_around_four),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
