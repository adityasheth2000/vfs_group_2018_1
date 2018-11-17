#include "../include/vfs4.h"

int vfsmovedir(char *P1, char *P2) {

	if (ismounted != 1) {
		return MOVEDIR_VFS_NOT_MOUNTED;
	}
	if (strcmp(P1, "/") == 0)
		return DELETEDIR_DIRECTORY_IS_NOT_EMPTY;
	P1 = removeslash(P1);
	P2 = removeslash(P2);

	/*printf("inorder in movedir before");
	 inorder(globaldata->root_bst);*/
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
	// int ret=move_Function(datastr->ntree,src_Path,dest_Path,"DIR");
	/*  if(mainstr->is_mounted!=5)
	 return 8;*/
	/*printf("bst inorder in movedir\n");
	 inorder(globaldata->root_bst);*/
	/*to do
	search P1 and P2 in the bst and store return result in src_fd and des_fd
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
	file_d* bst_fd_insert = prepareFileDescriptor(p22, temp, "DIR");
	file_d* bst_fd_del = prepareFileDescriptor(P1, temp, "DIR");
	/*to do
	insert bst_fd_insert in the bst
	delete bst_fd_del from the bst
	*/
	return 0;
}



int vfsaddfile(char *P1, char *P2, char *P3) {
if (ismounted != 1) {
		return ADDFILE_FILE_VFS_NOT_MOUNTED;
	}
	P1 = removeslash(P1);
	char ch, qname[MAX_PATH_SIZE];
	FILE *source, *fp;
	list l;
	int i;

	//checking "INVALID_CHARACTER_IN_NAME" 2
	if (strlen(P2) > MAX_FILE_NAME_SIZE || strlen(P2) == 0)
		return ADDFILE_INVALID_CHARACTER_IN_FILENAME;
	for (i = 0; i < strlen(P2); i++) {
		if (P2[i] == '/')
			return ADDFILE_INVALID_CHARACTER_IN_FILENAME;
	}
	//checking FILE_SYSTEM_FULL
	if (globaldata->max_num_f_d == globaldata->num_f_d_used) {
		return ADDFILE_FILE_SYSTEM_FULL;
	}
	strcpy(qname, P1);
	if (strcmp(P1, "/") != 0)
		strcat(qname, "/");
	strcat(qname, P2);

	//checking "FILE_ALREADY_EXISTS" 3
	bst_node *find;
	find = bst_find(globaldata->root_bst, qname);
	if (find != NULL )
		return ADDFILE_FILE_ALREADY_EXISTS;

	bst_node *dir;
	dir = bst_find(globaldata->root_bst, P1);
	if (dir == NULL )
		return ADDFILE_DIRECTORY_DOES_NOT_EXIST; //added by self, no appropriate error code found.

	//checking CANNOT_WRITE_TO_DATAFILE;
	//printf("\n%s\n",P3);
	source = fopen(P3, "rb");
	if (source == NULL )
		return ADDFILE_SOURCE_NOT_FOUND; //added by self, no appropriate error code found.

	//checking  FILE_TOO_LARGE
	fseek(source, ftell(source), SEEK_END);
	long int size_of_file = ftell(source);
	rewind(source);
	if (size_of_file - 1 > MAX_FILE_SIZE)
		return ADDFILE_FILE_TOO_LARGE;

	fp = fopen(globaldata->vfs_label, "rb+");
	char *type = getFileType(P2);
	file_d* fd = prepareFileDescriptor(P1, P2, type); //creating file descriptor without full path
	fseek(fp, globaldata->freelistPoint, SEEK_SET);
	for (i = 0; i < (globaldata->no_of_blocks); i++) {
		fread(&l, sizeof(list), 1, fp);
		if (l.isFull == 'n') {
			fd->file_block_no = l.block_num;
			break;
		}
	}
	//writing the updated data of the list back in the file
	fseek(fp, globaldata->freelistPoint + ((l.block_num) * sizeof(list)),
			SEEK_SET);
	l.isFull = 'y';
	fwrite(&l, sizeof(list), 1, fp);

	fd->start_addr = globaldata->datablkPoint
			+ ((fd->file_block_no) * globaldata->block_size);

	//creating data block and writing it to the vfs
	block blk;
	fread(&(blk.data), size_of_file - 1, 1, source);
	fd->file_size = size_of_file - 1;
	fseek(fp, fd->start_addr, SEEK_SET);
	errno = 0;

	// checking CANNOT_WRITE_TO_DATAFILE
	fwrite(&blk, sizeof(block), 1, fp);
	if (strcmp(strerror(errno), "Success") != 0)
		return ADDFILE_CANNOT_WRITE_TO_DATAFILE;

	//printf("Open error: %s\n\n", strerror(errno));
	fclose(fp);
	fclose(source);
	globaldata->num_f_d_used = globaldata->num_f_d_used + 1;

	//inserting in data structures
	//printf("values to be stored in nary are %s, %s", fd->file_path,fd->file_name);
	/* to do
	insert fd in all the data structure nary,hashtable and bst
	*/


	return 0;

}

