#include "my.h"
int my_strncmp(char *a, char *b, int n){
	if((a == NULL && b == NULL) || (n <= 0)){//null pointer checks
		return 0;
	} else if(a == NULL){
		return -1;
	} else if(b == NULL){
		return 1;
	} else {//both pointers not null
		while(  (*a != '\0') && (*b != '\0') && (n != 0) ){
			if(*a > *b){
				return 1;
			} else if(*b > *a){
				return -1;
			} else {
				a++;
				b++;
				n--;
			}
		}
		if( (*a == '\0' && *b == '\0') || (n==0) ){//if both empty or equal up to n
			return 0;
		} else if(*a == '\0'){//lengths differ, chars same up to end
			return -1;
		} else{ //a is longer than b
			return 1;
		}
	}
}