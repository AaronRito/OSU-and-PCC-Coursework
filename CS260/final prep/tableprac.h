#ifndef TABLE_H
#define TABLE_H
//table.h
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

/* ************** PLACE YOUR PROTOTYPE HERE ***************** */
int numberOfNodes(node * root);
bool retrieve(node * root, int  key);
bool removeLargest(node *& root); 
bool removeSmallest(node *& root);
bool remove(node *& root);
void removeEven(node *& root);
void addNode(node ** root, int key);
int sumR(node * root);
int height(node * root);
int treeHeight(node * root);
int getMin(node * root);
int getMax(node * root); 
#endif
