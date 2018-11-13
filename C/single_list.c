#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include "single_list.h"

#define FIRST_NODE 0
#define LAST_NODE 1

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

void merge_split(node_t **head, node_t **head1, node_t **head2)
{
	node_t *slow, *fast;

	if (!head)
		return;

	slow = *head;
	fast = slow->next;

	while(fast) {
		fast = fast->next;

		if (fast) {
			slow = slow->next;
			fast = fast->next;
		}
	}

	*head1 = *head;
	*head2 = slow->next;
	slow->next = NULL;
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
	} else {
		result = head2;
		result->next = sorted_merge(head1, head2->next);
	}

	return result;
}

int merge_sort(node_t **head)
{
	node_t *head1 = NULL, *head2 = NULL;

	if (!head || !*head || !(*head)->next)
		return 0;

	merge_split(head, &head1, &head2);

	merge_sort(&head1);
	merge_sort(&head2);

	*head = sorted_merge(head1, head2);

	return 0;
}

int bubble_sort(node_t **head)
{
	node_t *curr1, *curr2, *pre1, *pre2, *tmp;

	if (!head)
		return 0;

	if (!*head)
		return 0;

	for (curr1 = *head, pre1 = NULL; curr1; pre1 = curr1, curr1 = curr1->next) {
		for (curr2 = curr1->next, pre2 = curr1; curr2; pre2 = curr2, curr2 = curr2->next) {
			if (curr1->data > curr2->data) {
				if (*head == curr1)
					*head = curr2;
				//Update prev->next
				if (pre1)
					pre1->next = curr2;
				pre2->next = curr1;

				//Update curr->next
				tmp = curr1->next;
				curr1->next = curr2->next;
				curr2->next = tmp;

				//Swap curr1 and curr2
				tmp = curr1;
				curr1 = curr2;
				curr2 = curr1;
			}
		}
	}
}

node_t *get_nthnode(node_t *head, int count)
{
	if (count == 1)
		return head;

	return get_nthnode(head->next, count-1);
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

void introduce_loop(node_t *head, int n)
{
	node_t *loop_node = head, *last = head;
	int count = 0;

	if (n <= 0 || !head)
		return;

	while(head) {
		if (count == n)
			loop_node = head;
		last = head;
		head = head->next;
		count++;
	}

	if (last != loop_node)
		last->next = loop_node;

}

int find_loop(node_t *head, node_t **loop)
{
	node_t *slow = head, *fast = head;
	int n = 0;
	char loop_found = 0;

	if (!slow)
		return -1;

	fast = head;
	*loop = NULL;

	while (slow && fast && fast->next) {
		n++;
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast) {
			loop_found = 1;
			*loop = slow;
			break;
		}
	}

	return loop_found ? n : -1;
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
