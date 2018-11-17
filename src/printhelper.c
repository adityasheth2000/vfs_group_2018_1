
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "../include/linkedlist.h"
#include "../include/narytree.h"
#include "../include/hashtable.h"
#include "../include/printhelper.h"
#include "../include/vfs.h"

void printFileDescriptorLinkedList(l_node* head) {
	l_node *current = head;
	while (current != NULL ) {
		file_d* f = (file_d*) (current->data);
		printf("%s - > ", (*f).file_name);
		current = current->next;
	}
	printf("\n");
}

void hashtable_print(hash_table *h_t) {
	int i;
	for (i = 0; i < HASHTABLESIZE; i++) {
		printf("%d -> ", i);
		if (h_t->Table[i] != NULL ) {
			printFileDescriptorLinkedList(h_t->Table[i]->next);//list_print(h_t->Table[i]->next);
		}
		printf("\n");
	}
}

void nary_print(t_node* root) {
	if (root == NULL )
		return;
	if (strcmp(root->data->file_name, "/") == 0) {
		printf("%s\n", root->data->file_path);
		nary_print(root->left_child);
		return;
	}
	printf("%s %s\n", root->data->file_path, root->data->file_name);
	nary_print(root->left_child);
	t_node* node = root;
	while (node->right_sibling != NULL ) {
		printf("%s %s\n", node->right_sibling->data->file_path,
				node->right_sibling->data->file_name);
		node = node->right_sibling;
		nary_print(node->left_child);
	}
	return;
}

