#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "arrays.h"
#include "sort.h"

int main(int argc, char *argv[])
{
	int len = 0, choice, ret, ret1, ret2;
	array_t *data = NULL;

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
		printf("5: Bubble sort the array\n");
		printf("6: Quick sort the array\n");
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
		case 5:
			printf("case 5\n");
			bsort_array(data, len);
			break;
		case 6:
			printf("case 6\n");
			qsort_array(data, 0, len - 1);
			break;
		default:
			break;
		}
	}

	return 0;
}
