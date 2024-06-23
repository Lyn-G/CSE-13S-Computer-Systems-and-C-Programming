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
	
	bool bool_input = false;
	bool bool_output = false;
	bool verbose = false;
	bool help = false;
	bool bad = false;
	
	char * input_file = NULL;
	char * output_file = NULL;
	char *public = "rsa.pub";
	
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
				public = (char*) malloc (MAX_FILE * sizeof(char));
				strcpy(public, optarg);
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
	
	if (help == true) { // will only print the help page if -h
		
		fprintf(stderr, "Usage: ./encrypt [options]\n");
fprintf(stderr, "  ./encrypt encrypts an input file using the specified public key file,\n");
fprintf(stderr, "  writing the result to the specified output file.\n");
fprintf(stderr, "    -i <infile> : Read input from <infile>. Default: standard input.\n");
fprintf(stderr, "    -o <outfile>: Write output to <outfile>. Default: standard output.\n");
fprintf(stderr, "    -n <keyfile>: Public key is in <keyfile>. Default: rsa.pub.\n");
fprintf(stderr, "    -v          : Enable verbose output.\n");
fprintf(stderr, "    -h          : Display program synopsis and usage.\n");

	}
	
	// this is for bad options; exits with 1
	else if (bad == true) {
		fprintf(stderr, "Usage: ./encrypt [options]\n");
fprintf(stderr, "  ./encrypt encrypts an input file using the specified public key file,\n");
fprintf(stderr, "  writing the result to the specified output file.\n");
fprintf(stderr, "    -i <infile> : Read input from <infile>. Default: standard input.\n");
fprintf(stderr, "    -o <outfile>: Write output to <outfile>. Default: standard output.\n");
fprintf(stderr, "    -n <keyfile>: Public key is in <keyfile>. Default: rsa.pub.\n");
fprintf(stderr, "    -v          : Enable verbose output.\n");
fprintf(stderr, "    -h          : Display program synopsis and usage.\n");
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
		
		FILE *public2 = fopen(public, "r");
		
		// if file doesn't open
		if (!public2) {
			fprintf(stderr, "Error opening files.\n");
			exit(1);
		}
		
		char * user = (char*) malloc(MAX_FILE * sizeof(char));
		mpz_t s; // signature
		mpz_t n;
		mpz_t e;
		mpz_t verify;

		mpz_init(s);
		mpz_init(n);
		mpz_init(e);
		mpz_init(verify);
		
		rsa_read_pub(n,e,s,user, public2);
		
		user = getenv("USER");

		// print out verbose
		if (verbose == true) {
			printf("username: %s\n", user);
			gmp_printf("user signature (%zu bits): %Zd\n", mpz_sizeinbase(s,2), s);
			gmp_printf("n - modulus (%zu bits): %Zd\n", mpz_sizeinbase(n,2), n);
			gmp_printf("e - public exponent (%zu bits): %Zd\n", mpz_sizeinbase(e,2), e);
		}
		
		mpz_set_str(verify, user, 62);
	
		// verify the signature
		if (rsa_verify(verify, s, e, n) == false) {
			fprintf(stderr, "Signature was not verified.\n");
			exit(1);
		}
		
		rsa_encrypt_file(input, output, n, e);
		
		fclose(public2);
		
		// also close the files specified 
		
		if (bool_input == true) {
			free(input_file);
			
		}
		fclose(input);
		
		if (bool_output == true) {
			free(output_file);
			
		}
		
		fclose(output);
		
		mpz_clear(n);
		mpz_clear(e);
		mpz_clear(s);
	}
}
