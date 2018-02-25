#include "list.h"

/*
 Allocates and returns a new node with the given pointers. You may
 create nodes with NULLs.
*/
struct s_node* new_node(void* elem, struct s_node* next, struct s_node* previous){
	struct s_node* newNode = (struct s_node*) malloc(sizeof(struct s_node));
	newNode->elem = elem;
	newNode->next = next;
	newNode->prev = previous;
	return newNode;
}

/*
 Inserts a node at the start of the list. DO NOT add a NULL pointer or
 a node with a NULL elem.
 DOES NOT PARSE
*/
void add_node(struct s_node* node, struct s_node** head){
	if(node == NULL || node->elem == NULL){//node is null or null elem
		return;
	} else if(head == NULL || *head == NULL){//empty or no list
		head = &node;
	} else {//list is not empty
		node->next = *head;
		(*head)->prev = node;
		*head = node;
	}
}

/* 
 Creates a new node with elem and adds it to head. DO NOT add a NULL 
 elem.
 DOES NOT PARSE
*/
void add_elem(void* elem, struct s_node** head){
	if(elem == NULL || head == NULL){
		return;
	}
	struct s_node* addNode = new_node(elem, NULL, NULL);	
	add_node(addNode, head);
}

/*
 Adds a node to the end of a list. DO NOT add a NULL pointer or
 a node with a NULL elem.
 Parse once
*/
void append(struct s_node* node, struct s_node** head){
	if(node == NULL || node->elem == NULL){
		return;
	} else if(head == NULL || *head == NULL){//head doesnt exist so the appended node becomes head
		head = &node;
	} else {//no null catches, appends to list
		struct s_node* lastNode = *head;
		while(lastNode->next != NULL){
			lastNode = lastNode->next;
		}
		lastNode->next = node;
		node->prev = lastNode;
		node->next = NULL;
	}
}

/*
 Adds a node at index n of a list or at the end of the list if n is 
 too large.
 Parse once
*/
void add_node_at(struct s_node* node, struct s_node** head, int n){
	if(node == NULL){//inserting a NULL pointer or  NULL node
		return;
	} else if(head == NULL || *head == NULL){//if head is null or points to null then 
		return;
		// struct s_node* headNode = new_node(NULL, NULL, NULL);
		// head = &headNode;
		// head = &node;
	} else if(n == 0){//reduces to add node as head
		add_node(node, head);
	} else {//no NULLs 
		struct s_node* nodeAtIndex = *head;
		while(nodeAtIndex->next != NULL && n > 0){
			nodeAtIndex = nodeAtIndex->next;
			n--;
		}
		if(nodeAtIndex->next == NULL){//n is >= length of list
			nodeAtIndex->next = node;
			node->prev = nodeAtIndex;
		} else {//add in between two nodes
			//fixes prev node pointers
			nodeAtIndex->prev->next = node;
			node->prev = nodeAtIndex->prev;
			//fixes next pointers
			node->next = nodeAtIndex;
			nodeAtIndex->prev = node;
		}	
	}
}

/* 
 Removes the given node from the list. Returns elem and frees the 
 node from memory.
 DOES NOT PARSE.
*/
void* remove_node(struct s_node** node){
	if(node == NULL || *node == NULL){
		return NULL;
	} else {
		if((*node)->next == NULL && (*node)->prev == NULL){//node is head of 1 item list
			void* ret = (*node)->elem;
			free(*node);
			*node = NULL;
			return ret;
		} else if ((*node)->prev == NULL){//node is the head of a list w length > 1
			//WHAT TO DO WITH HEAD POINTER
			void* ret = (*node)->elem;
			(*node)->next->prev = NULL;
			struct s_node* newNode = (*node)->next; 
			free(*node);
			*node = newNode;
			return ret;
		} else if((*node)->next == NULL){//node is tail
			void* ret = (*node)->elem;
			(*node)->prev->next = NULL;
			struct s_node* newNode = (*node)->next; 
			free(*node);
			*node = newNode;
			return ret;
		} else {
			void* ret = (*node)->elem;
			((*node)->next)->prev = (*node)->prev;
			((*node)->prev)->next = (*node)->next;
			struct s_node* newNode = (*node)->next; 
			free(*node);
			*node = newNode;
			return ret;

		}
	}
}

/*
 Removes the last node from the list.
 Parse Once.
*/
void* remove_last(struct s_node** node){
	if(node == NULL || *node == NULL){
		return NULL;
	} else if((*node)->next == NULL){//passed in a single element list
		void* ret = (*node)->elem;
		remove_node(node);
		return ret;
	}
	struct s_node* lastNode = *node;
		while(lastNode->next != NULL){
			lastNode = lastNode->next;
		}
		void* ret = lastNode->elem;
		remove_node(&lastNode);
		return ret;
}

/*
 Removes the node at index n or the last node.
 Parse once
*/
void* remove_node_at(struct s_node** head, int n){
	if(head == NULL || *head == NULL){
		return NULL;
	} else if(n <= 0){//fixes pointer problems with 
		void* ret = (*head)->elem;
		remove_node(head);
		return ret;
	} else {
		struct s_node* removee = *head;
		while(removee->next != NULL && n>0){
			removee = removee->next;
			n--;
		}
		void* ret = removee->elem;
		remove_node(&removee);
		return ret;
	}
}

/*
 Returns the value the length of the list
 Parse Once.
*/
int count_s_nodes(struct s_node* head){
	if(head == NULL){
		return 0;
	}
	int length = 0;
	struct s_node* currNode = head;
	while(currNode != NULL){
		currNode = currNode->next;
		length++;
	}
	return length;
}

