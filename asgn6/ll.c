#include "bv.h"
#include "bf.h"
#include "city.h"
#include "node.h"
#include "ll.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h> 
#include <stdio.h>

uint64_t seeks; // Number of seeks performed.
uint64_t links; // Number of links traversed.

struct LinkedList {
uint32_t length;
Node *head; // Head sentinel node.
Node *tail; // Tail sentinel node.
bool mtf;
};

// my own string length function
int own_strlen1 (char *string) {

	int counter = 0;
		// since terminating value in string is \0
		while (string[counter] != '\0') {
			counter++;
			
	}
	return counter;
}

// my own string compare function
bool own_strcom (char * string1, char * string2) {
	//bool compare = false;
	// we know that the strings cannot be the same if they are not the same length

	if (string1 == NULL || string2 == NULL) {
		return false;
	}
	if(own_strlen1(string1) != own_strlen1(string2)) {
		return false;
	}
	int i = 0;
	while(string1[i] && string2[i]) {
		if(string1[i] != string2[i]){
			return false;
		}
		i++;
	}
	return true;
	
}

// constructor for linked list
LinkedList *ll_create(bool mtf) {
	LinkedList *ll = (LinkedList *) malloc(sizeof(LinkedList));
	if (ll) {
		ll->mtf = mtf;
		ll->head = node_create(NULL, NULL);
		ll->tail = node_create(NULL, NULL);
		ll->head->next = ll->tail;
		ll->tail->prev = ll->head;
		ll->length = 0;
	} // end of first if-statement
	return ll;
}

// each node in the linked list should be freed with node_delete()
// pointer must be set to NULL
void ll_delete(LinkedList **ll) {

	if (*ll) {
		Node *next = (*ll)->head;
		Node*next_pointer;
			while (next) {
				
				next_pointer = next->next;
				node_delete(&next);
				next = next_pointer;
		
			}
		free (*ll);
		*ll = NULL;
	}
}

uint32_t ll_length(LinkedList *ll) {
	return ll->length;
}

// searches for a node containing oldspeak

/*If a node was found and the move-to-front option was specified when constructing the linked
list, then the found node is moved to the front of the linked list. The move-to-front technique decreases look-up
times for nodes that are frequently searched for. */
Node *ll_lookup(LinkedList *ll, char *oldspeak) {
	Node *node_next = ll->head;
	
	if (ll) {
		// if the length is 0
		if (ll_length(ll) == 0) {
			node_next = NULL;
			return node_next;
		
		// if the length is 1
		} else if (ll_length (ll) == 1) {
			node_next = node_next->next;
			if (own_strcom(node_next->oldspeak, oldspeak)==false) {
				node_next = NULL;
				return node_next;
			} else if (own_strcom(node_next->oldspeak, oldspeak)==true) {
				return node_next;
			} // end of nested else-if-statement
			
		// if the length isn't 1 or 0
		} else {
			node_next = node_next->next;
			while (node_next != NULL) {
				if (own_strcom(node_next->oldspeak, oldspeak)==true) {
					
					// check if mtf is true
						if (ll->mtf == true) {
							return node_next;
						} else if (ll->mtf == false) {
							return node_next;
						}
				// end of if-statement
				} 
					node_next = node_next->next;	
			} // end of while-loop
			node_next = NULL;
			return node_next;
			
		} 
		
	}
	node_next = NULL;
	return node_next;
}
void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
	if (ll) {
		
		if (own_strcom(oldspeak, "\0") || oldspeak == NULL) {
			return;
		} // end of first if-statement
		 //printf("inside ll : oldspeak %s\n", oldspeak);
		// check with lookup to see if the oldspeak is  the same
		Node *new = ll_lookup(ll,oldspeak);
		
		if (new == NULL) { // NULL means no node was found
			Node *new_node = node_create(oldspeak, newspeak);
			if (ll_length(ll) == 0) {
				new_node->next = ll->tail;
				new_node->prev = ll->head;
				ll->head->next = new_node;
				ll->tail->prev = new_node;
				ll->length++;
			} else {
					
					new_node->next = ll->head->next; // head->next holding the old new node
					new_node->prev = ll->head;
					ll->head->next = new_node;
					new_node->next->prev = new_node;
					ll->length++;
				}
			// if not NULL, that means it already exists
		} else if (ll->mtf == true) {
			Node *new_node = node_create(oldspeak, newspeak);
			
			// we need to delete where node new is
			new->next->prev = new->prev;
			new->prev->next = new->next;
			new->next = NULL;
			new->prev = NULL;
			node_delete(&new);
			
			// then we implement the new node at the head
			new_node->next = ll->head->next; // head->next holding the old new node
			new_node->prev = ll->head;
			ll->head->next = new_node;
			new_node->next->prev = new_node;
			ll->length++;
		}
	}
	
	
}

// print out each node in the linked list except for the head and tail nodes
void ll_print(LinkedList *ll) {
	if (ll) {
		Node *print = ll->head->next;

		while (print != NULL) {
			node_print(print);
			print = print->next;
		} // end of while-loop
	} // end of if-statement
}

/*Copies the number of linked list lookups to n_seeks, and the number of links traversed during lookups to n_links.
Unlike BloomFilter and HashTable, these statistics are tracked across all linked lists, not maintained separately
for each list.*/
void ll_stats(uint32_t *n_seeks, uint32_t *n_links) {
	
	*n_seeks = seeks;
	*n_links = links;
}

/*int main () {

	char a[] = "hello";
	char b[] = "howdy";
	char c[] = "hello";
	char d[] = "\0";
	char e[] = "\0";
	
	printf("a:b 0? %d\n", own_strcom(a, b));
	printf("a:c 1? %d\n", own_strcom(a, c));
	printf("b:c 0? %d\n", own_strcom(b, c));
	printf("e:d 1? %d\n", own_strcom(e, d));
	printf("a:d 0? %d\n", own_strcom(a, d));
	printf("d:a 0? %d\n", own_strcom(d, a));
	LinkedList *v;
	
	v = ll_create(false);
	ll_print(v);
	printf("\n");
	ll_insert(v, "hey", "bad");
	
	ll_insert(v, "stink", "ye");

	ll_insert(v, "singgg", "say");

	ll_insert(v, "stink", "sao");

	ll_insert(v, "dd", "ddd");
	
	ll_insert(v, "singgg", "b");

	ll_print(v);
	
	printf("%d\n", ll_length(v));
	
	ll_delete(&v);
	
return 0;
}*/
