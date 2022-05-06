#ifndef __SCENE_H__
#define __SCENE_H__

#define NORTH_DIRECTION 0
#define EAST_DIRECTION 1
#define SOUTH_DIRECTION 2
#define WEST_DIRECTION 3

#define DIRECTIONS 4

struct scene {
	char *things[DIRECTIONS];
};

const char *direction_to_string(int);

#endif /* end of include guard: __SCENE_H__ */
