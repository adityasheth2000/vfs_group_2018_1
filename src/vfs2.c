#include "../include/vfs2.h"


int vfsmount(char label[]) {
	//checking mounted status
	if (ismounted == 1) {
		return MOUNTVFS_VFS_ALREADY_MOUNTED;
	}
	int j;
	FILE *fp;
	vfs main_header;
	errno = 0;
	//initilizing all data structure
	globaldata->root_nary = nary_root_init();
	hashtable_init(&globaldata->hash_table);
	globaldata->root_bst = NULL;
	file_d* bstfd = prepareFileDescriptor("", "", "DIR");
	bst_insert(&globaldata->root_bst, bstfd);
	file_d* fd = (file_d*) malloc(sizeof(file_d));
	//file_d *fd;// = (file_d*) malloc(sizeof(file_d));
	//Open a binary file in read mode

	fp = fopen(label, "rb");
	if (fp == NULL )
		return MOUNTVFS_DATA_FILE_NOT_FOUND;

	//set mounted true
	ismounted = 1;
	if (!fread(&main_header, sizeof(main_header), 1, fp)) {
		fclose(fp);
		return MOUNTVFS_CANNOT_READ_FROM_FILE;
	}
	strcpy(globaldata->vfs_label, main_header.vfs_label);
	globaldata->vfs_size = main_header.vfs_size;
	globaldata->no_of_blocks = main_header.no_of_blocks;
	globaldata->block_size = main_header.block_size;
	globaldata->max_num_f_d = main_header.max_num_f_d;
	globaldata->num_f_d_used = main_header.num_f_d_used;
	globaldata->datablkPoint = main_header.datablkPoint;
	globaldata->freelistPoint = main_header.freelistPoint;
	globaldata->file_d_arrayPoint = main_header.file_d_arrayPoint;
	/*if (fseek(fp, main_header.file_d_arrayPoint, SEEK_SET)) {
	 fclose(fp);
	 return MOUNTVFS_CANNOT_READ_FROM_FILE;
	 }*/
	if (errno != 0) {
		fclose(fp);
		return MOUNTVFS_CANNOT_READ_FROM_FILE;
	}
	fseek(fp, main_header.file_d_arrayPoint, SEEK_SET);
	//Read fd and load it on nary tree, BST, hash-table one by one
	for (j = 0; j <= globaldata->num_f_d_used; j++) {
		if (!fread(fd, sizeof(file_d), 1, fp)) {
			fclose(fp);
			return MOUNTVFS_CANNOT_READ_FROM_FILE;
		}
		if (strcmp(fd->file_name, "") != 0) {
			bst_insert(&globaldata->root_bst, fd);
			hashtable_insert(&globaldata->hash_table, fd);
			nary_insert_node(&globaldata->root_nary, fd);
		}

	}
	/*printf("\nn-ary tree:\n");
	 nary_print(globaldata->root_nary);
	 printf("\nhash table:\n");
	 hashtable_print(&globaldata->hash_table);
	 printf("\nInorder traversal for BST:\n");
	 inorder(globaldata->root_bst);*/
	fclose(fp);
	return 0;
	return 0;
}

int vfsremovefile(char *P1) {
	if (ismounted != 1) {
		return REMOVEFILE_VFS_NOT_MOUNTED;
	}
	FILE *fp;
	block blk;
	/*printf("\ninorder in removefile before\n");
	 inorder(globaldata->root_bst);*/
	fp = fopen(globaldata->vfs_label, "rb");
	//printf("inorder in removefile:\n");
	//inorder(globaldata->root_bst);
	//Deleting the data from the block
	bst_node *find = NULL;
	find = bst_find(globaldata->root_bst, P1);

	if (find == NULL )
		return REMOVEFILE_CANNOT_FIND_SPECIFIED_FILE;
	if (strcmp(find->data->file_type, "DIR") == 0)
		return REMOVEFILE_CANNOT_FIND_SPECIFIED_FILE;

	file_d* duplicate = (file_d*) malloc(sizeof(file_d));
	sprintf(duplicate->file_name, "%s", find->data->file_name);
	sprintf(duplicate->file_path, "%s", find->data->file_path);
	duplicate->file_size = find->data->file_size;
	duplicate->start_addr = find->data->start_addr;
	duplicate->file_block_no = find->data->file_block_no;
	sprintf(duplicate->file_type, "%s", find->data->file_type);

	fseek(fp, duplicate->start_addr, SEEK_SET);
	blk.data[0] = '\0';
	fwrite(&blk, sizeof(block), 1, fp);

	//decrementing num of used fd's and changing corresponding free list as empty
	globaldata->num_f_d_used = globaldata->num_f_d_used - 1;
	list l;
	fseek(fp,
			globaldata->freelistPoint
					+ ((duplicate->file_block_no) * sizeof(list)), SEEK_SET);
	l.isFull = 'n';
	l.block_num = duplicate->file_block_no;
	fwrite(&l, sizeof(list), 1, fp);

	//deleting from data structures
	char file_path[100];
	char * first = strchr(duplicate->file_path, '/');
	char * last = strrchr(duplicate->file_path, '/');
	if (strcmp(first, last) == 0) {
		strncpy(file_path, last, 1);
	} else {
		strncpy(file_path, first, last - first);
	}

	file_d* fd1 = prepareFileDescriptor(file_path, duplicate->file_name,
			duplicate->file_type);

	//printf("\ndeleting from nary %s and %s and whole path is %s",fd1->file_path, fd1->file_name, find->data->file_path);
	int res = nary_delete_node(&globaldata->root_nary, fd1);
	/*	hashtable_print(&globaldata->hash_table);*/
	hashtable_delete_fd(&globaldata->hash_table, duplicate);
	/*	hashtable_print(&globaldata->hash_table);*/
	bst_delete(&globaldata->root_bst, duplicate);
	/*printf("\ninorder in removefile after\n");
	inorder(globaldata->root_bst);*/
	return 0;
}

