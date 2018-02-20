#include "my.h"
int my_strindex(char* c, char find){
	if(c == NULL){return -1;}
	int index = 0;
	while(1){
		if(*c == '\0'){
			return -1;
		} else if(*c == find) {
			return index;
		} else {
			index++;
			c++;
		}
	}
}