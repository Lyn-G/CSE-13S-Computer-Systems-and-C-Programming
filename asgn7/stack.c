#include "stack.h"
#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Stack {
uint32_t top;
uint32_t capacity;
Node **items;
};

// stack constructor
Stack *stack_create(uint32_t capacity) {
	Stack *s = (Stack *) malloc (sizeof(Stack));
	
	if (s) {
		s->top = 0;
		s->capacity = capacity;
		
		// The maximum number of nodes the stack can hold is specified by capacity
		s->items = (Node**) malloc (capacity * sizeof(Stack));
		
	}
	
	return s;
}

// stack destructor
void stack_delete(Stack **s) {
	if ((*s) && (*s)->items) {
	
		// Remember to set the pointer to NULL after you free the memory allocated by the stack.
		free((*s)->items);
		(*s)->items = NULL;
		
		free(*s);
		(*s) = NULL;
	}
}

// Returns true if the stack is empty and false otherwise
// check if there are 0 items and return false otherwise
bool stack_empty(Stack *s) {
	if (s) {
	
		if (s->top == 0) {
			return true;
		} else {
			return false;
		}
	}
	return false;
}

// Returns true if the stack is full and false otherwise.
// returns true if the stack has the same size as the capacity that was passed in 
bool stack_full(Stack *s) {
	if (s) {
	
		if (s->top == s->capacity) {
			return true;
		} else {
			return false;
		}
	}
	return false;
}

// Returns the number of nodes in the stack
uint32_t stack_size(Stack *s) {
	return s->top;
}

// Pushes a node onto the stack. 
bool stack_push(Stack *s, Node *n) {
	if (s) {
		
		// Returns false if the stack is full prior to pushing the node
		if (stack_full(s) == true) {
			return false;
		} else {
			
			// return true otherwise to indicate the successful pushing of a node
			s->items[s->top] = n;
			s->top++;
			return true;
		}
	}
	return false;
}

// stack_pop will delete the passed in node and the node that was popped off
bool stack_pop(Stack *s, Node **n) {
	if (s) {
		// Returns false if the stack is empty prior to popping a node
		if (stack_empty(s) == true) {
			// puts("can't pop");
			return false;
		} else {
		
			// Pops a node off the stack, passing it back through the double pointer n. 
			(*n) = s->items[s->top - 1];
			s->items[s->top - 1] = NULL;
			s->top --;

			// return true otherwise to idicate the successful popping of a node
			return true;
		}
	}
	return false;
}

void stack_print(Stack *s) {
	puts("inside stack print");
	if (s) {
		// print out if stack is empty
		if (stack_empty(s) == true) {
			printf("stack is empty!!!\n");
		} else {
			printf("stack is NOT empty!!!\n");
		}
		
		// print out if stack is full
		if (stack_full(s) == true) {
			printf("stack is full!!!\n");
		} else {
			printf("stack is NOT full!!!\n");
		}
		
		printf("stack top: %u\n", s->top);
		printf("stack capacity: %u\n", s->capacity);
		puts("stack items:");
		// print out items in the stack
		
		if (stack_empty(s) == false) {
			for(uint32_t i = 0; i < stack_size(s); i++) {
			node_print(s->items[i]);
			}
		} 
		
	}
}

/*
int main () {
	
	Node *n = node_create('n', 3);
	Node *m = node_create('m', 4);
	Node *l = node_create('l', 4);
	Node *p = node_create('p', 4);
	Node *o = node_create('o', 4);
	Node *hello = NULL;
	
	
	Stack *s = stack_create(2);
	stack_print(s);
	puts("");
	// stack_pop(s, &hello);
	stack_push(s,n);
	stack_push(s,m);
	stack_push(s, l);
	stack_push(s, p);
	stack_push(s, o);
	stack_print(s);
	stack_pop(s, &hello);
	stack_push(s, o);
	puts("");
	// node_print(hello);
	stack_print(s);
	
	stack_delete(&s);
	
	node_delete(&n);
	node_delete(&l);
	node_delete(&p);
	node_delete(&o);
	//node_delete(&m);
	//node_delete(&hello);
	
	return 0;
}
*/
