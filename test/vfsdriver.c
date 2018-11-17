/*
 * File: vfsdriver.c
 *
 * Description: This is a driver program for testing your VFS system using an interaction script as input
 * You need to make additional calls to your respective functions as noted in the comments below
 * Make sure the output you display is exactly as per the given specifications for you. Do NOT print
 * any extra output (like debug messages) in the final version of your driver program. You can use this driver program
 * in a in incremental manner as you keep implementing one operator after another. For operators not yet implemented,
 * you can leave the output as given ("TO_BE_DONE"). So you can use this program as your "main" program for testing purposes.
 *
 * DO NOT write the full code for operators in the driver program! You must only CALL your functions from here.
 *
 * Usage: vfsdriver <scriptfilename>
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFSIZE 200
#define CMDSIZE 30
#define PARSIZE 100
#include "../include/global.h"
#include "../include/vfs_errorcodes.h"

extern global* globaldata;

void createvfs(char *P1, int P2);
void mountvfs(char *P1);
void unmountvfs(char *P1);
void makedir(char *P1, char *P2);
void deletedir(char *P1);
void movedir(char *P1, char *P2);
void listdir(char *P1, int P2, char *P3);
void addfile(char *P1, char *P2, char *P3);
void listfile(char *P1, char *P2);
void updatefile(char *P1, char *P2);
void removefile(char *P1);
void movefile(char *P1, char *P2);
void copyfile(char *P1, char *P2);
void exportfile(char *P1, char *P2);
void searchfile(char *P1, char *P2);

void processcommand(char *command, char *P1, char *P2, char *P3);

int main(int argc, char *argv[]) {
	printf(
			"#################################################################################################################################\n#\t\t\t\t\tCOMMANDS\t\t\t\t  #\t\t    ERRORS\t\t\t#\n#################################################################################################################################\n");
	globaldata = (global*) malloc(sizeof(global));
	FILE *scriptfp;
	char linebuffer[BUFSIZE];
	char command[CMDSIZE], par1[PARSIZE], par2[PARSIZE], par3[PARSIZE];
	char *token;

	if (argc != 2) {
		fprintf(stderr, "Usage: vfsdriver <scriptfile>\n");
		return (1);
	}

	if ((scriptfp = fopen(argv[1], "r")) == NULL ) {
		fprintf(stderr, "Unable to open script file: %s\n", argv[1]);
		return (2);
	}

	while (fgets(linebuffer, sizeof(linebuffer), scriptfp) != NULL ) {
		/* This output is for debugging... do not uncomment in final version */
		/*
		 printf("==================================================\n");
		 printf("Processing: %s", linebuffer);
		 printf("==================================================\n");
		 */

		/* Remove the extra newline character in the end of line */
//		linebuffer[strlen(linebuffer)] = ' ';
		linebuffer[strlen(linebuffer) - 1] = '\0';
		/* Get the command and the parameters using tokenizer */
		strcpy(command, (token = strtok(linebuffer, " ")) == NULL ? "" : token);

		strcpy(par1, (token = strtok(NULL, " ")) == NULL ? "" : token);
		strcpy(par2, (token = strtok(NULL, " ")) == NULL ? "" : token);
		strcpy(par3, (token = strtok(NULL, " ")) == NULL ? "" : token);
		/*printf("Command:%s:p1:%s:p2:%s:p3:%s\n",command, par1, par2, par3);*/
		processcommand(command, par1, par2, par3);
	}
	return 0;
}

void processcommand(char *command, char *P1, char *P2, char *P3) {
	if (strcmp(command, "createvfs") == 0) {
		int size = atoi(P2);
		createvfs(P1, size);
	} else if (strcmp(command, "mountvfs") == 0)
		mountvfs(P1);
	else if (strcmp(command, "unmountvfs") == 0)
		unmountvfs(P1);
	else if (strcmp(command, "makedir") == 0)
		makedir(P1, P2);
	else if (strcmp(command, "deletedir") == 0)
		deletedir(P1);
	else if (strcmp(command, "movedir") == 0)
		movedir(P1, P2);
	else if (strcmp(command, "listdir") == 0) {
		int flag = atoi(P2);
		listdir(P1, flag, P3);
	} else if (strcmp(command, "addfile") == 0)
		addfile(P1, P2, P3);
	else if (strcmp(command, "listfile") == 0)
		listfile(P1, P2);
	else if (strcmp(command, "updatefile") == 0)
		updatefile(P1, P2);
	else if (strcmp(command, "removefile") == 0)
		removefile(P1);
	else if (strcmp(command, "movefile") == 0)
		movefile(P1, P2);
	else if (strcmp(command, "copyfile") == 0)
		copyfile(P1, P2);
	else if (strcmp(command, "exportfile") == 0)
		exportfile(P1, P2);
	else if (strcmp(command, "searchfile") == 0)
		searchfile(P1, P2);
	else
		printf("Ignoring invalid command %s\n", command);
}

