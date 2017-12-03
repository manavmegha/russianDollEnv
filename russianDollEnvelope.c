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

/* print out the envelopes */
static void printEnvelopes(int** envelopes, int envelopesRowSize, 
	int envelopesColSize)
{
	for (int i = 0 ; i < envelopesRowSize; ++i)
	{
		printf("( ");
		for (int j = 0; j < envelopesColSize; ++j)
			printf("%d ", *(*(envelopes + i)+j));
		printf(")\n");
	}
}

/* test the function swapPair() */
static void test_swapPair() 
{
	int** arr = malloc(3 * sizeof(int*));
	for (int i = 0; i < 3; ++i) 
	{
		*(arr + i) = malloc(2 * sizeof(int));
		arr[i][0] = rand() % 10;
		arr[i][1] = rand() % 10;
	}

	/*
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 2; ++j)
			*(*(arr+i)+j) = 2 * (3 - i) + 3 * j;
	*/
	printf("before swap \n");
	printEnvelopes(arr, 3, 2);
	printf("after swapping 1st and 2nd pair\n");
	printf("*(*arr+2) = %d\n", *(*arr+2));
	swapPair(*arr, *(arr+2));
	printEnvelopes(arr, 3, 2);

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

/* test the use of qsort */
static void test_qsort()
{
	int** array;
	int number = 10;
	int i;
	array = malloc(number * sizeof(int*));
    for (i = 0; i < number; i++){
        array[i] = malloc(2 * sizeof(int));
        array[i][0] = rand()%20;
        array[i][1] = rand()%20;
    }
    for(i = 0;i < number;++i)
        printf("%2d, %2d\n", array[i][0], array[i][1]);

    printf("\n");

    qsort(array, number, sizeof array[0], compare);

    for(i = 0;i < number;++i)
        printf("%2d, %2d\n", array[i][0], array[i][1]);

}

/* test maxEnvelopes */
void test_maxEnvelopes()
{
	int** env;
	int numEnv = 10;
	env = malloc(numEnv * sizeof(int*));
	for (int i = 0; i < numEnv; ++i)
	{
		env[i] = malloc(2 * sizeof(int));
		env[i][0] = rand() % 10;
		env[i][1] = rand() % 10;
	}
	int max = maxEnvelopes(env, numEnv, 2);
	printf("max envelopes = %d\n", max);
}

int main()
{
	/*
	test_swapPair();
	printf("swapPair() is good!\n");
	test_qsort();
	printf("qsort test!\n");
	*/ 
	test_maxEnvelopes();

	return 0;
}