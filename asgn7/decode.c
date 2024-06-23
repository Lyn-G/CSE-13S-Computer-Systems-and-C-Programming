#include "huffman.h"
#include "pq.h"
#include "io.h"
#include "stack.h"
#include "code.h"
#include "header.h"
#include "defines.h"

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
	
	if (help) {
		fprintf(stderr, "SYNOPSIS\n");
		fprintf(stderr, "  A Huffman decoder.\n");
		fprintf(stderr, "  Decompresses a file using the Huffman coding algorithm.\n\n");

		fprintf(stderr, "USAGE\n");
		fprintf(stderr, "  ./decode [-h] [-i infile] [-o outfile]\n\n");

		fprintf(stderr, "OPTIONS\n");
		fprintf(stderr, "  -h             Program usage and help.\n");
		fprintf(stderr, "  -v             Print compression statistics.\n");
		fprintf(stderr, "  -i infile      Input file to decompress.\n");
		fprintf(stderr, "  -o outfile     Output of decompressed data.\n");


	// exit with 0 because this is just the help message
		exit(0);
	} else if (bad) {
		fprintf(stderr, "SYNOPSIS\n");
		fprintf(stderr, "  A Huffman decoder.\n");
		fprintf(stderr, "  Decompresses a file using the Huffman coding algorithm.\n\n");

		fprintf(stderr, "USAGE\n");
		fprintf(stderr, "  ./decode [-h] [-i infile] [-o outfile]\n\n");

		fprintf(stderr, "OPTIONS\n");
		fprintf(stderr, "  -h             Program usage and help.\n");
		fprintf(stderr, "  -v             Print compression statistics.\n");
		fprintf(stderr, "  -i infile      Input file to decompress.\n");
		fprintf(stderr, "  -o outfile     Output of decompressed data.\n");
		
		// exit with 1 because this is a bad option
		exit(1);
	} else if (bad == false && help == false) {
		int input = 0;
		int output = 0;
		
		if (bool_input == false) {
			input = STDIN_FILENO;
			
		} else {
			open_input = fopen(input_file, "r");
			input = fileno(open_input);
		} //end if-else
		
		if (bool_output == false) {
			output = STDOUT_FILENO;
		} else {
			open_output = fopen(output_file, "w+");
			output = fileno(open_output);
		} //end if else
		
		// first, read in header symbols to check magic number
		Header header;
		read_bytes(input, (uint8_t *) &header, sizeof(Header));
		
		// read in the input file and get the header
		// you can use of size of header to get the number of bytes from the infile
		
		// read in the header from infile and verify the magic number
		if (header.magic != MAGIC) {
			fprintf (stderr, "Magic number does not match file. Exiting.\n");
			exit(1);
		}
		
		struct stat p; // permissions
		fstat(input, &p);
		fchmod(output, header.permissions);

		// read the dumped tree from infile into an array that is tree_size bytes long
		uint8_t array[header.tree_size];
		read_bytes(input, array, header.tree_size);
		
		// then, reconstruct Huffman tree using rebuild_tree()
		Node *root = rebuild_tree(header.tree_size, array);

		// we will be traversing down the tree one link at a time for each bit that is read
		uint8_t bit = 0;
		uint64_t w = 0;
		uint64_t index = 0;
		Node * reconstruct = root;
		
		while (w < header.file_size) {
		
			// read infile one bit at a time using read_bit()
			read_bit(input, &bit);
			
			if (reconstruct->left == NULL && reconstruct->right == NULL) {
				// puts("right and left are NULL");
				buffer[index] = reconstruct->symbol;		
				index++;
				w++;
				
				// set the node as the root node once again
				reconstruct = root;
				
				// write out bytes and reset index
				if (index == BLOCK) {
					write_bytes(output, buffer, BLOCK);
					index = 0;
				}
				
			}
			
			// see what bit is read and go either to the left or right
			if (bit == 0) {
				// puts("bit = 0");
				reconstruct = reconstruct->left;
			} else if (bit == 1) {
				// puts("bit = 1");
				reconstruct = reconstruct->right;
			}
			
			
				
			
		}
		
		// write out bytes
		write_bytes(output, buffer, index);
			
		if (compress == true) {
			fprintf(stderr, "Compressed file size: %lu bytes\n", bytes_read);
			fprintf(stderr, "Decompressed file size: %lu bytes\n", bytes_written);
			double space = 100 * (1 - ((double) bytes_read/ header.file_size));
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
