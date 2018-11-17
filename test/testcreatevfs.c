#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/binarysearchtree.h"
#include "../include/hashtable.h"
#include "../include/vfs.h"
#include "../include/vfs_errorcodes.h"

int main() {
	long int i;
	struct virtual_file_system main_header;
	struct free_list l;
	struct file_descriptor fd;
	FILE *fp;
	/*----------------------------------Creating VFS-----------------------------------------*/
	/*---------------------------------------------------------------------------------------*/

	printf("\nCreating dummy VFS");
	char* res = vfscreate("demo1", 1024 * 1024);
/*	if (strcmp(res, ERR_VFS_CREATE_01) == 0) {
		printf("\nExiting due to error: DATA_FILE_ALREADY_EXISTS");
		return 0;
	}
	if (strcmp(res, ERR_VFS_CREATE_02) == 0) {
		printf("\nExiting due to error: CANNOT_CREATE_DATAFILE");
		return 0;
	}
	if (strcmp(res, ERR_VFS_CREATE_03) == 0) {
		printf("\nExiting due to error: NOT_ENOUGH_MEMORY");
		return 0;
	}
	if (strcmp(res, ERR_VFS_CREATE_04) == 0) {
		printf("\nExiting due to error: INVALID_CHARACTER_IN_NAME");
		return 0;
	}
	if (strcmp(res, ERR_VFS_CREATE_05) == 0) {
		printf("\nExiting due to error: INVALID_SIZE");
		return 0;
	}*/

	fp = fopen("demo1", "rb+");

	/*---------------------printing main_header after reading from binary file ---------------*/

	fread(&main_header, sizeof(struct virtual_file_system), 1, fp);
	printf("\nIn test case:\nSize created is %lu", main_header.vfs_size);
	printf("\nsize of max f_d is %lu", main_header.max_num_f_d);
	printf("\nsize of max blks is %lu", main_header.no_of_blocks);
	printf("\nDatablk point is %lu", main_header.datablkPoint);
	printf("\nfreelist point is %lu", main_header.freelistPoint);
	printf("\nf_d point is %lu", main_header.file_d_arrayPoint);
	printf("\nsize of one block is %lu", main_header.block_size);


	/*---------------------printing free list after reading from binary file ---------------*/

	fseek(fp, main_header.freelistPoint+(4*sizeof(list)), SEEK_SET);
	for (i = 0; i < 10; i++) {
		fread(&l, sizeof(struct free_list), 1, fp);
		printf("\nblock number is %lu and isfull value is %c", l.block_num,
				l.isFull);
	}

	/*---------------------printing file descriptors after reading from binary file ---------------*/

	fseek(fp, main_header.file_d_arrayPoint, SEEK_SET);
	for (i = 0; i < 10; i++) {
		fread(&fd, sizeof(struct file_descriptor), 1, fp);
		printf("\nfd values are:--------file name is %s", fd.file_name);
		printf(".....start addr is %lu and block number is %lu", fd.start_addr,
				fd.file_block_no);
	}
	fclose(fp);

}
