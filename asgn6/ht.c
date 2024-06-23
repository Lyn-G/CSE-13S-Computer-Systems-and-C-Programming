#include "node.h"
#include "ll.h"
#include "city.h"
#include "ht.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

struct HashTable {
uint64_t salt;
uint32_t size;
uint32_t n_keys;
uint32_t n_hits;
uint32_t n_misses;
uint32_t n_examined;
bool mtf;
LinkedList ** lists;
};

// code given to us in the assignment document
HashTable *ht_create(uint32_t size , bool mtf) {
	HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
	if (ht != NULL) {
		ht->mtf = mtf;
		ht->salt = 0x9846e4f157fe8840;
		ht->n_hits = ht->n_misses = ht->n_examined = 0;
		ht->n_keys = 0;
		ht->size = size;
		ht->lists = (LinkedList **) calloc(size , sizeof(LinkedList *));
		if (!ht->lists) {
			free(ht);
			ht = NULL;
		}
	}
	return ht;
}

// each of the linked lists in lists and the underlying array of linked lists is freed
void ht_delete(HashTable **ht) {
	if (*ht && (*ht)->lists) {
		for (uint32_t i = 0; i < (*ht)->size; i++) {
			if ((*ht)->lists[i]) {
				ll_delete(&(*ht)->lists[i]);
				(*ht)->lists[i] = NULL;
			} // end of if-statement
		} // end of for-loop
		
		free((*ht)->lists);
		free(*ht);
		(*ht) = NULL;
		
	} else {
		free(*ht);
		*ht = NULL;
	}
}

uint32_t ht_size(HashTable *ht) {
	return ht->size;
}

// searches for an entry, a node, in the hash table that contains oldspeak
// the node stores the oldspeak and its newspeak
Node *ht_lookup(HashTable *ht, char *oldspeak) {
	// call ll_stats and remember the number of links returned 
	uint32_t seeks, links, new_links;
	ll_stats(&seeks, &links);
	
	Node *n = NULL;
	uint32_t index = 0;	
	
	// the index of the linked list to perform a look-up is calculated by hashing the oldspeak
	index = hash(ht->salt, oldspeak) % ht->size;
	
	// if the node is found, the pointer to the node is returned 
	if (ht->lists[index]!= NULL){
		n = ll_lookup(ht->lists[index], oldspeak);
	}
	ll_stats(&seeks, &new_links);
	//printf("newlinks = %d links = %d", new_links, links);
	ht->n_examined += (new_links - links);
	
	if (n) {
		ht->n_hits++;
	} else {
		ht->n_misses++;
	}
	// before returning, call ll_stats again
	// get the updated number of links returned
	// the number of links accessed during the lookup is the difference between the updated number of link and the orignal number of links
	// add this to the hash table's count of n_examined
	return n;
}

// insert the specified oldspeak and newspeak into the hash table
// if the linked list that should be inserted into hasn't been intialized yet, create it first before inserting the oldspeak and the newspeak
void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
	uint32_t index = 0;
	
	if (ht->lists) {
		// the index of the linked list to insert into is calculated by hashing the old speak
		index = hash(ht->salt, oldspeak) % ht->size;
		
		// puts("d");
		ht->n_keys++;
		
		if (!(ht->lists[index])) {
			ht->lists[index] = ll_create(ht->mtf); 
			ll_insert(ht->lists[index] , oldspeak, newspeak);
		} else {
			ll_insert(ht->lists[index] , oldspeak, newspeak);
		}
	}
}


uint32_t ht_count(HashTable *ht) {
	uint32_t counter = 0;
	
	// check if the linked lists aren't NULL
	if (ht && ht->lists) {
		for (uint32_t i = 0; i < ht->size; i++) {
			if (ht->lists[i]) {
				counter ++;
			}
		}
	}
	return counter;
}

void ht_print(HashTable *ht) {
	for (uint32_t i = 0; i < ht->size; i++) {
		if (ht->lists[i]) {
			ll_print(ht->lists[i]);
		}
	}
}


void ht_stats(HashTable *ht, uint32_t *nk, uint32_t *nh, uint32_t *nm, uint32_t *ne) {
	*nk = ht->n_keys;
	*nh = ht->n_hits;
	*nm = ht->n_misses;
	*ne = ht->n_examined;
}

/*int main () {
	
	HashTable *v;
	
	v = ht_create(10 , true);
	
	ht_insert(v, "hey", "bad");
	ht_print(v);
	puts("");
	
	ht_insert(v, "stink", "ye");
	ht_print(v);
	puts("");

	ht_insert(v, "singgg", "say1");
	ht_print(v);
	puts("");
	
	ht_insert(v, "singgg", "say");
	puts("");
	ht_print(v);

	puts("");

	ht_insert(v, "dd", "ddd");
	ht_print(v);
	
	printf("%d\n", ht_size(v));
	printf("%d\n", ht_count(v));

	ht_delete(&v);
	
	
	return 0;
}*/
