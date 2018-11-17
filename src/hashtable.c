#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hashtable.h"

void hashtable_init(hash_table *h_t) {
	int i;
	for (i = 0; i < HASHTABLESIZE; i++) {
		h_t->Table[i] = NULL;
	}
}

int hash_function(char c) {
	int asc = (int) c;
	if (asc >= 65 && asc <= 90)
		return (asc % 65);
	else
		return ((asc % 97) + 26);
}

int hashtable_insert(hash_table *h_t, file_d *fd) {
	int index;int result = 0;
	file_d* fd_new = (file_d*) malloc(sizeof(file_d));
	fd_new->file_size = fd->file_size;
	strcpy(fd_new->file_name, fd->file_name);
	strcpy(fd_new->file_path, fd->file_path);
	strcpy(fd_new->file_type, fd->file_type);
	//strcpy(fd_new->file_blocks, fd->file_blocks);
	fd_new->file_block_no = fd->file_block_no;
	fd_new->start_addr = fd->start_addr;
	char c = fd->file_name[0];
	index = hash_function(c);
	if (h_t->Table[index]!=NULL)
		result = list_insert(&h_t->Table[index]->next,
				fd_new, fd_new->file_name);
	else {
		l_node* node = (l_node*) malloc(sizeof(l_node));
		node->next = NULL;
		h_t->Table[index] = node;
		result = list_insert(&(h_t->Table[index]->next),
				fd_new, fd_new->file_name);
	}
	if(result == SUCCESS)
		return SUCCESS;
	return FAILURE;
}

int hashtable_delete(hash_table *h_t, file_d *fd) {
	int index;
	char c = fd->file_name[0];
	index = hash_function(c);
	int result = list_delete(&h_t->Table[index]->next,
			fd->file_name);
	return result;
}

int hashtable_search(hash_table *h_t,l_node** result, char* filename) {
	int key;
	void* b = filename;
	l_node *current;
	char c = filename[0];
	key = hash_function(c);
//printf("%d", key);
	if(h_t->Table[key]==NULL)
		return ERRORNOTFOUND;
	current = h_t->Table[key]->next;
	//l_node* result = NULL;
	return list_search(&current, result, filename);
}



