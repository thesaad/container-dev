#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]){
	char *path;
	int result;
	int fd;
	char *buffer;
	int unshareResult;
	struct stat path_stat;

	buffer = (char *)malloc(sizeof(char) * 1);

	unshareResult = unshare(CLONE_NEWIPC);
	if(unshareResult < 0){
		perror("Failed to unshare IPC!");
		return -1;
	}

	path = "/tmp/testfile.crossnamespaces";

	fd = open(path, O_RDONLY);
	if(fd < 0){
		perror("Failed to open file!");
		return -1;
	}

	result = read(fd, (void *)(buffer), 1);
	if(result < 0)
		perror("Failed to read file!");

	result = fstat(fd, &path_stat);
	if(result < 0){
		perror("Failed to get inode!");
	}else{
		printf("inode(%s) = %ld\n", path, path_stat.st_ino);
	}

	close(fd);

	unlink(path);

	return 0;
}
