#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#define HASHTABLESIZE 256

#define SUCCESS 0
#define FAILURE -1

#include "../include/linkedlist.h"
#include "../include/vfs.h"
#include "../include/error_code.h"

typedef struct hash_table {
	l_node* Table[HASHTABLESIZE];
} hash_table;

void hashtable_init(hash_table *);
int hash_function(char);
int hashtable_insert(hash_table *, file_d *);
int hashtable_search(hash_table*, l_node** , char[]);
int hashtable_delete(hash_table*, file_d *);

#endif // HASHTABLE_H_INCLUDED
