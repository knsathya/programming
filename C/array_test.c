#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "array.h"
#include "array_sort.h"

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
		printf("7: Rotate left\n");
	        printf("8: Rotate right\n");
		printf("9: Find rotation element\n");
	        printf("10: Find element index in rotated array\n");
		printf("11: Find rotation count\n");
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
		case 7:
			printf("case 7\n");
			printf("Enter the number of left rotations\n");
			scanf("%d", &ret1);
			rotate_left(data, len, ret1);
			break;
		case 8:
			printf("case 8\n");
			printf("Enter the number of right rotations\n");
			scanf("%d", &ret1);
			rotate_right(data, len, ret1);
			break;
		case 9:
			printf("case 9\n");
			printf("Rotation element: %d\n",
			find_rotation_element(data, 0, len-1, len-1));
			break;
		case 10:
			printf("case 10\n");
			printf("Enter search element in rotated array:\n");
			scanf("%d", &ret1);
			printf("Element index of %d is %d\n", ret1,
			       rotated_binary_search(data, 0, len - 1, ret1));
	        case 11:
			printf("case 11\n");
			printf("Number of rotations: %d\n",
			find_number_rotations(data, 0, len - 1));
		default:
			break;
		}
	}

	return 0;
}

