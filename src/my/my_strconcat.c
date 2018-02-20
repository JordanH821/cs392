#include "my.h"
char* my_strconcat(char *a, char *b){
	if(a == NULL && b == NULL){
		return NULL;
	} else if(a == NULL){
		return my_strdup(b);
	} else if(b == NULL){
		return my_strdup(a);
	} else {//both not NULL
		int len = my_strlen(a) + my_strlen(b);
		char* newStr = (char *)malloc(len);
		char* bStart = newStr + my_strlen(a);
		char* start = newStr;
		my_strcpy(newStr, a);
		my_strcpy(bStart, b);
		//newStr++;
		//*newStr = '\0';
		return start;
	}
}