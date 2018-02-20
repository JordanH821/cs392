#include "my.h"
char* my_strdup(char *str){ 
	if(str == NULL){
		char* ptr;
		ptr = (char*)malloc(0);
		return ptr;
	}
	char* newStr = (char*)malloc(my_strlen(str));
	my_strcpy(newStr, str);
	return newStr;
}