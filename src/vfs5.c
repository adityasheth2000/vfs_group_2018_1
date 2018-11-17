#include "../include/vfs5.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <errno.h>
#include <ctype.h>
#include <sys/stat.h>

#include "../include/linkedlist.h"
#include "../include/narytree.h"
#include "../include/hashtable.h"
#include "../include/binarysearchtree.h"
#include "../include/error_code.h"
#include "../include/vfs.h"
#include "../include/global.h"
#include "../include/vfs_errorcodes.h"
#include "../include/printhelper.h"
#include "../include/general_vfs_op.h"

global* globaldata;

int vfscreate(char label[], long int size) {
	//checking "DATA_FILE_ALREADY_EXISTS" 1
	errno = 0;
	FILE* p = fopen(label, "rb");
	if (errno == 0) {
		//fclose(p);
		return CREATEVFS_DATA_FILE_ALREADY_EXISTS;
	}

	if (p != NULL )
		fclose(p);

	//when erro == 13 Permission denied  "CANNOT_CREATE_DATAFILE" 2
	if (errno == 13)
		return CREATEVFS_CANNOT_CREATE_DATAFILE;

	//checking "INVALID_CHARACTER_IN_NAME" 4
	int i;
	if (strlen(label) > 30)
		return CREATEVFS_VFS_LABEL_TOO_LARGE;
	for (i = 0; i < strlen(label); i++) {
		if (label[i] == '/')
			return CREATEVFS_INVALID_CHARACTER_IN_NAME;
	}

	//checking "INVALID_SIZE" 5
	if (size < 1 || size > 1024)
		return CREATEVFS_INVALID_SIZE;

	vfs main_header;
	file_d fd;
	list l;
	int flag = 0;

	//when errno =2 path does not exist  "CANNOT_CREATE_DATAFILE" 2
	if (errno == 2)
		flag = 1;
	FILE* fp = fopen(label, "wb+");

	//when errno =28 checking "NOT_ENOUGH_MEMORY" 3
	if (errno == 28) {
		remove(label);
		return CREATEVFS_NOT_ENOUGH_MEMORY;
	}

	//when errno =2 path does not exist  "CANNOT_CREATE_DATAFILE" 2
	if (errno == 2 && flag != 1) {
		remove(label);
		return CREATEVFS_CANNOT_CREATE_DATAFILE;
	}

	/*---------Adding data in the main header---------*/

	strcpy(main_header.vfs_label, label);
	main_header.vfs_size = size * 1024;
	main_header.num_f_d_used = 0;
	main_header.block_size = sizeof(block);
	main_header.no_of_blocks = (int) main_header.vfs_size
			/ main_header.block_size;
	main_header.max_num_f_d = main_header.no_of_blocks;
	main_header.freelistPoint = sizeof(main_header) + 1;
	main_header.file_d_arrayPoint = sizeof(main_header)
			+ (sizeof(struct free_list) * main_header.no_of_blocks) + 1;
	main_header.datablkPoint = sizeof(struct virtual_file_system)
			+ ((sizeof(struct file_descriptor)) * main_header.max_num_f_d)
			+ (sizeof(struct free_list) * main_header.no_of_blocks) + 1;

	/*---------writing main header---------*/

	fwrite(&main_header, sizeof(main_header), 1, fp);

	if (errno == 28) {
		remove(label);
		return CREATEVFS_NOT_ENOUGH_MEMORY;
	}
	/*----------writing free List-------------*/

	fseek(fp, main_header.freelistPoint, SEEK_SET);
	if (errno == 28) {
		remove(label);
		return CREATEVFS_NOT_ENOUGH_MEMORY;
	}
	for (i = 0; i < main_header.no_of_blocks; i++) {
		l.block_num = i;
		l.isFull = 'n';
		fwrite(&l, sizeof(l), 1, fp);
		if (errno == 28) {
			remove(label);
			return CREATEVFS_NOT_ENOUGH_MEMORY;
		}
	}

	/*---------writing file descriptors---------*/

	fseek(fp, main_header.file_d_arrayPoint, SEEK_SET);
	if (errno == 28) {
		remove(label);
		return CREATEVFS_NOT_ENOUGH_MEMORY;
	}
	//Initializing file descriptor
	fd.file_name[0] = '\0';
	fd.file_path[0] = '\0';
	fd.file_type[0] = '\0';
	fd.file_size = -1;

	for (i = 0; i < main_header.max_num_f_d; i++) {
		fd.start_addr = main_header.datablkPoint
				+ (i * sizeof(struct data_block));
		fd.file_block_no = i;
		fwrite(&fd, sizeof(fd), 1, fp);
		if (errno == 28) {
			remove(label);
			return CREATEVFS_NOT_ENOUGH_MEMORY;
		}
	}

	/*---------writing data blocks---------*/
	fseek(fp, main_header.datablkPoint, SEEK_SET);
	block blk;
	for (i = 0; i < main_header.no_of_blocks; i++) {
		//blk.next = ftell(fp) + main_header.block_size;
		blk.data[0] = '\0';
		fwrite(&blk, sizeof(blk), 1, fp);
		if (errno == 28) {
			remove(label);
			return CREATEVFS_NOT_ENOUGH_MEMORY;
		}
	}

	fclose(fp);
	return 0;
}


