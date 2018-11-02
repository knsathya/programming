#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <math.h>

#define LEFT 0
#define RIGHT 1

typedef struct node {
	int data;
	struct node *left;
	struct node *right;
}node_t;

int add_BT_node(node_t **head, int data, int dir)
{
	node_t *new, *tmp, *prev_head;

	if (!head)
		return -EINVAL;

	new =  (node_t*) malloc(sizeof(node_t));
	if (!new)
		return -ENOMEM;

	new->data = data;
	new->left = NULL;
	new->right = NULL;

	if (!*head)
		*head = new;
	else {
		prev_head = tmp = *head;

		while (tmp) {
			if (!tmp->left) {
				tmp->left = new;
				break;
			}
			if (!tmp->right) {
				tmp->right = new;
				break;
			}
			if (dir == LEFT)
				tmp = tmp->left;
			else
				tmp = tmp->right;
		}
	}

	return 0;
}

int find_maxdepth(node_t *head)
{
	int ldepth, rdepth;

	if (!head)
		return 0;
	else {
		ldepth = find_maxdepth(head->left);
		rdepth = find_maxdepth(head->right);

		if (ldepth > rdepth)
			return ldepth + 1;
		else
			return rdepth + 1;
	}
}

void printgivenlevel(node_t *head, int level, int tab)
{
	int i;

	if (!head)
		return;

	if (level == 1) {
		for (i = 0; i < tab; i++)
			printf("\t");
		printf("%d\t", head->data);
	} else if (level > 1) {
		printgivenlevel(head->left, level-1, tab);
		printgivenlevel(head->right, level-1, tab);
	}
}

void print_tree(node_t *head)
{
	int max_depth = find_maxdepth(head);
	int i, tab, max_el = pow(2, (max_depth - 1));

	printf("Max depth: %d Max El:%d\n", max_depth, max_el);

	for (i = 1; i <= max_depth; i++) {
		tab = ((int)(max_el / 2) - (i - 1));
		printf("Level: %d Tab size: %d\n", i, tab);
		printgivenlevel(head, i, tab);
		printf("\n");
	}
	printf("\n");
}

int create_rand_BT(node_t **head, int max_level)
{
	time_t t;
	int ret, i, data, lcount;

	srand((unsigned) time(&t));

	i = max_level + 1;

	while (i-- > 0)
		lcount += 2 ^ (max_level - i);

	for (i = 0; i < lcount; i++) {
		data = rand() % (lcount * 10);
		ret = add_BT_node(head, data, rand() % 10 > 5 ? RIGHT : LEFT);
		if (ret != 0) {
			printf("Add node failed. head:%p, data:%d\n",
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

	ret = create_rand_BT(&head, max);
	if (ret) {
		printf("Create randlist failed ret:%d\n", ret);
		return ret;
	}

	while (status) {
		printf("Choose one of the following option:\n");
		printf("0: Exit the program\n");
		printf("1: Print the tree\n");
		scanf("%d", &choice);

		switch(choice) {
		case 0:
			printf("case 0\n");
			return 0;
		case 1:
			printf("case 1\n");
			print_tree(head);
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
