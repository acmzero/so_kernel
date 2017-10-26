/*
 * llist.h
 *
 */

#ifndef LLIST_H_
#define LLIST_H_
#include<_NULL.H>

#define NULL_ENTRY -1

struct ll_node {
	int id;
	int value;
	struct ll_node *next;

};

typedef struct ll_node list_node;

typedef struct {
	int size;
	list_node *head;
} l_list;


extern list_node* remove_head(l_list* h);
extern void add_first(int id, int val, l_list *l);
extern void add_last(int id, int val, l_list *l);
extern void print_list(l_list *l);

#endif /* LLIST_H_ */
