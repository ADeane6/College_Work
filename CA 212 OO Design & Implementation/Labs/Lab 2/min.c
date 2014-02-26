#include <stdio.h>

int min(int x, int y)
{
	printf("x = %d, y = %d\n", x, y);
	return x < y? x:y;
}
