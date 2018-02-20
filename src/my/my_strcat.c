#include "my.h"
char* my_strcat(char *dst, char *src){
	if(dst == NULL){
		return NULL;
	} else if(src == NULL){//dst is not null but src is
		return dst;
	} else {
		char* catStr = dst;
		while(*dst != '\0'){
			dst++;
		}
		while(*src != '\0'){
			*dst = *src;
			dst++;
			src++;
		}
		*dst = '\0';
		return catStr;
	}
}