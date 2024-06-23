#include "bv.h"
#include "bf.h"
#include "city.h"
#include "node.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h> 
#include <stdio.h>
#include <ctype.h>

// need to implement something that works like strlen()
// create a for-loop that goes through the string
// uses a counter variable to count the amount of times

int own_strlen (char * string) {
	int counter = 0;
	
	for (int i = 0; string[i]; i ++) {
		counter ++;
	}	
	return counter;
}

// make a copy of oldspeak and its newspeak translation that is passed in
// allocate memory and copy the character for oldspeak and newspeak
char * own_strdup (char * old) {
	
	// allocate memory just like strlen and strdup does
	int old_size = own_strlen(old);
	char * new = (char*) malloc (sizeof(char)*old_size+1);
	
	if (new) {
		char* new1 = new;
		while (*old) {
			*new1 = *old;
			old ++;
			new1++;
		}
		
		// terminating string
		*new1 = '\0';
	
	}
	return (new);
}

// if the newspeak filed is NULL, then the oldspeak contained in this ode is badspeak
Node *node_create(char *oldspeak, char *newspeak) {

	Node *n = (Node *) malloc(sizeof(Node));
	
	if (n) {
		n->next = NULL;
		n->prev = NULL;
		
		if (oldspeak != NULL) {
			
			// get length of oldspeak
			int old_length = own_strlen(oldspeak);
			n->oldspeak = (char*) malloc((old_length) * sizeof(char));
			n->oldspeak = own_strdup(oldspeak);
			
			
			if (newspeak != NULL) {
			int new_length = own_strlen(newspeak);
			n->newspeak = (char*) malloc((new_length) * sizeof(char));
			n->newspeak = own_strdup(newspeak);
			} else {
				n->newspeak = NULL;
			}
		}
		
		
	} // end of first if-statement
	return n;
}

void node_delete(Node **n) {
	if (*n) {
		if ((*n)->oldspeak) {
		//printf("%s oldspeak\n", ((*n)->oldspeak));
			free((*n)->oldspeak);
			(*n)->oldspeak = NULL;
		}
		
		if ((*n)->newspeak) {
		//printf("%s newspeak\n", ((*n)->newspeak));
			free((*n)->newspeak);
			(*n)->newspeak = NULL;
		}
		
		free (*n);
		*n = NULL;
	}
}

void node_print(Node *n) {
	if (n) {
		
		// the node n contains oldspeak and newspeak 
		if (n->newspeak && n->oldspeak) {
			printf("%s -> %s\n", n->oldspeak , n->newspeak);
		}
		// If the node n contains only oldspeak, meaning that newspeak == NULL
		else if (n->oldspeak && n->newspeak == NULL) {
			printf("%s\n", n->oldspeak);
	
		}
	}
}


