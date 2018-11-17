#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

typedef struct list_node {
	char* key;
	void* data;
	struct list_node* next;
} l_node;

int list_insert(l_node** head, void *data, char* key);

int list_delete(l_node** head, char *key);

int list_search(l_node** head, l_node** result, char *key);
#endif /* LINKEDLIST_H_ */

