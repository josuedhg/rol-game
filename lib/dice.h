#ifndef __DICE_H__
#define __DICE_H__

struct dice {
	int num_dices;
#define D2 2
#define D3 3
#define D4 4
#define D6 6
#define D8 8
#define D10 10
#define D12 12
#define D20 20
#define D100 100
	int dice_type;
};

int dice_roll(struct dice*);

#endif /* end of include guard: __DICE_H__ */
