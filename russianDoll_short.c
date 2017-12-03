/*******************************************************************************
*   Author: Johnny Chan
*   Date:   Dec 01 2017
*	
*   Russian Doll Envelopes (LeetCode 354):
*   You have a number of envelopes with widths and heights given as a pair of 
*   integers (w, h). One envelope can fit into another if and only if both the 
*   width and height of one envelope is greater than the width and height of the 
*   other envelope.

*   What is the maximum number of envelopes can you Russian doll? (put one 
*   inside other)

Example:
Given envelopes = [[5,4],[6,4],[6,7],[2,3]], the maximum number of envelopes 
you can Russian doll is 3 ([2,3] => [5,4] => [6,7]). 


*  This is the submit(short) version
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0


/* swap the two given pairs */
void swapPair(int* a, int* b)
{
	int temp;
	for (int i = 0; i < 2; ++i) 
	{
		temp = *(a + i);
		*(a + i) = *(b + i);
		*(b + i) = temp;
	}
}

/* 
compare function returns 1 (> 0) if a[0] > b[0] and -1 (< 0) if a[0] < b[0]
for cases where a[0] equals b[0] returns 1 if a[1] > b[1]. 
*/
int compare (const void *pa, const void *pb) {
    const int *a = *(const int **)pa;
    const int *b = *(const int **)pb;
    if(a[0] == b[0])
        return a[1] - b[1];
    else
        return a[0] - b[0];
}


int maxEnvelopes(int** envelopes, int envelopesRowSize, int envelopeColSize)
{
	if (!envelopesRowSize) return 0;  // if no envelopes at all
	int maxEnv = 0, envRowNum = 0, env_h, env_w;
	printEnvelopes(envelopes, envelopesRowSize, envelopeColSize);
	qsort(envelopes, envelopesRowSize, sizeof(envelopes[0]), compare);
	printf("---- after qsort ----\n");
	printEnvelopes(envelopes, envelopesRowSize, envelopeColSize);
	env_h = envelopes[0][1];
	env_w = envelopes[0][0];
	for (int* itr = *envelopes; itr < *envelopes + envelopesRowSize; ++itr)
	{	
		while (itr[0] == env_w)
		{
			++itr;
		}
		env_w = itr[0];
		if (itr[1] > env_h)
		{
			++maxEnv;
			env_h = itr[1];
		}
	}
	return maxEnv;
}


int main()
{
	return 0;
}