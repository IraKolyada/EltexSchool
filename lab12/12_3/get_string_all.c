#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * get_string - creates a string of any length and remembers its lenght
 * @len: pointer lenght of string
 * @rez: pointer information about separators between tokens
 * @first_char: pointer first letter of next token
 * 
 * the variable rez indicates the state in which the function was completed
 * rez = 0: last character entered end of string
 * 
 * rez = 1: the last character entered was stored in a variable first_char,
 * the penultimate character is a space - the word before the space 
 * will be returned as a result of the function
 * 
 * rez = 2: the last character entered was call connection symbol,
 * the penultimate character is a space - the word before the space 
 * will be returned as a result of the function
 */
char *get_string(int *len,int *rez, char *first_char)
{
	*len = 0;
	int capacity = 1;
	char *s;
	char c;
	char check_connect;

	s = (char*) malloc(sizeof(char));
	//printf(" Malloc: Addr - '%p',  Memory - '%ld'\n", s, sizeof(char));

	if((*first_char) != 0)
		s[(*len)++] = (*first_char);

	c = getchar();
	if((c == ' '))
		c = getchar();


	while(1){
		if(c == '\n'){
			*rez = 0;
			break;
		}
		s[(*len)++] = c;
		if((*len) >= capacity){
			//capacity++;
			capacity *= 2;
			s = (char*) realloc(s, capacity * sizeof(char));
			//printf(" Realloc: Addr - '%p',  Memory - '%ld'\n", s, capacity * sizeof(char));
		}
		c = getchar();
		if(c == '\n'){
			*rez = 0;
			break;
		}
		if(c == ' '){
			check_connect = getchar();
			if (check_connect == '|'){
				*rez = 2;
				break;
			}
			else{
				(*first_char) = check_connect;
				*rez = 1;
				break;
			}
		}
	}

	s[*len] = '\0';
	capacity = 0;
	return s;
}

/**
 * get_string_2 - creates a string of any length and remembers its lenght
 * @len_command: pointer number of tokens in the request
 * @check: information about how many calls are in the request
 */
char **get_string_2(int *len_command, int *check)
{
	*len_command = 0;
	int len_str = 0;
	int rez = 1;
	int flag = 1;
	int capacity = 1;
	char **s = (char**) malloc(2 * (sizeof(char*)));
	//printf(" Malloc 2: Addr - '%p',  Memory - '%ld'\n", s, sizeof(char*));
	//char check_connect;
	char first_char = 0;

	while(flag){
		if((*len_command) >= capacity){
				capacity +=2;
				s = (char**) realloc(s, capacity * sizeof(char*));
				//printf(" Realloc 2: Addr - '%p',  Memory - '%ld'\n", s, capacity * sizeof(char*));
		}

		char *token = get_string(&len_str, &rez, &first_char);
		s[*len_command] = token;
		//printf("ADD '%s' to %d [%d]\n", token, *len_command, capacity);

		if(rez == 0){     // end str
			flag = 0;
			if ((*check) == 0)
				(*check) = 0;  // conect command dontf
			if ((*check) == 1)
				(*check) = 2;  // conect command did*/
			break;
		}
		if(rez == 2){  // is |
			(*check) = 1;
			break;
		}
		(*len_command)++;
	}

	(*len_command)++;
	s = (char**) realloc(s, (*len_command)* sizeof(char*));
	//printf(" Realloc 3: Addr - '%p',  Memory - '%ld'\n", s, (*len_command)* sizeof(char*));
	s[(*len_command)] = NULL;
	return s;
}