#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "lib/inc/triangle.h"
#include "lib/inc/cake.h"
#include "lib/inc/common.h"

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
			fscanf (fp, "%d %lf %lf", &(cur_ptr->patch_num), &(cur_ptr->cake_w), &(cur_ptr->cake_h));
			// p, q, r ,s
			double p, q, r, s;
			fscanf (fp, "%lf %lf %lf %lf", &p, &q, &r, &s);
			// [1 .. patch#]: x, y, joy_a, joy_b
			cur_ptr->patch_att = malloc(sizeof(st_patch_att) * cur_ptr->patch_num);
			memset (cur_ptr->patch_att, 0, sizeof(st_patch_att) * cur_ptr->patch_num);
			for (int i=0; i<cur_ptr->patch_num; i++) {
				double tmp_x, tmp_y;
				fscanf (fp, "%lf %lf %lf %lf",	&tmp_x, &tmp_y,
											&(cur_ptr->patch_att[i].joy_a),
											&(cur_ptr->patch_att[i].joy_b));
				cur_ptr->patch_att[i].pos[0].x = tmp_x;
				cur_ptr->patch_att[i].pos[0].y = tmp_y;
				cur_ptr->patch_att[i].pos[1].x = tmp_x + p;
				cur_ptr->patch_att[i].pos[1].y = tmp_y + q;
				cur_ptr->patch_att[i].pos[2].x = tmp_x + r;
				cur_ptr->patch_att[i].pos[2].y = tmp_y + s;
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
		printf ("    cake size(h,w): (%f, %f)\n", cur_ptr->cake_h, cur_ptr->cake_w);
		for (int i=0; i<cur_ptr->patch_num; i++) {
			st_patch_att *cur_patch = (st_patch_att *)&(cur_ptr->patch_att[i]);
			printf ("        p_%02d:  (%f, %f)(%f, %f)(%f, %f),  joyment: (%f, %f)\n", i+1, cur_patch->pos[0].x, cur_patch->pos[0].y,
																							cur_patch->pos[1].x, cur_patch->pos[1].y,
																							cur_patch->pos[2].x, cur_patch->pos[2].y,
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
	int         t_num        = 0;
	double      min_joy_diff = INFINITY;
	st_cake     *p_cake      = NULL;
	st_cake     *cur_cake    = NULL;

	p_cake = read_data(&t_num);
	cur_cake = p_cake;

	for (int pnum = 0; pnum < cur_cake->patch_num; pnum++) {
		st_patch_att *cur_patch = &(cur_cake->patch_att[pnum]);
	
		// split the area by a vertical line
		for (int vLine = 1; vLine < cur_cake->cake_w; vLine++) {
			if (!isLineHitTriangle(cur_patch->pos[0], cur_patch->pos[1], cur_patch->pos[2], (float)vLine))
				continue;
			float r = SplitTriangleArea (cur_patch->pos[0], cur_patch->pos[1], cur_patch->pos[2], (float)vLine);
			double joy_diff = abs(r*cur_patch->joy_a - (1.-r)*cur_patch->joy_b);
		
			printf ("vLine: %d, A = %f, B = %f, D = %f\n", vLine, r, 1-r, joy_diff);
			min_joy_diff = MIN(min_joy_diff, joy_diff);
		}
		printf ("=> min joy difference: %f\n", min_joy_diff);
	}

	release_data(p_cake);
	return 0;
}
