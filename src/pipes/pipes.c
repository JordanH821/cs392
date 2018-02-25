#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include "my.h"
int main(int argc, char **argv){
	if(argc == 1){
		printf("%s\n", "This program takes in strings as command line arguments");
		return 0;
	}
	pid_t pidChild;
	pid_t pidGChild;
	int p_to_c[2];
	char buff[100];

	pipe(p_to_c);

	if ((pidChild = fork())< 0){
		//error checking
	} else if(pidChild == 0){
		//child
		pidChild = getpid();
		//code for child to gc pipe
		int c_to_gc[2];
		pipe(c_to_gc);
		printf("Here is the child process. PID = %d\n", getpid());
		char buffShift[100];
		char buffPass[100];
		read(p_to_c[0], buffShift, 100);
		write(c_to_gc[1], buffShift, 100);
		for(int i = 0; i < my_strlen(buffShift); i++){
			if(buffShift[i] >= 97 && buffShift[i] <= 122){//lowercase
				buffShift[i] = ((buffShift[i] - 'a' + 1) % 26) + 'a';
			} else if(buffShift[i] >= 65 && buffShift[i] <= 90){//uppercase
				buffShift[i] = ((buffShift[i] - 'A' + 1) % 26) + 'A';
			}
		}
		my_str("Child: ");
		my_str(buffShift);
		//fork grandchild
		if ((pidGChild = fork())< 0){
			//error in grandchild
		} else if(pidGChild == 0){
			//grandchild
			printf("Here is the grandchild process. PID = %d\n", getpid());
			printf("Here is the grandchild's parent process. PID = %d\n", getppid());
			char buffRev[100];
			read(c_to_gc[0], buffRev, 100);
			my_str("Grandchild: ");
			my_revstr(buffRev);
			my_str(buffRev);
			exit(0);
		}
		exit(0);
	} else {
		//parent 
		printf("Here is the parent process. PID = %d\n", getpid());
		char* buff = my_vect2str(argv);
		write(p_to_c[1], buff, 100);
		my_str("Parent: ");
		my_str(buff);
		wait(NULL);
	}
	return 0;
}