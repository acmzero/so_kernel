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
int lista_print_y = 50;
void print_list(l_list *l) {
	//prints only next 3 items
	list_node *p, *s, *t, *u, *v;
	p = s = t = u = v = NULL;
//	print_line(2, 10, lista_print_y, str_plist, BLACK);
	if (l->head != NULL) {
		p = l->head;
		if (p->next != NULL) {
			s = p->next;
			if (s->next != NULL) {
				t = s->next;
				if (t->next != NULL) {
					u = t->next;
					if (u->next != NULL) {
						v = u->next;
					}
				}
			}
		}
	}
	if (p == NULL) {
		sprintf(str_plist, "->NULL");
	} else if (p != NULL && s == NULL) {
		sprintf(str_plist, "->%d/%d->NULL", p->id, p->value);
	} else if (s != NULL && t == NULL) {
		sprintf(str_plist, "->%d/%d->%d/%d->NULL", p->id, p->value, s->id,
				s->value);
	} else if (t != NULL && u == NULL) {
		sprintf(str_plist, "->%d/%d->%d/%d->%d/%d->NULL", p->id, p->value,
				s->id, s->value, t->id, t->value);
	} else if (u != NULL && v == NULL) {
		sprintf(str_plist, "->%d/%d->%d/%d->%d/%d->%d/%d->NULL", p->id,
				p->value, s->id, s->value, t->id, t->value, u->id, u->value);

	}
	print_line(2, 10, lista_print_y, str_plist, WHITE);
	lista_print_y += 10;
}

