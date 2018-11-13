#include <stdio.h>

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
 *		for j 0 -> len - i - 1
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
