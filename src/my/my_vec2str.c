#include "my.h"
char* my_vect2str(char **x){
	if(x == NULL || x[0] == NULL){
		return NULL;
	}
	int buffIndex = 0;
	// int totalLength = 0;
	// int i = 1;
	// while(x[i] != NULL){
	// 	totalLength += my_strlen(x[i]);
	// 	i++;
	// }
	char* buff = malloc(sizeof(x) + 1);
	int i = 0;
	while(x[i] != NULL){
		if(i > 0){
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