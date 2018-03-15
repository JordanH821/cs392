#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "my.h"
pid_t pidChild = -1;

void sigIntHandler(int sig){
	if(pidChild != -1 && kill(pidChild, 0) == 0){
		kill(pidChild, 9);
		my_str("Child is killed\n");
		return;
	}
}

int main(int argc, char **argv){
	//pid_t pidChild;
	signal(SIGINT, sigIntHandler);
	int p_to_c[2];
	pipe(p_to_c);
	char* currentPath = malloc(1024);
	currentPath = getcwd(NULL, 0);
	while(1){
			//parent
			char* buff = malloc(1024);
			my_str("MINISHELL: ");
			my_str(currentPath);
			my_str(" $: \0");
			char* commandsBuff = malloc(1024);
			read(0, commandsBuff, 1024);
			char** stuff = my_str2vect(commandsBuff);
			if(my_strcmp(stuff[0], "cd") == 0){
				if(chdir(stuff[1]) < 0){
					my_str("The directory \'");
					my_str(stuff[1]);
					my_str("\' does not exist.\n");
				}
				currentPath = getcwd(NULL, 0);
				memset(&buff[0], '\0', 1024);
				free(buff);
			} else if(my_strcmp(stuff[0], "exit") == 0){
				exit(0);
				return 0;
			} else if(my_strcmp(stuff[0], "help") == 0){
				my_str("HELP ME LORD\n");
			} else {
				if((pidChild = fork()) < 0){
					perror("DAS BROKE\n");
					exit(0);
				} else if(pidChild == 0){
					// my_str("\t");
					if(execvp(stuff[0], stuff) < 0){
						my_str("YOU DID SOMETHING WRONG\n");
						exit(0);	
					}
				}
				wait(NULL);
			}
		}
	return 0;
}

