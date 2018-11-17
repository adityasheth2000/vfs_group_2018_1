#ifndef NARYTREE_H_INCLUDED
#define NARYTREE_H_INCLUDED

#include <stdio.h>
#include "../include/vfs.h"
#include "../include/constants.h"


typedef struct nary_tree {
	 file_d *data;
	 struct nary_tree *left_child;
	 struct nary_tree *right_sibling;
}t_node;

t_node* nary_root_init();

/**used to create first node in an nary tree that will be the root node**/
int init_root(t_node *root, file_d *data);

/**used to insert a new node*/
int insert_node(t_node **node,file_d *data);

/**used to search for position where node is to be inserted **/
int insert_in_subtree(t_node **node,file_d *data,int index);

/**search in the sibling nodes of a node for the path specified in fd**/
int node_searchInSibling(t_node *root, char data[CHARSIZE],
                         t_node** resultnode,n_op_type operation);


/**allocate memory to node**/
t_node *allocate_node(file_d *data);

/**used to traverse the tree as InOrder,PreOrder,PostOrder,level order
works like ls command in linux file system**/
void n_node_traversal(t_node *root,n_traversal_type order,li_search s_type,FILE *ft);

void list_dir(t_node* root,n_traversal_type traversal,
                      li_search search_type,char *opfile);
/**used to validate thefiledescriptor must be made generic for all datastructures**/
int validate_file_descriptor(file_d *fd);


/**used to delete a node**/
int delete_node(t_node** root, file_d *data);

/**to delete anode from subtree search recursively using this function**/
int delete_from_subtree(t_node** root, file_d* data, int index);

/**to move a subtree source dir to dest directory**/
int  move_from_subtree(t_node* root,file_d *src_dir,file_d *dest_dir);

/**for making tokens**/
int makeTokens(char fp[],char p[][CHARSIZE]);

int unmount_travesal(t_node* root);

int insertDirRecursively(int index,int tokens,char path[][CHARSIZE],
                         t_node *prevnode,int is_child,file_d* data);
t_node* tree_traversal(t_node *root,char path[][CHARSIZE],char* f_type,int flag);


int move_Function(t_node* root,char *srcpath,char *destpath,char *temp_type);

#endif // NARYTREE_H_INCLUDED
