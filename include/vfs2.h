#ifndef VFS_2_INCLUDED
#define VFS_2_INCLUDED

int vfsmount(char label[]);

int vfsremovefile(char *);

int vfsexportfile(char *, char *);

#endif 
