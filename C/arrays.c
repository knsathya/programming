#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include "arrays.h"

int find_min(array_t *data, int len)
{
	int i, min = 0;

	if (!data || (len == 0))
		return -ENOMEM;

	for (i = 0; i < len; i++) {
		if (data[i] < data[min])
			min = i;
	}

	return min;
}

int find_max(array_t *data, int len)
{
	int i, max = 0;

	if (!data || (len == 0))
		return -ENOMEM;

	for (i = 0; i < len; i++) {
		if (data[i] > data[max])
			max = i;
	}

	return max;
}

void swap(array_t *data1, array_t *data2)
{
	printf("swap %d %d\n", *data1, *data2);
	if (*data1 != *data2) {
		*data1 = *data1 ^ *data2;
		*data2 = *data1 ^ *data2;
		*data1 = *data1 ^ *data2;
	}
}

int reverse(array_t *data, int len)
{
	int i;

	for (i = 0; i < len / 2; i++) {
		swap(&data[i], &data[len - i - 1]);
	}

	return 0;
}

int recursive_reverse(array_t *data, int len)
{
	if (len == 0)
		return 0;

	swap(&data[0], &data[len - 1]);

	if (len == 1)
		return 0;
	else
		return recursive_reverse(&data[1], len - 2);
}

int print_array(array_t *data, int len)
{
	int i = 0;

	if (data == NULL)
		printf("Empty array\n");

	for (i = 0; i < len; i++)
		printf("Index %d Addr:%p Value %d\n", i,
		       &data[i], data[i]);

	return 0;
}

int create_randarray(array_t **datap, int len)
{
	time_t t;
	int i;
	array_t *data;

	data = (array_t *) malloc(sizeof(array_t) * len);
	if (!data)
		return -ENOMEM;

	*datap = data;

	srand((unsigned) time(&t));

	for (i = 0; i < len; i++)
		data[i] = rand() % (len * 10);

	return 0;
}


