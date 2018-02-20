#include "my.h"
int my_strlen(char* c){
	if(c == NULL){return -1;}
	int len = 0;
	while(*c != '\0'){
		len++;
		c++;
	}
	return len;
}