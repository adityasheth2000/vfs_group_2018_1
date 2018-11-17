#ifndef VFS_1_INCLUDED
#define VFS_1_INCLUDED

#define MAX_PATH_SIZE 50
#define MAX_FILE_NAME_SIZE 50 

int vfsmakedir(char parent_path[MAX_PATH_SIZE],
		char dir_name[MAX_FILE_NAME_SIZE]);

int vfslistdir(char *, int , char *);

int vfsupdatefile(char *, char *);

#endif // VFS_H_INCLUDED
