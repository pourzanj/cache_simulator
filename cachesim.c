#include <stdio.h>
#include <stdlib.h>
#include "cachesim.h"

#define INVALID 0 //used to indicate when the data in the cache is valid
#define VALID 1

#define HIT 1
#define MISS 0

#define TRUE 1
#define FALSE 0

#define WORD_SIZE 32
#define WORD_SIZE_BYTES 4
#define WORD_OFFSET 2

#define MISS_PENALTY 100

#define UPPER_N_BITS(N) (~0 << (WORD_SIZE-N) )
#define LOWER_N_BITS(N) ((1 << N) - 1 )

int logbase2(int num) {
	int t = 1;
	int base = 0;
	while (num > t) {
		t = t << 1;
		base++;
	}
	return base;
}

void *createAndInitialize(int blockSize, int cacheSize, int type)
{
	cacheinfo* ret = (cacheinfo*)malloc( sizeof(cacheinfo) );
	ret->type = type;
	ret->blockSize = blockSize;
	ret->cacheSize = cacheSize;
	ret->numBlocks = cacheSize/blockSize;

	ret->misses = 0;
	ret->accesses = 0;
	ret->cycles = 0;

	ret->cachearray = (int*)malloc( cacheSize );
	ret->tags = (int*)malloc( cacheSize );
	ret->isValid = (int*)malloc( cacheSize );

	ret->sizeOfTag = WORD_SIZE  - (logbase2(ret->numBlocks)+logbase2(blockSize/WORD_SIZE_BYTES)+WORD_OFFSET); 

	//initialize all tags to invalid
	int i;
	for(i=0; i<cacheSize; i++) ret->isValid[i] = INVALID;

	switch(type)
	{
		//direct-mapped
		case 0:

			break;

		//2-way-associative
		case 1:

			break;

		//4-way-associative
		case 2:

			break;

		default:
			printf("Invalid type, choose 0 for direct-mapped, 1 for pseudo-associative, and 2 for 4-way associative\n");
			exit(1);
	}

	return (void*)ret;
}

//check whether an index in cache is valid
int isValid(int index)
{
	/*
	if( UPPER_N_BITS(1) >> (WORD_SIZE-1) & tag == UPPER_N_BITS(1) )
		return VALID;
	else
		return INVALID;
	*/

	return -42;
}

int getIndex(int address, int numBlocks, int blockSize)
{
	int blockAddress = address/blockSize; 

	return blockAddress & LOWER_N_BITS(logbase2(numBlocks-1));
}

int compareTag(int address, int tag, int sizeOfTag)
{
	if( (address & UPPER_N_BITS(sizeOfTag)) >> (WORD_SIZE-sizeOfTag) == tag & LOWER_N_BITS(sizeOfTag))
		return TRUE;
	else
		return FALSE;

}

//In this function, we access the cache with a particular address.
//If the address results in a hit, return 1. If it is a miss, return 0.
int accessCache(void *cache, int address)
{
	cacheinfo* c = (cacheinfo*)cache;

	int index;
	int tag;
	switch(c->type)
	{
		//direct-mapped
		case 0:
			index = getIndex(address, c->numBlocks, c->blockSize);
			tag = c->tags[index];

			//printf("%d\n", compareTag(address, tag, c->sizeOfTag));
			//printf("%d\n", isValid(tag));

			c->accesses++;

			if( compareTag(address, tag, c->sizeOfTag) && c->isValid[index] )
			{
				//hit!
				c->cycles++;
				return HIT;
			}
			else
			{
				//miss; pull in the missed block i.e. update address and set valid bit
				//printf("#%d#\n", (WORD_SIZE-c->sizeOfTag));
				//printf("#%d#\n",UPPER_N_BITS(1));
				//printf("~%d~\n", (((address & UPPER_N_BITS(c->sizeOfTag))) >> (WORD_SIZE-c->sizeOfTag)) );

				c->tags[index] = (((address & UPPER_N_BITS(c->sizeOfTag))) >> (WORD_SIZE-c->sizeOfTag));
				c->isValid[index] = VALID;

				c->misses++;
				c->cycles++;
				c->cycles += MISS_PENALTY;				
				return MISS;
			}

			break;

		//2-way-associative
		case 1:

			break;

		//4-way-associative
		case 2:

			break;

		default:
			printf("Invalid type, choose 0 for direct-mapped, 1 for pseudo-associative, and 2 for 4-way associative\n");
			exit(1);
	}
}

int missesSoFar(void *cache){return ((cacheinfo*)cache)->misses;}
int accessesSoFar(void *cache){return ((cacheinfo*)cache)->accesses;}
int totalAccessTime(void *cache){return ((cacheinfo*)cache)->cycles;}