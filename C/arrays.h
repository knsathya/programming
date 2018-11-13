#ifndef __ARRAYS_H__
#define __ARRAYS_H__

typedef int array_t;
int find_min(array_t *data, int len);
int find_max(array_t *data, int len);
void swap(array_t *data1, array_t *data2);
int reverse(array_t *data, int len);
int recursive_reverse(array_t *data, int len);
int print_array(array_t *data, int len);
int create_randarray(array_t **datap, int len);

#endif
