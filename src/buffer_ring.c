#include <stdio.h>

#include "buffer_ring.h"

int main(int argc, char *argv[])
{
	declare_bring(x, int);
	init_bring(x);

	push_bring(x, int, 2);
	push_bring(x, int, 3);
	push_bring(x, int, 4);
	push_bring(x, int, 5);
	push_bring(x, int, 6);
	push_bring(x, int, 7);

	int r = pull_bring(x);
	printf("Valor sacado %d\n", r);
	
	foreach(x, int, i){
		printf("Valor %d\n", i);
	}

	return 0;
}