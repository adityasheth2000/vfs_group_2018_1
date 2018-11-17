#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/narytree.h"
#include "../include/vfs.h"
#include "../include/printhelper.h"

int main(int argc, char **argv) {
	t_node *root = nary_root_init();
	file_d *fd;
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");
	fd = prepareFileDescriptor("/", "home", "dir");
	int res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("----------------------------------inserted1\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");
	fd = prepareFileDescriptor("/", "usr", "dir");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("----------------------------------inserted2\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");
	fd = prepareFileDescriptor("/", "etc", "dir");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("----------------------------------inserted3\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr", "bin", "dir");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("----------------------------------inserted4\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr", "include", "dir");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("----------------------------------inserted5\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr", "abc.txt", "txt");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("----------------------------------inserted6\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr/include", "xyz.txt", "txt");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("----------------------------------inserted7\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr/include", "vivek", "dir");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("----------------------------------inserted8\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr/include", "ght.txt", "txt");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("----------------------------------inserted9\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");
	fd = prepareFileDescriptor("/vivek/include", "ght.txt", "txt");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("----------------------------------inserted10\n");
	else
		printf("----------------------------------Notinserted10\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr", "ght.txt", "txt");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("----------------------------------inserted11\n");
	else
		printf("----------------------------------Notinserted11\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr/include", "drive", "dir");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("----------------------------------inserted12\n");
	else
		printf("----------------------------------Notinserted12\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr/include/drive", "abc.doc", "doc");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("----------------------------------inserted13\n");
	else
		printf("----------------------------------Notinserted13\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");
	fd = prepareFileDescriptor("/", "home", "dir");
	res = nary_delete_node(&root, fd);
	if (res == 0)
		printf("---------------------------------------------deleted1\n");
	else
		printf("---------------------------------------------Notdeleted1\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr/include", "vivek", "dir");
	res = nary_delete_node(&root, fd);
	if (res == 0)
		printf("---------------------------------------------deleted2\n");
	else
		printf("---------------------------------------------Notdeleted2\n");
	nary_print(root);
	fd = prepareFileDescriptor("/usr", "ght.txt", "txt");
	res = nary_delete_node(&root, fd);
	if (res == 0)
		printf("---------------------------------------------deleted3\n");
	else
		printf("---------------------------------------------Notdeleted3\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr/include/xyz.txt", "df", "dir");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("----------------------------------inserted14\n");
	else
		printf(" ----------------------------------Notinserted14\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr/include/abc/xyz", "pqr", "dir");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("----------------------------------inserted15\n");
	else
		printf(" ----------------------------------Notinserted15\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");
	fd = prepareFileDescriptor("/xyz/me/bb/pp/qq/ww/lol/strv/fghj/trtr", "pqr",
			"dir");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("----------------------------------inserted16\n");
	else
		printf(" ----------------------------------Notinserted16\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");
	fd = prepareFileDescriptor("/", "xyz", "dir");
	res = nary_delete_node(&root, fd);
	if (res == 0)
		printf("---------------------------------------------deleted4\n");
	else
		printf("---------------------------------------------Notdeleted4\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");
	fd = prepareFileDescriptor(NULL, NULL, "dir");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("----------------------------------inserted17\n");
	else
		printf("----------------------------------Notinserted17\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");
	fd = prepareFileDescriptor("mcj", "jhd", "dir");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("----------------------------------inserted18\n");
	else
		printf("----------------------------------Notinserted18\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");
	fd = prepareFileDescriptor("/usr/include/xyz.txt", "jhd", "dir");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("----------------------------------inserted19\n");
	else
		printf("----------------------------------Notinserted19\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");
	fd = prepareFileDescriptor("/", "vivek", "doc");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("----------------------------------inserted20\n");
	else
		printf("----------------------------------Notinserted20\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");
	fd = prepareFileDescriptor("/", "xyz", "dir");
	res = nary_delete_node(&root, fd);
	if (res == 0)
		printf("---------------------------------------------deleted5\n");
	else
		printf("---------------------------------------------Notdeleted5\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");
	fd = prepareFileDescriptor("/", "xyzjhjhj", "dir");
	res = nary_delete_node(&root, fd);
	if (res == 0)
		printf("---------------------------------------------deleted6\n");
	else
		printf("---------------------------------------------Notdeleted6\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");

	fd = prepareFileDescriptor("/", "xyz.txt", "dir");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("---------------------------------------------inserted22\n");
	else
		printf("---------------------------------------------Notinserted22\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");

	fd = prepareFileDescriptor("/", "  ", "dir");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("---------------------------------------------inserted23\n");
	else
		printf("---------------------------------------------Notinserted23\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");

	fd = prepareFileDescriptor("/", " ", "dir");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("---------------------------------------------inserted23\n");
	else
		printf("---------------------------------------------Notinserted23\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");

	fd = prepareFileDescriptor("/usr/include/drive", "abc.doc", "dir");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("---------------------------------------------inserted24\n");
	else
		printf("---------------------------------------------Notinserted24\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");

	fd = prepareFileDescriptor("usr/include/drive/restinpeace", "abc.doc",
			"dir");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("---------------------------------------------inserted26\n");
	else
		printf("---------------------------------------------Notinserted26\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");

	fd = prepareFileDescriptor("//", "abc", "dir");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("---------------------------------------------inserted27\n");
	else
		printf("---------------------------------------------Notinserted27\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");

	fd = prepareFileDescriptor("//vivek", "abc", "dir");
	res = nary_insert_node(&root, fd);
	if (res == 0)
		printf("---------------------------------------------inserted28\n");
	else
		printf("---------------------------------------------Notinserted28\n");
	printf("Printing n-ary tree \n");
	nary_print(root);
	printf("Done\n");


	return 0;
}
