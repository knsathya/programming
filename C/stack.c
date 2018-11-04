#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "stack.h"

static int isempty(stack_t *s)
{
	if (!s || !s->sp)
		return 1;

	return 0;
}

static int isfull(stack_t *s)
{
	if (!s || s->curr_count >= s->max_count)
		return 1;

	return 0;
}

static node_t *alloc_node(void *data)
{
	node_t *node;

	if (!data) {
		printf("Invalid data\n");
		return NULL;
	}

	node = malloc(sizeof(node_t));
	if (!node) {
		printf("Node alloc failed\n");
		return NULL;
	}

	node->next = NULL;
	node->data = data;

	return node;
}

int push(stack_t *s, void *data)
{
	node_t *n;

	if (!s) {
		printf("Invalid stack\n");
		return -EINVAL;
	}

	if (!data) {
		printf("Invalid data\n");
		return -EINVAL;
	}

	if (isfull(s)) {
		printf("Stack is full\n");
		return -ENODEV;
	}

	n = alloc_node(data);
	if (!n) {
		printf("Node alloc failed\n");
		return -ENOMEM;
	}

	n->next = s->sp;
	s->sp = n;
	s->curr_count++;

	return 0;
}

void *pop(stack_t *s)
{
	node_t *n;
	void *data;

	if (!s) {
		printf("Invalid stack\n");
		return NULL;
	}

	if (isempty(s)) {
		printf("Stack is empty\n");
		return NULL;
	}

	n = s->sp;
	data = n->data;
	s->sp = n->next;
	s->curr_count--;

	free(n);

	return data;
}

void print_stack(stack_t *s)
{
	node_t *n;
	int index = 0;

	if (!s) {
		printf("Invalid/Empty stack\n");
		return;
	}

	printf("Max elements in stack: %lu\n", s->max_count);
	printf("Curr elements in stack: %lu\n", s->curr_count);
	printf("Element size: %lu\n", s->esize);

	n = s->sp;

	while (n) {
		if (s->print_data)
			s->print_data(index, n->data);
		else
			printf("Index:%d, data:%x\n", index,
			       *((char *)(n->data)));
		n = n->next;
		index++;
	}
}

stack_t *alloc_stack(int num, size_t size)
{
	stack_t *s;

	s = (stack_t *) malloc(sizeof(stack_t));
	if (!s) {
		printf("Stack malloc failed\n");
		return NULL;
	}

	s->sp = NULL;
	s->esize = size;
	s->curr_count = 0;

	if (num  <= 0)
		s->max_count = INT_MAX;
	else
		s->max_count = num;

	return s;
}

void free_stack(stack_t *s)
{
	node_t *curr, *next;

	if (!s) {
		printf("Invalid stack pointer");
		return;
	}

	curr = s->sp;

	while (curr) {
		next = curr->next;
		if (curr->data)
			free(curr->data);
		free(curr);
		curr = next;
	}

	free(s);
}
