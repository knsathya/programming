#include <stdio.h>
#include <errno.h>
#include "sort.h"

/*
 * Bubble sort:
 *
 * Pseudo Algorithm:
 *
 * Array:
 *
 *	1. for every element in the list,
 *		for i 0 -> len - 1
 *	2. for every element in the list except sorted element,
 *		for j 0 -> len - i
 *	3. Compare element[0] with element[1]
 *		if element[j] > element[j + 1] then;
 *		swap(element[j], element[j + 1])
 *
 *
 * Linked list:
 *  *
 *	1. do while element to be sorted
 *		do {} while (swapped)
 *	2. for every element in the list except sorted element,
 *		while (element->next != sorted_element) // Inital value is NULL
 *	3. comparse element with element->next,
 *		if element->data > element->next->data then;
 *		swap element and element->next
 *
 */

int bsort_array(array_t *data, int len)
{
	int i, j;
	array_t temp;

	for (i = 0; i < len; i++) {
		for (j = 0; j < len - i - 1; j++) {
			if (data[j] > data[j + 1]) {
				temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
			}
		}
	}

	return 0;
}

int bsort_list(node_t **head)
{
	int swapped = 0;
	node_t *curr, *prev, *next, *sorted = NULL;

	if (!head) {
		printf("Head is NULL\n");
		return -EINVAL;
	}

	do {
		swapped = 0;
		prev = curr = *head;
		if (curr)
			next = curr->next;
		printf("Starting curr:%p sorted:%p\n", curr, sorted);

		while (next != sorted) {
			printf("Bsort curr:%p,%d next:%p,%d\n", curr, curr->data, next, next->data);
			if ( curr->data > next->data) {
				if (*head == curr)
					*head = next;
				prev->next = next;
				curr->next = next->next;
				next->next = curr;
				swapped = 1;
				prev = next;
			} else {
				prev = curr;
				curr = next;
			}
			next = curr->next;
			printf("Asort curr:%p,%d next:%p,%d\n", curr, curr->data, next, next != NULL ? next->data : -1);
		}

		sorted = curr;

	} while (swapped);

	return 0;
}