int vfsmovefile(char *P1, char *P2) {
	if (ismounted != 1)
		return MOVEFILE_VFS_NOT_MOUNTED;
	FILE *fp;
	char *name;
	bst_node *source_path;
	fp = fopen(globaldata->vfs_label, "rb+");

	//checking MOVEFILE_CANNOT_FIND_SOURCEFILE and getting the fd for the corresponding file path
	source_path = bst_find(globaldata->root_bst, P1);
	if (source_path == NULL )
		return MOVEFILE_CANNOT_FIND_SOURCEFILE;
	if (strcmp(source_path->data->file_type, "DIR") == 0)
		return MOVEFILE_CANNOT_FIND_SOURCEFILE;

	//checking  MOVEFILE_CANNOT_FIND_DESTINATION_PATH;
	//P2 = removeslash(P2);
	char file_path1[100];
	char * first = strchr(P2, '/');
	char * last = strrchr(P2, '/');
	if (strcmp(first, last) == 0) {
		strncpy(file_path1, last, 1);
	} else {
		strncpy(file_path1, first, last - first);
		file_path1[last - first] = '\0';
	}
	bst_node *destination_path;
	destination_path = bst_find(globaldata->root_bst, file_path1);
	if (destination_path == NULL )
		return MOVEFILE_CANNOT_FIND_DESTINATION_PATH;

	//preparing new fd
	char *type = getFileType(P2);
	name = getFileName(P2);
	// printf("\n\nfile name is %s\n", name);
	file_d* fd = prepareFileDescriptor(file_path1, name, type);
	fd->start_addr = source_path->data->start_addr;
	fd->file_size = source_path->data->file_size;
	fd->file_block_no = source_path->data->file_block_no;

	/* printf("\nsource path: size is %lu, startaddr is %lu, blk num is %lu ",
	 source_path->data->file_size,source_path->data->start_addr,source_path->data->file_block_no);*/

	char* temp1 = strrchr(source_path->data->file_path, '/');
	char file_path[100];
	int value1 = temp1 - source_path->data->file_path; // + 1;
	strncpy(file_path, source_path->data->file_path, value1);
	file_d* fd1 = prepareFileDescriptor(file_path, source_path->data->file_name,
			type);
	fd1->start_addr = source_path->data->start_addr;
	fd1->file_size = source_path->data->file_size;
	fd1->file_block_no = source_path->data->file_block_no;

	/*to do 
		deleting old fd(source_path) from all data structures (nary, hashtable,bst)
	*/

	bst_node *duplicate = bst_find(globaldata->root_bst, P2);
	if (duplicate == NULL ) {
		/*to do
			adding new fd(fd) in all data structures
		*/
	} else //else just update the datablock of the corresponding file
	{
		//decrementing num of used fd's and changing fd corresponding free list as empty
		globaldata->num_f_d_used = globaldata->num_f_d_used - 1;
		list l;
		fseek(fp,
				globaldata->freelistPoint
						+ ((duplicate->data->file_block_no) * sizeof(list)),
				SEEK_SET);
		l.isFull = 'n';
		l.block_num = fd->file_block_no;
		errno = 0;
		fwrite(&l, sizeof(list), 1, fp);
		if (strcmp(strerror(errno), "Success") != 0)
			printf("error in writing to datafile");

		strcpy(duplicate->data->file_name, fd->file_name);
		strcpy(duplicate->data->file_type, fd->file_type);
		strcpy(duplicate->data->file_path, P2);

		duplicate->data->file_size = fd->file_size;
		duplicate->data->start_addr = fd->start_addr;
		duplicate->data->file_block_no = fd->file_block_no;

	}
	/*printf("inorder in movefile");
	 inorder(globaldata->root_bst);*/
	return 0;
}

int vfsexportfile(char *P1, char *P2) {
	if (ismounted != 1) {
		return EXPORTFILE_VFS_NOT_MOUNTED;
	}
	P1 = removeslash(P1);
	block blk;
	FILE *fp, *fp1;
	bst_node *find;

	//checking EXPORTFILE_CANNOT_FIND_SOURCEFILE
	/*to do 
		search P1 in the bst and store result in find
	*/
	if (find == NULL )
		return EXPORTFILE_CANNOT_FIND_SOURCEFILE;

	//checking EXPORTFILE_CANNOT_EXPORT_DIR
	if (strcmp(find->data->file_type, "DIR") == 0)
		return EXPORTFILE_CANNOT_EXPORT_DIR;

	//checking EXPORTFILE_CANNOT_CREATE_OUTPUTFILE
	fp1 = fopen(P2, "w+");
	if (fp1 == NULL )
		return EXPORTFILE_CANNOT_CREATE_OUTPUTFILE;

	fp = fopen(globaldata->vfs_label, "rb");
	if (find != NULL ) {
		fseek(fp, find->data->start_addr, SEEK_SET);
		fread(&blk, sizeof(block), 1, fp);
	}
	fwrite(&blk, find->data->file_size, 1, fp1);
	fclose(fp1);
	fclose(fp);
	return 0;
}

