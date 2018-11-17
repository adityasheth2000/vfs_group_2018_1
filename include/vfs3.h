#ifndef VFS_3_INCLUDED
#define VFS_3_INCLUDED

int vfsunmount(char label[]);

int vfslistfile(char *, char *);

int vfssearchfile(char *, char *);

#endif 
