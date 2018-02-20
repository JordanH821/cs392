#include "my.h"
char* my_strcpy(char *dst, char *src){
	char* cpyStr = dst;
	if(dst == NULL || src == NULL){
		return dst;
	}
	while(*src != '\0'){
		*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
	return cpyStr;
} 