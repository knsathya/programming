#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <math.h>
#include "queue.h"

static int create_randqueue(queue_t **q, int max)
{
	time_t t;
	node_t *n;

	srand((unsigned) time(&t));

	*q = alloc_queue(max, sizeof(int));
	if (!*q)
		return -ENOMEM;

	n = (*q)->front;

	while (n) {
		*((int *)n->data) = rand() % (max * 10);
		n = n->next;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	int max = 0, choice, ret;
	queue_t *q;
	node_t *n;

	printf("Enter the max number of elements\n");
	scanf("%d", &max);

	ret = create_randqueue(&q, max);
	if (ret) {
		printf("Create randqueue failed ret:%d\n", ret);
		return ret;
	}

	while (1) {
		printf("Choose one of the following option:\n");
		printf("0: Exit the program\n");
		printf("1: Print the tree\n");
		printf("2: Enqueue data\n");
		printf("3: Dequeue data\n");
		scanf("%d", &choice);

		switch(choice) {
		case 0:
			printf("case 0\n");
			return 0;
		case 1:
			printf("case 1\n");
			print_queue(q);
			break;
		case 2:
			printf("Enter the data\n");
			scanf("%d", &max);
			n = alloc_node(sizeof(int));
			if (!n) {
				printf("Node alloc failed\n");
				break;
			}

			*((int *)n->data) = max;

			ret = enqueue(q, n);

			if (ret)
				free_node(n);
			break;
		case 3:
			printf("case 3\n");
			n = dequeue(q);
			if (n)
				printf("Dequeued data: %d\n",
				       *((int *)n->data));
			break;
		case 4:
			printf("case 4\n");
			break;
		case 5:
			printf("case 5\n");
			break;
		case 6:
			printf("case 6\n");
			break;
		case 7:
			printf("case 7\n");
			break;
		case 8:
			printf("case 8\n");
			break;
		case 9:
			printf("case 9\n");
			break;
		case 10:
			printf("case 10\n");
			break;
		default:
			printf("case default %d\n", choice);
			break;
		}
	}

	printf("End of main\n");

	return 0;
}
