#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

typedef int array_t;

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

int main(int argc, char *argv[])
{
	int len = 0, choice, ret, ret1, ret2;
	array_t *data = NULL, *tmp;

	printf("Enter the length of the array\n");
	scanf("%d", &len);

	ret = create_randarray(&data, len);
	if (ret) {
		printf("Create randarray failed ret:%d\n", ret);
		return ret;
	}

	while (1) {
		printf("Choose one of the following option:\n");
		printf("0: Exit the program\n");
		printf("1: Print the array\n");
		printf("2: Find Min and Max\n");
		printf("3: Reverse the array\n");
		printf("4: Recursive reverse the array\n");
		scanf("%d", &choice);

		switch(choice) {
		case 0:
			printf("case 0\n");
			return 0;
		case 1:
			printf("case 1\n");
			print_array(data, len);
			break;
		case 2:
			printf("case 2\n");

			ret1 = find_min(data, len);
			if (ret1 < 0) {
				printf("Find min() failed\n");
				return ret1;
			}

			ret2 = find_max(data, len);
			if (ret2 < 0) {
				printf("Find min() failed\n");
				return ret2;
			}

			printf("Min:%d,%d, Max:%d,%d\n",
			       ret1, data[ret1],
			       ret2, data[ret2]);

			break;
		case 3:
			printf("case 3\n");
			reverse(data, len);
			break;
		case 4:
			printf("case 4\n");
			recursive_reverse(data, len);
			break;
		default:
			break;
		}
	}

	return 0;
}
