#include "my.h"
char* my_strrfind(char *s, char c){
	char* ptr = NULL;
	if(s == NULL){return NULL;}
	while(*s != '\0'){
		if(*s == c){
			ptr = s;
			s++;
		} else {
			s++;
		}
	}
	return ptr;
}