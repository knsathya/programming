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

node_t *find_element(node_t *head, int data)
{
	if (!head)
		return NULL;

	while(head) {
		if (head->data == data)
			return head;
		head = head->next;
	}

	return NULL;
}

int del_middle(node_t **head)
{
	node_t *pre, *fast, *slow;

	if (!head || !*head)
		return -EINVAL;

	pre = *head;
	fast = *head;
	slow = *head;

	while (fast != NULL && fast->next != NULL) {
		pre = slow;
		slow = slow->next;
		fast = fast->next->next;
	}

	pre->next = slow->next;

	free(slow);

	if (slow == *head)
		*head = NULL;

	return 0;
}

int list_len(node_t *head)
{
	int count = 0;

	if (!head)
		return 0;

	while(head) {
		count++;
		head = head->next;
	}

	return count;
}

int list_rec_len(node_t *head)
{
	if (!head)
		return 0;

	return 1 + list_rec_len(head->next);
}

int reverse(node_t **head)
{
	node_t *prev = NULL, *curr, *next;

	if (!head)
		return -EINVAL;

	curr = *head;

	while(curr) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	*head = prev;

	return 0;
}

int recursive_reverse(node_t **head)
{
	node_t *first, *rest;

	first = *head;

	if (!first)
		return 0;

	rest = first->next;

	if (!rest)
		return 0;

	recursive_reverse(&rest);

	first->next->next = first;
	first->next = NULL;
	*head = rest;
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
			break;
		default:
			printf("case default %d\n", choice);
			break;
		}
	}

	printf("End of main\n");

	return 0;
}



