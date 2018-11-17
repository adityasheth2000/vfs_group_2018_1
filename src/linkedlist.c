#include <stdlib.h>
#include <stddef.h>
#include<string.h>
#include "../include/linkedlist.h"


#define ERRORNOTFOUND -1
#define FOUND 0
#define SUCCESS 0
#define FAILURE -1

int list_insert(l_node** head, void *data, char* key) {
	if(data == NULL)
		return FAILURE;
	l_node *current;
	current = (l_node*) malloc(sizeof(l_node));
	if (current == NULL )
		return FAILURE;
	current->key = key;
	current->data = data;
	current->next = *head;
	(*head) = current;
	return SUCCESS;
}

int list_delete(l_node** head, char *key) {
	l_node *prev, *current;
	if (head == NULL )
		return FAILURE;
	current = *head;
	if (strcmp((current)->key, key) == 0) {
		current = current->next;
		free(*head);
		(*head) = current;
		return SUCCESS;
	}
	prev = NULL;
	current = *head;
	int isdeleted = 0;
	while (current != NULL ) {
		if (strcmp(current->key, key) == 0) {
			prev->next = current->next;
			free(current);
			isdeleted = 1;
			break;
		}
		prev = current;
		current = current->next;
	}
	if (isdeleted == 1)
		return SUCCESS;
	return FAILURE;
}

int list_search(l_node** head, l_node** result, char *key) {
	l_node* current = *head;
	if (head == NULL )
		return FAILURE;
	int isfound = 0;
	if ((*result) != NULL )
		*result = NULL;
	while (current != NULL ) {
		if (strncmp(current->key, key,strlen(key)) == 0) {
			list_insert(&(*result), current->data, key);
			isfound = 1;
		}
		current = current->next;
	}
	if (isfound == 1)
		return SUCCESS;
	return FAILURE;
}


