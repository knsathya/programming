#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#define FIRST_NODE 0
#define LAST_NODE 1

typedef struct node {
	int data;
	struct node *next;
}node_t;

int add_node(node_t **head, int pos, int data) {
	node_t *new, *tmp;

	if (!head)
		return -EINVAL;

	new = (node_t *) malloc(sizeof(node_t));
	if (!new)
		return -ENOMEM;

	new->data = data;
	new->next = NULL;

	if (*head == NULL)
		*head = new;
	else {
		tmp = *head;
		/* Add at the end of the list */
		if (pos == FIRST_NODE) {
			new->next = tmp;
			*head = new;
		} else {
			while (tmp != NULL && tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = new;
		}
	}

	return 0;
}

node_t *find_middle(node_t *head)
{
	node_t *slow = head, *fast = head;

	if (head != NULL)
	{
		while (fast != NULL && fast->next != NULL) {
			fast = fast->next->next;
			slow = slow->next;
		}
	}

	return slow;
}

int print_list(node_t *head)
{
	int pos = 0;

	if (head == NULL)
		printf("Empty list\n");

	while (head) {
		printf("Node %d, Value %d\n", pos++, head->data);
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
		default:
			printf("case default %d\n", choice);
			break;
		}
	}

	printf("End of main\n");

	return 0;
}



