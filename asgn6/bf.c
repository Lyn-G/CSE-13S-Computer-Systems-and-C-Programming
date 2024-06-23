#include "bv.h"
#include "bf.h"
#include "city.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h> 
#include <stdio.h>

#define N_HASHES 5

struct BloomFilter {
uint64_t salts[N_HASHES]; // Salts for five hash functions
uint32_t n_keys;
uint32_t n_hits;
uint32_t n_misses;
uint32_t n_bits_examined;
BitVector *filter;
};

static uint64_t default_salts [] = {
	0x5adf08ae86d36f21 ,
	0x419d292ea2ffd49e ,
	0x50d8bb08de3818df ,
	0x272347aea4045dd5 ,
	0x7c8e16f768811a21
};

BloomFilter *bf_create(uint32_t size) {

	BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
	if (bf) {
		bf->n_keys = bf ->n_hits = 0;
		bf->n_misses = bf->n_bits_examined = 0;
		for (int i = 0; i < N_HASHES; i++) {
			bf->salts[i] = default_salts[i];
		}
		bf->filter = bv_create(size);
		if (bf->filter == NULL) {
			free(bf);
			bf = NULL;
		}
	}
	return bf;
}

void bf_delete(BloomFilter **bf) {
	if (*bf && (*bf)->filter) {
		free ((*bf)->filter);
		free (*bf);
		*bf = NULL;
	} else if (*bf) {
		// if there is only Bloom filter
		free (*bf);
		*bf = NULL;
	}
}

// this is the length of the underlying bit vector 
uint32_t bf_size(BloomFilter *bf) {
	return bv_length(bf->filter);
}

// take oldspeak and insert it into the Bloom filter
void bf_insert(BloomFilter *bf, char *oldspeak) {
	// hash oldspeak with each of the five salts for five indices 	
	uint64_t hash1 = 0;
	uint64_t hash2 = 0;
	uint64_t hash3 = 0;
	uint64_t hash4 = 0;
	uint64_t hash5 = 0;
	
	// uint64_t hash(uint64_t salt, char *key)
	if (bf && bf-> filter) {
		hash1  = hash(bf->salts[0], oldspeak);
		hash2  = hash(bf->salts[1], oldspeak);
		hash3  = hash(bf->salts[2], oldspeak);
		hash4  = hash(bf->salts[3], oldspeak);
		hash5  = hash(bf->salts[4], oldspeak);
	}
	// set bits at those indices in the undeerlying bit vector
	bv_set_bit(bf->filter, hash1 % bf_size(bf));
	bv_set_bit(bf->filter, hash2 % bf_size(bf));
	bv_set_bit(bf->filter, hash3 % bf_size(bf));
	bv_set_bit(bf->filter, hash4 % bf_size(bf));
	bv_set_bit(bf->filter, hash5 % bf_size(bf));
	
	bf->n_keys += 1;
}

// probes the Bloom filter for oldspeak
// similar to bf_insert()
// oldspeak is hashed with each of the five slalts for the five indices

bool bf_probe(BloomFilter *bf, char *oldspeak) {
	uint64_t hash1 = 0;
	uint64_t hash2 = 0;
	uint64_t hash3 = 0;
	uint64_t hash4 = 0;
	uint64_t hash5 = 0;
	
	if (bf && bf->filter) {
	bf->n_bits_examined += 1;
		hash1  = hash(bf->salts[0], oldspeak) % bf_size(bf);
		hash2  = hash(bf->salts[1], oldspeak)% bf_size(bf);
		hash3  = hash(bf->salts[2], oldspeak)% bf_size(bf);
		hash4  = hash(bf->salts[3], oldspeak)% bf_size(bf);
		hash5  = hash(bf->salts[4], oldspeak)% bf_size(bf);
		
		if ((bv_get_bit(bf->filter, hash1) && 
		        bv_get_bit(bf->filter, hash2) && 
		        bv_get_bit(bf->filter, hash3) && 
		        bv_get_bit(bf->filter, hash4) && 
		        bv_get_bit(bf->filter, hash5)) == false) {
		        	bf->n_misses++;
		        }
		// if all indices are set, return true
		return (bv_get_bit(bf->filter, hash1) && 
		        bv_get_bit(bf->filter, hash2) && 
		        bv_get_bit(bf->filter, hash3) && 
		        bv_get_bit(bf->filter, hash4) && 
		        bv_get_bit(bf->filter, hash5));
	}
	
	bf->n_hits ++;
	return false;
}

// returns the number of set bits
// use a for-loop and an if-statement 
uint32_t bf_count(BloomFilter *bf) {
	uint32_t count = 0;
	
	if (bf && bf->filter) {
		for (uint32_t i = 0; i < bf_size(bf); i++) {
			count++;
		}
	}
	return count;
}

void bf_print(BloomFilter *bf) {
	bv_print(bf->filter);
}

/* It sets each passed pointers to the value of the original variable for the relevant statistic that the Bloom filter is
tracking: *nk to the number of keys, *nh to the number of hits, *nm to the number of misses, and *ne to the
number of bits examined.*/
void bf_stats(BloomFilter *bf, uint32_t *nk, uint32_t *nh, uint32_t *nm, uint32_t *ne) {
	*nk = bf->n_keys;
	*nh = bf->n_hits;
	*nm = bf->n_misses;
	*ne = bf->n_bits_examined;
}

/*int main (){
	BloomFilter *v;
	
	v = bf_create(10);
	bf_print(v);
	printf("\n");
	bf_insert(v, "hey");
	bf_insert(v, "singgg");
	bf_insert(v, "stink");
	bf_insert(v, "yo");
	//bf_print(v);
	
	bool p1 = bf_probe(v, "hey");
	bool p2 = bf_probe(v, "singgg");
	bool p3 = bf_probe(v, "stink");
	bool p4 = bf_probe(v, "yooo");
	
	printf("\n%d", p1);
	printf("\n%d", p2);
	printf("\n%d", p3);
	printf("\n%d", p4);
	
	printf("\n%d", bf_size(v));
	printf("\n%d", bf_count(v));
	
	bf_delete(&v);
	
	return 0;
}*/
