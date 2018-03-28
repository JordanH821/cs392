#include "my.h"
char** my_str2vect(char* str){
	char** vect = malloc(my_strlen(str) + 1);
	if(str == NULL || my_strlen(str) == 0){
		vect[0] = NULL;
		return vect;
	} else {
		char* illegal = " \n\t";
		int v = 0;
		int i = 0;
		while(str[i] != '\0'){//builds strings until the \0
			int j = 0;
			char* strPiece = malloc(my_strlen(str));
			while(my_strfind(illegal, str[i]) == NULL && str[i] != '\0'){//builds string until split character
				strPiece[j] = str[i];
				j++;
				i++;
			}
			while(my_strfind(illegal, str[i]) != NULL && str[i] != '\0'){//parse through extra chars
				i++;
			}
			vect[v] = strPiece;
			v++;
		}
		vect[v] = NULL;
		return vect; 
	}
}
 // Takes a string 
 // Allocates a new vector (array of string ended by a NULL), 
 // Splits apart the input string x at each space character 
 // Returns the newly allocated array of strings
 // Any number of ' ','\t', and '\n's can separate words.
 // I.e. "hello \t\t\n class,\nhow are you?" -> {"hello", "class,", "how", "are","you?", NULL}