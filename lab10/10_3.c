#include <stdio.h>
//#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * get_string - creates a string of any length and remembers its lenght
 * @len:pointer lenght of string
 */
char *get_string(int *len,int *rez)
{
	*len = 0;
	int capacity = 1;
	char *s = (char*) malloc(sizeof(char));
	char c = getchar();

	if(c == ' ')
			c = getchar();

	while(1){
			s[(*len)++] = c;
			if(*len >= capacity){
					capacity *= 2;
					s = (char*) realloc(s, capacity * sizeof(char));
			}
			c = getchar();
			if(c == '\n'){
				*rez = 0;
				break;
			}
			if(c == ' '){
				*rez = 1;
				break;
			}
	}

	s[*len] = '\0';
	return s;
}

char **get_string_2(int *len)
{
	*len = 0;
	int len_str = 0;
	int rez = 1;
	int flag = 1;
	int capacity = 1;
	char **s = (char**) malloc(sizeof(char*));

	while(flag){
		char *xyu = get_string(&len_str, &rez);
		s[*len] = xyu;
		printf("ADD '%s' to %d [%d]\n", xyu, *len, capacity);
		if(rez == 0){
			flag = 0;
			break;
		}
		if(*len >= capacity){
				capacity++;
				s = (char**) realloc(s, capacity * sizeof(char*));
		}
		(*len)++;
	}

	return s;
}



int exists(const char *com_name){
	FILE *comm;
	if((comm = fopen(com_name,"r"))){
		fclose(comm);
		return 1;
	}

	return 0;
}


int main(){
	char **command;
	int len_command;
	pid_t pid;
	char ind[] = "/usr/bin";
	char *god_comm;
	int len_god_comm;

	
	command = get_string_2(&len_command);
	len_god_comm = strlen(ind) + len_command;
	god_comm = malloc(len_god_comm + 1);
	snprintf(god_comm,strlen(command[0]),"%s%s",ind,command[0]);

	if (exists(god_comm) == 1){
		pid = fork();

		if(pid == 0){

		}
	}
	else
		printf("Command %s dont",command[0]);
	return 0;
}