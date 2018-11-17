#ifndef GENERAL_VFS_OP_H_INCLUDED
#define GENERAL_VFS_OP_H_INCLUDED
#include "../include/binarysearchtree.h"
#include "../include/vfs.h"
#include "../include/narytree.h"
#include "../include/hashtable.h"

int validate_name(char name[]);
int if_valid_args_(char *p);
int if_valid_flag_(char p);
file_d* insertIntoFD(char *path, char *filename,char *filetype);

int populate(hash_table* ht,t_node* n_root,bst_node* bst,file_d* fd);

int remove_fd_(hash_table* ht,t_node* n_root,bst_node* bst,file_d* fd);
#endif // GENERAL_VFS_OP_H_INCLUDED
