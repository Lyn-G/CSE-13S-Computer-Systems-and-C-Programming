#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "stats.h"

uint32_t j;
uint32_t temp;

uint32_t gaps(uint32_t n) { // create gaps for the sort
	
	if(n <= 2) {
		n = 1;
		}
	else {
		n = 5 * n / 11;	
		}
	return n;
	
}

void shell_sort(Stats *stats, uint32_t *arr, uint32_t n_elements) { 
	
	for (uint32_t gap = gaps(n_elements); gap > 0; gap --) { // get the gap
		for (uint32_t i = gap; i < n_elements; i ++) {
			j = i;
			temp = move(stats, arr[i]);
			while (j >= gap && cmp(stats, arr[j - gap] , temp) == 1) { // move values if needed
				arr[j] = move(stats, arr[j - gap]);
				j = j - gap;
				}
			arr[j] = move(stats, temp);
			} // end of second for-loop
		} // end of first for-loop
	      
}
