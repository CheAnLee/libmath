#include <stdio.h>
#include <stdlib.h>
#include "inc/triangle.h"
#include "inc/common.h"

#define Slope(a, b)		((b.y-a.y)/(b.x-a.x))

double CalTriangleArea (st_node a, st_node b, st_node c) {
	double area = 0;

	area = 0.5*(a.x*(b.y-c.y) + b.x*(c.y-a.y) + c.x*(a.y-b.y));

	return area;
}

double SplitTriangleArea (st_node a, st_node b, st_node c, float vLine) {
	float   ratio     = 0;
	float   area      = 0;
	st_node nd_map[3] = {a, b, c};

	area = CalTriangleArea (a, b, c);
	for (int i=0; i<2; i++) {
		for (int j=i+1; j<3; j++) {
			if (nd_map[i].x > nd_map[j].x) {
				int tmp = nd_map[i].x;
				nd_map[i].x = nd_map[j].x;
				nd_map[j].x = tmp;
			}
		}
	}
	//printf("%f %f %f\n", nd_map[0].x,  nd_map[1].x,  nd_map[2].x);
	if (vLine < nd_map[0].x || vLine > nd_map[2].x)
		return 0;

	if (vLine < nd_map[1].x ) {
		st_node mid1, mid2;
		mid1.x = vLine;
		mid1.y = Slope(nd_map[0], nd_map[1])*vLine + nd_map[0].y;
		mid2.x = vLine;
		mid2.y = Slope(nd_map[0], nd_map[2])*vLine + nd_map[0].y;

		float mid_area = CalTriangleArea (nd_map[0], mid1, mid2);
		ratio = mid_area / area;
	} else if (vLine > nd_map[1].x) {
		st_node mid1, mid2;
		mid1.x = vLine;
		mid1.y = Slope(nd_map[1], nd_map[2])*vLine + nd_map[1].y;
		mid2.x = vLine;
		mid2.y = Slope(nd_map[0], nd_map[2])*vLine + nd_map[0].y;

		float mid_area = CalTriangleArea (mid1, mid2, nd_map[2]);
		ratio = mid_area / area;
	} else {
		st_node mid;
		mid.x = vLine;
		mid.y = Slope(nd_map[0], nd_map[2])*vLine + nd_map[0].y;

		float mid_area = CalTriangleArea (nd_map[0], nd_map[1], mid);
		ratio = mid_area / area;
	}

	return ratio;
}

int isLineHitTriangle (st_node a, st_node b, st_node c, float vLine) {
	if (vLine >= MIN(MIN(a.x, b.x), c.x) && vLine <= MAX(MAX(a.x, b.x), c.x))
		return 1;

	return 0;
}
