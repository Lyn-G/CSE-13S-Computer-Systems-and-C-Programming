#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "bubble.h"
#include "stats.h"

void bubble_sort(Stats *stats, uint32_t *arr, uint32_t n_elements) {
	bool swapped;
	
					
	for (uint32_t i = 0; i < n_elements -1; i++) { // go through the array 
		swapped = false;
		for (uint32_t k = n_elements - 1; k > i; k--) {	// look at the two elements
			int compare = cmp(stats, arr[k] , arr[k-1]);
			if (compare == -1) { // swap values
				swap(stats, &arr[k] , &arr[k-1]);
				swapped = true;
			}
			
		}
		if (swapped == false) { // if we haven't swapped, everything is sorted
				break;
		}
	}
}
