#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define SIZE 	sizeof(char)
#define NMEMB 	1024

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		printf("Usage: %s <src> <dst>\n", argv[0]);
		exit(1);
	}


	FILE *fp_src = fopen(argv[1], "r");
	FILE *fp_dst = fopen(argv[2], "w");
	int read_num = 0;
	int i = 0;
	int diff_val = 'a' - 'A';


	if(fp_src == NULL || fp_dst == NULL)
	{
		perror("fopen()");
		exit(1);
	}

	char buf[SIZE * NMEMB];
	int total = 0;
	long pos1, pos2;
	while(1)
	{
		bzero(buf, SIZE * NMEMB);
		pos1 = ftell(fp_src);
		if((read_num = fread(buf, SIZE, NMEMB, fp_src)) < NMEMB)
		{
			
			for (i = 0; i < read_num; i++) {
				if (buf[i] >= 'A' && buf[i] <= 'Z') {
					buf[i] += diff_val;
				}
			}
			if(feof(fp_src))
			{
				pos2 = ftell(fp_src);
				

				fwrite(buf, pos2-pos1, 1, fp_dst);
				total += (pos2 - pos1);

				printf("copy completed, %d bytes"
					" have been copied.\n", total);
				break;
			}
			else if(ferror(fp_src))
			{
				perror("fread()");
				break;
			}
			
		}
		
		
		for (i = 0; i < read_num; i++) {
			
			if (buf[i] >= 'A' && buf[i] <= 'Z') {
				buf[i] += diff_val;
			}
		}

		fwrite(buf, SIZE, NMEMB, fp_dst);
		total += SIZE*NMEMB;
	}


	fclose(fp_src);
	fclose(fp_dst);

	return 0;
}






