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

		while (next != sorted) {
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
		}

		sorted = curr;

	} while (swapped);

	return 0;
}


/*
 * Quicksort:
 *
 * Psudocode:
 *
 * Array:
 *
 *	quickSort(arr[], low, high)
 *	{
 *		if (low < high)	{
 *			//pi is partitioning index, arr[p] is now at right place
 *			pi = partition(arr, low, high);
 *			quickSort(arr, low, pi - 1);  // Before pi
 *			quickSort(arr, pi + 1, high); // After pi
 *		}
 *	}
 *
 *	partition (arr[], low, high)
 *	{
 *		// pivot (Element to be placed at right position)
 *		pivot = arr[high];
 *
 *		 i = (low - 1)  // Index of smaller element
 *
 *		 for (j = low; j <= high- 1; j++) {
 *			// If current element is smaller than or equal to pivot.
 *			 if (arr[j] <= pivot) {
 *				  i++;    // increment index of smaller element
 *				  swap arr[i] and arr[j]
 *			 }
 *		 }
 *
 *		 swap arr[i + 1] and arr[high])
 *
 *		 return (i + 1)
 *	}
 *		 
 */

void swap_array_data(array_t *data_a, array_t *data_b)
{
	if (*data_a != *data_b) {
		*data_a = *data_a ^ *data_b;
		*data_b = *data_a ^ *data_b;
		*data_a = *data_a ^ *data_b;
	}
}

int qsort_array_partition(array_t *data, int low, int high)
{
	int i, j;

	if (!data)
		return -EINVAL;


	i =  low - 1;

	for (j = low; j <= high - 1; j++) {
		if (data[j] < data[high]) {
			i++;
			swap_array_data(&data[j], &data[i]);
		}
	}

	swap_array_data(&data[i + 1], &data[high]);

	return i + 1;
}

int qsort_array(array_t *data, int low, int high)
{
	int pi;

	if (low < high) {
		pi = qsort_array_partition(data, low, high);
		qsort_array(data, low, pi - 1);
		qsort_array(data, pi  + 1,  high);
	}

	return 0;
}
