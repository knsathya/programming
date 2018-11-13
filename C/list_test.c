#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "single_list.h"
#include "sort.h"

int main(int argc, char *argv[])
{
	int max = 0, status = 1, choice, ret;
	node_t *head = NULL, *tmp;

	printf("Enter the max number of elements\n");
	scanf("%d", &max);

	ret = create_randlist(&head, max);
	if (ret) {
		printf("Create randlist failed ret:%d\n", ret);
		return ret;
	}

	while (status) {
		printf("Choose one of the following option:\n");
		printf("0: Exit the program\n");
		printf("1: Print the list\n");
		printf("2: Find the middle of the list\n");
		printf("3: Delete the middle of the list\n");
		printf("4: Length of the list\n");
		printf("5: Reverse the list\n");
		printf("6: Find the element\n");
		printf("7: Introduce loop at nth element\n");
		printf("8: Find the loop element\n");
		printf("9: Merge sort the list\n");
		printf("10: Bubble sort the list\n");
		scanf("%d", &choice);

		switch(choice) {
		case 0:
			printf("case 0\n");
			return 0;
		case 1:
			printf("case 1\n");
			print_list(head);
			break;
		case 2:
			printf("case 2\n");
			tmp = find_middle(head);
			if (tmp)
				printf("Middle element is %d\n", tmp->data);
			break;
		case 3:
			printf("case 3\n");
			ret = del_middle(&head);
			if (ret)
				printf("Delete middle element failed\n");
			break;
		case 4:
			printf("case 4\n");
			printf("List length %d\n", list_len(head));
			printf("Recursive List length %d\n",
			       list_rec_len(head));
			break;
		case 5:
			printf("case 5\n");
			printf("Choose one of the following option\n");
			printf("0: Normal reverse\n");
			printf("1: Recursive reverse\n");
			scanf("%d", &choice);
			switch(choice) {
			case 0:
				ret = reverse(&head);
				if (ret)
					printf("Reverse (normal) linked list failed\n");
				break;
			case 1:
				ret = recursive_reverse(&head);
				if (ret)
					printf("Reverse (recursive) linked list failed\n");
				break;
			default:
				break;
			}
			break;
		case 6:
			printf("case 6\n");
			printf("Enter the value of the element:\n");
			scanf("%d", &ret);
			printf("Choose the search method:\n");
			scanf("%d", &choice);
			switch(choice) {
			case 0:
				tmp = find_element(head, ret);
				printf("Element assosiated with data %d is %p\n",
				       ret, tmp);
				break;
			default:
				break;
			}
		case 7:
			printf("case 7\n");
			printf("Enter the pos of the loop element:\n");
			scanf("%d", &ret);
			introduce_loop(head, ret);
			break;
		case 8:
			printf("case 8\n");
			ret = find_loop(head, &tmp);
			printf("Loop status index:%d Addr:%p\n", ret, tmp);
			break;
		case 9:
			printf("case 9\n");
			merge_sort(&head);
			break;
		case 10:
			printf("case 10\n");
			bsort_list(&head);
			break;
		default:
			printf("case default %d\n", choice);
			break;
		}
	}

	printf("End of main\n");

	return 0;
}
