#include "my.h"
char* my_strncpy(char *dst, char *src, int n){
	if(dst == NULL || src == NULL || n <= 0){
		return dst;
	}
	char* cpyStr = dst;
	while(*src != '\0' && n > 0){
		*dst = *src;
		dst++;
		src++;
		n--;
	}
	if(*src == '\0' && n > 0){//special case specified in discussions
		*dst = '\0';
	}
	return cpyStr;
} 