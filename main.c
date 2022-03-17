#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "lib/inc/triangle.h"
#include "lib/inc/cake.h"

#define MIN(x,y)	((x<y)? x: y)
#define MAX(x,y)	((x>y)? x: y)

st_cake* read_data (int *t_num) {
	FILE *fp         = NULL;
	char buf[256]    = {0};
	int  cnt         = 0;
	st_cake *ptr     = NULL;
	st_cake *cur_ptr = NULL;

	fp = fopen("test.input", "r");
	if (fp != NULL ) {
		fscanf (fp, "%d", t_num);
		printf("Number of case is %d\n", *t_num);
		while (++cnt <= *t_num) {
			if (ptr == NULL) {
				ptr = malloc(sizeof(st_cake));
				memset (ptr, 0, sizeof(st_cake));
				cur_ptr = ptr;
			} else {
				cur_ptr->next = malloc(sizeof(st_cake));
				cur_ptr = cur_ptr->next;
				memset(cur_ptr, 0, sizeof(st_cake));
			}

			// patch#, w, h
			fscanf (fp, "%d %d %d", &(cur_ptr->patch_num), &(cur_ptr->cake_w), &(cur_ptr->cake_h));
			// p, q, r ,s
			fscanf (fp, "%d %d %d %d", &(cur_ptr->p), &(cur_ptr->q), &(cur_ptr->r), &(cur_ptr->s));
			// [1 .. patch#]: x, y, joy_a, joy_b
			cur_ptr->patch_att = malloc(sizeof(st_patch_att) * cur_ptr->patch_num);
			memset (cur_ptr->patch_att, 0, sizeof(st_patch_att) * cur_ptr->patch_num);
			for (int i=0; i<cur_ptr->patch_num; i++) {
				fscanf (fp, "%d %d %d %d",	&(cur_ptr->patch_att[i].x),
											&(cur_ptr->patch_att[i].y),
											&(cur_ptr->patch_att[i].joy_a),
											&(cur_ptr->patch_att[i].joy_b));
			}
		}
		cur_ptr->next = NULL;
	} else {
		return NULL;
	}

#if 1
	cnt = 0;
	cur_ptr = ptr;
	while (cur_ptr) {
		printf ("[Case #%d]\n", ++cnt);
		printf ("    cake size(h,w): (%d, %d)\n", cur_ptr->cake_h, cur_ptr->cake_w);
		for (int i=0; i<cur_ptr->patch_num; i++) {
			st_patch_att *cur_patch = (st_patch_att *)&(cur_ptr->patch_att[i]);
			printf ("        p_%02d:  (%d, %d)(%d, %d)(%d, %d),  joyment: (%d, %d)\n", i+1, cur_patch->x, cur_patch->y,
																					cur_patch->x+cur_ptr->p, cur_patch->y+cur_ptr->q,
																					cur_patch->x+cur_ptr->r, cur_patch->y+cur_ptr->s,
																					cur_patch->joy_a, cur_patch->joy_b);
		}

		cur_ptr = cur_ptr->next;
	}
#endif
	return ptr;
}

int release_data (void* ptr) {
	if (ptr == NULL)
		return 0;

	st_cake *p_cake = (st_cake *)ptr;

	free (p_cake->patch_att);
	free (p_cake);

	return 0;
}
int main (int argc, char ** argv) {
	st_node     a, b, c;
	int         joyment[2]   = {-10, 5};
	int         t_num        = 0;
	double      min_joy_diff = INFINITY;

	a.x = 1; a.y = 2;
	b.x = 4; b.y = 1;
	c.x = 3; c.y = 4;

	st_cake *p_cake = read_data(&t_num);

	// split the area by a vertical line
	for (int vLine = MIN(MIN(a.x,b.x),c.x); vLine <= MAX(MAX(a.x,b.x),c.x); vLine++) {
		float r = SplitTriangleArea (a, b, c, (float)vLine);

		double joy_diff = abs( r*joyment[0] - (1.-r)*joyment[1]);
		
		printf ("vLine: %d, A = %f, B = %f, D = %f\n", vLine, r, 1-r, joy_diff);
		min_joy_diff = MIN(min_joy_diff, joy_diff);
	}
	printf ("=> min joy difference: %f\n", min_joy_diff);

	release_data(p_cake);
	return 0;
}
