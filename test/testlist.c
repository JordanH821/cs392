#include "list.h"
#include <stdio.h>
int main(){
	//integer tests
	int num = 16;
	int* numPtr = &num;

	int num2 = 32;
	int* numPtr2 = &num2;

	int num3 = 48;
	int* numPtr3 = &num3;

	int num4 = 64;
	int* numPtr4 = &num4;

	struct s_node* first = new_node(numPtr, NULL, NULL);
	struct s_node** head = &first;

	add_elem(numPtr2, head);
	add_node_at(new_node(numPtr3, NULL, NULL), head, 48);
	append(new_node(numPtr4, NULL, NULL), head);
	debug_int(*head);
	remove_last(head);
	my_str("\n");
	debug_int(*head);
	my_str("\n");
	my_str(">>>>>Integers pass all test cases!<<<<<");
	my_str("\n");

	//char tests
	char a = 'a';
	char* aPtr = &a;

	char b = 'b';
	char* bPtr = &b;

	char c = 'c';
	char* cPtr = &c;

	struct s_node* firstChar = new_node(aPtr, NULL, NULL);
	struct s_node** headChar = &firstChar;
	add_elem(bPtr, headChar);
	struct s_node* cNode = new_node(cPtr, NULL, NULL);
	append(cNode, headChar);
	traverse_char(*headChar);
	my_str("\n");
	debug_char(*headChar);
	my_str("\n");
	my_int(count_s_nodes(*headChar));
	my_str("\n");
	my_str(">>>>>Characters pass all test cases!<<<<<");
	my_str("\n");

	//string tests
	char* strPtr = "HI";
	char* str2Ptr = "BYE";
	char* str3Ptr = "TACO";

	struct s_node* firstStr = new_node(strPtr, NULL, NULL);
	struct s_node** headStr = &firstStr;
	append(new_node(str2Ptr, NULL, NULL), headStr);
	append(new_node(str3Ptr, NULL, NULL), headStr);
	traverse_string(*headStr);
	my_str("\n");
	debug_string(*headStr);
	my_str("\n");
	empty_list(headStr);
	my_int(count_s_nodes(*headStr));
	my_str("\n");
	my_str(">>>>>Strings pass all test cases!<<<<<");
	my_str("\n");
	return 0;
}
