/*************************************************************************************/
/*  C program to implement a binary search tree                                      */
/************************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/binarysearchtree.h"

/*---------Inserts a node in the binary search tree---------*/

int bst_insert(bst_node **node, file_d *key)
{
    int status;
    if((*node) == NULL)
    {
        (*node) = (struct binarysearchtree_node *) malloc(sizeof(struct binarysearchtree_node));
        if((*node) == NULL)
        {
    //        printf( "Out of space!!!" );
        }
        else
        {
            (*node)->data = (file_d*) malloc (sizeof(file_d));
            (*node)->data=initilize_f_d((*node)->data);
            sprintf(((*node)->data)->file_path,"%s",key->file_path);
            ((*node)->data)->file_block_no=key->file_block_no;
            sprintf(((*node)->data)->file_name,"%s",key->file_name);
            ((*node)->data)->file_size = key->file_size;
            ((*node)->data)->start_addr=key->start_addr;
            sprintf(((*node)->data)->file_type,"%s",key->file_type);
            (*node)->left = (*node)->right = NULL;
        }
        return BST_SUCCESSFULL_INSERTION;
    }
    else
    {
        char a[200];
        sprintf(a,"%s",((*node)->data)->file_path);

        if(strcmp(a,key->file_path) > 0)
            status=bst_insert(&((*node)->left), key);

        else if(strcmp(((*node)->data)->file_path,key->file_path) < 0)
            status=bst_insert(&((*node)->right), key);
        else
            return BST_DUPLICATE_INSERTION;
    }
    return status;
}



/*------ Prints inorder traversal of the binary search tree--------*/

void inorder(bst_node *node)
{
    static int i=0;
    if(node==NULL && i==0)
    {
        printf("\ntree is empty\n");
        i++;
    }
    if(node!= NULL)
    {
        i++;
        inorder(node->left);
        printf("%s\t", node->data->file_path);
        inorder(node->right);
    }
}

/*-------Finds a minimum node in the right subtree of the specified node-------*/

bst_node* bst_findMin(bst_node *node)
{
    if(node==NULL)
        return NULL;
    else if(node->left==NULL)
        return node;
    else
        return bst_findMin(node->left);
}


/*------Deletes a node from the binary search tree-------*/

int bst_delete(bst_node **node, file_d *key)
{
    tnode temp_node;
    int st=0;
    temp_node = (struct binarysearchtree_node *) malloc(sizeof(struct binarysearchtree_node));
    if((*node) == NULL)
    {
        return BST_UNSUCCESSFUL_DELETION;
    }

    else if(strcmp((*node)->data->file_path,key->file_path) > 0)
    {
        //Go Left
        st=bst_delete(&(*node)->left, key);
    }
    else if(strcmp((*node)->data->file_path,key->file_path) < 0)
    {
        //Go Right
        st=bst_delete(&(*node)->right, key);
    }
    //if element to be deleted is found
    else if((*node)->left && (*node)->right)
    {
        temp_node=bst_findMin((*node)->right);
        strcpy((*node)->data->file_path,temp_node->data->file_path);
        st=bst_delete(&(*node)->right,temp_node->data);
    }
    else
    {
        temp_node=(*node);
        if((*node)->left==NULL)
            (*node)=(*node)->right;
        else if((*node)->right==NULL)
            (*node)=(*node)->left;
        free(temp_node);
        return BST_SUCCESSFULL_DELETION;
    }
    return st;
}


/*-------Searches the specified node in the binary search tree and returns the node if found------*/

bst_node* bst_find(bst_node *node, char absolute_path[])
{
    if(node == NULL)
        return NULL;
    if(strcmp(node->data->file_path,absolute_path) > 0)
        return bst_find(node->left,absolute_path);
    else if(strcmp(node->data->file_path,absolute_path) < 0)
        return bst_find(node->right,absolute_path);
    return node;
}

/*-------initialize f_d---------*/

file_d* initilize_f_d(file_d* fd)
{
   // fd->file_id=-1;
    fd->file_name[0]='\0';
    fd->file_path[0]='\0';
    fd->file_size=-1;
   // fd->file_block_no=-1;
    return(fd);
}





