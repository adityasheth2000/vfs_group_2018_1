#ifndef VFS_5_INCLUDED
#define VFS_5_INCLUDED

int vfscreate(char label[], long int size);

int vfsdeletedir(char *P1) ;

int vfsmovefile(char *, char *);

#endif 
