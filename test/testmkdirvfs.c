#include "../include/binarysearchtree.h"
#include "../include/hashtable.h"
#include "../include/vfs.h"
#include "../include/error_code.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	/*--------------------------------make directory-------------------------*/
	/*-----------------------------------------------------------------------*/
	int res = vfsmakedir("/", "home");
	if (res == VFS_04_SUCCESS) {
		printf("Directroy created");
	} else
		//if(res=VFS_04_FAILURE_OTHER_REASON)
		printf("Directory not created");
	return 0;
}