void createvfs(char *P1, int P2) {
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
//	printf("createvfs_TO_BE_DONE\n");
	char *temp = "createvfs";
	printf("#\t %s %30s %30d  #   ", temp, P1, P2);
	int result = vfscreate(P1, P2);
	switch (result) {
	case 1:
		ERR_VFS_CREATE_01
		break;
	case 2:
		ERR_VFS_CREATE_02
		break;
	case 3:
		ERR_VFS_CREATE_03
		break;
	case 4:
		ERR_VFS_CREATE_04
		break;
	case 5:
		ERR_VFS_CREATE_05
		break;
	default:
		printf("SUCCESS\n");
		break;
	}

}

void mountvfs(char *P1) {
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
//	printf("mountvfs_TO_BE_DONE\n");
	char *temp = "mountvfs";
	printf("#\t  %s  %60s  #   ", temp, P1);
	int result = vfsmount(P1);
	switch (result) {
	case 1:
		ERR_VFS_MOUNT_01
		break;
	case 2:
		ERR_VFS_MOUNT_02
		break;
	case 3:
		ERR_VFS_MOUNT_03
		break;
	default:
		printf("SUCCESS\n");
		break;
	}
}

void unmountvfs(char *P1) {
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	printf("unmountvfs_TO_BE_DONE\n");
}

void makedir(char *P1, char *P2) {
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	//printf("makedir_TO_BE_DONE\n");
	char *temp = "makedir";
	printf("#\t   %s %30s %30s  #   ", temp, P1, P2);
	int result = vfsmakedir(P1, P2);
	switch (result) {
	case 1:
		ERR_VFS_MAKEDIR_01
		break;
	case 2:
		ERR_VFS_MAKEDIR_02
		break;
	case 3:
		ERR_VFS_MAKEDIR_03
		break;
	default:
		printf("SUCCESS\n");
		break;
	}
}

void deletedir(char *P1) {
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	printf("deletedir_TO_BE_DONE\n");
}

void movedir(char *P1, char *P2) {
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	printf("movedir_TO_BE_DONE\n");
}

void listdir(char *P1, int P2, char *P3) {
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	printf("listdir_TO_BE_DONE\n");
}

void addfile(char *P1, char *P2, char *P3) {
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	//printf("addfile_TO_BE_DONE\n");
	char *temp = "addfile";
	printf("#\t   %s %30s %30s %30s #   ", temp, P1, P2, P3);
	int result = vfsaddfile(P1, P2, P3);
	switch (result) {
	case 1:
		ERR_VFS_ADDFILE_01
		break;
	case 2:
		ERR_VFS_ADDFILE_02
		break;
	case 3:
		ERR_VFS_ADDFILE_03
		break;
	case 4:
		ERR_VFS_ADDFILE_04
		break;
	default:
		printf("SUCCESS\n");
		break;
	}
}

void listfile(char *P1, char *P2) {
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	char *temp = "listfile";
	printf("#\t   %s %30s %30s #   ", temp, P1, P2);
	int result = vfslistfile(P1, P2);
	switch (result) {
	case 1:
		ERR_VFS_LISTFILE_01
		break;
	case 2:
		ERR_VFS_LISTFILE_02
		break;
	case 3:
		ERR_VFS_LISTFILE_03
		break;
	case 4:
		ERR_VFS_LISTFILE_04
		break;
	case 5:
		ERR_VFS_LISTFILE_05
		break;
	default:
		printf("SUCCESS\n");
		break;
	}
}

void updatefile(char *P1, char *P2) {
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	//printf("updatefile_TO_BE_DONE\n");
	char *temp = "updatefile";
	printf("#\t   %s %30s %30s #   ", temp, P1, P2);
	int result = vfsupdatefile(P1, P2);
	switch (result) {
	case 1:
		ERR_VFS_UPDATEFILE_01
		break;
	case 2:
		ERR_VFS_UPDATEFILE_02
		break;
	case 3:
		ERR_VFS_UPDATEFILE_03
		break;
	case 4:
		ERR_VFS_UPDATEFILE_04
		break;
	default:
		printf("SUCCESS\n");
		break;
	}
}

void removefile(char *P1) {
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	char *temp = "removefile";
	printf("#\t %s %30s #   ", temp, P1);
	int result = vfsremovefile(P1);
	switch (result) {
	case 1:
		ERR_VFS_REMOVEFILE_01
		;
		break;
	default:
		printf("SUCCESS\n");
		break;
	}
}

void movefile(char *P1, char *P2) {
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	printf("movefile_TO_BE_DONE\n");
}

void copyfile(char *P1, char *P2) {
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	printf("copyfile_TO_BE_DONE\n");
}

void exportfile(char *P1, char *P2) {
	/* Call the appropriate function with given arguments and display appropriate output on the screen */

	printf("exportfile_TO_BE_DONE\n");
}

void searchfile(char *P1, char *P2) {
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	char *temp = "searchfile";
	printf("#\t %s %30s %30s #   ", temp, P1, P2);
	int result = vfssearchfile(P1,P2);
	switch (result) {
	case 1:
		ERR_VFS_SEARCHFILE_00
		;
		break;
	case 2:
		ERR_VFS_SEARCHFILE_02
		;
		break;
	default:
		printf("SUCCESS\n");
		break;
	}
}

