//Justin Phang
//John Jordan Dyer
//Arya Pourzanjani

#ifndef _CACHESIM_H
#define _CACHESIM_H

typedef struct
{
	int type;

	int blockSize;
	int cacheSize;
	int numBlocks;

	int misses;
	int accesses;
	int cycles;

	int* cachearray;
	int* tags;
	int* isValid;

	int sizeOfTag;
} cacheinfo;

void *createAndInitialize(int blocksize, int cachesize, int type);

int accessCache(void *cache, int address);
int missesSoFar(void *cache);
int accessesSoFar(void *cache);
int totalAccessTime(void *cache);

#endif