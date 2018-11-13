#ifndef __SORT_H
#define __SORT_H

typedef int array_t;
typedef struct node {
	int data;
	struct node *next;
}node_t;

int bsort_array(array_t *data, int len);
int bsort_list(node_t **head);

#endif
