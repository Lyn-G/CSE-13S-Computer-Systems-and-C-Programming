#include "huffman.h"
#include "pq.h"
#include "io.h"
#include "stack.h"
#include "code.h"
#include "header.h"
#include "defines.h"
#include "node.h"

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

#define OPTIONS "hi:o:v"
#define MAX_FILE 100

int main (int argc, char **argv) {
	
	int r;
	bool help = false; // for help statement 
	bool bad = false; // for invalid option
	bool compress = false;
	
	bool bool_input = false;
	bool bool_output = false;
	char * input_file = NULL;
	char * output_file = NULL;
	FILE *open_input = NULL; // initial files
	FILE *open_output = NULL;
	FILE *tmp = tmpfile();
	
	uint8_t buffer[BLOCK] = {0};
	
	while ((r = getopt (argc, argv, OPTIONS)) != -1) {
		switch (r) {
			case 'h':
				help = true;
				break;
			case 'i':
				bool_input = true;
				input_file = (char*) malloc (MAX_FILE * sizeof(char));
				strcpy(input_file, optarg);
				break;
			case 'o':
				bool_output = true;
				output_file = (char*) malloc (MAX_FILE * sizeof(char));
				strcpy(output_file, optarg);
				break;
			case 'v':
				compress = true;
				break;
			default:
				bad = true;
				break;
		} // end of cases
	} // end of while-loop
	
	// print out the help message
	if (help) {
		fprintf(stderr, "SYNOPSIS\n");
		fprintf(stderr, "  A Huffman encoder.\n");
		fprintf(stderr, "  Compresses a file using the Huffman coding algorithm.\n\n");

		fprintf(stderr, "USAGE\n");
		fprintf(stderr, "  ./encode [-h] [-i infile] [-o outfile]\n\n");

		fprintf(stderr, "OPTIONS\n");
		fprintf(stderr, "  -h             Program usage and help.\n");
		fprintf(stderr, "  -v             Print compression statistics.\n");
		fprintf(stderr, "  -i infile      Input file to compress.\n");
		fprintf(stderr, "  -o outfile     Output of compressed data.\n");

	// exit with 0 because this is just the help message
		exit(0);
	} else if (bad) {
		fprintf(stderr, "SYNOPSIS\n");
		fprintf(stderr, "  A Huffman encoder.\n");
		fprintf(stderr, "  Compresses a file using the Huffman coding algorithm.\n\n");

		fprintf(stderr, "USAGE\n");
		fprintf(stderr, "  ./encode [-h] [-i infile] [-o outfile]\n\n");

		fprintf(stderr, "OPTIONS\n");
		fprintf(stderr, "  -h             Program usage and help.\n");
		fprintf(stderr, "  -v             Print compression statistics.\n");
		fprintf(stderr, "  -i infile      Input file to compress.\n");
		fprintf(stderr, "  -o outfile     Output of compressed data.\n");
		
		// exit with 1 because this is a bad option
		exit(1);
	} else if (bad == false && help == false) {
	
		// check if we need to accept a file or not
		// use int since we want the file number
		int input = 0;
		int output = 0;

		if (bool_input == false) {
		
			open_input = stdin;
			
			int o = 0;
			while ((o = read_bytes(input, buffer, BLOCK)) > 0) {
				write_bytes(fileno(tmp), buffer, o);
			}
			
			// set and use the created temporary file
			input = fileno(tmp);
		} else {
			// open the specified file
			open_input = fopen(input_file, "r");
			input = fileno(open_input);
		} //end if-else
		
		if (bool_output == false) {
			output = STDOUT_FILENO;
		} else {
			// open the specified output file
			open_output = fopen(output_file, "w+");
			output = fileno(open_output);
		} //end if else
		
		// reset everything that is necessary
		lseek(input, 0, SEEK_SET);
		bytes_written = 0;
		bytes_read = 0;
		
		// compute a histogram of the file
		// count the number of occurrences of each unique symbol in the file
		uint64_t histogram[ALPHABET] = {0};
		
		int q = 0;
		while ((q = read_bytes(input, buffer, BLOCK)) > 0) {
			for (int i = 0; i < q; i++) {
				int ascii = buffer[i];
				histogram[ascii]++;
			} // end of for-loop
		} // end of while-loop
		
		if (histogram[0] == 0) {
			histogram[0] = 1;
		} 
		
		if (histogram[1] == 0) {
			histogram[1] = 1;
		}
		
		// construct Huffman tree using a priority queue
		Node *root = build_tree(histogram);
		Code table[ALPHABET] = {0}; //initialize code table
		build_codes(root, table);
		
		// count how many unique symbols
		lseek(input, 0, SEEK_SET);
		int unique = 0;
		for (int u = 0; u < ALPHABET; u++) {
			if (histogram[u] > 0) {
				unique++;
			}
		}
		struct stat p; // permissions

		lseek(input, 0, SEEK_SET);
		
		// construct a header
		// we need to use fstat()
		Header header;
		
		fstat(input, &p);
		
		// set outfile's permissions
		fchmod(output, p.st_mode);
		
		header.magic = MAGIC;
		header.permissions = p.st_mode;
		header.tree_size = (3 * unique) - 1;
		header.file_size = p.st_size;
		
		// printf("%u\n%x\n%u\n%lu\n", header.magic, header.permissions, header.tree_size, header.file_size);
		
		if (fchmod(output, header.permissions) != 0) {
			fprintf (stderr, "Permission denied.\n");
			exit(1);
		}
		// write the constructed header to outfile
		write_bytes(output, (uint8_t *)&header, sizeof(Header));

		// write the constructed Huffman tree to outfile using dump_tree()
		dump_tree(output, root);
		
		// Starting at the beginning of infile
		lseek(input, 0, SEEK_SET);
		
		// write the corresponding code for each symbol to outfile with write_code().
		uint64_t w = 0;
		while ((w = read_bytes(input, buffer, BLOCK)) > 0) {
			for (uint64_t i = 0; i < w; i++) {
				write_code(output, &table[buffer[i]]);
			}
		}

		//When finished with all the symbols, make sure to flush any remaining buffered codes with flush_codes().
		flush_codes(output);
		
		// print out the compression data
		if (compress == true) {
			fprintf(stderr, "Uncompressed file size: %lu bytes\n", header.file_size);
			fprintf(stderr, "Compressed file size: %lu bytes\n", bytes_written);
			// uint64_t compress = bytes_written - (header.file_size * 2 + 2);
			double space = 100 * (1 - ((double) bytes_written/ header.file_size));
			fprintf(stderr, "Space saving: %.2f%%\n", space);
		}
		
		// close out files
		if (bool_input == true) {
			fclose(open_input);
		}
		if (bool_output == true) {
			fclose(open_output);
		}
		delete_tree(&root);
	}
	return 0;
}
