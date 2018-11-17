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

file_d* prepareFileDescriptor(char *path, char *filename, char *filetype) {
	file_d* dir = (file_d*) malloc(sizeof(file_d));
	if (path == NULL || filename == NULL ) {
		dir = NULL;
		return dir;
	}
	dir->file_size = 10;
	strcpy(dir->file_name, filename);
	strcpy(dir->file_path, path);
	strcpy(dir->file_type, filetype);
//	dir->file_blocks[0] = 12;
	return dir;
}


char* getFileType(char* P1) {
	char tokens[MAX_PATH_SIZE][MAX_FILE_NAME_SIZE];
	globaldata->num_f_d_used = globaldata->num_f_d_used + 1;
	char* token;
	char filepath[20];
	int num_token = 0;
	sprintf(filepath, "%s", P1);
	token = strtok(filepath, "/");
	while (token != NULL ) {
		strcpy(tokens[num_token], token);
		token = strtok(NULL, "/");
		num_token++;
	}
	sprintf(filepath, "%s", tokens[num_token - 1]);
	num_token = 0;
	token = strtok(filepath, ".");
	while (token != NULL ) {
		strcpy(tokens[num_token], token);
		token = strtok(NULL, "/");
		num_token++;
	}
	return tokens[num_token - 1];
}
