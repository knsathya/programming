#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include "array.h"

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
	//printf("swap %d %d\n", *data1, *data2);
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

void rotate_left(array_t *data, int len, int d)
{
    while (d > len)
        d = d - len;

    reverse(data, d);
    reverse(&data[d], len-d);
    reverse(data, len);
}

void rotate_right(array_t *data, int len, int d)
{
    while (d > len)
        d = d - len;

    reverse(&data[len - d], d);
    reverse(data, len);
    reverse(&data[d], len - d);
}

array_t find_rotation_element(array_t *data, int start, int end, int last)
{
    int mid = start + ((end - start) / 2);

    if (start > end)
        return data[mid];

    if (data[mid] > data[last])
        return find_rotation_element(data, mid + 1, end, last);
    else if (data[mid] < data[last])
        return find_rotation_element(data, start, mid - 1, last);
    else
        return data[mid];
}

int rotated_binary_search(array_t *data, int l, int h, array_t key)
{
    int m = l + ((h - l) / 2);

    if (!data)
        return -1;

    if (key == data[m])
        return m;

    /* This part of array is sorted */
    if (data[l] < data[m]) {
        if  (data[l] <= key && key < data[m])
            return rotated_binary_search(data, l, m - 1, key);
        else
            return rotated_binary_search(data, m + 1, h, key);
    /* Right part of the array is sorted */
    } else if (data[h] > data[m]) {
        if (key > data[m] && key <= data[h])
            return rotated_binary_search(data, m + 1, h, key);
        else
            return rotated_binary_search(data, l, m - 1, key);
    }

    return -1;

}

int find_number_rotations(array_t *data, int l, int h)
{
    int m;

    if (l >= h)
        return 0;

    while (data[l] > data[h]) {

        m = l + ((h - l) / 2);

        if (data[m] > data[h])
            l = m + 1;
        else
            h = m;
    }

    return l;
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
