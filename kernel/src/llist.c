/*
 * llist.c
 */
#include"llist.h"
#include"libs.h"
#include<ALLOC.H>

list_node *new_list_node(int id, int val) {
	list_node *n;
	n = (list_node*) malloc(sizeof(list_node));
	n->id = id;
	n->value = val;
	n->next = NULL;
	return n;
}
list_node* remove_head(l_list *l) {
	list_node *x;
	if (l->head != NULL) {
		x = l->head;
		l->head = x->next;
	} else {
		x = NULL;
	}
	return x;
}
void add_first(int id, int val, l_list *l) {
	list_node *n = new_list_node(id, val);
	n->next = l->head;
	l->head = n;
}
void add_last(int id, int val, l_list *l) {
	list_node *e;
	list_node *n = new_list_node(id, val);
	if (l->head == NULL) {
		l->head = n;
		return;
	}
	e = l->head;
	while (e->next != NULL) {
		e = e->next;
	}
	e->next = n;
}

char str_plist[50];
void print_list(l_list *l) {
	//prints only next 3 items
	list_node *p, *s, *t;
	print_line(2, 10, 50, str_plist, BLACK);
	if (l->head != NULL) {
		p = l->head;
		if (p->next != NULL) {
			s = p->next;
			if (s->next != NULL) {
				t = s->next;
			}
		}
	}
	sprintf(str_plist, "First 3 items %d/%d->%d/%d->%d/%d", p->id, p->value,
			s->id, s->value, t->id, t->value);
	print_line(2, 10, 50, str_plist, WHITE);
}

