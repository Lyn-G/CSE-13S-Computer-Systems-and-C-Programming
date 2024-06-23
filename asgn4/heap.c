#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "heap.h"
#include "stats.h"

uint32_t bigger;

uint32_t l_child (uint32_t n) {
	return 2 * n + 1;
}

uint32_t r_child (uint32_t n) {
	return 2 * n + 2;
}

uint32_t parent (uint32_t n) {
	return (n - 1) / 2;
}

void up_heap (Stats *stats, uint32_t *a, uint32_t n) {
	while (n > 0 && cmp(stats, a[n], a[parent(n)]) == -1) {
		swap(stats, &a[n], &a[parent(n)]);
		n = parent(n);
	}
} // end of going up heap function

void down_heap (Stats *stats, uint32_t* a, uint32_t heap_size) {
	uint32_t n = 0;
	while (l_child(n) < heap_size) {
		if (r_child(n) ==heap_size) {
			bigger = l_child(n);
		}//end of if-statement
		else {
			if (cmp(stats, a[l_child(n)] , a[r_child(n)]) == -1) {
				bigger = l_child(n);
				}
			else {
				bigger = r_child(n);
				}	
		}//end of else-statement
		if (cmp(stats, a[n], a[bigger]) == -1) {
				break;
				}
		swap(stats, &a[n], &a[bigger]);
		n = bigger;
	}//end of while-loop
} // end of going down heap function

void build_heap(Stats *stats, uint32_t *arr, uint32_t n_elements, uint32_t *heap) {
	for(uint32_t n = 0; n < n_elements; n++) {
		heap[n] = move(stats, 0);
		}
	for (uint32_t n = 0; n < n_elements; n ++) { 
		heap[n] = move(stats, arr[n]);
		up_heap (stats, heap , n);
	}
} // end of building heap function

void heap_sort(Stats *stats, uint32_t *arr, uint32_t n_elements){
	
	uint32_t heap[n_elements];
	uint32_t sorted[n_elements];
	for(uint32_t n = 0; n < n_elements; n++) {
		sorted[n] = move(stats, 0);
		}
	
	//heap = build heap(a)
	build_heap(stats, arr, n_elements, heap);
	
	for(uint32_t n = 0; n < n_elements; n++) {
		//sorted[n], heap [0] = heap[0], heap[len(a) - n - 1]
		sorted[n] = move(stats, heap[0]);
		heap[0] = move(stats, heap[n_elements - n - 1]);
		down_heap(stats, heap, n_elements - n);
	}//end of for-loop
	
	//arr = sortedlist
	for(uint32_t i = 0; i < n_elements; i++) {
		arr[i] = move(stats, sorted[i]);
	}//end of for-loop
		
}
