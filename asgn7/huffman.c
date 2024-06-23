#include "huffman.h"
#include "pq.h"
#include "io.h"
#include "stack.h"

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

Code c;

// constructs a Huffman tree given a computed histogram
Node *build_tree(uint64_t hist[static ALPHABET]) {
	PriorityQueue *pq = pq_create(ALPHABET);
	
	// // it will have ALPHABET indices, one index for each possible symbol
	for (uint64_t i = 0; i < ALPHABET; i++) {
		
		// check if the frequency is higher than zero
		if (hist[i] > 0) {
			Node *node = node_create (i, hist[i]);
			enqueue(pq, node);
		} // end of if-statement
	} // end of for-loop
	
	// create nodes to use
	Node *left;
	Node *right;
	Node *parent;
		
	while (pq_size(pq) > 1) { // there needs to exist a pair of nodes in the priority queue
		
		dequeue(pq, &left);
		dequeue(pq, &right);
		
		parent = node_join(left, right);
		
		enqueue(pq, parent);
	} // end of while-loop
	
	// pq_print(pq);
	
	// returns the root node of the constructed tree
	Node *root;
	dequeue(pq, &root);
	
	pq_delete(&pq);
	
	return root;
	
}

// populated a code table, building the code for each symbol in the Huffman tree
void build_codes(Node *root, Code table[static ALPHABET]) {
	
	uint8_t bit = 0;
	if (root) {
		
		// check if current node is a leaf
		if (root->left == NULL && root->right == NULL) {
			table[root->symbol] = c;
		// end of leaf if-statement
		} else { // post-order traversal to create the codes for each character
			
			// push a 0 and traverse down the left 
			code_push_bit(&c, 0);
			build_codes(root->left, table);
			
			code_pop_bit(&c, &bit);
			
			// push a 1 and traverse down the right 
			code_push_bit(&c, 1);
			build_codes(root->right, table);
			
			// pop bit from c
			code_pop_bit(&c, &bit);
			
		} 
	} // end of if-statement
}

// conducts a post-order traversal of the Huffman tree rooted at root
// write it out to outfile
void dump_tree(int outfile, Node *root) {
	if (root) {
		dump_tree(outfile, root->left);
		dump_tree(outfile, root->right);
		
		uint8_t letter1 = 'L';
		uint8_t letter2 = 'I';
		if (root->left == NULL && root->right == NULL) {
			// write L followed by the bytes of the symbol
			write_bytes(outfile, &letter1, 1);
			write_bytes(outfile, &root->symbol, 1);	
		} else {
			// write I for interior nodes and don't write symbol
			write_bytes(outfile, &letter2, 1);
		} // end of else-statement
	} // end of first if-statement
	
}

// reconstructs a Huffman tree given its post-order tree dump stored in the array tree_dump (i think they mean tree)
// the length in bytes of tree is given by nbytes
Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {

	Node *right;
	Node *left;
	Node *parent;

	// a stack of nodes will be needed to reconstruct the tree
	Stack *s = stack_create(nbytes);
	Node *node;
	
	for (int i = 0; i < nbytes; i++) {
		if (tree[i] == 'L') {
		// create a new node and push the created node onto the stack
			node = node_create(tree[i+1], 0);
			stack_push(s, node);
			i++;
		} else if (tree[i] == 'I') {
		
			// pop the stack to get the right child of the interior node
			stack_pop(s, &right);
			
			// pop again to get the left child of the interior node
			stack_pop(s, &left);
			
			// join the left and right nodes with node_join()
			parent = node_join(left, right);
			
			// push the joined parent node on the stack
			stack_push(s, parent);
		}
	} // end of for-loop
	// there will be one node left in the stack after you finish iterating over the contents 
	Node *root;
	stack_pop(s, &root);
	stack_delete(&s);
	return root;
}

// post-order traversal of the tree to free all nodes
void delete_tree(Node **root) {
	if (*root) {
		if ((*root)->left != NULL) {
			delete_tree(&(*root)->left);
		}
		if ((*root)->right != NULL) {
			delete_tree(&(*root)->right);
		}
		node_delete(root);
		*root = NULL;
	}
}
/*
int main () {

	FILE *file = fopen("hello.txt", "r");
	build_tree(file);

	return 0;
}
*/
