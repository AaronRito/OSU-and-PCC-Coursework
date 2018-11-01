//clist.h
#include <iostream>
#include <cstring>
#include <cctype>

struct node
{
    int		data;
    node*	next;
};

// These functions are in supplied.o and can be called from your code.
void build(node*& head);
void display(node* head);
void destroy(node* &head);
void duplicate(node*& new_copy);  //Provides a duplicate copy of the list.
int sumi(node * head);
int sum(node* head);
int sumR(node* head, node * first);
int counti(node * head);
int count(node * head);
int countR(node * head, node * first);
// Add the prototypes for your functions below this comment.