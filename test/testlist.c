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
	struct s_node* node1 = new_node("BELLBELL", NULL, NULL);
	struct s_node** segHead = &node1;
	struct s_node* node2 = new_node("TacoTaco", NULL, NULL);
	struct s_node* node3 = new_node("BEEPBEEP", NULL, NULL);
	//remove_last(segHead);
	add_node(node2, segHead);
	add_node(node3, segHead);
	//my_str("taco");
	//struct s_node* addNode = new_node("TacoTaco", NULL, NULL);
	//my_str((*segHead)->elem);
	debug_string(*segHead);
	remove_node(&node2);
	my_str("\n");
	debug_string(*segHead);
	remove_node_at(segHead, 0);
	my_str("\n");
	debug_string(*segHead);
	my_str("\n");
	remove_node_at(segHead, 0);
	my_str("\n");
	debug_string(*segHead);
	add_node(new_node("NEWNEW", NULL, NULL), segHead);
	debug_string(*segHead);
	remove_last(segHead);
	//add_node(new_node("HERE", NULL, NULL), segHead);
	struct s_node* n = new_node("HELP", NULL, NULL);
	struct s_node** bitch = &n;
	my_str("\n");
	debug_string(*bitch);
	my_str("\n");
	//remove_last(bitch);
	remove_node(bitch);
	//remove_node_at(bitch, 0);
	debug_string(*bitch);
	//add_node(new_node("NO", NULL, NULL), bitch);
	append(new_node("CRASH", NULL, NULL), bitch);
	debug_string(*bitch);
	return 0;
}
