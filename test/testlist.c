#include "list.h"
#include <stdio.h>
int main(){
	int num = 16;
	int* numPtr = &num;
	int num2 = 32;
	int* numPtr2 = &num2;
	// int num3 = 48;
	// int numPtr3 = &num3;
	// int num4 = 64;
	// int numPtr4 = num4;
	struct s_node* first = new_node(numPtr, NULL, NULL);
	struct s_node** head = &first;
	add_elem(numPtr2, head);
	debug_int(*head);
	//printf("%s\n", "taco");
	my_str("taco");
	//my_int(345);
	return 0;
}