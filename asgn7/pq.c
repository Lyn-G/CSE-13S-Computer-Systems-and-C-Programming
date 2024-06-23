#include "pq.h"
#include "node.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

struct PriorityQueue {
uint32_t size;
uint32_t capacity;
Node **items;
};

// code from assignment 4's implementation

uint32_t bigger;

int cmp(uint32_t x, uint32_t y) {
    if (x < y) {
        return -1;
    } else if (x > y) {
        return 1;
    } else {
        return 0;
    }
}

void swap(PriorityQueue *q, uint32_t x, uint32_t y) {
    Node *t = q->items[x]; // temporary node for swapping
    q->items[x] = q->items[y];
    q->items[y] = t;
}

uint32_t l_child (uint32_t n) {
	return 2 * n + 1;
}

uint32_t r_child (uint32_t n) {
	return 2 * n + 2;
}

uint32_t parent (uint32_t n) {
	return (n - 1) / 2;
}

void up_heap (PriorityQueue *q, uint32_t n) {
	while (n > 0 && q->items[n]->frequency < q->items[parent(n)]->frequency) {
		swap(q, n, parent(n));
		n = parent(n);
	}
} // end of going up heap function

void down_heap (PriorityQueue *q, uint32_t heap_size) {
	uint32_t n = 0;
	while (l_child(n) < heap_size) {
		if (r_child(n) == heap_size) {
			bigger = l_child(n);
		}//end of if-statement
		else {
			if (q->items[l_child(n)]->frequency < q->items[r_child(n)]->frequency) {
				bigger = l_child(n);
				}
			else {
				bigger = r_child(n);
				}	
		}//end of else-statement
		if (q->items[n]->frequency < q->items[bigger]->frequency) {
				break;
				}
		swap(q, n, bigger);
		n = bigger;
	}//end of while-loop
} // end of going down heap function

PriorityQueue *pq_create(uint32_t capacity) {
	// The constructor for a priority queue.
	PriorityQueue *q = (PriorityQueue *) malloc (sizeof(PriorityQueue));
	
	if (q) {
		q->capacity = capacity;
		q->size = 0;
		q->items = malloc(capacity * sizeof(Node)); // The priority queue’s maximum capacity is specified by capacity.
	}
	return q;
}

void pq_delete(PriorityQueue **q) {
	// Make sure to set the pointer to NULL after freeing the memory for a priority queue.
	if (*q && (*q)->items) {
		free((*q)->items);
		(*q)->items = NULL;
		free(*q);
		(*q) = NULL;
	}
}

// Returns true if the priority queue is empty and false otherwise.
bool pq_empty(PriorityQueue *q) {
	return q->size == 0;
}

// Returns true if the priority queue is full and false otherwise.
bool pq_full(PriorityQueue *q) {
	return q->size == q->capacity;
}

// Returns the number of items currently in the priority queue.
uint32_t pq_size(PriorityQueue *q) {
	return q->size;
}

bool enqueue(PriorityQueue *q, Node *n) {

	// Returns false if the priority queue is full prior to enqueuing the node 
	if (pq_full(q)) {
		return false;
	} else {
		// return true otherwise to indicate the successful enqueuing of the node
		q->items[q->size] = n;
		up_heap(q, q->size);
		q->size++;
		return true;
	}
}


// Dequeues a node from the priority queue, passing it back through the double pointer n
// The node dequeued should have the highest priority over all the nodes in the priority queue.
bool dequeue(PriorityQueue *q, Node **n) {
	// Returns false if the priority queue is empty prior to dequeuing a node
	if (pq_empty(q)) {
		return false;
	} else {
		// true otherwise to indicate the successful dequeuing of a node
		(*n) = q->items[0]; // place it in the passed in Node
		
		q->items[0] = q->items[q->size - 1];
		down_heap(q,q->size - 1);
		q->size--;
		return true;
	}
}

void pq_print(PriorityQueue *q) {
	printf("is it empty??? %d\n", pq_empty(q));
	printf("is it full??? %d\n", pq_full(q));
	printf("what is its size??? %d\n", pq_size(q));
	puts("printing out the priority queue:");
	
	for (uint32_t i = 0; i < q->size; i++) {
		node_print(q->items[i]);
	}
	puts("");
}
/*
int main () {
	PriorityQueue *pq = pq_create(10);
	pq_print(pq);
	
	Node *node = node_create ('f', 1);
	Node *node1 = node_create ('t', 500);
	Node *node2 = node_create ('x', 3);
	Node *node3;
	Node *node4;
	enqueue(pq, node);
	pq_print(pq);
	
	enqueue(pq, node1);
	enqueue(pq, node2);
	pq_print(pq);
	
	dequeue(pq, &node3);
	pq_print(pq);
	
	dequeue(pq, &node4);
	pq_print(pq);
	
	node_print(node3);
	
	node_delete(&node);
	node_delete(&node1);
	node_delete(&node2);
	// node_delete(&node3);
	pq_delete(&pq);
}
*/
