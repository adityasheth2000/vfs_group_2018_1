/*
 * printhelper.h
 *
 *  Created on: 30-Oct-2012
 *      Author: vivek
 */

#ifndef PRINTHELPER_H_
#define PRINTHELPER_H_

#include "../include/linkedlist.h"
#include "../include/narytree.h"
#include "../include/hashtable.h"

void printFileDescriptorLinkedList(l_node* head);

void hashtable_print(hash_table*);

void nary_print(t_node* root);

#endif /* PRINTHELPER_H_ */
