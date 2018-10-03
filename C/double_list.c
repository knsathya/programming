#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#define FIRST_NODE 0
#define LAST_NODE 1

typedef struct node {
	int data;
	struct node *prev;
	struct node *next;
} node_t;

void merge_split(node_t *head, node_t **head1, node_t **head2)
{
	node_t *slow = head, *fast = head;

	if (!head)
		return;

	slow = head;
	fast = slow->next;

	while (fast) {
		fast = fast->next;
		if (fast) {
			slow = slow->next;
			fast = fast->next;
		}
	}

	*head1 = head;
	*head2 = slow->next;
	slow->next = NULL;
	(*head2)->prev = NULL;
}

node_t *sorted_merge(node_t *head1, node_t *head2)
{
	node_t *result = NULL;

	if (!head1)
		return head2;
	else if (!head2)
		return head1;

	if (head1->data <= head2->data) {
		result = head1;
		result->next = sorted_merge(head1->next, head2);
		result->next->prev = result;
		result->prev = NULL;

	} else {
		result = head2;
		result->next = sorted_merge(head1, head2->next);
		result->next->prev = result;
		result->prev = NULL;
	}

	return result;
}

int merge_sort(node_t **head)
{
	node_t *head1 = NULL, *head2 = NULL;

	if (!head || !*head || !(*head)->next)
		return 0;

	merge_split(*head, &head1, &head2);

	merge_sort(&head1);
	merge_sort(&head2);

	*head = sorted_merge(head1, head2);

	return 0;
}

int add_node(node_t **head, int pos, int data) {
	node_t *new, *tmp;

	if (!head)
		return -EINVAL;

	new = (node_t *) malloc(sizeof(node_t));
	if (!new)
		return -ENOMEM;

	new->data = data;
	new->next = NULL;
	new->prev = NULL;

	if (*head == NULL)
		*head = new;
	else {
		tmp = *head;
		/* Add at the end of the list */
		if (pos == FIRST_NODE) {
			new->next = tmp;
			tmp->prev = new;
			*head = new;
		} else {
			while (tmp != NULL && tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = new;
			new->prev = tmp;
		}
	}

	return 0;
}

int print_list(node_t *head)
{
	int pos = 0;

	if (head == NULL)
		printf("Empty list\n");

	while (head) {
		printf("Node %d, Addr %p, Value %d\n", pos++,
		       head, head->data);
		head = head->next;
	}

	return 0;
}

int create_randlist(node_t **head, int len)
{
	time_t t;
	int i, ret, data;

	srand((unsigned) time(&t));

	for (i = 0;i < len; i++) {
		data = rand() % (len * 10);
		ret = add_node(head, LAST_NODE, data);
		if (ret != 0) {
			printf("Add node failed, head:%p, data:%d\n",
			       head, data);
			return ret;
		}
	}

	return 0;
}

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
			break;
		case 3:
			printf("case 3\n");
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
			merge_sort(&head);
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
