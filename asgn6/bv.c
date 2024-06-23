#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "bv.h"

struct BitVector {
	uint32_t length;
	uint64_t *vector;
};

// In the event that sufficient memory cannot be allocated, the function must return NULL. 
// Else, it must return a BitVector *, or a pointer to an allocated BitVector. 
// Each bit of the bit vector should be initialized to 0.
BitVector *bv_create(uint32_t length) {

	uint32_t location = length / 64;
	uint32_t position = length % 64;
	uint32_t add = 0;
	
	//add one if there is a remainder
	//this is because we need the ceiling
	if (position != 0) {
		add = 1;
	}
	
	add = add + location;
	
	BitVector *bv = (BitVector *) malloc(sizeof(BitVector));
	// if item is defined and not NULL
	if (bv) {
		// need to initialize bits to 0
		bv->length = length;
		bv->vector = (uint64_t *) calloc(add, sizeof(uint64_t));
	} else {
		// return NULL if not enough memory
		bv = NULL;
	}
	
	return bv;
}

void bv_print(BitVector *bv) {
	for (uint32_t i = 0; i < bv->length; i++) {
		printf("%d", bv_get_bit(bv,i));

	}
}
 
// free memory and null out the pointer
void bv_delete(BitVector **bv) {
	if (*bv && (*bv)->vector) {
		free ((*bv)->vector);
		free (*bv);
		*bv = NULL;
	} else if ((*bv)) {
		free(*bv);
		*bv = NULL;
	}
}

uint32_t bv_length(BitVector *bv) {	
	return bv->length;
}

void bv_set_bit(BitVector *bv, uint32_t i) {
	uint32_t location = i / 64;
	uint32_t position = i % 64;
	
	
	// \=
	// <<
	// take vector[byte]
	// or it with shifting by one
	
	// can't use 0x1
	//unsigned long one = 1;
	
	if (bv && bv->vector && i < bv->length) {
		bv->vector[location] |= ((uint64_t)0x1 << position);
	}
}


void bv_clr_bit(BitVector *bv, uint32_t i) {
	uint32_t location = i / 64;
	uint32_t position = i % 64;
	
	// same process as set bit, but use &=
	// and use ~ (negation) on shifting bit
	
	// can't use 0x1
	unsigned long one = 1;
	
	if (bv) {
		bv->vector[location] &= ~(one << position);	
	}

}

uint8_t bv_get_bit(BitVector *bv, uint32_t i) {
	uint32_t location = i / 64;
	uint32_t position = i % 64;
	
	uint8_t get = 0;
	
	if (bv && bv->vector && i < bv->length) {
		get = (bv->vector[location] >> position) & 0x1;
	}

	return get;
}

/*int main() {
	BitVector *bv = bv_create(10);
	// printf("\n");
	bv_print(bv);
	bv_set_bit(bv, 3);
	printf("\n");
	printf("\n");
	bv_print(bv);
	
	return 0;
}*/
