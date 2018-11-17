#ifndef VFS_H_INCLUDED
#define VFS_H_INCLUDED

#define BLOCK_SIZE 1024
#define MAX_FILE_NAME_SIZE 255
#define MAX_FILE_SYSTEM_LABEL_SIZE 20
#define MAX_PATH_SIZE 200
#define MAX_TYPE_SIZE 10
#define MAX_BLOCKS 20
#define MAX_FILESYSTEMSIZE 1024*1024
#define MAX_FILE_SIZE 100

typedef struct file_descriptor {
	//int file_id;
	char file_name[MAX_FILE_NAME_SIZE];
	char file_path[MAX_PATH_SIZE];
	char file_type[MAX_TYPE_SIZE];
	long int file_size;
	long int file_block_no;
	long int start_addr;
} file_d;

typedef struct virtual_file_system {
	char vfs_label[MAX_FILE_SYSTEM_LABEL_SIZE];
	long int vfs_size;
	long int no_of_blocks;
	long int block_size;
	long int max_num_f_d;
	long int num_f_d_used;
	long int datablkPoint;
	long int freelistPoint;
	long int file_d_arrayPoint;
} vfs;

typedef struct free_list {
	long int block_num;
	char isFull;  //y=full n=not full
} list;

typedef struct data_block {
	//long int block_num;
	char data[MAX_FILE_SIZE];
	long int next;
} block;

char* getFileType(char*);

file_d* prepareFileDescriptor(char *path, char *filename, char *filetype);

#endif // VFS_H_INCLUDED
