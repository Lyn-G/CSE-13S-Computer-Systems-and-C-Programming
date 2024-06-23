#include "node.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>

Node *node_create(uint8_t symbol, uint64_t frequency) {
	Node *n = (Node *) malloc (sizeof(Node));
	
	// sets the node’s symbol as symbol and its frequency as frequency
	if (n) {
		n->left = NULL;
		n->right = NULL;
		n->frequency = frequency;
		n->symbol = symbol;
	}
	
	return n;
}

// the destructor for a node
void node_delete(Node **n) {
	if (*n) {
		free(*n);
		(*n) = NULL;
	}
}

// Joins a left child node and right child node, returning a pointer to a created parent node. 
// The parent node’s left child will be left and its right child will be right. 
// The parent node’s symbol will be ‘$’ and its frequency the sum of its left child’s frequency and its right child’s frequency.
Node *node_join(Node *left, Node *right) {
	
	// create the parent node
	Node *parent = (Node*) malloc (sizeof(Node));
	
	parent->left = left;
	parent->right = right;
	parent->symbol = '$';
	parent->frequency = 0;
	
	uint64_t left_freq = 0;
	uint64_t right_freq = 0;
	
	// check if the left node's frequency isn't node
	if ((parent->left) != NULL) {
		left_freq = left->frequency;
		parent->frequency = left_freq + parent->frequency;
	}
	
	if ((parent->right) != NULL) {
		right_freq = right->frequency;
		parent->frequency = right_freq + parent->frequency;
	}
	
	return parent;
}

// node_print() prints the symbol followed by the frequency as a uint64_t.
void node_print(Node *n) {
	if (n) {
		
		// print out symbol and frequency of node passed in
		printf("parent node's frequency: %lu\n", n->frequency);
		
		if (iscntrl(n->symbol) == 0 && isprint(n->symbol) != 0) {
			// If a character passed to isprint() is a printable character, it returns non-zero integer, if not it returns 0.
				// puts("did it make it in?");
				printf("parent node's symbol print: %c\n", n->symbol);

		// end of iscntrl() if-statement
		} else {
			printf("node's symbol does not pass through any if-statements: 0x%02"PRIx8 "\n", n->symbol);
		}

		// print out left node
		if (n->left != NULL) {
			
			// print out frequency
			printf("left node's frequency: %lu\n", n->left->frequency);
		
			if (iscntrl(n->left->symbol) == 0 && isprint(n->left->symbol) != 0) {
			// If a character passed to isprint() is a printable character, it returns non-zero integer, if not it returns 0.
				printf("left node's symbol print: %c\n", n->left->symbol);

			// end of iscntrl() if-statement
			} else {
				printf("left node's symbol does not pass through any if-statements: 0x%02"PRIx8 "\n", n->left->symbol);
			}
		}
		// print out right node
		if (n->right != NULL) {
			
			// print out right node's frequency
			printf("right node's frequency: %lu\n", n->right->frequency);
		
			if (iscntrl(n->right->symbol) == 0 && isprint(n->right->symbol) != 0) {
			// If a character passed to isprint() is a printable character, it returns non-zero integer, if not it returns 0.
				printf("right node's symbol print: %c\n", n->right->symbol);

			// end of iscntrl() if-statement
			} else {
				printf("right node's symbol does not pass through any if-statements: 0x%02"PRIx8 "\n", n->right->symbol);
			}
		}
	}
}

bool node_cmp(Node *n, Node *m) {
	if (n && m) {
	
		// Returns true if the first node has a greater frequency than the second, false otherwise. 
		if ((n->frequency) > (m->frequency)) {
			return true;
		} else {
			return false;
		}
	}
	return false;
}

/*
node_print_sym() prints only the symbol associated with a node. 

For both cases, you should print control characters or unprintable symbols as 0x%02"PRIx8, and printable non-control characters as the character itself. You should use iscntrl() and isprint() to identify printable characters that aren’t control characters.
*/
void node_print_sym(Node *n) {
	if (n) {
		if (iscntrl(n->symbol) == 0) {
		
			// If a character passed to isprint() is a printable character, it returns non-zero integer, if not it returns 0.
			if (isprint(n->symbol) != 0) {
				printf("node's symbol print: %c\n", n->symbol);
			} // end of isprint() if-statement
		// end of iscntrl() if-statement
		} else {
			printf("this node's symbol does not pass through any if-statements: 0x%02"PRIx8 "\n", n->symbol);
		}
	} // end of initial if-statement
}

/*
int main () {
	Node *n = node_create('n', '\n');
	Node *m = node_create('m', '\n');
	Node *parent;
	// printf("should be false? %d\n", node_cmp(m, n));
	// node_print(n);
	// node_print_sym(n);
	// node_print_sym(m);
	parent = node_join(m, n);
	node_print(parent);
	node_delete(&n);
	node_delete(&m);
	node_delete(&parent);

	return 0;
}
*/
