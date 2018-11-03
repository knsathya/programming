#ifndef __QUEUE_H

#define __QUEUE_H

struct node;
struct queue;

typedef struct node {
	void *data;
	struct node *next;
	struct node *prev;
} node_t;

typedef struct queue {
	node_t *front;
	node_t *last;
	size_t dsize;
} queue_t;

int isempty(queue_t *q);
int enqueue(queue_t *q, node_t *n);
node_t *dequeue(queue_t *q);
void print_queue(queue_t *q);
void free_queue(queue_t *q);
void free_node(node_t *n);
node_t *alloc_node(size_t size);
queue_t *alloc_queue(int num, size_t size);

#endif
