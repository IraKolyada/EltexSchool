#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "get_string_all.h"

/**
 * @command_1: array of strings up to the "|" character or its absence
 * @command_2: array of strings after the "" character
 * @len_command_1: length command_1
 * @len_command_2: length command_2
 */
struct command_connecnt
{
	char **command_1;
	char **command_2;

	int len_command_1;
	int len_command_2;	
};

/**
 * exists - checks whether a file with the same name exists
 * @com_name: pointer string file's name 
 */
int exists(const char *com_name){
	FILE *comm;
	if((comm = fopen(com_name,"r"))){
		fclose(comm);
		return 1;
	}

	return 0;
}

int main(){
	int pipe_des[2] = {0};
	int pipe_do = -1;
	struct command_connecnt command = {0};
	pid_t pid1 = -1; 
	char ind[] = "/usr/bin/";
	char *god_comm_1; // the access string: path + call(command 1)
	char *god_comm_2; // the access string: path + call(command 2)
	int len_god_comm_1 = -1; //lenght god_comm_1
	int len_god_comm_2 = -1; //lenght god_comm_2
	int exec_rez = -1;
	int status1 = -1; //status fork 1
	int status2 = -1; //status fork 2
	int w_flag = 1; //checking while
	char str_exit[5] ="exit"; 
	int check_flag = 0; //checking call connection
	command.len_command_1 = 0;
	command.len_command_2 = 0;

	while (w_flag)
	{
		check_flag = 0;
		
		printf("Enter command (Example: ls -la | grep a):");
		command.command_1 = get_string_2(&(command.len_command_1), &check_flag);

		/*
		 Remember the line after the "|" symbol to another array of strings
		 and create a pipe for the call connection
		*/
		if(check_flag == 1){
			command.command_2 = get_string_2(&(command.len_command_2), &check_flag);

			pipe_do = pipe(pipe_des);
			if(pipe_do == -1){
				perror("erore pipe");
			}
		}

		/**
		 * if command_1 corresponds to the output line: 
		 * clear the memory and set the loop flag = 0
		 * 
		 * else - work
		 */
		if(strcmp(command.command_1[0], str_exit) == 0){
			for(int i = 0; i <= (command.len_command_1); i++){
					free(command.command_1[i]);
			}

			free(command.command_1);
			w_flag = 0;
		}
		else{
			/* create string for execv*/
			len_god_comm_1 = strlen(ind) + command.len_command_1;
			god_comm_1 = malloc(len_god_comm_1 + 1);
			snprintf(god_comm_1,(strlen(command.command_1[0])+strlen(ind) + 1),"%s%s", ind, command.command_1[0]);

			/* create strig for execv №2, if used connect command(|)*/
			if(check_flag == 2){
				len_god_comm_2 = strlen(ind) + command.len_command_2;
				god_comm_2 = malloc(len_god_comm_2 + 1);
				snprintf(god_comm_2,(strlen(command.command_2[0])+strlen(ind) + 1),"%s%s", ind, command.command_2[0]);
			}

			/**
			 * check if the call exists
			 */
			if (exists(god_comm_1) == 1){
				pid1 = fork();
				if(pid1 == -1){
					perror("error fork 1");
				}

				/**
				 * let's call in the child process
				 */
				if(pid1 == 0){

					/*If there is a second call, write the result of the first to the pipe*/
					if(check_flag == 2){

						if (close(pipe_des[0]) == -1){
							perror("error close 1");
						}

						/* Duplicate stdout on write end of pipe; close duplicated descriptor */
						if (pipe_des[1] != STDOUT_FILENO) {
							if (dup2(pipe_des[1], STDOUT_FILENO) == -1){
								perror("error dup2 1");
							}
							if (close(pipe_des[1]) == -1){
 								perror("error close 2");
							}
						}
					}

					exec_rez = execvp(god_comm_1, command.command_1);
					if(exec_rez == -1){
						perror("error execlp");
					}
					exit(0);
				}

				/**
				 * If there is a second call, 
				 * create a new process and read input data from the pipe
				 */
				if(check_flag == 2){
					/**
					 * check if the call exists
					 */
					if(exists(god_comm_2) == 1){
						pid1 = fork();
						if(pid1 == -1){
							perror("error fork 2");
						}

						/**
						 * let's call in the child process
						*/
						if(pid1 == 0){

							if (close(pipe_des[1]) == -1){
								perror("error close 3");
							}

							/**
							 * Duplicate stdout on write end of pipe;
							 * close duplicated descriptor 
							 */
							if (pipe_des[0] != STDIN_FILENO) {
								if (dup2(pipe_des[0], STDIN_FILENO) == -1){
									perror("error dup2 2");
								}
								if (close(pipe_des[0]) == -1){
 									perror("error close 2");
								}
							}

							exec_rez = execvp(god_comm_2, command.command_2);
							if(exec_rez == -1){
								perror("error execlp");
							}
							exit(0);
						}
						// close pipe anf wait 
						close(pipe_des[0]);
						close(pipe_des[1]);
						waitpid(pid1, &status2, 0);
					}
					else
						printf("Command %s dont found\n",command.command_2[0]);
				}
				waitpid(pid1, &status1, 0);

				/**
				 * clear the memory of all the strings outside
				 * the array of strings - command.command_1
				*/
				if(command.len_command_1 != 0){
					for(int i = 0; i <= (command.len_command_1); i++){
						if(command.command_1[i])
							free(command.command_1[i]);
					}
				}

				/**
				 * clear the memory of all the strings outside
				 * the array of strings - command.command_2
				*/
				if(check_flag == 2){
					if(command.len_command_2 != 0){
						for(int i = 0; i <= (command.len_command_2); i++){
							if(command.command_2[i])
								free(command.command_2[i]);
						}
					}
				}

				/**
				 * clearing the memory of the array of strings 
				 * and the access string
				*/
				free(command.command_1);
				free(god_comm_1);
				if(check_flag == 2){
					free(command.command_2);
					free(god_comm_2);
				}
			}
			else{
				printf("Command %s dont found\n",command.command_1[0]);
			}
		}
	}

	return 0;
}