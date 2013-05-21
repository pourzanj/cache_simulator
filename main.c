#include <stdio.h>
#include "cachesim.h"

int main(int argc, char** argv) {
	
	//int t = getIndex(1200, 64, 16);
	//int t = compareTag(120001, 117, 22);
		
	
	cacheinfo* c;
	c = (cacheinfo*)createAndInitialize(16,1024,0);
	printf("%d\n",accessCache(c, 1200));
	printf("%d\n",accessCache(c, 1200));

	/*
	printf("Created a cache with a blocksize of %d, a cachesize of %d, and a type of %d\n",c->blocksize,c->cachesize,c->type);
	printf("%d\n",accessCache(c,22));
	printf("%d\n",accessCache(c,26));
	printf("%d\n",accessCache(c,22));
	printf("%d\n",accessCache(c,26));
	printf("%d\n",accessCache(c,16));
	printf("%d\n",accessCache(c,3));
	printf("%d\n",accessCache(c,16));
	printf("%d\n",accessCache(c,18));
	printf("%d\n",accessCache(c,16));
	*/

	return 0;
}
