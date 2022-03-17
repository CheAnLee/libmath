#ifndef __CAKE_H__
#define __CAKE_H__

#include "triangle.h"

typedef struct st_patch_att {
	st_node pos[3];
	double joy_a;
	double joy_b;
} st_patch_att;

typedef struct st_cake {
	int patch_num;
	double cake_h;
	double cake_w;
	st_patch_att *patch_att;

	struct st_cake *next;
} st_cake;

#endif
