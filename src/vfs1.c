#include "../include/vfs1.h"
/*dfajsfjhsdjhfashfjkadsh*/
int vfsmakedir(char parent_path[MAX_PATH_SIZE],
		char dir_name[MAX_FILE_NAME_SIZE]) {
	//checking mount status
	if (ismounted != 1) {
		return MAKEDIR_VFS_NOT_MOUNTED;
	}
	if (globaldata->num_f_d_used >= globaldata->max_num_f_d) {
		return MAKEDIR_FILESYSTEM_FULL;
	}

	int i;
	//checking INVALID_CHARACTER_IN_DIRNAME
	for (i = 0; i < strlen(dir_name); i++) {
		if (dir_name[i] == '/')
			return MAKEDIR_INVALID_CHARACTER_IN_DIRNAME;
	}
	//two continous / should not be there
	for (i = 0; i < strlen(parent_path) - 1; i++) {
		if (parent_path[i] == '/' && parent_path[i + 1] == '/')
			return MAKEDIR_INVALID_CHARACTER_IN_DIRNAME;
	}
	parent_path = removeslash(parent_path);
	if (parent_path[0] != '/') {
		return 11;
	}
	//preparing path variable
	char *qname = (char*) malloc((sizeof(char)) * MAX_PATH_SIZE);
	qname[0] = '\0';
	strcpy(qname, parent_path);
	if (strcmp(parent_path, "/") != 0)
		strcat(qname, "/");
	strcat(qname, dir_name);
	//preparing file descriptor
	file_d* fd = prepareFileDescriptor(qname, dir_name, "DIR");
	bst_node *find;
	/*to do
	search qname in bst and store result in find variable
	*/
	//checking DIRECTORY_ALREADY_EXISTS
	if (find != NULL )
		return MAKEDIR_DIRECTORY_ALREADY_EXISTS;
	//inserting in data structures
	char dir[MAX_FILE_SIZE], path[MAX_PATH_SIZE];
	int dcount = 0, pcount = 0, pathdone = 0, first = 0;
	char fullpath[MAX_PATH_SIZE];
	fullpath[0] = '\0';
	parent_path = removeslash(parent_path);
	strcat(fullpath, parent_path);
	if (strcmp(fullpath, "/") != 0)
		strcat(fullpath, "/");
	strcat(fullpath, dir_name);
	strcat(fullpath, "/");
	for (i = 0; i < strlen(fullpath); i++) {
		if (globaldata->num_f_d_used == globaldata->max_num_f_d) {
			return MAKEDIR_FILESYSTEM_FULL;
		}
		char c = fullpath[i];
		if (c == '/' && i != 0) {
			char file_p[100];
			char * first = strchr(path, '/');
			char * last = strrchr(path, '/');
			if (strcmp(first, last) == 0) {
				strncpy(file_p, last, 1);
			} else {
				strncpy(file_p, first, last - first);
			}
			file_p[last - first] = '\0';
			char dirnametemp[MAX_FILE_SIZE];
			strncpy(dirnametemp, dir, dcount);
			dirnametemp[dcount] = '\0';
			if (file_p[0] == '\0')
				strcpy(file_p, "/");
			file_d* fd = prepareFileDescriptor(file_p, dirnametemp, "DIR");
			bst_node* find1 = bst_find(globaldata->root_bst, path);
			if (find1 == NULL ) {
				globaldata->num_f_d_used = globaldata->num_f_d_used + 1;
				/*to do
				insert file descriptor(fd) into bst, hashtable and nary
				*/		
			}
			dcount = 0;
			//free(dirnametemp);
		} else if (i != 0) {

			dir[dcount] = c;
			dcount++;
		}
		path[pcount] = c;
		pcount++;
		path[pcount] = '\0';

	}
	return 0;
}


int vfslistdir(char *P1, int P2, char *P3) {
	if (ismounted != 1) {
		return LISTDIR_VFS_NOT_MOUNTED;
	}
	P1 = removeslash(P1);
	int ret = -1;
	if (P2 > 1 || P2 < 0)
		return LISTDIR_INVALID_FLAG;
	/*to do
		search P1 path in the bst and store result in the find variable of type bst_node*
	*/
	if (find == NULL )
		return LISTDIR_CANNOT_FIND_SPECIFIED_PATH_OR_DIR;
	ret = nary_list_dir(globaldata->root_nary, P2, P1, P3);
	if (ret != 0)
		return LISTDIR_CANNOT_FIND_SPECIFIED_PATH_OR_DIR;
	return 0;	
}


int vfsupdatefile(char *P1, char *P2) {

	if (ismounted != 1) {
		return UPDATEFILE_VFS_NOT_MOUNTED;
	}
	char data[MAX_FILE_SIZE];
	FILE *source, *fp;
	//checking INTERNAL_FILE_NOT_FOUND and getting the fd for the corresponding file path
	bst_node *find;
	find = bst_find(globaldata->root_bst, P1);
	if (find == NULL )
		return UPDATEFILE_INTERNAL_FILE_NOT_FOUND;

	//checking  EXTERNAL_FILE_NOT_FOUND;
	source = fopen(P2, "r");
	if (source == NULL )
		return UPDATEFILE_EXTERNAL_FILE_NOT_FOUND;

	fp = fopen(globaldata->vfs_label, "rb+");

	//checking EXTERNAL_FILE_TOO_LARGE
	fseek(source, ftell(source), SEEK_END);
	long int size_of_file = ftell(source);
	rewind(source);
	if (size_of_file - 1 > MAX_FILE_SIZE)
		return UPDATEFILE_EXTERNAL_FILE_TOO_LARGE;

	//creating data block and writing it to the vfs
	block blk;
	fread(&(blk.data), size_of_file - 1, 1, source);
	fseek(fp, find->data->start_addr, SEEK_SET);
	errno = 0;
	fwrite(&blk, sizeof(block), 1, fp);
	if (strcmp(strerror(errno), "Success") != 0)
		return UPDATEFILE_CANNOT_WRITE_TO_DATAFILE;
	find->data->file_size = size_of_file - 1;
	//printf("Open error: %s\n\n", strerror(errno));
	fclose(fp);
	fclose(source);
	return 0;

}





