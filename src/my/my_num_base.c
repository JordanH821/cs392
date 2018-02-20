#include "my.h"
void my_num_base(int i, char* c){
	if(c == NULL || *c == '\0'){
		my_str("The pointer cannot be NULL or empty");
		return;
	}

	int length = my_strlen(c);
	if(length == 1){
		for( ; i > 0; i--){
			my_char(*c);
		}
	}
	int place = 1;
	while(i >= place * length){
		place *= length;
	}
	while(i){
		my_char(c[i/place]);
		i %= place;
		place /= length;
	}
}