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

#define OPTIONS "b:i:n:d:s:vh"
#define MAX_FILE 100 

int main (int argc, char **argv) {

	int r;
	
	bool help = false;
	bool bad = false;
	bool bad_bits = false; // wrong option for bits
	bool bad_iter = false; // wrong option for iterations
	bool verbose = false;
	uint64_t bits = 1024;
	uint64_t iterations = 50;
	uint64_t seed = time(NULL);
	
	char *public = "rsa.pub";
	char *private = "rsa.priv";
	
while ((r = getopt (argc, argv, OPTIONS)) != -1) {
		switch (r) {
			case 'b': 
				bits = atoi(optarg);
				if (bits < 50 || bits > 4096) { // check for bad options
					bad_bits = true;
				}
				break;
			case 'i':
				iterations = atoi(optarg);
				if (iterations < 1 || iterations > 500) { // check for bad options
					bad_iter = true;
				}
				break;	
			case 'v':
				verbose = true;
				break;
			case 's':
				seed = atoi(optarg);
				break;
			case 'n':
				public = (char*) malloc (MAX_FILE * sizeof(char));
				strcpy(public, optarg);
				break;
			case 'd':
				private = (char*) malloc (MAX_FILE * sizeof(char));
				strcpy(private, optarg);
				break;
			case 'h':
				help = true;
				break;
			default:
				bad = true;
				break;
		} // end of cases
	} // end of while-loop

	// this is for help; exits with 0
	if (bad_iter == true) {
		fprintf(stderr, "./keygen: Number of iterations must be 1-500, not %lu.\n", iterations);
		fprintf(stderr, "Usage: ./keygen [options]\n");
		fprintf(stderr,"  ./keygen generates a public / private key pair, placing the keys into the public and private\n");
		fprintf(stderr,"  key files as specified below. The keys have a modulus (n) whose length is specified in\n");
		fprintf(stderr,"  the program options.\n");
		fprintf(stderr,"    -s <seed>   : Use <seed> as the random number seed. Default: time()\n");
		fprintf(stderr,"    -b <bits>   : Public modulus n must have at least <bits> bits. Default: 1024\n");
		fprintf(stderr,"    -i <iters>  : Run <iters> Miller-Rabin iterations for primality testing. Default: 50\n");
		fprintf(stderr,"    -n <pbfile> : Public key file is <pbfile>. Default: rsa.pub\n");
		fprintf(stderr,"    -d <pvfile> : Private key file is <pvfile>. Default: rsa.priv\n");
		fprintf(stderr,"    -v          : Enable verbose output.\n");
		fprintf(stderr,"    -h          : Display program synopsis and usage.\n");
	exit (1);
	}
	
	else if (bad_bits == true) {
		fprintf(stderr, "./keygen: Number of bits must be 50-4096, not %lu.\n", bits);
		fprintf(stderr, "Usage: ./keygen [options]\n");
		fprintf(stderr,"  ./keygen generates a public / private key pair, placing the keys into the public and private\n");
		fprintf(stderr,"  key files as specified below. The keys have a modulus (n) whose length is specified in\n");
		fprintf(stderr,"  the program options.\n");
		fprintf(stderr,"    -s <seed>   : Use <seed> as the random number seed. Default: time()\n");
		fprintf(stderr,"    -b <bits>   : Public modulus n must have at least <bits> bits. Default: 1024\n");
		fprintf(stderr,"    -i <iters>  : Run <iters> Miller-Rabin iterations for primality testing. Default: 50\n");
		fprintf(stderr,"    -n <pbfile> : Public key file is <pbfile>. Default: rsa.pub\n");
		fprintf(stderr,"    -d <pvfile> : Private key file is <pvfile>. Default: rsa.priv\n");
		fprintf(stderr,"    -v          : Enable verbose output.\n");
		fprintf(stderr,"    -h          : Display program synopsis and usage.\n");
	exit (1);
	}
	else if (help == true) {
		fprintf(stderr, "Usage: ./keygen [options]\n");
		fprintf(stderr,"  ./keygen generates a public / private key pair, placing the keys into the public and private\n");
		fprintf(stderr,"  key files as specified below. The keys have a modulus (n) whose length is specified in\n");
		fprintf(stderr,"  the program options.\n");
		fprintf(stderr,"    -s <seed>   : Use <seed> as the random number seed. Default: time()\n");
		fprintf(stderr,"    -b <bits>   : Public modulus n must have at least <bits> bits. Default: 1024\n");
		fprintf(stderr,"    -i <iters>  : Run <iters> Miller-Rabin iterations for primality testing. Default: 50\n");
		fprintf(stderr,"    -n <pbfile> : Public key file is <pbfile>. Default: rsa.pub\n");
		fprintf(stderr,"    -d <pvfile> : Private key file is <pvfile>. Default: rsa.priv\n");
		fprintf(stderr,"    -v          : Enable verbose output.\n");
		fprintf(stderr,"    -h          : Display program synopsis and usage.\n");

	} // end of if-statement
	
	// this is for bad options; exits with 1
	else if (bad == true) {
		fprintf(stderr, "Usage: ./keygen [options]\n");
		fprintf(stderr,"  ./keygen generates a public / private key pair, placing the keys into the public and private\n");
		fprintf(stderr,"  key files as specified below. The keys have a modulus (n) whose length is specified in\n");
		fprintf(stderr,"  the program options.\n");
		fprintf(stderr,"    -s <seed>   : Use <seed> as the random number seed. Default: time()\n");
		fprintf(stderr,"    -b <bits>   : Public modulus n must have at least <bits> bits. Default: 1024\n");
		fprintf(stderr,"    -i <iters>  : Run <iters> Miller-Rabin iterations for primality testing. Default: 50\n");
		fprintf(stderr,"    -n <pbfile> : Public key file is <pbfile>. Default: rsa.pub\n");
		fprintf(stderr,"    -d <pvfile> : Private key file is <pvfile>. Default: rsa.priv\n");
		fprintf(stderr,"    -v          : Enable verbose output.\n");
		fprintf(stderr,"    -h          : Display program synopsis and usage.\n");
	exit (1);
	}
	
	else if (help == false && bad == false) {
	
		char * user = (char*) malloc (MAX_FILE * sizeof(char));
		mpz_t signature;
		mpz_t p; // first prime
		mpz_t q; // second prime
		mpz_t n; // public modulus
		mpz_t e; // public exponent
		mpz_t d; // private
		
		mpz_init(signature);
		mpz_init(p);
		mpz_init(q);
		mpz_init(n);
		mpz_init(e);
		mpz_init(d);
		
		
		FILE *public2 = fopen(public, "w");
		FILE *private2 = fopen(private, "w");
		
		if (!public2 || !private2) {
			fprintf(stderr, "Error opening files.\n");
			exit(1);
		}
		
		// set private file permissions
		fchmod(fileno(private2), S_IRUSR | S_IWUSR);
		
		randstate_init(seed);
		
		// make public and private keys
		rsa_make_pub(p,q,n,e,bits,iterations);
		rsa_make_priv(d,e,p,q);
		
		// get username
		user = getenv("USER");
		
		mpz_set_str(signature, user, 62);
		rsa_sign(signature, signature, d, n);
		
		rsa_write_pub(n,e,signature,user,public2);
		rsa_write_priv(n,d,private2);
		
		// print out verbose
		if (verbose == true) {
			printf("username: %s\n", user);
			gmp_printf("user signature (%zu bits): %Zd\n", mpz_sizeinbase(signature,2), signature);
			gmp_printf("p (%zu bits): %Zd\n", mpz_sizeinbase(p,2), p);
			gmp_printf("q (%zu bits): %Zd\n", mpz_sizeinbase(q,2), q);
			gmp_printf("n - modulus (%zu bits): %Zd\n", mpz_sizeinbase(n,2), n);
			gmp_printf("e - public exponent (%zu bits): %Zd\n", mpz_sizeinbase(e,2), e);
			gmp_printf("d - private exponent (%zu bits): %Zd\n", mpz_sizeinbase(d,2), d);
		}
		
		fclose(public2);
		fclose(private2);
		
		randstate_clear();
		
		mpz_clear(p);
		mpz_clear(q);
		mpz_clear(n);
		mpz_clear(e);
		mpz_clear(d);
	}
}
