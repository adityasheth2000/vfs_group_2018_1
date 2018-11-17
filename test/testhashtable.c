#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#include "../include/hashtable.h"
#include "../include/printhelper.h"

int main() {
	printf("testing hash_table:init\n");
	hash_table ht;
	hashtable_init(&ht);
	printf("done!\n");
	printf("testing hash_table:hashfunction\n");
	char s = 'a';
	int i = hash_function(s);
	printf("Index is %d", i);
	printf("\n done!\n");
	printf("testing hash_table:insert\n");
	l_node* result = NULL;
	result = NULL;
	file_d *fd;
	fd = prepareFileDescriptor("/", "home", "dir");
	int res = 0;
	res = res = hashtable_insert(&ht, fd);
	if (res == 0)
		printf("----------------------------------inserted1\n");
	printf("Printing Hash Table \n");
	hashtable_print(&ht);
	printf("Done\n");
	fd = prepareFileDescriptor("/", "usr", "dir");
	res = hashtable_insert(&ht, fd);
	if (res == 0)
		printf("----------------------------------inserted2\n");
	printf("Printing Hash Table \n");
	hashtable_print(&ht);
	printf("Done\n");
	fd = prepareFileDescriptor("/", "etc", "dir");
	res = hashtable_insert(&ht, fd);
	if (res == 0)
		printf("----------------------------------inserted3\n");
	printf("Printing Hash Table \n");
	hashtable_print(&ht);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr", "bin", "dir");
	res = hashtable_insert(&ht, fd);
	if (res == 0)
		printf("----------------------------------inserted4\n");
	printf("Printing Hash Table \n");
	hashtable_print(&ht);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr", "include", "dir");
	res = hashtable_insert(&ht, fd);
	if (res == 0)
		printf("----------------------------------inserted5\n");
	printf("Printing Hash Table \n");
	hashtable_print(&ht);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr", "abc.txt", "txt");
	res = hashtable_insert(&ht, fd);
	if (res == 0)
		printf("----------------------------------inserted6\n");
	printf("Printing Hash Table \n");
	hashtable_print(&ht);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr/include", "xyz.txt", "txt");
	res = hashtable_insert(&ht, fd);
	if (res == 0)
		printf("----------------------------------inserted7\n");
	printf("Printing Hash Table \n");
	hashtable_print(&ht);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr/include", "vivek", "dir");
	res = hashtable_insert(&ht, fd);
	if (res == 0)
		printf("----------------------------------inserted8\n");
	printf("Printing Hash Table \n");
	hashtable_print(&ht);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr/include", "ght.txt", "txt");
	res = hashtable_insert(&ht, fd);
	if (res == 0)
		printf("----------------------------------inserted9\n");
	printf("Printing Hash Table \n");
	hashtable_print(&ht);
	printf("Done\n");
	fd = prepareFileDescriptor("/vivek/include", "ght.txt", "txt");
	res = hashtable_insert(&ht, fd);
	if (res == 0)
		printf("----------------------------------inserted10\n");
	else
		printf("----------------------------------Notinserted10\n");
	printf("Printing Hash Table \n");
	hashtable_print(&ht);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr", "ght.txt", "txt");
	res = hashtable_insert(&ht, fd);
	if (res == 0)
		printf("----------------------------------inserted11\n");
	else
		printf("----------------------------------Notinserted11\n");
	printf("Printing Hash Table \n");
	hashtable_print(&ht);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr/include", "drive", "dir");
	res = hashtable_insert(&ht, fd);
	if (res == 0)
		printf("----------------------------------inserted12\n");
	else
		printf("----------------------------------Notinserted12\n");
	printf("Printing Hash Table \n");
	hashtable_print(&ht);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr/include/drive", "abc.doc", "doc");
	res = hashtable_insert(&ht, fd);
	if (res == 0)
		printf("----------------------------------inserted13\n");
	else
		printf("----------------------------------Notinserted13\n");
	printf("Printing Hash Table \n");
	hashtable_print(&ht);
	printf("Done\n");
	fd = prepareFileDescriptor("/", "home", "dir");
	res =hashtable_delete(&ht, fd);
	if (res == 0)
		printf("---------------------------------------------deleted1\n");
	else
		printf("---------------------------------------------Notdeleted1\n");
	printf("Printing Hash Table \n");
	hashtable_print(&ht);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr/include", "vivek", "dir");
	res =hashtable_delete(&ht, fd);
	if (res == 0)
		printf("---------------------------------------------deleted2\n");
	else
		printf("---------------------------------------------Notdeleted2\n");
	hashtable_print(&ht);
	fd = prepareFileDescriptor("/usr", "ght.txt", "txt");
	res =hashtable_delete(&ht, fd);
	if (res == 0)
		printf("---------------------------------------------deleted3\n");
	else
		printf("---------------------------------------------Notdeleted3\n");
	printf("Printing Hash Table \n");
	hashtable_print(&ht);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr/include/xyz.txt", "df", "dir");
	res = hashtable_insert(&ht, fd);
	if (res == 0)
		printf("----------------------------------inserted14\n");
	else
		printf(" ----------------------------------Notinserted14\n");
	printf("Printing Hash Table \n");
	hashtable_print(&ht);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr/include/abc/xyz", "pqr", "dir");
	res = hashtable_insert(&ht, fd);
	if (res == 0)
		printf("----------------------------------inserted15\n");
	else
		printf(" ----------------------------------Notinserted15\n");
	printf("Printing Hash Table \n");
	hashtable_print(&ht);
	printf("Done\n");
	fd = prepareFileDescriptor("/xyz/me/bb/pp/qq/ww/lol/strv/fghj/trtr", "pqr",
			"dir");
	res = hashtable_insert(&ht, fd);
	if (res == 0)
		printf("----------------------------------inserted16\n");
	else
		printf(" ----------------------------------Notinserted16\n");
	printf("Printing Hash Table \n");
	hashtable_print(&ht);
	printf("Done\n");
	fd = prepareFileDescriptor("/", "xyz", "dir");
	res = hashtable_delete(&ht, fd);
	if (res == 0)
		printf("---------------------------------------------deleted4\n");
	else
		printf("---------------------------------------------Notdeleted4\n");
	printf("Printing Hash Table \n");
	hashtable_print(&ht);
	printf("Done\n");
	/*fd = prepareFileDescriptor(NULL, NULL, "dir");
	res = hashtable_insert(&ht, fd);
	if (res == 0)
		printf("----------------------------------inserted17\n");
	else
		printf("----------------------------------Notinserted17\n");
	printf("Printing Hash Table \n");
	hashtable_print(&ht);
	printf("Done\n");*/
	fd = prepareFileDescriptor("mcj", "jhd", "dir");
	res = hashtable_insert(&ht, fd);
	if (res == 0)
		printf("----------------------------------inserted18\n");
	else
		printf("----------------------------------Notinserted18\n");
	printf("Printing Hash Table \n");
	hashtable_print(&ht);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr/include/xyz.txt", "jhd", "dir");
	res = hashtable_insert(&ht, fd);
	if (res == 0)
		printf("----------------------------------inserted19\n");
	else
		printf("----------------------------------Notinserted19\n");
	printf("Printing Hash Table \n");
	hashtable_print(&ht);
	printf("Done\n");
	fd = prepareFileDescriptor("/", "vivek", "doc");
	res = hashtable_insert(&ht, fd);
	if (res == 0)
		printf("----------------------------------inserted20\n");
	else
		printf("----------------------------------Notinserted20\n");
	printf("Printing Hash Table \n");
	hashtable_print(&ht);
	printf("Done\n");
	fd = prepareFileDescriptor("/", "xyz", "dir");
	res =hashtable_delete(&ht, fd);
	if (res == 0)
		printf("---------------------------------------------deleted5\n");
	else
		printf("---------------------------------------------Notdeleted5\n");
	printf("Printing Hash Table \n");
	hashtable_print(&ht);
	printf("Done\n");
	fd = prepareFileDescriptor("/", "xyzjhjhj", "dir");
	res = hashtable_delete(&ht, fd);
	if (res == 0)
		printf("---------------------------------------------deleted6\n");
	else
		printf("---------------------------------------------Notdeleted6\n");
	printf("Printing Hash Table \n");
	hashtable_print(&ht);
	printf("Done\n");
	printf("---------------------------------------------searching pqr\n");
	hashtable_search(&ht, &result, "pqr");
	printFileDescriptorLinkedList(result);
	printf("Done\n");
	printf("---------------------------------------------searching usr\n");
	result = NULL;
	hashtable_search(&ht, &result, "usr");
	printFileDescriptorLinkedList(result);
	printf("Done\n");
	printf(
			"---------------------------------------------searching usrnfbfbhgf\n");
	result = NULL;
	hashtable_search(&ht, &result, "usrnfbfbhgf");
	printFileDescriptorLinkedList(result);
	printf("Done\n");
	return EXIT_SUCCESS;
}

