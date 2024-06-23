#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include "bubble.h"
#include "shell.h"
#include "heap.h"
#include "stats.h"
#include "quick.h"
#include "set.h"
#include "mtrand.h"


#define MASK 0x3FFFFFFF

#define BUBBLE 1
#define SHELL  2
#define QUICK  3
#define HEAP   4

#define OPTIONS "asbqhHr:n:p:"

int main(int argc, char **argv) 
{
	
	int r;
	uint32_t *arr;
	
	uint32_t arrsize = 100;
	uint32_t getting_size;
	
	uint64_t seed = 13371453;
	bool default_seed = true;
	
	uint32_t printing = 100;
	
	bool help = false;
	bool wrong = false;
	
	Stats * stats = malloc(sizeof(Stats)); //allocate memory for stats struct
	mtrand_seed(seed);
	Set set = set_empty();

	//Run through command line arguments
	while ((r = getopt (argc, argv, OPTIONS)) != -1) {
		switch (r) {
			case 'a': 
				set = set_insert(set, HEAP);
				set = set_insert(set, BUBBLE);
				set = set_insert(set, SHELL);
				set = set_insert(set, QUICK);
				  break;
			case 'b':
				set = set_insert(set, BUBBLE);
				break;
			case 's':
				set = set_insert(set, SHELL);
				break;
			case 'h':
				set = set_insert(set, HEAP);
				break;
			case 'q':
				set = set_insert(set, QUICK);
				break;
			case 'n':
				  getting_size = atoi(optarg);
				  if (getting_size > 250000000 || getting_size <= 0) {
				  	help = true;
				  	}
				  else {
				  	arrsize = getting_size;
				  	}
				break;
			case 'r':
				seed = atoi(optarg);
				default_seed = false;
				break;
			case 'p':
				printing = atoi(optarg);
				break;
			case 'H': 
				help = true;
				break;
				
			default:
				wrong = true;
				break;
				

			}
	}//end while


	if(help == true) { // will only print the help page if invalid option or -H
printf("SYNOPSIS\n");
printf("   A collection of comparison-based sorting algorithms.\n\n");

printf("USAGE\n");
printf("   ./sorting [-Hasbhq] [-n length] [-p elements] [-r seed]\n\n");

printf("OPTIONS\n");
printf("   -H              Display program help and usage.\n");
printf("   -a              Enable all sorts.\n");
printf("   -b              Enable Bubble Sort.\n");
printf("   -h              Enable Heap Sort.\n");
printf("   -q              Enable Quick Sort.\n");
printf("   -s              Enable Shell Sort.\n");
printf("   -n length       Specify number of array elements (default: 100).\n");
printf("   -p elements     Specify number of elements to print (default: 100).\n");
printf("   -r seed         Specify random seed (default: 13371453).\n");
	} 
	else if (wrong == true) {
		printf("SYNOPSIS\n");
printf("   A collection of comparison-based sorting algorithms.\n\n");

printf("USAGE\n");
printf("   ./sorting [-Hasbhq] [-n length] [-p elements] [-r seed]\n\n");

printf("OPTIONS\n");
printf("   -H              Display program help and usage.\n");
printf("   -a              Enable all sorts.\n");
printf("   -b              Enable Bubble Sort.\n");
printf("   -h              Enable Heap Sort.\n");
printf("   -q              Enable Quick Sort.\n");
printf("   -s              Enable Shell Sort.\n");
printf("   -n length       Specify number of array elements (default: 100).\n");
printf("   -p elements     Specify number of elements to print (default: 100).\n");
printf("   -r seed         Specify random seed (default: 13371453).\n");
exit(1);
		}
	else if (help != true) {
		if (default_seed != false) {
			seed = 13371453;
			}
		mtrand_seed(seed);
		// Create random array and assign values
		arr = (uint32_t*) malloc(arrsize * sizeof(uint32_t));
		for (uint32_t i = 0; i < arrsize; i = i + 1) {
			arr[i] = mtrand_rand64() & MASK;
		}// end of for-loop
		if(set_member(set, BUBBLE) == true) { // bubble sort 
			bubble_sort(stats, arr, arrsize);
			if (arrsize < printing) {
				printing = arrsize;
				} // end of if-statement
			printf("Bubble Sort, %d elements, %" PRIu64 " moves, %" PRIu64 " compares \n", arrsize, stats->moves, stats->compares); 
			for(uint32_t loop = 0; loop < printing; loop ++) {
				printf("%13" PRIu32, arr[loop]);
				if (loop % 5 == 4) {
					printf("\n");
					}
				} // end of for-loop
		reset(stats);
		if (arrsize % 5 !=0) {
			puts("\n");
			}
		} // end of if-statement for bubble 
		
				mtrand_seed(seed);
		// Create random array and assign values
		arr = (uint32_t*) malloc(arrsize * sizeof(uint32_t));
		for (uint32_t i = 0; i < arrsize; i = i + 1) {
			arr[i] = mtrand_rand64() & MASK;
		}// end of for-loop 
		
		if(set_member(set, HEAP) == true) { // heap sort
			// run heap sort
			heap_sort(stats, arr, arrsize);
			if (arrsize < printing) {
				printing = arrsize;
				} // end of if-statement
			printf("Heap Sort, %d elements, %" PRIu64 " moves, %" PRIu64 " compares \n", arrsize, stats->moves, stats->compares); 
			reset(stats);
			for(uint32_t loop = 0; loop < printing; loop ++) {
				printf("%13" PRIu32, arr[loop]);
				if (loop % 5 == 4) {
					printf("\n");
					}
				} // end of for-loop
		if (arrsize % 5 !=0) {
			puts("\n");
			}
		}// end of if-statement for heap
		
		mtrand_seed(seed);
		// Create random array and assign values
		arr = (uint32_t*) malloc(arrsize * sizeof(uint32_t));
		for (uint32_t i = 0; i < arrsize; i = i + 1) {
			arr[i] = mtrand_rand64() & MASK;
		}// end of for-loop
		if(set_member(set, QUICK) == true) { // quick sort
			quick_sort(stats, arr, arrsize);
			if (arrsize < printing) {
				printing = arrsize;
				} // end of if-statement
			printf("Quick Sort, %d elements, %" PRIu64 " moves, %" PRIu64 " compares \n", arrsize, stats->moves, stats->compares); 
			for(uint32_t loop = 0; loop < printing; loop ++) {
				printf("%13" PRIu32, arr[loop]);
				if (loop % 5 == 4) {
					printf("\n");
					}
				} // end of for-loop // end of for-loop
		reset(stats);
		if (arrsize % 5 !=0) {
			puts("\n");
			}
		}// end of if-statement for quick
		
		mtrand_seed(seed);
		// Create random array and assign values
		arr = (uint32_t*) malloc(arrsize * sizeof(uint32_t));
		for (uint32_t i = 0; i < arrsize; i = i + 1) {
			arr[i] = mtrand_rand64() & MASK;
		}// end of for-loop
		if(set_member(set, SHELL) == true) { // shell sort
			shell_sort(stats, arr, arrsize);
			if (arrsize < printing) {
				printing = arrsize;
				} // end of if-statement
			printf("Shell Sort, %d elements, %" PRIu64 " moves, %" PRIu64 " compares \n", arrsize, stats->moves, stats->compares); 
			for(uint32_t loop = 0; loop < printing; loop ++) {
				printf("%13" PRIu32, arr[loop]);
				if (loop % 5 == 4) {
					printf("\n");
					}
				} // end of for-loop
		reset(stats);
		if (arrsize % 5 !=0) {
			puts("\n");
			}
		}// end of if-statement for shell
	free(arr);
	}// end of else-statement
}
