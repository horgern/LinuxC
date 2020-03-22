include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <assert.h>

#include "thread_pool.h"


int copyfile(int fd_src, int fd_dst)
{
	char *buf = calloc(1, BUFSIZE);
	int nread, nwrite, ntotal=0;

	while(1)
	{
		bzero(buf, BUFSIZE);
		nread = read(fd_src, buf, BUFSIZE);
		if(nread == 0)
			break;
		else if(nread == -1)
		{
			perror("read error");
			return -1;
		}
		
		char *p = buf;
		while(nread > 0)
		{
			nwrite = write(fd_dst, p, nread);
			nread -= nwrite;
			p += nwrite;
			ntotal += nwrite;
		}
	}

	return ntotal;
}

void *mytask(void *arg)
{
	int *fd = (int *)arg;

	copyfile(fd[0], fd[1]);

	close(fd[0]);
	close(fd[1]);

	free(fd);

	return NULL;
}




void copydir(thread_pool *pool,
		const char *dir_src, const char *dir_dst) // ~/copy ../xx  test/yy
{
	assert(pool);
	assert(dir_src);
	assert(dir_dst);

	char *abs_ori = calloc(1, PATHSIZE); //  /home/gec
	char *abs_src = calloc(1, PATHSIZE); //  /home/xx
	char *abs_dst = calloc(1, PATHSIZE); //  /home/gec/test/yy

	getcwd(abs_ori, PATHSIZE);

	chdir(dir_src);
	getcwd(abs_src, PATHSIZE);

	chdir(abs_ori);
	mkdir(dir_dst, 0777);
	chdir(dir_dst);
	getcwd(abs_dst, PATHSIZE);

	DIR *dp_src;
	while((dp_src=opendir(abs_src)) == NULL && errno == EMFILE)usleep(1000);

	if(dp_src == NULL)
	{
		printf("[%d] opendir() %s failed: %s\n", __LINE__,
			abs_src, strerror(errno));
		return;
	}

	
	struct dirent *ep;
	struct stat *file_info;

	printf("abs_ori: %s\n", abs_ori);
	printf("abs_src: %s\n", abs_src);
	printf("abs_dst: %s\n", abs_dst);

	while(1)
	{
		chdir(abs_src);

		ep = readdir(dp_src);
		if(ep == NULL)
		{
			closedir(dp_src);
			break;
		}
		else if(!strcmp(ep->d_name, ".") ||
			!strcmp(ep->d_name, ".."))
			continue;

		file_info = calloc(1, sizeof(struct stat));
		stat(ep->d_name, file_info);
		
		
		if(S_ISDIR(file_info->st_mode))
		{
			chdir(abs_dst);
			mkdir(ep->d_name, 0777);
			chdir(ep->d_name);

			char *path = calloc(1, PATHSIZE);
			getcwd(path, PATHSIZE);

			chdir(abs_src);

			/* copy sub-directory recursively */
			copydir(pool, ep->d_name, path);
			free(path);
		}
		
		else if(S_ISREG(file_info->st_mode))
		{
			int *fd = calloc(2, sizeof(int));

			while((fd[0]=open(ep->d_name, O_RDONLY)) == -1
					&& errno==EMFILE)usleep(1000);
			if(fd[0] == -1)
			{
				printf("[%d] open() %s failed: %s\n", __LINE__,
					ep->d_name, strerror(errno));
				free(fd);
				continue;
			}
	
			chdir(abs_dst);
			while((fd[1]=open(ep->d_name, O_WRONLY|O_CREAT|O_TRUNC, 0644)) == -1
					&& errno==EMFILE)usleep(1000);
			if(fd[1] == -1)
			{
				printf("[%d] open() %s failed: %s\n", __LINE__,
					ep->d_name, strerror(errno));
				close(fd[0]);
				free(fd);
				continue;
			}
	
			add_task(pool, mytask, (void *)fd);
		}
	}
		
	free(abs_ori);
	free(abs_src);
	free(abs_dst);
	printf("[%d]\n", __LINE__);
		
}
		

int main(int argc, char **argv) // ./mycp xxx yyy
{
	if(argc != 3)
		exit(0);
		
	// 1, initialize the pool
	thread_pool *pool = malloc(sizeof(thread_pool));
	init_pool(pool, 100);
	
	struct stat *file_info = calloc(1, sizeof(struct stat));
	stat(argv[1], file_info);
	
	// 2, throw tasks
	if(S_ISREG(file_info->st_mode))
	{
		int *fd = calloc(2, sizeof(int));
		fd[0] = open(argv[1], O_RDONLY);
		fd[1] = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0644);
		add_task(pool, mytask, (void *)fd);
	}
	else if(S_ISDIR(file_info->st_mode))
	{
		copydir(pool, argv[1], argv[2]);
	}
	else
		printf("file format is NOT supported.\n");

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	