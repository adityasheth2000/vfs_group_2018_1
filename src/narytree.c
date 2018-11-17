//#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/narytree.h"
#include "../include/error_code.h"

t_node* nary_getT_node(file_d *fd) {
	t_node* temp = (t_node*) malloc(sizeof(t_node));
	temp->data = (file_d*) malloc(sizeof(file_d));
	temp->data->file_size = fd->file_size;
	strcpy(temp->data->file_name, fd->file_name);
	strcpy(temp->data->file_path, fd->file_path);
	strcpy(temp->data->file_type, fd->file_type);
	//sprintf(temp->data->file_path,"%s",fd->file_path);
	return temp;
}

t_node* nary_copyT_node(t_node* node) {
	t_node* temp = (t_node*) malloc(sizeof(t_node));
	temp->data = (file_d*) malloc(sizeof(file_d));
	temp->data->file_size = node->data->file_size;
	strcpy(temp->data->file_name, node->data->file_name);
	strcpy(temp->data->file_path, node->data->file_path);
	return temp;
}

t_node* nary_root_init() {
	t_node* root = (t_node*) malloc(sizeof(t_node));
	root->data = (file_d*) malloc(sizeof(file_d));
	strcpy(root->data->file_path, "/");
	strcpy(root->data->file_name, "/");
	strcpy(root->data->file_type, "dir");
	root->left_child = NULL;
	root->right_sibling = NULL;
	return root;
}

int nary_findinsibling(t_node *root, char data[], t_node** resultnode) {
	if (root->right_sibling == NULL )
		return NOTFOUND;
	t_node* node = root;
	while (node->right_sibling != NULL ) {
		if (strcmp(node->right_sibling->data->file_name, data) == 0
				&& strcmp(node->right_sibling->data->file_type, "dir") == 0) {
			*resultnode = node->right_sibling;
			return FOUND;
		}
		node = node->right_sibling;
	}
	return NOTFOUND;
}


int nary_insert_node_final(t_node** root, file_d* data, int token_index) {
	static char path[MAX_PATH_SIZE][MAX_FILE_NAME_SIZE];
	static int num_token = 0;
	int res;
	t_node* resultnode;
	if (token_index == -1) {
		char* token;
		num_token = 0;
		char temp[MAX_PATH_SIZE];
		strcpy(temp, data->file_path);
		token = strtok(temp, "/");
		while (token != NULL ) {
			strcpy(path[num_token], token);
			token = strtok(NULL, "/");
			num_token++;
		}
		res = nary_insert_node_final(&(*root)->left_child, data, ++token_index);
		if (res == FOUND)
			return INSERTEDSUCCESSFULLY;
		else
			return INVALIDPATH;
	}
	if (token_index == num_token) {
		if (*root == NULL ) {
			*root = nary_getT_node(data);
			(*root)->left_child = NULL;
			(*root)->right_sibling = NULL;
			return INSERTEDSUCCESSFULLY;
		} else {
			t_node* node = nary_getT_node(data);
			node->left_child = NULL;
			node->right_sibling = (*root)->right_sibling;
			(*root)->right_sibling = node;
			return INSERTEDSUCCESSFULLY;
		}
	} else if (strcmp((*root)->data->file_name, path[token_index]) != 0
			&& (res = nary_findinsibling(*root, path[token_index], &resultnode))
					!= 0) {
		file_d *fd = prepareFileDescriptor((*root)->data->file_path,
				path[token_index], "dir");
		t_node* node = nary_getT_node(fd);
		node->left_child = NULL;
		node->right_sibling = (*root)->right_sibling;
		(*root)->right_sibling = node;
		t_node** pre = &((*root)->right_sibling);
		t_node** current = &((*root)->right_sibling->left_child);
		token_index++;
		while (token_index < num_token) {
			char temp[MAX_PATH_SIZE];
			strcpy(temp, (*pre)->data->file_path);
			if (strcmp(temp, "/") != 0)
				strcat(temp, "/");
			strcat(temp, (*pre)->data->file_name);
			fd = prepareFileDescriptor(temp, path[token_index], "dir");
			*current = nary_getT_node(fd);
			(*current)->left_child = NULL;
			(*current)->right_sibling = NULL;
			pre = current;
			current = &((*current)->left_child);
			token_index++;
			//free(temp);
		}
		*current = nary_getT_node(data);
		(*current)->left_child = NULL;
		(*current)->right_sibling = NULL;
		return INSERTEDSUCCESSFULLY;
	}

	else if (strcmp((*root)->data->file_name, path[token_index]) == 0
			&& strcmp((*root)->data->file_type, "dir") == 0) {
		res = nary_insert_node_final(&(*root)->left_child, data, ++token_index);

	} else {
		resultnode = (t_node*) malloc(sizeof(t_node));
		res = nary_findinsibling(*root, path[token_index], &resultnode);
		if (res == FOUND) {
			res = nary_insert_node_final(&(resultnode->left_child), data,
					++token_index);
		} else
			return INVALIDPATH;
	}
	if (res == FOUND)
		return INSERTEDSUCCESSFULLY;
	else
		return INVALIDPATH;
}

