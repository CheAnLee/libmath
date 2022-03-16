#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lib/inc/triangle.h"

#define MIN(x,y)	((x<y)? x: y)
#define MAX(x,y)	((x>y)? x: y)

int main(int argc, char ** argv) {
	st_node a, b, c;
	int		joyment[2] = {-10, 5};

	a.x = 1; a.y = 2;
	b.x = 4; b.y = 1;
	c.x = 3; c.y = 4;

	// calculate the entire triangle area
	printf("-> %f\n", CalTriangleArea (a, b, c));

	// split the area by a vertical line
	for (int vLine = MIN(MIN(a.x,b.x),c.x); vLine <= MAX(MAX(a.x,b.x),c.x); vLine++) {
		float r = SplitTriangleArea (a, b, c, (float)vLine);

		double joy_diff = abs( r*joyment[0] - (1.-r)*joyment[1]);
		
		printf("vLine: %d, A = %f, B = %f, D = %f\n", vLine, r, 1-r, joy_diff);
	}

	return 0;
}
