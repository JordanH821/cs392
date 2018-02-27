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
		my_str("This program takes in strings as command line arguments");
		return 0;
	}
	pid_t pidChild;
	pid_t pidGChild;
	int p_to_c[2];
	char buff[101];

	pipe(p_to_c);

	if ((pidChild = fork())< 0){
		//error checking
	} else if(pidChild == 0){
		//child
		pidChild = getpid();
		//code for child to gc pipe
		int c_to_gc[2];
		pipe(c_to_gc);
		char buffShift[101];
		char buffPass[101];
		read(p_to_c[0], buffShift, 101);
		my_strcpy(buffPass, buffShift);
		for(int i = 0; i < my_strlen(buffShift); i++){
			if(buffShift[i] >= 97 && buffShift[i] <= 122){//lowercase
				buffShift[i] = ((buffShift[i] - 'a' + 1) % 26) + 'a';
			} else if(buffShift[i] >= 65 && buffShift[i] <= 90){//uppercase
				buffShift[i] = ((buffShift[i] - 'A' + 1) % 26) + 'A';
			}
		}
		my_str("\nChild: ");
		my_str(buffShift);
		write(c_to_gc[1], buffPass, 101);
		//fork grandchild
		if ((pidGChild = fork())< 0){
			//error in grandchild
		} else if(pidGChild == 0){
			//grandchild
			my_str("\n");
			char buffRev[101];
			read(c_to_gc[0], buffRev, 101);
			my_str("Grandchild: ");
			my_revstr(buffRev);
			my_str(buffRev);
			exit(0);
		}
		wait(NULL);
		exit(0);
	} else {
		//parent 
		char* buff = my_vect2str(argv);
		my_str("Parent: ");
		my_str(buff);
		write(p_to_c[1], buff, 101);
		wait(NULL);
		exit(0);
	}
	return 0;
}