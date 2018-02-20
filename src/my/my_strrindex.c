#include "my.h"
int my_strrindex(char* c, char find){
	int atIndex = -1;
	int currIndex = 0;
	if(c == NULL){ return -1;}
	while(1){
		if(*c == '\0'){
			return atIndex;
		} else if(*c == find){
			atIndex = currIndex;
			currIndex++;
			c++;
		} else {
			currIndex++;
			c++;
		}
	}
}

