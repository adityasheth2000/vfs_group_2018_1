#include "../include/binarysearchtree.h"
#include "../include/hashtable.h"
#include "../include/vfs.h"
#include "../include/error_code.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
file_d* mount_vfs_preparefd(char *f_name, char *f_path, char *f_type)
{

		file_d* fd = (file_d*) malloc(sizeof(file_d));
		strcpy(fd->file_name, f_name);
		strcpy(fd->file_path, f_path);
		strcpy(fd->file_type, f_type);
		//int i;
		/*for (i = 0; i < MAX_BLOCKS; i++) {

			fd->file_blocks[i] = f_blocks[i];
		}*/
		return fd;
	}

void main() {

    int j;
	FILE *fp;
	file_d *fd[10];
	fd[0] = mount_vfs_preparefd("bin", "/", "dir");
	fd[1] = mount_vfs_preparefd("etc", "/", "dir");
	fd[2] = mount_vfs_preparefd("usr", "/", "dir");
	fd[3] = mount_vfs_preparefd("home", "/", "dir");
	fd[4] = mount_vfs_preparefd("shilpi", "/home", "dir");
	fd[5] = mount_vfs_preparefd("files", "/home/shilpi", "dir");
	fd[6] = mount_vfs_preparefd("abc.txt", "/home/shilpi/files", "txt");
	fd[7] = mount_vfs_preparefd("abc.pdf", "/home/shilpi/files", "pdf");
	fd[8] = mount_vfs_preparefd("programs", "/home/shilpi", "dir");
	fd[9] = mount_vfs_preparefd("abc.c", "/home/shilpi/programs", "c");

	fp = fopen("mount.bin", "wb");
	if (fp == NULL ) {
		printf("Error opening file\n");
	}
	for (j = 0; j < 10; j++) {
		fwrite(fd[j], sizeof(file_d), 1, fp);
	}
	fclose(fp);
	fp = fopen("mount.bin", "rb");
		for (j = 0; j < 10; j++) {
			fread(fd[j], sizeof(file_d), 1, fp);

		}
	fclose(fp);
	int res=mountvfs("mount.bin");
	if(res==0)
		printf("File system mounted successfully");
	else
		printf("File system not mounted");

}
