#include "bv.h"
#include "bf.h"
#include "city.h"
#include "node.h"
#include "ll.h"
#include "messages.h"
#include "ht.h"
#include "parser.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h> 
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#define OPTIONS "hmt:f:s"

int main (int argc, char **argv) {
	
	int r;
	bool help = false; // for help statement 
	bool bad = false; // for invalid option
	
	uint64_t hash_size = 10000;
	uint64_t bloom_size = pow(2,19);
	
	bool stats = false;
	bool mtf = false;
	
	while ((r = getopt (argc, argv, OPTIONS)) != -1) {
		switch (r) {
			case 'h':
				help = true;
				break;
			case 't':
				hash_size = atoi(optarg);
				break;
			case 'f':
				bloom_size = atoi(optarg);
				break;
			case 's':
				stats = true;
				break;
			case 'm':
				mtf = true;
				break;
			default:
				bad = true;
				break;
		} // end of cases
	} // end of while-loop
	
	// print out the help message
	if (help) {
		fprintf(stderr, "Usage: ./banhammer-dist [options]\n");
		fprintf(stderr, "  ./banhammer-dist will read in words from stdin, identify any badspeak or old speak and output an\n");
		fprintf(stderr, "  appropriate punishment message. The badspeak and oldspeak (with the newspeak translation)\n");
		fprintf(stderr, "  that caused the punishment will be printed after the message. If statistics are enabled\n");
		fprintf(stderr, "  punishment messages are suppressed and only statistics will be printed.\n");
		fprintf(stderr, "    -t <ht_size>: Hash table size set to <ht_size>. (default: 10000)\n");
		fprintf(stderr, "    -f <bf_size>: Bloom filter size set to <bf_size>. (default 2^19)\n");
		fprintf(stderr, "    -s          : Enables the printing of statistics.\n");
		fprintf(stderr, "    -m          : Enables move-to-front rule.\n");
		fprintf(stderr, "    -h          : Display program synopsis and usage.\n");

	// exit with 0 because this is just the help message
		exit(0);
	} else if (bad) {
		fprintf(stderr, "Usage: ./banhammer-dist [options]\n");
		fprintf(stderr, "  ./banhammer-dist will read in words from stdin, identify any badspeak or old speak and output an\n");
		fprintf(stderr, "  appropriate punishment message. The badspeak and oldspeak (with the newspeak translation)\n");
		fprintf(stderr, "  that caused the punishment will be printed after the message. If statistics are enabled\n");
		fprintf(stderr, "  punishment messages are suppressed and only statistics will be printed.\n");
		fprintf(stderr, "    -t <ht_size>: Hash table size set to <ht_size>. (default: 10000)\n");
		fprintf(stderr, "    -f <bf_size>: Bloom filter size set to <bf_size>. (default 2^19)\n");
		fprintf(stderr, "    -s          : Enables the printing of statistics.\n");
		fprintf(stderr, "    -m          : Enables move-to-front rule.\n");
		fprintf(stderr, "    -h          : Display program synopsis and usage.\n");
		
		// exit with 1 because this is a bad option
		exit(1);
	} else if (bad == false && help == false) {
		// initialized Bloom filter and hash table
		HashTable *ht = ht_create(hash_size, mtf);
		BloomFilter *bf = bf_create(bloom_size);
		
		// read in a list of badspeak with fgets()
		// each badspeak word should be added to the Bloom filter and the hash table
		
		Parser *bad_p;
		FILE *badspeak = fopen("badspeak.txt", "r");
		char bad_word[MAX_PARSER_LINE_LENGTH];
	
		bad_p = parser_create( badspeak);
	
		while (next_word(bad_p, bad_word)) {
			bf_insert(bf, bad_word);
			ht_insert(ht, bad_word, NULL); // set newspeak to NULL since we haven't received it yet
			
	
		} 
		fclose(badspeak);
		parser_delete(&bad_p);
		
		
		// read in a list of oldspeak and newspeak with fgets()
		// only oldspeak should be added to the Bloom filter
		// oldspeak and newspeak are added to the hash table
		
		Parser *new_p;
		FILE *newspeak = fopen("newspeak.txt", "r");
		char new_word[MAX_PARSER_LINE_LENGTH];
		char temp[MAX_PARSER_LINE_LENGTH];
	
		new_p = parser_create( newspeak);

		// oldspeak only to Bloom filter
		// old speak and new speak are added to the hash table
		while (next_word(new_p, new_word)) {
			
			bf_insert(bf, new_word);
			next_word(new_p, temp);
			ht_insert(ht, new_word, temp);
			
		}
		
		fclose(newspeak);
		
		// we can start filtering out word using stdin using our parsing module
		Parser *p;
		p = parser_create(stdin);
		
		LinkedList *badspeak_list;
		badspeak_list = ll_create(mtf);
		
		LinkedList *newspeak_list;
		newspeak_list = ll_create(mtf);
		
		char word[MAX_PARSER_LINE_LENGTH];
		
		while (next_word(p, word)) {
			if (bf_probe(bf, word)) {
				char *new = ht_lookup(ht, word)->newspeak;
					if (new == NULL) {
						ll_insert(badspeak_list, word, NULL);
					} else {
						ll_insert(newspeak_list, word, new);
					}
				
			} // end of if-statement
		}
	
		// delete parsing module
		if (p) {
			parser_delete(&p);
		}
		
		// calculate stats
		// enabling the priting of stats should suppress all messagges the program may otherwise print
		if (stats == true) {
			double bits_examined_per_miss = 0.0;
			double false_pos = 0.0;
			double bf_load = 0.0;
			double avg_len = 0.0;
			
			uint32_t bnk; 
			uint32_t bnh; 
			uint32_t bnm ; 
			uint32_t bne ;
			
			uint32_t hnk ; 
			uint32_t hnh ; 
			uint32_t hnm ; 
			uint32_t hne ; 
			
			bf_stats(bf, &bnk, &bnh, &bnm, &bne);
			ht_stats(ht, &hnk, &hnh, &hnm, &hne);
			
			printf("ht keys: %u\n",hnk);
			printf("ht hits: %u\n",hnh);
			printf("ht misses: %u\n",hnm);
			printf("ht probes: %u\n",hne);
			
			printf("bf keys: %u\n",bnk);
			printf("bf hits: %u\n",bnh);
			printf("bf misses: %u\n",bnm);
			printf("bf bits examined: %u\n",bne);
			
			// since dividing by 0 will give us a major error, let's avoid that
			if (bnm != 0) {
				bits_examined_per_miss = (bne - (5 * bnh))/ (double)bnm;
			}
			if (bnh != 0) {
				false_pos = (hnh / bnh);
			}
			if (bf_size(bf) != 0) {
				bf_load = bf_count(bf)/(double) bf_size(bf);
			}
			if (hnh != 0 || hnm != 0) {
			 	avg_len = hnh + hnm;
			 	avg_len = hne/avg_len;
			}
			
			printf("Bits examined per miss: %f\n",bits_examined_per_miss);
			printf("False positives: %f\n",false_pos);
			printf("Average seek length: %f\n",bf_load);
			printf("Bloom filter load: %f\n",avg_len);
		// end of stats if-statement	
		} else { 
			if (badspeak_list != NULL && newspeak_list != NULL) {
				printf("%s", mixspeak_message);
				ll_print(badspeak_list);
				ll_print(newspeak_list);
			} else if (badspeak_list != NULL && newspeak_list == NULL) {
				printf("%s", badspeak_message);
				ll_print(badspeak_list);
			} else if (badspeak_list == NULL && newspeak_list != NULL) {
				printf("%s", goodspeak_message);
				ll_print(newspeak_list);
			}
		} // end of else-statement
		
		//printf("bllo filter size%u\n", bf_size(bf));
		// free memory
		if (ht) {
			ht_delete(&ht);
		}
		//puts("ss");
		if (bf) {
			bf_delete(&bf);
		}
		return 0;
		//puts("sss");
		if (badspeak_list) {
			ll_delete(&badspeak_list);		
		}
		//puts("ssssssssssssssnjdnfjndjfn");
		if ( newspeak_list) {
			ll_delete(&newspeak_list);
		}
		//puts("ssssss");
	} // end of else-if-statement from way above
	
	return 0;
}