/*
 Frees all the nodes in the list.
 CHALLENGE: Write in two lines (allowed to use other methods in 
 this assignment)
*/
void empty_list(struct s_node** head){
	while(head != NULL && *head != NULL){
		remove_node_at(head, 0);
	}
}

/*
 Returns a pointer to the node at index n or the last node.
 Parse once
*/
struct s_node* node_at(struct s_node* head, int n){
	if(head == NULL){
		return NULL;
	}
	struct s_node* nodeAt = head;
	while(nodeAt->next != NULL && n > 0){
		nodeAt = nodeAt->next;
		n--;
	}
	return nodeAt;
}

/*
 Returns a pointer to the elem at index n or the last node.
 Parse once.
*/
void* elem_at(struct s_node* head, int n){
	if(head == NULL){
		return NULL;
	}
	return node_at(head,n)->elem;
}

/*
 Prints all the elems as ints separated by a space
*/
void traverse_int(struct s_node* head){
	if (head == NULL){
		return;
	}
	struct s_node* cur = head;
	while(cur != NULL){
		my_int(*(int*)elem_at(cur,0));
		my_str(" ");
		cur = cur->next;
	}
}

/*
 Prints all the elems as chars separated by a space
*/
void traverse_char(struct s_node* head){
	if (head == NULL){
		return;
	}
	struct s_node* cur = head;
	while(cur != NULL){
		my_char(*(char*)elem_at(cur,0));
		my_str(" ");
		cur = cur->next;
	}
}

/*
 Prints all the elems as strings separated by a space
*/
void traverse_string(struct s_node* head){
	if (head == NULL){
		return;
	}
	struct s_node* cur = head;
	while(cur != NULL){
		my_str((char*)elem_at(cur,0));
		my_str(" ");
		cur = cur->next;
	}
}

/*
 Prints all the elems as ints separated by a space in the format
 (NULL <- Elem -> Next elem), ..., (Previous elem <- Elem -> NULL) 
*/
void debug_int(struct s_node* head){
	if(head == NULL){
		return;
	}
	struct s_node* currNode = head->next;
	my_str("(NULL <- ");
	my_int(*(int*)head->elem);
	my_str(" -> ");
	if(currNode == NULL){
		my_str("NULL)");
		return;
	} else {
		my_int(*(int*)currNode->elem);
		my_str("), ");
	}
	//currNode = currNode->next;
	while(currNode->next != NULL){
		my_str("(");
		my_int(*(int*)currNode->prev->elem);
		my_str(" <- ");
		my_int(*(int*)currNode->elem);
		my_str(" -> ");
		my_int(*(int*)currNode->next->elem);
		my_str("), ");
		currNode = currNode->next;
	}
	my_str("(");
	my_int(*(int*)currNode->prev->elem);
	my_str(" <- ");
	my_int(*(int*)currNode->elem);
	my_str(" -> ");
	my_str("NULL)");
}

/*
 Prints all the elems as chars separated by a space in the format
 (NULL <- Elem -> Next elem), ..., (Previous elem <- Elem -> NULL) 
*/
void debug_char(struct s_node* head){
	if(head == NULL){
		return;
	}
	struct s_node* currNode = head->next;
	my_str("(NULL <- ");
	my_char(*(char*)head->elem);
	my_str(" -> ");
	if(currNode == NULL){
		my_str("NULL)");
		return;
	} else {
		my_char(*(char*)currNode->elem);
		my_str("), ");
	}
	//currNode = currNode->next;
	while(currNode->next != NULL){
		my_str("(");
		my_char(*(char*)currNode->prev->elem);
		my_str(" <- ");
		my_char(*(char*)currNode->elem);
		my_str(" -> ");
		my_char(*(char*)currNode->next->elem);
		my_str("), ");
		currNode = currNode->next;
	}
	my_str("(");
	my_char(*(char*)currNode->prev->elem);
	my_str(" <- ");
	my_char(*(char*)currNode->elem);
	my_str(" -> ");
	my_str("NULL)");
}

/*
 Prints all the elems as strings separated by a space in the format
 (NULL <- Elem -> Next elem), ..., (Previous elem <- Elem -> NULL) 
*/
void debug_string(struct s_node* head){
	if(head == NULL){
		return;
	}
	struct s_node* currNode = head->next;
	my_str("(NULL <- ");
	my_str((char*)head->elem);
	my_str(" -> ");
	if(currNode == NULL){
		my_str("NULL)");
		return;
	} else {
		my_str((char*)currNode->elem);
		my_str("), ");
	}
	//currNode = currNode->next;
	while(currNode->next != NULL){
		my_str("(");
		my_str((char*)currNode->prev->elem);
		my_str(" <- ");
		my_str((char*)currNode->elem);
		my_str(" -> ");
		my_str((char*)currNode->next->elem);
		my_str("), ");
		currNode = currNode->next;
	}
	my_str("(");
	my_str((char*)currNode->prev->elem);
	my_str(" <- ");
	my_str((char*)currNode->elem);
	my_str(" -> ");
	my_str("NULL)");
}

/*
 Prints the elem of node as a int
*/
void print_int(struct s_node* node){
	if(node == NULL){
		return;
	}
	my_int(*(int*)node->elem);
}

/*
 Prints the elem of node as a char
*/
void print_char(struct s_node* node){
	if(node == NULL){
		return;
	}
	my_char(*(char*)node->elem);
}

/*
 Prints the elem of node as a string
*/
void print_string(struct s_node* node){
	if(node == NULL){
		return;
	}
	my_str((char*)node->elem);
}

