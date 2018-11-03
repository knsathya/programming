#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "queue.h"

int isempty(queue_t *q)
{
	if (!q || !q->front)
		return 1;

	return 0;
}

int enqueue(queue_t *q, node_t *n)
{
	if (!q) {
		printf("Invalid queue\n");
		return -EINVAL;
	}

	if (!n) {
		printf("Invalid node\n");
		return -EINVAL;
	}

	if (isempty(q))
		q->front = q->last = n;
	else {
		n->prev = q->last;
		q->last->next = n;
		q->last = n;
	}

	return 0;
}

node_t *dequeue(queue_t *q)
{
	node_t *curr;

	if (isempty(q)) {
		printf("Invalid/Empty queue\n");
		return NULL;
	}

	curr = (node_t*) q->front;
	q->front = curr->next;

	if (q->front)
		q->front->prev = NULL;
	else
		q->front = q->last = NULL;

	return curr;
}

void print_queue(queue_t *q)
{
	node_t *n;
	char *data;
	int index = 0;

	if (isempty(q)) {
		printf("Queue is empty\n");
		return;
	}

	n = q->front;

	while (n) {
		data = n->data;
		printf("Element %d Address %p Value %x\n", index, n, *data);
		index++;
		n = n->next;
	}
}

void free_queue(queue_t *q)
{
	node_t *curr, *next;

	if (!q)
		return;

	curr = q->front;

	while (curr) {
		next = curr->next;

		if(curr->data)
			free(curr->data);
		free(curr);
		curr = next;
	}

	free(q);
}

void free_node(node_t *n)
{
	if (!n)
		return;

	if (n->data)
		free(n->data);

	free(n);

	return;
}

node_t *alloc_node(size_t size)
{
	node_t *node;
	void *data;

	node = malloc(sizeof(node_t));
	if (!node) {
		printf("Node alloc failed\n");
		return NULL;
	}

	node->prev = node->next = NULL;

	data = malloc(size * sizeof(char));
	if (!data) {
		printf("Node data alloc failed\n");
		free(node);
		return NULL;
	}

	node->data = data;

	return node;
}

/*
 *  alloc_queue(): Alloc queue of given size
 *  @num : Number of elements in the queue. Use -1 for undefined size.
 *  @size: Size of the data in elements of the queue.
 */
queue_t *alloc_queue(int num, size_t size)
{
	queue_t *q;
	node_t *node;
	int i;

	q = (queue_t *) malloc(sizeof(queue_t));
	if (!q) {
		printf("Queue malloc failed\n");
		return NULL;
	}

	q->front = NULL;
	q->last = NULL;
	q->dsize = size;

	for (i = 0; i < num; i++) {
		node = alloc_node(size);
		if (!node)
			goto node_alloc_err;

		if (enqueue(q, node)) {
			printf("Queue node enqueue failed\n");
			goto enqueue_err;
		}
	}

	return q;

enqueue_err:
	free_node(node);
node_alloc_err:
	free_queue(q);
	return NULL;
}
