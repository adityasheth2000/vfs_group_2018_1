#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "../include/vfs.h"

#define BST_SUCCESSFULL_INSERTION 0
#define BST_DUPLICATE_INSERTION 1
#define BST_SUCCESSFULL_DELETION 0
#define BST_UNSUCCESSFUL_DELETION 1


typedef struct binarysearchtree_node
{
    file_d *data;
    struct binarysearchtree_node *left;
    struct binarysearchtree_node *right;
}bst_node;

typedef struct binarysearchtree_node *tnode;

//search in bst on the basis of absolute path and return the node
bst_node* bst_find(bst_node* , char absolute_path[]);

//insert a node in bst and returns the status(0=inserted, 1=duplicate)
int bst_insert(bst_node **node , file_d *);

//delete a node in tree and returns the status(0=deleted 1=unsuccessful deletion)
int bst_delete(bst_node** , file_d*);

//prints inorder traversal of tree
void inorder( bst_node*);

//finds next successor
bst_node* bst_findMin(bst_node*);

//initialize the f_d
file_d* initilize_f_d(file_d* fd);


#endif // BINARYSEARCHTREE_H
