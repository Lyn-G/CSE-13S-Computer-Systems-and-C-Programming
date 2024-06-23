#include "rsa.h"
#include "numtheory.h"
#include "randstate.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
	// (random % upper - lower + 1) + lower
	uint64_t p_bits = (random() % ((2 * nbits) / 4));
	p_bits = p_bits + nbits/4 + 1;
	
	uint64_t q_bits = nbits - p_bits;
	
	bool loops = false;
	
	mpz_t subtract_p;
	mpz_t subtract_q;
	mpz_t answer;
	mpz_t gcd_answer;
	
	mpz_init (subtract_p);
	mpz_init (subtract_q);
	mpz_init (answer);
	mpz_init(gcd_answer);
	
	make_prime(p, p_bits, iters);
	make_prime(q, q_bits, iters);
	
	mpz_sub_ui(subtract_p, p, 1); // p - 1
	mpz_sub_ui(subtract_q, q, 1); // q - 1
	mpz_mul(answer, subtract_p, subtract_q);
	
	mpz_mul(n, p, q);
	
	mpz_urandomb(e, state, nbits);
	gcd(gcd_answer, e, answer);
	
	//print e and nbits and make sure that number of  bits in e <= nbits
	while (loops == false) {
		if (mpz_cmp_ui(gcd_answer, 1) !=0 || mpz_sizeinbase(e, 2) < nbits) {
			mpz_urandomb(e, state, nbits);
			gcd(gcd_answer, e, answer); 

		} // end of if-statment
		else {
			loops = true;
		}
	}
	mpz_clear(subtract_p);
	mpz_clear(subtract_q);
	mpz_clear(answer);
	mpz_clear(gcd_answer);
} 

// The format of a public key should be n, e, s, then the username, each of which are written with a trailing newline.
// The values n, e, and s should be written as hexstrings.
void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
	gmp_fprintf(pbfile, "%Zx\n", n);
	gmp_fprintf(pbfile, "%Zx\n", e);
	gmp_fprintf(pbfile, "%Zx\n", s);
	gmp_fprintf(pbfile, "%s\n", username);
}

// The format of a public should be n, e, s, then the username, each of which should have been written with a trailing newline.
// The values n, e, and s should have been written as hexstrings.
void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
	gmp_fscanf(pbfile, "%Zx\n", n);
	gmp_fscanf(pbfile, "%Zx\n", e);
	gmp_fscanf(pbfile, "%Zx\n", s);
	gmp_fscanf(pbfile, "%s\n", username);
}

// Creates a new RSA private key d given primes p and q and public exponent e. 
// To compute d, simply compute the inverse of e modulo λ(n) = lcm(p−1,q−1).
// inverse of e modulo = mod_inverse
void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
	
	mpz_t subtract_p;
	mpz_t subtract_q;
	mpz_t answer;
	
	mpz_init (subtract_p);
	mpz_init (subtract_q);
	mpz_init (answer);
	
	mpz_sub_ui(subtract_p, p, 1);
	mpz_sub_ui(subtract_q, q, 1);
	
	mpz_mul(answer, subtract_p, subtract_q);
	
	mod_inverse(d, e, answer);
	
	mpz_clear (subtract_p);
	mpz_clear (subtract_q);
	mpz_clear (answer);
}

// Writes a private RSA key to pvfile.
// The format of a private key should be n then d, both of which are written with a trailing newline.
void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
	gmp_fprintf(pvfile, "%Zx\n", n);
	gmp_fprintf(pvfile, "%Zx\n", d);
}

// Reads a private RSA key from pvfile. 
// The format of a private key should be n then d, both of which should have been written with a trailing newline. 
void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
	gmp_fscanf(pvfile, "%Zx\n", n);
	gmp_fscanf(pvfile, "%Zx\n", d);
}

// computing ciphertext c by encrypting message m using public exponent e and modulus n
// E(m) = c= me (mod n).
void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
	pow_mod(c, m, e, n);
}

// value of block cannot be 0 or 1
void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
	uint64_t block_size = 0;
	uint64_t j = 1; // bytes read
	
	mpz_t message;
	mpz_t cypher;

	mpz_init(message);
	mpz_init(cypher);

	block_size = mpz_sizeinbase(n,2) - 1;
	block_size = block_size / 8 ;

	// dynamically allocate an array that can hold k bytes
	uint8_t *block = (uint8_t*) malloc(block_size * sizeof(uint8_t));
	for (uint64_t i = 1; i < block_size - 1; i ++) {
			block[i] = 0;
		}
	
	block[0] = 0xFF; // set zeroth byte of the block to 0xFF
		
	// read at most k-1 bytes in from infile
	while (!feof(infile)) {		
		j = fread(block+1, 1, block_size -1, infile);

		
		// convert the read bytes into an mpz_t m
		mpz_import(message, j+1, 1,1,1,0, block);
		
		// Encrypt m with rsa_encrypt(), then write the encrypted number to outfile as a hexstring followed by a trailing newline.
		rsa_encrypt(cypher,message,e,n);
		gmp_fprintf(outfile, "%Zx\n", cypher);
	} // end of while-loop

	free(block);
	
	mpz_clear(cypher);
	mpz_clear(message);
}

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
	pow_mod(m, c, d, n);
}

void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
	// use code from encrypting
	uint64_t block_size = 0;
	
	mpz_t message; // the outputting message
	mpz_t cypher;
	
	mpz_init(message);
	mpz_init(cypher);
	
	block_size = mpz_sizeinbase(n,2) - 1;
	block_size = block_size / 8;
	
	uint8_t *block = (uint8_t*) malloc(block_size * sizeof(uint8_t));
	uint64_t *i = &block_size;
	
	for (uint64_t i = 1; i < block_size - 1; i ++) {
			block[i] = 0;
		}
		
	// scan in a hexstring
	while (!feof(infile)) {
		*i = gmp_fscanf(infile, "%Zx\n", message, d, n);
		rsa_decrypt(cypher, message, d, n);
		mpz_export(block, i, 1,1,1,0, cypher);
		fwrite(block + 1, *i -1,1, outfile);
		
	}
	// the first byte will be 0xFF that was prepended
	// don't write it out
	
	free(block);
	
	mpz_clear(cypher);
	mpz_clear(message);
}

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
	pow_mod(s, m, d, n);
}

bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
	mpz_t output;
	mpz_init (output);
	
	bool verify = false;	
	
	pow_mod(output, s, e, n);
	
	if (mpz_cmp(output, m) == 0) {
		verify = true;
	}
	mpz_clear (output);
	
	return verify;
}
