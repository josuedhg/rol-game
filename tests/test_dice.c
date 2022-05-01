#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "dice.h"

static void test_dice_in_range(void **state)
{
	int *param = (int *)*state;

	struct dice dice = {.dice_type = D8, .num_dices = 1};
	will_return(rand, *param);
	int result = dice_roll(&dice);
	assert_true(result > 0 && result <= D8);
}

static void test_dice_in_range_multidice(void **state)
{
	int *param = (int *)*state;

	struct dice dice = {.dice_type = D8, .num_dices = 2};
	will_return(rand, *param);
	will_return(rand, *param + D8);
	int result = dice_roll(&dice);
	assert_true(result > 0);
	assert_true(result <= (D8 * 2));
}

int main()
{
	int test_params[] = {0, 3, 8, 203};
	const struct CMUnitTest tests[] = {
		cmocka_unit_test_prestate(test_dice_in_range, &test_params[0]),
		cmocka_unit_test_prestate(test_dice_in_range, &test_params[1]),
		cmocka_unit_test_prestate(test_dice_in_range, &test_params[2]),
		cmocka_unit_test_prestate(test_dice_in_range, &test_params[3]),
		cmocka_unit_test_prestate(test_dice_in_range_multidice, &test_params[0]),
		cmocka_unit_test_prestate(test_dice_in_range_multidice, &test_params[1]),
		cmocka_unit_test_prestate(test_dice_in_range_multidice, &test_params[2]),
		cmocka_unit_test_prestate(test_dice_in_range_multidice, &test_params[3]),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
