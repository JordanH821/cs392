#include "my.h"
char* my_strnconcat(char *a, char *b, int n){
	if(a == NULL && b == NULL){
		return NULL;
	} else if(a == NULL){
		if(n <= 0){
			char* ptr = (char*)malloc(1);
			*ptr = '\0';
			return ptr;
		}
		char* newStr = (char *)malloc(n);
		my_strncpy(newStr, b, n);
		return newStr;
	} else if(b == NULL){
		char* newStr = (char *)malloc(my_strlen(a));
		my_strcpy(newStr, a);
		return newStr;
	} else {//both not NULL
		if(n <= 0){n = 0;}
		int len = my_strlen(a) + n;
		char* newStr = (char *)malloc(len);
		char* bStart = newStr + my_strlen(a);
		char* start = newStr;
		my_strcpy(newStr, a);
		my_strncpy(bStart, b, n);
		return start;
	}
}