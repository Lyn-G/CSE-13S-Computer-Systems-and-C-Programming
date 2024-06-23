#include "defines.h"
#include "code.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// This function will not require any dynamic memory allocation. 
Code code_init(void) {

	// You will simply create a new Code on the stack
	Code c;
	
	// setting top to 0
	c.top = 0;
	
	// zeroing out the array of bits
	for (uint8_t i = 0; i < MAX_CODE_SIZE; i++) {
		c.bits[i] = 0;
	}
	
	return c;
}

// Returns the size of the Code, which is exactly the number of bits pushed onto the Code
uint32_t code_size(Code *c) {
	return c->top;
}

// Returns true if the Code is empty and false otherwise.
bool code_empty(Code *c) {
	return c->top == 0;
}

// Returns true if the Code is full and false otherwise. The maximum length of a code in bits is 256, which we have defined using the macro ALPHABET
bool code_full(Code *c) {
	return c->top == ALPHABET;
}

// Sets the bit at index i in the Code, setting it to 1. 
bool code_set_bit(Code *c, uint32_t i) {

	if (c) {
		uint32_t location = i / 8;
		uint32_t position = i % 8;
		
		// If i is out of range, return false
		if (i > MAX_CODE_SIZE) {
			return false;
		} else {
			// Sets the bit at index i in the Code, setting it to 1
			c->bits[location] |= ((uint8_t)1 << position);
			
			// Otherwise, return true to indicate success
			return true;
		}
	}
	return false;
}

// Clears the bit at index i in the Code, clearing it to 0. If i is out of range, return false. Otherwise, return true to indicate success.
bool code_clr_bit(Code *c, uint32_t i) {	
	if (c) {
		
		uint32_t location = i / 8;
		uint32_t position = i % 8;

		// If i is out of range, return false
		if (i > MAX_CODE_SIZE) {
			return false;
		} else {
			// clears the bit at index i in the Code, setting it to 0
			c->bits[location] &= ~(1 << position);
			
			// Otherwise, return true to indicate success
			return true;
		}	
	}
	return false;
}

// Gets the bit at index i in the Code. 
bool code_get_bit(Code *c, uint32_t i) {
	uint32_t location = i / 8;
	uint32_t position = i % 8;

	// If i is out of range, or if bit i is equal to 0, return false. 
	if (i > MAX_CODE_SIZE || i < 0) {
		return false;
		
	// Return true if and only if bit i is equal to 1.
	} else if ((c->bits[location] >> position) & 1){
		return true;
	}
	return false;
}

// Pushes a bit onto the Code. The value of the bit to push is given by bit.
bool code_push_bit(Code *c, uint8_t bit) {
	if (c) {
		
		// Returns false if the Code is full prior to pushing a bit
		if (code_full(c) == true) {
			return false;	
		
		} else {
			if (bit == 1) {
				code_set_bit(c, c->top);
			}
			// return true otherwise to indicate the successful pushing of a bit
			c->top++;
			return true;
		}
	}
	return false;
}

// Pops a bit off the Code. The value of the popped bit is passed back with the pointer bit. 
bool code_pop_bit(Code *c, uint8_t *bit) {
	if (c) {

		// Returns false if the Code is empty prior to popping a bit
		if (code_empty(c) == true) {
			return false;
		
		// return true otherwise to indicate the successful popping of a bit
		} else {
			*bit = code_get_bit(c, c->top - 1);
			code_clr_bit(c, c->top - 1);
			c->top--;
			return true;
		}
	}
	return false;
}

void code_print(Code *c) {
	printf("is it empty? %d\n", code_empty(c));
	printf("is it full? %d\n", code_full(c));
	printf("top: %u\n", c->top);
	printf("size: %u\n", code_size(c));
	
	puts("printing bits now:");
	for (uint32_t i = 0; i < MAX_CODE_SIZE; i++) {
		printf("%d", code_get_bit(c, i));
	}
	puts("");
}

/*
int main () {

	uint8_t hello = 0;	
	
	Code c = code_init();
	// code_push_bit(&c, 0);
	code_print(&c);
	
	// code_set_bit(&c, 0);
	// code_print(&c);
	
	code_push_bit(&c, 1);
	code_print(&c);
	
	code_push_bit(&c, 1);
	code_push_bit(&c, 1);
	code_push_bit(&c, 1);
	code_push_bit(&c, 1);
	code_push_bit(&c, 1);
	code_print(&c);
	code_set_bit(&c, 8);
	code_pop_bit(&c, &hello);
	code_clr_bit(&c, 2);
	// printf("%d\n", hello);
	// printf("%d\n", code_get_bit(&c, 2));
	// code_set_bit(&c, 0);
	code_print(&c);
	
	return 0;
}
*/
