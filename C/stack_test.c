#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <math.h>
#include "stack.h"

void print_data(int index, void *data)
{
	int *idata = (int *) data;

	printf("Index: %d data: %x\n", index, *idata);
}

static int create_randstack(stack_t **s, int max)
{
	time_t t;
	int i;
	int *data;

	srand((unsigned) time(&t));

	*s = alloc_stack(max, sizeof(int));
	if (!*s)
		return -ENOMEM;

	(*s)->print_data = print_data;

	for (i = 0; i < max; i++ ) {
		data = malloc(sizeof(int));
		*data = rand() % (max * 10);
		push(*s, data);
	}

	return 0;
}

int main(int argc, char *argv[])
{
	int max = 0, choice, ret, *data;
	stack_t *s;

	printf("Enter the max number of elements\n");
	scanf("%d", &max);

	ret = create_randstack(&s, max);
	if (ret) {
		printf("Create randstack failed ret:%d\n", ret);
		return ret;
	}

	while (1) {
		printf("Choose one of the following option:\n");
		printf("0: Exit the program\n");
		printf("1: Print the stack\n");
		printf("2: Push data\n");
		printf("3: Pop data\n");
		scanf("%d", &choice);

		switch(choice) {
		case 0:
			printf("case 0\n");
			return 0;
		case 1:
			printf("case 1\n");
			print_stack(s);
			break;
		case 2:
			data = malloc(sizeof(int));

			printf("Enter the data\n");
			scanf("%d", data);

			ret = push(s, data);
			if (ret)
				free(data);
			break;
		case 3:
			printf("case 3\n");
			data = pop(s);
			if (data) {
				print_data(0, data);
				free(data);
			}
			break;
		case 4:
			printf("case 4\n");
			break;
		default:
			printf("case default %d\n", choice);
			break;
		}
	}

	printf("End of main\n");

	return 0;
}
