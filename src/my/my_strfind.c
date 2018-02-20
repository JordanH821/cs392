#include "my.h"
char* my_strfind(char *s, char c){
	if(s == NULL){
		return NULL;
	}
	while(*s != '\0'){
		if(*s == c){
			return s;
		} else {
			s++;
		}
	}
	return NULL;
}