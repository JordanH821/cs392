#include "my.h"
int my_atoi(char *n){
	if(n == NULL){return 0;}
	long num = 0;
	long negCount = 0;
	while(*n != '\0'){
		if(*n >='0'  && *n <='9'){//nint char
			num = num * 10 + *n - '0';
			n++;
		} else if( num != 0 && *n > '9'){//comes on a char after num
			return (negCount % 2) ? -1 * num : num;
		}else if(*n == '-'){//negative sign
			negCount++;
			n++;
		} else {//non int char
			n++;
		}
	}
	// if(isNeg){nums = '-' + nums;}
	return (negCount % 2) ? -1 * num : num;
}