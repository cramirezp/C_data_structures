#include <stdio.h>

#include "buffer_ring.h"

#undef _BR_BUFFER_SIZE
#define _BR_BUFFER_SIZE 10000000

int main(int argc, char *argv[])
{
	declare_bring(x, int);
	init_bring(x);

	for(int i=0; i<_BR_BUFFER_SIZE; i++)
		push_bring(x, int, i);

	int r = pull_bring(x);
	printf("Valor sacado %d\n", r);
	
	foreach_bring(x, int, i){
		printf("Valor %d\n", i);
	}

	return 0;
}

