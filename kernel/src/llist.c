/*
 * llist.c
 */
#include"llist.h"
#include"libs.h"

list_node *new_list_node(int id, int val) {
	list_node *n;
	n = (list_node*) malloc(sizeof(list_node));
	n->id = id;
	n->value = val;
	n->prev = NULL_ENTRY;
	n->next = NULL_ENTRY;
	return n;
}
list_node* remove_head(l_list *l) {
	list_node *x;
	if (l->size > 0) {
		x = l->head;
		l->head = l->head->next;
		l->head->prev = NULL_ENTRY;
		l->size--;
	} else {
		x = NULL_ENTRY;
	}
	return x;
}
void insert_head(int id, int val, l_list *l) {
	list_node *n = new_list_node(id, val);
	if (l->size > 0) {
		n->next = l->head;
		l->head->prev = n;
	} else {
		l->tail = n;
	}
	l->head = n;
	l->size++;
}
void insert_tail(int id, int val, l_list *l) {
	list_node *n = new_list_node(id, val);
	if (l->size > 0) {
		l->tail->next = n;
		n->prev = l->tail;
	} else {
		l->head = n;
	}
	n->next = NULL_ENTRY;
	l->tail = n;
	l->size++;
}

char str_plist[50];
void print_list(l_list *l) {
	//prints only next 3 items
	list_node *p, *s, *t;
	print_line(2, 10, 50, str_plist, BLACK);
	if (l->size > 0) {
		p = l->head;
		if (p->next != NULL_ENTRY) {
			s = p->next;
			if (s->next != NULL_ENTRY) {
				t = s->next;
			}
		}
	}
	sprintf(str_plist, "First 3 items %d/%d->%d/%d->%d/%d", p->id, p->value,
			s->id, s->value, t->id, t->value);
	print_line(2, 10, 50, str_plist, WHITE);
}

void init_list(l_list *l){
	l->head = NULL_ENTRY;
	l->tail = NULL_ENTRY;
	l->size = 0;
}
