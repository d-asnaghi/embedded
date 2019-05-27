
/*
********************************************************************************
*                                                                              *
* Copyright (c) 2019 Davide Asnaghi                                            *
*                                                                              *
* Permission is hereby granted, free of charge, to any person obtaining a      *
* copy of this software and associated documentation files (the "Software"),   *
* to deal in the Software without restriction, including without limitation    *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,     *
* and/or sell copies of the Software, and to permit persons to whom the        *
* Software is furnished to do so, subject to the following conditions:         *
*                                                                              *
* The above copyright notice and this permission notice shall be included      *
* in all copies or substantial portions of the Software.                       *
*                                                                              *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR   *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,     *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL      *
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER   *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING      *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER          *
* DEALINGS IN THE SOFTWARE.                                                    *
*                                                                              *
********************************************************************************
*/

#include <stdint.h>

/*******************************************************************************
 INSERTION SORT
 *******************************************************************************/

void embedded_insertionsort(int32_t * arr, uint32_t len){
	// traverse the array
	for(uint32_t i=1; i<len; i++){
		// select current value and store it in temp
		uint32_t j = i;
		int32_t temp = arr[i];
		// push forward all the elements greater than current value
		while (j > 0 && arr[j-1] > temp)
			arr[j] = arr[j-1], j--;
		// push back current value to the furthes point reached
		arr[j] = temp;
	}
}

/*******************************************************************************
 SHELL SORT
 *******************************************************************************/

void embedded_shellsort(int32_t * arr, uint32_t len){
	// create smaller sub arrays to sort in
	for (uint32_t gap = len/2; gap > 0; gap /= 2) {
		uint32_t i;
		// sort the sub arrays
		for(i = gap; i<len; i++){
			uint32_t j;
			int32_t temp = arr[i];
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) 
				arr[j] = arr[j - gap]; 
			arr[j] = temp;
		}
	}
}

/*******************************************************************************
 HEAP SORT
 *******************************************************************************/

#define l_child(node) 2*node+1
#define r_child(node) 2*node+2

void swap (int32_t* a, int32_t* b){
	int32_t temp = *a;
	*a = *b;
	*b = temp;
}

void create_heap(int32_t heap[], uint32_t node, uint32_t last){
	int32_t child;
	uint8_t exit = 0;

	while(!exit && l_child(node) <= last){
		// choose the greater between right and left child 
		child = l_child(node);
		if(r_child(node) <= last && heap[r_child(node)] > heap[l_child(node)])
			child = r_child(node);
		// if the parent is greater than the child exit the loop
		if(heap[node] > heap[child])
			exit = 1;
		else			
			swap (&heap[node], &heap[child]), node=child;
	}
}

void embedded_heapsort(int32_t * arr, uint32_t len){
	// create heap
	for(int i=len/2; i>=0; i--)
		create_heap(arr, i, len-1);

	// perform sorting
	for (int last=len-1; last > 0; last--) {
		//swap heap[0] and heap[last]
		swap(&arr[0], &arr[last]);
		// create heap for remaining array
		create_heap(arr, 0, last-1);
	}
}

/*******************************************************************************
 DRIVER CODE
 *******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N_TRIAL 100

void fill_random(int32_t arr[], uint32_t len){
	for (uint32_t i = 0; i < len; i++)
		arr[i] = rand()%(2*len) * pow(-1, rand()%2);
}

uint8_t check(int32_t arr[], uint32_t len){
	for (uint32_t i = 1; i<len; i++)
		if (arr[i-1] > arr[i])
			return 0;
	return 1;
}

float timed_sorting(void sort_fn(int32_t*, uint32_t), int32_t arr[], uint32_t len){
    
    clock_t t; 
    double ms_taken=0;
    uint8_t n;

    for (n=0; n<N_TRIAL; n++){
	    fill_random(arr, len);
	    t = clock(); 
	    sort_fn(arr, len);
	    t = clock() - t; 
	    ms_taken += ((double)t)/CLOCKS_PER_SEC; // in seconds 
	}
    
    check(arr, len) ? printf("[ARRAY SORTED] ") : printf("[SORTING FAILED] ");
	return (ms_taken/N_TRIAL)*1000;
}

int main(int argc, char const *argv[])
{
	double time_taken;

	// parse user input
	if (argc < 2 || atoi(argv[1]) <= 0){
		printf("[INVALID ARGUMENT]\n");
		return 0;
	}
		
	// create an array to sort
	const uint32_t len = atoi(argv[1]);	
	int32_t array[len];

	// timing for heap sort
	time_taken = timed_sorting(embedded_heapsort, array, len);
    printf("[HEAP SORT: %.3f ms, N = %d]\n", time_taken, len); 

    // timing for shell sort
    time_taken = timed_sorting(embedded_shellsort, array, len);
    printf("[SHELL SORT: %.3f ms, N = %d]\n", time_taken, len);

	// timing for insertion sort
    time_taken = timed_sorting(embedded_insertionsort, array, len);
    printf("[INSERTION SORT: %.3f ms, N = %d]\n", time_taken, len);

	return 0;
}