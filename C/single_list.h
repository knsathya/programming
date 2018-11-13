#ifndef __SINGLE_LIST_H__

#define __SINGLE_LIST_H__

typedef struct node {
	int data;
	struct node *next;
}node_t;

int add_node(node_t **head, int pos, int data);
node_t *find_middle(node_t *head);
node_t *find_element(node_t *head, int data);
int del_middle(node_t **head);
int list_len(node_t *head);
int list_rec_len(node_t *head);
int reverse(node_t **head);
int recursive_reverse(node_t **head);
int print_list(node_t *head);
int merge_sort(node_t **head);
int bubble_sort(node_t **head);
node_t *get_nthnode(node_t *head, int count);
void introduce_loop(node_t *head, int n);
int find_loop(node_t *head, node_t **loop);
int create_randlist(node_t **head, int len);

#endif /* __SINGLE_LIST_H__ */
