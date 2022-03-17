#ifndef __LIB_TRIANGLE__
#define __LIB_TRIANGLE__

typedef struct st_node {
	float x;
	float y;
} st_node;

extern double CalTriangleArea (st_node a, st_node b, st_node c);
extern double SplitTriangleArea (st_node a, st_node b, st_node c, float vLine);
extern int isLineHitTriangle (st_node a, st_node b, st_node c, float vLine);

#endif
