#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char string[] = "String from file";
	char *str_buf;
	FILE *fp;
	size_t num_wr,num_r;
	int seek;

	fp = fopen("output.txt", "w+");
	if(fp == NULL)
		printf("open");

	num_wr = fwrite(string, sizeof(string), 1, fp);
	
	if(num_wr == 0)
		printf("write");

	str_buf = (char*) malloc(sizeof(char));

	for(int i = 0;i <= strlen(string);i++)
	{
		seek = fseek(fp, (-1-i), SEEK_END);
		if(seek == -1)
			printf("seek");
		num_r = fread(str_buf, sizeof(char), 1, fp);
		if(num_r == 0){
			free(str_buf);
			printf("read");
		}
		printf("%s", str_buf);
	}
	printf("\n");
	free(str_buf);
	fclose(fp);
	return 0;
}