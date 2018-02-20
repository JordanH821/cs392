#include "my.h"
int my_revstr(char* c){
	if(c == NULL) {return -1;}
	int length = my_strlen(c);
	int diff = length - 1;
	for(int i = 0; i < length/2; i++){
		char holder = *c;
		char* last = (c + diff);
		*c = *last;
		*last = holder;
		c++;
		diff -= 2;

	}
	return length;
}