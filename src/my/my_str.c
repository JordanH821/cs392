#include "my.h"
void my_str(char* c){
	if( (char*)c ){
		if(*c != '\0'){
			my_char(*c);
			my_str(++c);
		}
	}
}
