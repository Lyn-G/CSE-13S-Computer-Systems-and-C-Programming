#include "code.h"
#include "io.h"

#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

uint8_t buffer[BLOCK] = {0};
uint64_t bytes_written = 0;
uint64_t bytes_read = 0;
static uint32_t index1 = 0;
static uint32_t bits_left = 0;
static uint32_t bit1 = 0;
static uint32_t written = 0;

//You should use this function whenever you need to perform a read.
int read_bytes(int infile, uint8_t *buf, int nbytes) {
// puts("read bytes called");
	int total_bytes_read = 0; // bytes read so far
	int subtract = nbytes; // keep track if there are no more bytes to read by subtracting nbytes minus total bytes read
	int reading = 0; // bytes that have been read by read()
	bool finished = false;
	uint32_t bytes_read1 = 0;
	
	if (nbytes <= 0) {
		return 0;
	}

	// loop calls to read() 	
	while (finished == false) {
		reading = read(infile, buf + bytes_read1, nbytes);
		
		// break out if we reached the end of the file
		if (reading == 0) {
			break;
		} // end of if-statement
		
		bytes_read1 += reading;
		total_bytes_read = reading + total_bytes_read;
		subtract = nbytes - total_bytes_read;
		
		// check if we have read all the bytes that were specified (nbytes) into the byte buffer buf, or there are no more bytes to read
		if (total_bytes_read == nbytes || subtract == 0) {
			finished = true; // exit out of loop
			break;
		} // end of if-statement
	} // end of while-loop

	bytes_read += total_bytes_read;
	return total_bytes_read;
	
}

// functions the same as read_bytes(), but with write()
int write_bytes(int outfile, uint8_t *buf, int nbytes) {
	int total_bytes_write = 0; // bytes read so far
	int subtract = nbytes; // keep track if there are no more bytes to read by subtracting nbytes minus total bytes read
	int writing = 0; // bytes that have been read by read()
	bool finished = false;
	// puts("\nentering write bytes");
	if (nbytes <= 0) {
		return 0;
	}

	// loop calls to read() 	
	while (finished == false) {
		
		// if nbytes < BLOCK, write the nbytes
		// else write BLOCK bytes until nbytes == 0
		if(subtract < BLOCK) {
			writing = write(outfile, buf, subtract);
		} else {
			writing = write(outfile, buf, nbytes);
		}//end if
		
		// printf("buffer = %s\n", buf);

		total_bytes_write = writing + total_bytes_write;
		subtract = nbytes - total_bytes_write;
		// printf("writing = %d\ntotal_bytes_write = %d\nsubtract = %d\nnbytes = %d\n", writing, total_bytes_write, subtract, nbytes);
		
		// check if we have read all the bytes that were specified (nbytes) 6into the byte buffer buf, or there are no more bytes to read
		if (total_bytes_write == nbytes || subtract == 0) {
			finished = true; // exit out of loop
		} // end of if-statement
	} // end of while-loop
	bytes_written += total_bytes_write;
	return total_bytes_write;
}

// will read BLOCK bytes into a buffer from input file and will dole them out
// read in a block of bytes and dole out bits one at a time
bool read_bit(int infile, uint8_t *bit) {
	
	// read in BLOCK bytes only if we've finished reading a byte or haven't started
	if (index1 == bits_left) {
		bits_left = 8 * read_bytes(infile, buffer, BLOCK);
		index1 = 0;
		
	}
	
	// there's nothing to be read if there's 0 bits left
	if (bits_left == 0) {
		return false;
	}
	
	// get bit
	uint32_t location = index1 / 8;
	uint32_t position = index1 % 8;
	*bit = ((buffer[location] >> position) & 1);
		
	index1++; // increase the index of which bit to return next time
	
	// returns true if there are bits left in the file, false otherwise
	return true;
}

// use a static buffer and an index
// when the buffer of BLOCK bytes is filled with bits, write the contents of the buffer to outfile
void write_code(int outfile, Code *c) {
	bit1 = 0;
	// puts("\nentering write code");
	// each bit in the code c will be buffered ito the buffer
	for (uint32_t i = 0; i < code_size(c); i++) {
		bit1 = code_get_bit(c, i);
		
		// printf("written = %u\nbit = %u\n", written, bit);
		
		if (bit1 == 1) {
			uint32_t location = written / 8;
			uint32_t position = written % 8;
		
			buffer[location] |= ((uint8_t)1 << position);
			
		} else if (bit1 == 0) {
			uint32_t location = written / 8;	
			uint32_t position = written % 8;
			
			buffer[location] &= ~(1 << position);
		}
		written++;
		
		// check if buffer is filled with code, we need to flush it out
		if (written == BLOCK * 8) {
			write_bytes(outfile, buffer, BLOCK);
			written = 0;
			
			// clear buffer
			memset(buffer, 0, BLOCK);
		} // end of if-statement
	} 
}

// write out any leftover, buffered bits
// make sure that any extra bits in the last byte are zeroed before flushing the codes
void flush_codes(int outfile) {
	if (written > 0) {

		// make sure that any extra bits in the last byte are zeroed before flushing the codes
		while ((written % 8) > 0) {
			uint32_t location = written / 8;	
			uint32_t position = written % 8;
			
			buffer[location] &= ~((uint8_t)1 << position);
			written++;
		}
		write_bytes(outfile, buffer, written/8);
	}
}


/*
int main() {
	int s = STDIN_FILENO;
	printf("%d\n", read_bytes(s, buffer, BLOCK));

	
	for(unsigned long i = 0; i < 50;i++)
		printf("buffer[i] = %c\n", buffer[i]);
	
	printf("%d\n", write_bytes(fileno(stdout), buffer, 54));
	return 0;
}
*/
