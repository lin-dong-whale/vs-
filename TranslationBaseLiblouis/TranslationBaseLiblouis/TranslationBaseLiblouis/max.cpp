#include<stdio.h>
#include"max.h"

int max(int x, int y) {
	int z;
	if (x > y) {
		z = x;
	}
	else z = y;

	return z;
}

