#include <sys/wait.h>
#include <stdio.h>
#include "my.h"
int main(int argc, char **argv){

	while(1){
		pid_t pidChild;
		int p_to_c[2];
		pipe(p_to_c);
		if ((pidChild = fork())< 0){
			//error checking
			perror("Initial fork was unsuccessful");
			exit(0);
		} else if(pidChild == 0){
			//child
			char* execBuff = malloc(1024);
			read(p_to_c[0], execBuff, 1024);
			char** args = my_str2vect(execBuff);
			free(execBuff);
			execvp(args[0], args);
		} else {
			//parent
			char* buff = malloc(1024);
			my_str("MINISHELL: ");
			my_str(getcwd(buff, 1024));
			my_str(" $:");
			free(buff);
			char* commandsBuff = malloc(1024);
			read(0, commandsBuff, 1024);
			write(p_to_c[1], commandsBuff, 1024);	
			free(commandsBuff);
		}
	}
	return 0;
}
	