int vfsdeletedir(char *P1) {
	//removing slash from path
	P1 = removeslash(P1);
	//check if file system is mounted 
	if (ismounted != 1) {
		return MAKEDIR_VFS_NOT_MOUNTED;
	}
	//check directory is empty
	if (strcmp(P1, "/") == 0)
		return DELETEDIR_DIRECTORY_IS_NOT_EMPTY;
	int res = -1;
	/*printf("\ninorder in deletedir\n");
	 inorder(globaldata->root_bst);*/
	char *dir_Name;
	char *dir_Path;
	bst_node* fd;
	dir_Path = (char *) malloc(sizeof(char) * 1024);
	fd = bst_find(globaldata->root_bst, P1);
	//checking if directory excisting after searching in bst
	if (fd == NULL )
		return DELETEDIR_CANNOT_FIND_SPECIFIED_DIR;
	if (strcmp(fd->data->file_type, "DIR") != 0)
		return DELETEDIR_CANNOT_FIND_SPECIFIED_DIR;
	char* temp = strrchr(fd->data->file_path, '/');
	char* file_path = (char*) malloc(sizeof(char) * MAX_PATH_SIZE);
	int value = temp - fd->data->file_path + 1;
	strncpy(file_path, fd->data->file_path, value);
	file_path = removeslash(file_path);
	//preparing file discriptor to delete
	file_d* fd1 = prepareFileDescriptor(file_path, fd->data->file_name, "DIR");
	/*to do
		delete fd1 from globaldata
			-globaldata->root_nary
			-globaldata->hash_table
			-globoldata->root_bst
		reduce number of file discriptor used by one stored in globaldata.
	*/
	return 0;

}

int vfsmovefile(char *P1, char *P2) {
	//check if vfs is mounted
	if (ismounted != 1) {
		return MOVEDIR_VFS_NOT_MOUNTED;
	}
	if (strcmp(P1, "/") == 0)
		return DELETEDIR_DIRECTORY_IS_NOT_EMPTY;
	P1 = removeslash(P1);
	P2 = removeslash(P2);

	char *p22 = (char*) malloc((sizeof(char)) * MAX_PATH_SIZE);
	strcpy(p22, P2);
	char *src_Path, *dest_Path;
	src_Path = (char*) malloc(sizeof(char) * MAX_PATH_SIZE);
	dest_Path = (char*) malloc(sizeof(char) * MAX_PATH_SIZE);
	strcpy(src_Path, P1);
	strcpy(dest_Path, P2);
	char *src_Dir;
	src_Dir = (char*) malloc(sizeof(char) * CHARSIZE);
	bst_node *src_fd, *des_fd, *temp_src_fd;
	/*to do
		search for P1 and P2 in bst and store result in scr_fd and des_fd
	*/
	if (src_fd == NULL )
		return MOVEDIR_CANNOT_FIND_SPECIFIED_SOURCEDIR;
	if (des_fd == NULL )
		return MOVEDIR_CANNOT_FIND_SPECIFIED_DESTINATIONDIR;
	if (strcmp(src_fd->data->file_type, "DIR") != 0)
		return MOVEDIR_SOURCE_CANNOT_BE_FILE;
	if (strcmp(des_fd->data->file_type, "DIR") != 0)
		return MOVEDIR_DESTINATION_CANNOT_BE_FILE;
	src_Dir = strrchr(P1, '/');
	strcat(P2, src_Dir);
	temp_src_fd = bst_find(globaldata->root_bst, P2);
	if (temp_src_fd != NULL )
		return MOVEDIR_DESTINATION_ALREADY_HAVE_SOURCE_DIR;
	if (strncmp(P1, p22, strlen(P1)) == 0 && p22[strlen(P1)] == '/')
		return MOVEDIR_CANNOT_MOVE_PARENT_TO_CHILD_DIR;
	nary_move_node(globaldata->root_nary, src_Path, dest_Path);
	update_bst_ht(P1, p22);
	char* lst = strrchr(P1, '/');
	char temp[MAX_PATH_SIZE];
	strcpy(temp, ++lst);
	file_d* bst_fd_insert = prepareFileDescriptor(p23, temp, "DIR");
	file_d* bst_fd_del = prepareFileDescriptor(P1, temp, "DIR");
	/*to do
	insert into bst above file descriptor(bst_fd_insert)
	delete from bst above file descriptor(bst_fd_del)
	*/
	return 0;
}
