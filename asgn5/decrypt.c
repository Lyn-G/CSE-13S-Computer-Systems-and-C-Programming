#include "randstate.h"
#include "rsa.h"
#include "numtheory.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#define MAX_FILE 100

#define OPTIONS "i:o:n:vh"

int main (int argc, char **argv) {
	
	int r;
	
	bool help = false;
	bool bad = false;
	bool verbose = false;
	bool bool_input = false;
	bool bool_output = false;
	
	char * input_file = NULL;
	char * output_file = NULL;
	char *private = "rsa.priv";
	
	FILE *input = NULL; // initial files
	FILE *output = NULL;

	while ((r = getopt (argc, argv, OPTIONS)) != -1) {
		switch (r) {
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
			case 'n':
				private = (char*) malloc (MAX_FILE * sizeof(char));
				strcpy(private, optarg);
				break;
			case 'v':
				verbose = true;
				break;
			case 'h':
				help = true;
				break;
			default:
				bad = true;
				break;
		} // end of cases
	} // end of while-loop
	
	if (help == true) { // exits with 0

		fprintf(stderr, "Usage: ./decrypt [options]\n");
		fprintf(stderr,"  ./decrypt decrypts an input file using the specified private key file,\n");
		fprintf(stderr,"  writing the result to the specified output file.\n");
		fprintf(stderr,"    -i <infile> : Read input from <infile>. Default: standard input.\n");
		fprintf(stderr,"    -o <outfile>: Write output to <outfile>. Default: standard output.\n");
		fprintf(stderr,"    -n <keyfile>: Private key is in <keyfile>. Default: rsa.priv.\n");
		fprintf(stderr,"    -v          : Enable verbose output.\n");
		fprintf(stderr,"    -h          : Display program synopsis and usage.\n");
	} // end of help if-statement
	
	// this is for bad options; exits with 1
	else if (bad == true) {
		fprintf(stderr, "Usage: ./decrypt [options]\n");
		fprintf(stderr,"  ./decrypt decrypts an input file using the specified private key file,\n");
		fprintf(stderr,"  writing the result to the specified output file.\n");
		fprintf(stderr,"    -i <infile> : Read input from <infile>. Default: standard input.\n");
		fprintf(stderr,"    -o <outfile>: Write output to <outfile>. Default: standard output.\n");
		fprintf(stderr,"    -n <keyfile>: Private key is in <keyfile>. Default: rsa.priv.\n");
		fprintf(stderr,"    -v          : Enable verbose output.\n");
		fprintf(stderr,"    -h          : Display program synopsis and usage.\n");
	exit (1);
	}
	
	else if (help == false && bad == false) {
		if (bool_input == false) {
			input = stdin;
		}
		else {
			input = fopen(input_file, "r");
		}//end if else
		if (bool_output == false) {
			output = stdout;
		} else {
			output = fopen(output_file, "w");
		}//end if else
		
		FILE *private2 = fopen(private, "r");
		
		// if file doesn't open
		if (!private2) {
			fprintf(stderr, "Error opening files.\n");
			exit(1);
		}
		
		mpz_t n;
		mpz_t d;
		
		mpz_init (n);
		mpz_init (d);
		
		rsa_read_priv(n,d,private2);
		
		if (verbose == true) {
			gmp_printf("n - modulus (%zu bits): %Zd\n", mpz_sizeinbase(n,2), n);
			gmp_printf("d - public exponent (%zu bits): %Zd\n", mpz_sizeinbase(d,2), d);
		}
		
		rsa_decrypt_file(input, output, n, d);
		
		fclose(private2);
		
		if (bool_input == true) {
			free(input_file);
			
		}
		fclose(input);
		
		if (bool_output == true) {
			free(output_file);
			
		}
		
		fclose(output);
		
		mpz_clear(n);
		mpz_clear(d);
	}
}
