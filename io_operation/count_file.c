#include <stdio.h>
#include <sys/vfs.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int GetFileNum(char *base_path)
{
	DIR *dir;
	struct dirent *ptr;
	int i = 0;
	int file_num = 0;

	if ((dir = opendir(base_path)) == NULL) {
		//perror("Open dir error...");
		printf("Open dir [%s] error[%s]\n", base_path, strerror(errno));
		return -1;
	}

	while ((ptr = readdir(dir)) != NULL)
	{
		if(strcmp(ptr->d_name,".") == 0 || strcmp(ptr->d_name, "..") == 0) {///current dir OR parrent dir
			continue;
		} 

		file_num++;		
	}

	closedir(dir);
	return file_num;
}

int main(int argc, char **argv)
{
	int num = GetFileNum(argv[1]);
	printf("[%s] -- [%d]\n", argv[1], num);
	return 0;
}
