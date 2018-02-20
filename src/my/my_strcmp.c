#include "my.h"
int my_strcmp(char *a, char *b){
	if(a == NULL && b == NULL){//null pointer checks
		return 0;
	} else if(a == NULL){
		return -1;
	} else if(b == NULL){
		return 1;
	} else {//both pointers not null
		while( (*a != '\0') && (*b != '\0') ){
			if(*a > *b){
				return 1;
			} else if(*b > *a){
				return -1;
			} else {
				a++;
				b++;
			}
		}
		if(*a == '\0' && *b == '\0'){
			return 0;
		} else if(*a == '\0'){//lengths differ, chars same up to end
			return -1;
		} else{//*b == '\0 '
			return 1;
		}
	}
}