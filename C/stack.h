#ifndef __STACK_H

#define __STACK_H

struct node;
struct stack;

typedef struct node {
	void *data;
	struct node *next;
} node_t;

typedef struct stack {
	node_t *sp;
	size_t esize;
	size_t max_count;
	size_t curr_count;
	void (*print_data)(int, void*);
} stack_t;

int push(stack_t *s, void *data);
void *pop(stack_t *s);

void free_stack(stack_t *s);
void print_stack(stack_t *s);
stack_t *alloc_stack(int num, size_t size);

#endif
