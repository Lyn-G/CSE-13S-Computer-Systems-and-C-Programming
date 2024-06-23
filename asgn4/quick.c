#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "quick.h"
#include "stats.h"
#include "shell.h"

#define SMALL 8

// create the parts that we need for comparing and moving
uint32_t partition (Stats *stats, uint32_t *arr ,uint32_t first,uint32_t last) { 
	uint32_t pivot_value = arr[first]; 
	uint32_t left_mark = first + 1;
	uint32_t right_mark = last;
	bool done = false;
	
	while (done == false) {
		while (left_mark <= right_mark && arr[left_mark] <= pivot_value) {
			left_mark = left_mark + 1;
			}
		if ((int) right_mark >= 0) {

			while (arr[right_mark] >= pivot_value && right_mark >= left_mark && right_mark >= 0) {
				right_mark = right_mark - 1;
				if ((int)right_mark < 0) {
					break;
					}
				}
		}
		

		if (cmp(stats, right_mark , left_mark)==-1) {
			done = true;
			}
		else {

			if ((int) right_mark >= 0) {
				swap(stats, &arr[left_mark], &arr[right_mark]);
				}
			}
		} // end of first while-loop
	if ((int) right_mark >= 0) {
		swap(stats, &arr[first], &arr[right_mark]);
		}
	
	return right_mark;
	}

// since we can't edit the quick sort function given to us, we can create another function to help us to do so
void quick_sort_helper(Stats *stats, uint32_t *arr, uint32_t n_elements, uint32_t first, uint32_t last) { 
	if (n_elements < SMALL) {
		shell_sort (stats, arr, n_elements);
		return;
	}
	
	if (first < last) { 
		if ((int) last >= 0) {
				
		uint32_t split_point = partition(stats, arr, first, last);
			if ((int) split_point > 0) {
				quick_sort_helper(stats, arr, n_elements, first, split_point - 1); // recursion
				quick_sort_helper(stats, arr, n_elements, split_point + 1, last); // recursion
				}
		}
	}
}

void quick_sort(Stats *stats, uint32_t *arr, uint32_t n_elements) {
	uint32_t first = 0;
	uint32_t last = n_elements - 1;
	quick_sort_helper(stats, arr, n_elements, first, last); // recursion kind of
	
}
