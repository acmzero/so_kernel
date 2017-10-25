/*
 * llist.h
 *
 */

#ifndef LLIST_H_
#define LLIST_H_

#define NULL_ENTRY -1

struct ll_node {
	int id;
	int value;
	struct ll_node *next;
	struct ll_node *prev;

};

typedef struct ll_node list_node;

typedef struct {
	list_node *head;
	list_node *tail;
	int size;
} l_list;


extern list_node* remove_head(l_list *l);
extern void insert_head(int id, int val, l_list *l);
extern void insert_tail(int id, int val, l_list *l);
extern void print_list(l_list *l);
extern void init_list(l_list *l);

#endif /* LLIST_H_ */