int vfscopyfile(char *P1, char *P2) {
	if (ismounted != 1) {
		return COPYFILE_VFS_NOT_MOUNTED;
	}

	FILE *fp;
	fp = fopen(globaldata->vfs_label, "rb+");

	//checking COPYFILE_FILE_SYSTEM_FULL
	if (globaldata->max_num_f_d == globaldata->num_f_d_used)
		return COPYFILE_FILE_SYSTEM_FULL;

	//checking MOVEFILE_CANNOT_FIND_SOURCEFILE and getting the fd for the corresponding file path
	bst_node *source_path;
	source_path = bst_find(globaldata->root_bst, P1);
	//temp = source_path;
	if (source_path == NULL )
		return COPYFILE_CANNOT_FIND_SOURCEFILE;

	//checking  COPYFILE_CANNOT_COPY_DIR_TO_FILE;
	if (strcmp(source_path->data->file_type, "DIR") == 0)
		return COPYFILE_CANNOT_COPY_DIR_TO_FILE;

	//checking  COPYFILE_CANNOT_FIND_DESTINATION_PATH;
	char file_path1[100];
	char * first = strchr(P2, '/');
	char * last = strrchr(P2, '/');
	if (strcmp(first, last) == 0) {
		strncpy(file_path1, last, 1);
		file_path1[strlen(last)] = '\0';
	} else {
		strncpy(file_path1, first, last - first);
		file_path1[last - first] = '\0';
	}
	bst_node *destination_path;
	destination_path = bst_find(globaldata->root_bst, file_path1);
	if (destination_path == NULL )
		return COPYFILE_CANNOT_FIND_DESTINATIONPATH;

	bst_node *duplicate = bst_find(globaldata->root_bst, P2);
	if (duplicate == NULL ) {
		//preparing new fd
		char *type = getFileType(P2);
		char *name = getFileName(P2);
		file_d* fd = prepareFileDescriptor(file_path1, name, type);
		int i;
		list l;
		//getting free block
		fseek(fp, globaldata->freelistPoint, SEEK_SET);
		for (i = 0; i < (globaldata->no_of_blocks); i++) {
			fread(&l, sizeof(list), 1, fp);
			if (l.isFull == 'n') {
				fd->file_block_no = l.block_num;
				break;
			}
		}
		//writing the updated data of the list back in the file
		fseek(fp, globaldata->freelistPoint + ((l.block_num) * sizeof(list)),
				SEEK_SET);
		l.isFull = 'y';
		fwrite(&l, sizeof(list), 1, fp);

		fd->start_addr = globaldata->datablkPoint
				+ ((fd->file_block_no) * globaldata->block_size);

		//creating data block and writing it to the vfs
		block blk;
		fseek(fp, source_path->data->start_addr, SEEK_SET);
		fread(&(blk.data), source_path->data->file_size, 1, fp);
		fd->file_size = source_path->data->file_size;
		fseek(fp, fd->start_addr, SEEK_SET);
		fwrite(&blk, sizeof(block), 1, fp);
		if (strcmp(strerror(errno), "Success") != 0)
			return ADDFILE_CANNOT_WRITE_TO_DATAFILE; //return something if error while writing
		//printf("Open error: %s\n\n", strerror(errno));
		fclose(fp);
		globaldata->num_f_d_used = globaldata->num_f_d_used + 1;

		//inserting in data structures
		int res = nary_insert_node(&globaldata->root_nary, fd);
		hashtable_insert(&globaldata->hash_table, fd);
		bst_insert(&globaldata->root_bst, fd);

	} else {
		//else just update the datablock of the corresponding file
		//decrementing num of used fd's and changing fd corresponding free list as empty

		block blk;
		fseek(fp, source_path->data->start_addr, SEEK_SET);
		fread(&(blk.data), source_path->data->file_size, 1, fp);
		duplicate->data->file_size = source_path->data->file_size;
		fseek(fp, duplicate->data->start_addr, SEEK_SET);
		fwrite(&blk, sizeof(block), 1, fp);
		if (strcmp(strerror(errno), "Success") != 0)
			return ADDFILE_CANNOT_WRITE_TO_DATAFILE; //return something if error while writing
		fclose(fp);

	}

	return 0;	
}


