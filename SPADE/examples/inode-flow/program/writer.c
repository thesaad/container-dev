#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]){
	char *path;
	int result;
	int fd;
	char buffer[1];
	struct stat path_stat;

	buffer[0] = 'X';

	path = "/tmp/testfile.crossnamespaces";

	fd = open(path, O_CREAT|O_WRONLY, 0666);
	if(fd < 0){
		perror("Failed to open file!");
		return -1;
	}

	result = write(fd, (void *)(&buffer[0]), 1);
	if(result < 0){
		perror("Failed to write file!");
	}else{
		fsync(fd);
	}

        result = fstat(fd, &path_stat);
        if(result < 0){
                perror("Failed to get inode!");
        }else{
                printf("inode(%s) = %ld\n", path, path_stat.st_ino);
        }

	close(fd);

	return 0;
}
