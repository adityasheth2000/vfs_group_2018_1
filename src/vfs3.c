#include "../include/vfs3.h"


int vfsunmount(char* label) {
	FILE *fp;
	vfs main_header;
	if (ismounted != 1) {
		return UNMOUNTVFS_VFS_NOT_MOUNTED;
	}
	if (ismounted == 1) {
		if (strcmp(globaldata->vfs_label, label) != 0)
			return UNMOUNTVFS_DATA_FILE_NOT_FOUND;
	}
	fp = fopen(label, "wb+");
	if (fp == NULL )
		return UNMOUNTVFS_DATA_FILE_NOT_FOUND;

	/*if (fseek(fp, main_header.file_d_arrayPoint, SEEK_SET)) {
	 unmount_setglobals();
	 fclose(fp);
	 return UNMOUNTVFS_CANNOT_WRITE_TO_FILE;
	 }*/
	strcpy(main_header.vfs_label, globaldata->vfs_label);
	main_header.vfs_size = globaldata->vfs_size;
	main_header.no_of_blocks = globaldata->no_of_blocks;
	main_header.block_size = globaldata->block_size;
	main_header.max_num_f_d = globaldata->max_num_f_d;
	main_header.num_f_d_used = globaldata->num_f_d_used;
	main_header.datablkPoint = globaldata->datablkPoint;
	main_header.freelistPoint = globaldata->freelistPoint;
	main_header.file_d_arrayPoint = globaldata->file_d_arrayPoint;
	//errno = 0;
	if (!fwrite(&main_header, sizeof(main_header), 1, fp)) {
		//printf("error is %s", strerror(errno));
		unmount_setglobals();
		fclose(fp);
		return UNMOUNTVFS_CANNOT_WRITE_TO_FILE;
	}
	rewind(fp);
	/*if (!fseek(fp, main_header.freelistPoint, SEEK_SET)) {
	 unmount_setglobals();
	 fclose(fp);
	 return UNMOUNTVFS_CANNOT_WRITE_TO_FILE;
	 }*/
	int i;
	/*list l;
	 for (i = 0; i < main_header.no_of_blocks; i++) {
	 l.block_num = i;
	 l.isFull = 'n';
	 if (!fwrite(&l, sizeof(l), 1, fp)) {
	 unmount_setglobals();
	 fclose(fp);
	 return UNMOUNTVFS_CANNOT_WRITE_TO_FILE;
	 }
	 }*/
	fseek(fp, main_header.file_d_arrayPoint, SEEK_SET);
	//file_d* fd = (file_d*) malloc(sizeof(file_d));

	file_d* result = (file_d*) malloc(sizeof(file_d) * main_header.max_num_f_d);
	for (i = 0; i < main_header.max_num_f_d; i++) {
		//sprintf(result[i].file_path, "%s", "");
		result[i].file_path[0] = '\0';
		result[i].file_block_no = i;
		//sprintf(result[i].file_name, "%s", "");
		result[i].file_name[0] = '\0';
		result[i].file_size = 0;
		result[i].start_addr = main_header.datablkPoint
				+ (i * sizeof(struct data_block));
		//sprintf(result[i].file_type, "%s", "");
		result[i].file_type[0] = '\0';
	}
	// = unmount_travesal_nary(globaldata->root_nary, -1, result);
	bstcount = -1;
	int count = unmount_travesal_bst(globaldata->root_bst, result);
	file_d fd;
	//inorder(globaldata->root_bst);
	/*for (i = 0; i <= globaldata->num_f_d_used; i++) {
	 printf("\nresult %d - file path is  %s and file_name is %s\n", i,
	 result[i].file_path, result[i].file_name);
	 }*/
	for (i = 0; i <= count; i++) {
		/*	fd.start_addr = main_header.datablkPoint
		 + (i * sizeof(struct data_block));
		 fd.file_block_no = i;*/
		/*char file_path1[100];
		 file_path1[0]='\0';*/
		char *file_path1 = (char*) malloc(sizeof(char) * MAX_PATH_SIZE);
		char * first = strchr(result[i].file_path, '/');
		char * last = strrchr(result[i].file_path, '/');
		if (strcmp(first, last) == 0) {
			strncpy(file_path1, first, 1);
			file_path1[strlen(last)] = '\0';
		} else {
			strncpy(file_path1, first, last - first);
			file_path1[last - first] = '\0';
		}
		strcpy(result[i].file_path, file_path1);
		file_d fd;
		fd.file_block_no = result[i].file_block_no;
		strcpy(fd.file_name, result[i].file_name);
		strcpy(fd.file_path, result[i].file_path);
		fd.file_size = result[i].file_size;
		strcpy(fd.file_type, result[i].file_type);
		fd.start_addr = result[i].start_addr;
		if (strcmp(result[i].file_name, "") != 0)
			if (!fwrite(&fd, sizeof(fd), 1, fp)) {
				unmount_setglobals();
				fclose(fp);
				return UNMOUNTVFS_CANNOT_WRITE_TO_FILE;
			}
		/*if (!fwrite(&result, sizeof(fd), 1, fp)) {
		 unmount_setglobals();
		 fclose(fp);
		 return UNMOUNTVFS_CANNOT_WRITE_TO_FILE;
		 }*/
	}
	for (i = count + 1; i < main_header.max_num_f_d; i++) {
		if (!fwrite(&result[i], sizeof(fd), 1, fp)) {
			unmount_setglobals();
			fclose(fp);
			return UNMOUNTVFS_CANNOT_WRITE_TO_FILE;
		}
	}
	fclose(fp);
	unmount_setglobals();
	return 0;
}


