#ifndef CONSTANTS_H
#define CONSTANTS_H

#define CHARSIZE 256
#define DATASIZE 1024
#define PATHSIZE 256
#define TYPESIZE 4
#define ARRAYSIZE 50
#define FILESIZE 1024
#define MAXFD 100
#define MAXSIZE 1000000
#define BLOCKSIZE 1024

#define YES 1
#define NO 0

//bst
#define SUCCESSFUL 1
//#define UNSUCCESSFUL 0
#define INVALID -1

//debug
#define DEBUG 0
#define DISPLAY 1
//create/mount
#define CREATE 0
#define MOUNT 1

//ht:
#define MAXNODE 52
//nary




typedef enum {
  IN_ORDER,
  PRE_ORDER,
  POST_ORDER,
  LEVEL_ORDER
} n_traversal_type;

typedef enum {
    N_DELETE,
    N_INSERT,
    N_SEARCH
} n_op_type;

typedef enum{
IS_DIR,
IS_FILE
}li_search;
#endif
