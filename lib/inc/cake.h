#ifndef __CAKE_H__
#define __CAKE_H__

typedef struct st_patch_att {
	int x;
	int y;
	int joy_a;
	int joy_b;
} st_patch_att;

typedef struct st_cake {
	int patch_num;
	int cake_h;
	int cake_w;
	int p;
	int q;
	int r;
	int s;
	st_patch_att *patch_att;

	struct st_cake *next;
} st_cake;

#endif
