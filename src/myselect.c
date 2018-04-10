#include <ncurses.h>
#include "my.h"

int main(int argc, char* argv[]){
	printf("%s\n", argc);
	for(int i = 0; i < argc; i++){
		printf("%s\n", argv[i]);
	}
}