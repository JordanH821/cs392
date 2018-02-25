#include "my.h"
char* my_vect2str(char **x){
	int buffIndex = 0;
	char* buff = malloc(100);
	int i = 1;
	while(x[i] != NULL){
		if(i > 1){
				buff[buffIndex] = ' ';
				buffIndex++;
			}
		for(int j = 0; j < my_strlen(x[i]); j++){
			buff[buffIndex] = x[i][j];
			buffIndex++;
		}
		i++;
	}
	buff[buffIndex] = '\0';
	return buff;
}