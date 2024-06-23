#include "mathlib.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h> // For getopt().
#include <stdbool.h>

#define OPTIONS "-ascCSTl"

int main(int argc, char **argv) {
int opt = 0;
double difference;
double first;
double second;

bool sin_x = false;
bool cos_x = false;
bool arcsin_x = false;
bool arccos_x = false;
bool arctan_x = false;
bool log_x = false;

while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
	switch (opt) {
		case 'a':
		if (sin_x == false) {
		printf("  x	       sin		Library	      Difference\n");
		printf("  -	       ------ 		-------       ----------\n");
		sin_x = true;
		for (double starting = (0.05)*(M_PI); starting < (2)*(M_PI); starting += (0.05)*(M_PI)) {
			first = my_sin(starting);
			second = sin(starting);
			difference = first - second;
			printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", starting, first, second, difference);
			}
		}
		
		if (cos_x == false) { 
		printf("  x	       cos		Library	      Difference\n");
		printf("  -	       ------ 		-------       ----------\n");
		cos_x = true;
		for (double starting = (0.05)*(M_PI); starting < (2)*(M_PI); starting += (0.05)*(M_PI)) {
			first = my_cos(starting);
			second = cos(starting);
			difference = first - second;
			printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", starting, first, second, difference);
			}
		}
		
		if (arcsin_x == false) {
		printf("  x	       arcsin		Library	      Difference\n");
		printf("  -	       ------ 		-------       ----------\n");
		arcsin_x = true;
		for (double starting = (-1); starting < (1); starting += (0.05)) {
			first = my_arcsin(starting);
			second = asin(starting);
			difference = first - second;
			printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", starting, first, second, difference);
			}
		}
		
		if (arccos_x == false) {
		printf("  x	       arccos		Library	      Difference\n");
		printf("  -	       ------ 		-------       ----------\n");
		arccos_x = true;
		for (double starting = (-1); starting < (1); starting += (0.05)) {
			first = my_arccos(starting);
			second = acos(starting);
			difference = first - second;
			printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", starting, first, second, difference);
			}
		}
		
		if (arctan_x == false) {
		printf("  x	       arctan		Library	      Difference\n");
		printf("  -	       ------ 		-------       ----------\n");
		arctan_x = true;
		for (double starting = (1); starting < (10); starting += (0.05)) {
			first = my_arctan(starting);
			second = atan(starting);
			difference = first - second;
			printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", starting, first, second, difference);
			}
		}
		
		if (log_x == false) {
		printf("  x	       log		Library	      Difference\n");
		printf("  -	       ------ 		-------       ----------\n");
		log_x = true;
		for (double starting = (1); starting < (10); starting += (0.05)) {
			first = my_log(starting);
			second = log(starting);
			difference = first - second;
			printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", starting, first, second, difference);
			}
		}
		break;
		
		
		case 's':
		if (sin_x == false) {
		printf("  x	       sin		Library	      Difference\n");
		printf("  -	       ------ 		-------       ----------\n");
		for (double starting = (0.05)*(M_PI); starting < (2)*(M_PI); starting += (0.05)*(M_PI)) {
			first = my_sin(starting);
			second = sin(starting);
			difference = first - second;
			printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", starting, first, second, difference);
			}
		break;
		}
		
		case 'c':
		if (cos_x == false) {
		printf("  x	       cos		Library	      Difference\n");
		printf("  -	       ------ 		-------       ----------\n");
		cos_x = true;
		for (double starting = (0.05)*(M_PI); starting < (2)*(M_PI); starting += (0.05)*(M_PI)) {
			first = my_cos(starting);
			second = cos(starting);
			difference = first - second;
			printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", starting, first, second, difference);
			}
		break;
		}

		case 'S':
		if (arcsin_x == false) {
		printf("  x	       arcsin		Library	      Difference\n");
		printf("  -	       ------ 		-------       ----------\n");
		arcsin_x = true;
			for (double starting = (-1); starting < (1); starting += (0.05)) {
			first = my_arcsin(starting);
			second = asin(starting);
			difference = first - second;
			printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", starting, first, second, difference);
			}
		break;
		}

		case 'C':
		if (arccos_x == false) {
		printf("  x	       arccos		Library	      Difference\n");
		printf("  -	       ------ 		-------       ----------\n");
		arccos_x = true;
		for (double starting = (-1); starting < (1); starting += (0.05)) {
			first = my_arccos(starting);
			second = acos(starting);
			difference = first - second;
			printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", starting, first, second, difference);
			}
		break;
		}
		
		case 'T':
		if (arctan_x == false) {
		printf("  x	       arctan		Library	      Difference\n");
		printf("  -	       ------ 		-------       ----------\n");
		arctan_x = true;
		for (double starting = (1); starting < (10); starting += (0.05)) {
			first = my_arctan(starting);
			second = atan(starting);
			difference = first - second;
			printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", starting, first, second, difference);
			}
		break;
		}
		
		case 'l':
		if (log_x == false) {
		printf("  x	       log		Library	      Difference\n");
		printf("  -	       ------ 		-------       ----------\n");
		log_x = true;
		for (double starting = (1); starting < (10); starting += (0.05)) {
			first = my_log(starting);
			second = log(starting);
			difference = first - second;
			printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", starting, first, second, difference);
			}
		break;
		}
		}
	}
	return 0;
}