int nary_insert_node(t_node** root, file_d* data) {
	if (data == NULL )
		return INVALIDDATA;
	if (root == NULL || *root == NULL )
		return INVALIDROOT;
	if ((int) (*root)->data->file_path[0] != 47)
		return INVALIDROOT;
	if ((int) data->file_path[0] != 47)
		return INVALIDROOT;
	int res;
	res = nary_insert_node_final(root, data, -1);
	return res;
}

int nary_findinsiblingprevious(t_node *root, char data[], t_node** resultnode) {
	if (root->right_sibling == NULL )
		return NOTFOUND;
	t_node* node = root;
	while (node->right_sibling != NULL ) {
		if (strcmp(node->right_sibling->data->file_name, data) == 0) {
			*resultnode = node;
			return FOUND;
		}
		node = node->right_sibling;
	}
	return NOTFOUND;
}

int nary_delete_node_final(t_node** root, file_d* data, int token_index) {
	static char path[MAX_PATH_SIZE][MAX_FILE_NAME_SIZE];
	static int num_token = 0;
	if (token_index == -1) {
		char* token;
		num_token = 0;
		char temp[MAX_PATH_SIZE];
		strcpy(temp, data->file_path);
		token = strtok(temp, "/");
		while (token != NULL ) {
			strcpy(path[num_token], token);
			token = strtok(NULL, "/");
			num_token++;
		}
		int res = nary_delete_node_final(&(*root)->left_child, data,
				++token_index);
		if (res == FOUND)
			return DELETEDSUCCESSFULLY;
		else
			return INVALIDPATH;
	}
	if (token_index == num_token) {
		if (*root == NULL ) {
			return NOTFOUND;
		} else {
			if (strcmp((*root)->data->file_name, data->file_name) == 0) {
				*root = (*root)->right_sibling;
				return DELETEDSUCCESSFULLY;
			} else {
				t_node* resultnode;
				resultnode = (t_node*) malloc(sizeof(t_node));
				int res = nary_findinsiblingprevious(*root, data->file_name,
						&resultnode);
				if (res == FOUND) {
					//if( token_index == i)
					resultnode->right_sibling =
							resultnode->right_sibling->right_sibling;
					return DELETEDSUCCESSFULLY;
				} else
					return INVALIDPATH;
			}
		}
	}
	int res;
	if (strcmp((*root)->data->file_name, path[token_index]) == 0) {
		res = nary_delete_node_final(&(*root)->left_child, data, ++token_index);

	} else {
		t_node* resultnode;
		resultnode = (t_node*) malloc(sizeof(t_node));
		int res = nary_findinsibling(*root, path[token_index], &resultnode);
		if (res == FOUND) {
			//if( token_index == i)
			res = nary_delete_node_final(&(resultnode->left_child), data,
					++token_index);
		} else
			return INVALIDPATH;
	}
	if (res == FOUND)
		return INSERTEDSUCCESSFULLY;
	else
		return INVALIDPATH;
}

int nary_delete_node(t_node** root, file_d* data) {
	int res = nary_delete_node_final(root, data, -1);
	return res;
}
