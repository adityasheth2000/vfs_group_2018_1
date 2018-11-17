/*
 * global.h
 *
 *  Created on: 30-Oct-2012
 *      Author: vivek
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "../include/hashtable.h"
#include "../include/narytree.h"
#include "../include/binarysearchtree.h"

typedef struct globalStruct {
 	hash_table hash_table;
	t_node *root_nary;
	bst_node *root_bst;
	char vfs_label[MAX_FILE_SYSTEM_LABEL_SIZE];
	long int vfs_size;
	long int no_of_blocks;
	long int block_size;
	long int max_num_f_d;
	long int num_f_d_used;
	long int datablkPoint;
	long int freelistPoint;
	long int file_d_arrayPoint;
} global;

#endif /* GLOBAL_H_ */
