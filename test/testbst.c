#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/binarysearchtree.h"
#include "../include/vfs.h"


int main()
{
    //printf("print 1");
    int ch;
    file_d *aa;    //object of the struct file_descriptor
    bst_node *find=NULL;
    bst_node *root=NULL;
    aa = (file_d*) malloc (sizeof(file_d));
    aa = initilize_f_d(aa);
    find = (struct binarysearchtree_node *) malloc(sizeof(struct binarysearchtree_node));
    int i;
    char a[200];
/*--------------------testcase 1--------------------*/

/*---------deleting a node--------------*/
    printf("\n\ndeleting element jan");
    strcpy(aa->file_path,"jan");
    i=bst_delete(&root,aa);  //deleting the node from the tree whose file_path=mar
    if(i==BST_SUCCESSFULL_DELETION)
        printf("\nsuccessfully deleted");
    if(i==BST_UNSUCCESSFUL_DELETION)
        printf("\nDeletion unsuccessful. Element not found");
    printf("\n\nInorder travsersal:\n");
    inorder(root);

/*---------inserting 12 nodes in the tree----------*/
    char test_data[13][200]= {"jan","feb","mar","apr","may","jun","jly","aug","sep","oct","nov","dec","dec"};
    for(i=0; i<13; i++)
    {
        sprintf(aa->file_path,"%s",test_data[i]);
        ch = bst_insert(&root,aa); //calls the insert function to insert the node in the tree
        if(ch==BST_SUCCESSFULL_INSERTION)
            printf("\nnode %s successfully inserted",aa->file_path);
        if(ch==BST_DUPLICATE_INSERTION)
            printf("\nnode %s already exists",aa->file_path);
    }
    printf("\n\nInorder travsersal:\n");
    inorder(root);   //inorder walk of the tree

/*---------deleting a node--------------*/
    printf("\n\ndeleting element mar");
    strcpy(aa->file_path,"mar");
    i=bst_delete(&root,aa);  //deleting the node from the tree whose file_path=mar
    if(i==BST_SUCCESSFULL_DELETION)
        printf("\nsuccessfully deleted");
    if(i==BST_UNSUCCESSFUL_DELETION)
        printf("\nDeletion unsuccessful");
    printf("\n\nInorder travsersal after deletion:\n");
    inorder(root);

/*----------searching a node------------*/
    printf("\n\nsearching element jly\n");
    strcpy(a,"jly");
    find=bst_find(root,a);  //searches for the node having key "jly"
    if(find!=NULL)
        printf("Element %s found\n",find->data->file_path);
    else
        printf("Element %s not found",a);

/*-----------searching another node which was deleted----------*/
    strcpy(a,"mar");
    printf("\nsearching for element %s\n",a);
    find=bst_find(root,a);
    if(find!=NULL)
        printf("Element %s found\n",find->data->file_path);
    else
        printf("Element %s not found\n",a);

/*---------deleting a node--------------*/
    printf("\n\ndeleting element jan");
    strcpy(aa->file_path,"jan");
    i=bst_delete(&root,aa);  //deleting the node from the tree whose file_path=mar
    if(i==BST_SUCCESSFULL_DELETION)
        printf("\nsuccessfully deleted");
    if(i==BST_UNSUCCESSFUL_DELETION)
        printf("\nDeletion unsuccessful. Element not found");
    printf("\n\nInorder travsersal after deletion:\n");
    inorder(root);
    printf("\n Root is %s",root->data->file_path);

/*--------end of test case 1------------------*/
}