int vfslistfile(char *P1, char *P2) {
	if (ismounted != 1) {
		return LISTFILE_VFS_NOT_MOUNTED;
	}
	block blk;
	FILE *fp, *fp1;
	bst_node *find;

	//checking LISTFILE_NOT_A_TEXT_FILE
	char *type = getFileType(P1);
	if (strcmp(type, "txt") != 0)
		return LISTFILE_NOT_A_TEXT_FILE;
	if (strcmp(type, "") == 0)
		return LISTFILE_NOT_A_TEXT_FILE;

	//checking LISTFILE_SOURCE_FILE_PATH_NOT_FOUND
	/*to do
	search P1 in the bst and store result in find 
	*/
	//printf("\nP1 searched in find is  %s\n",find->data->file_path);

	if (find == NULL )
		return LISTFILE_SOURCE_FILE_PATH_NOT_FOUND;

	//checking LISTFILE_CANNOT_CREATE_OUTPUTFILE
	fp1 = fopen(P2, "w");
	if (fp1 == NULL )
		return LISTFILE_CANNOT_CREATE_OUTPUTFILE;

	fp = fopen(globaldata->vfs_label, "rb");
	if (find != NULL ) {
		fseek(fp, find->data->start_addr, SEEK_SET);
		fread(&blk, sizeof(block), 1, fp);
	}
 	/*to do
	use fwrite to store data in fp1 and then close fp1 and fb
	*/	
	return 0;

}


int vfssearchfile(char *P1, char *P2) {
	if (ismounted != 1) {
		return SEARCHFILE_VFS_NOT_MOUNTED;
	}
	//hash_table ht;
	l_node* result = NULL;
	//hashtable_print(&globaldata->hash_table);
	/*to do
	search file(P1) in the hash table and store result in result variable
	*/
	//printFileDescriptorLinkedList(result);
	FILE* fp = fopen(P2, "w");
	if (fp == NULL ) {
		return 11;
	}
	*count = 0;
	int cnt = 0;
	l_node *current = result;
	while (current != NULL ) {
		file_d* f = (file_d*) (current->data);
		if (strcmp((*f).file_type, "DIR") != 0) {
			char p[100];
			sprintf(p, "%s\n", (*f).file_path);
			cnt = cnt + 1;
			//printf("%s\n",p);
			fputs(p, fp);
		}
		current = current->next;
	}
	//printf("count is %d", cnt);
	(*count) = cnt;
	fclose(fp);
	//printf("Done\n");
	return 0;
}


