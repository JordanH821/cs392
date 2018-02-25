#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>
int main(int argc, char* argv[]){
	pid_t pidChild;
	pid_t pidGChild;
	int p_to_c[2];
	int c_to_p[2];
	int c_to_gc[2];
	char buff[100];

	pipe(p_to_c);
	pipe(c_to_p);
	pipe(c_to_gc);

	if ((pidChild = fork())< 0){
		//error checking
	} else if(pidChild == 0){
		//child
		pidChild = getpid();
		//code for child
		printf("Here is the child process. PID = %d\n", getpid());
		//fork grandchild
		if ((pidGChild = fork())< 0){
			//error in grandchild
		} else if(pidGChild == 0){
			printf("Here is the grandchild process. PID = %d\n", getpid());
			printf("Here is the grandchild's parent process. PID = %d\n", getppid());
			exit(0);
		}

	} else {
		printf("Here is the parent process. PID = %d\n", getpid());
		wait(NULL);
	}
	return 0;
}