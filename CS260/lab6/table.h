//list.h
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

struct node
{
    int data;
    node * left;
    node * right;;
};

void build(node * & root);  //supplied
void display(node *  root); //supplied
void destroy(node * & root); //supplied
int size(node * root);
int sum(node * root);
int sumR(node * root);
int height(node * root);
int treeHeight(node * root);
/* ************** PLACE YOUR PROTOTYPE HERE ***************** */
 
