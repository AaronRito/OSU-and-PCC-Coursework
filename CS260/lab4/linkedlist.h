#ifndef _LINKED_LIST_
#define _LINKED_LIST_

#include <iostream>
using namespace std;

class LinkedList
{
public:
	LinkedList();
	~LinkedList();

	bool add(int key);
	bool find(int key);
	bool del(int key);
	void print() const;
	int sum(void);
	//void append(int aData);

	friend std::ostream& operator<< (std::ostream& out, LinkedList& list);
private:
	struct Node
	{
		int  aData;
		Node * next;
	};
	bool del(Node * first, int key);
	void print(Node * first) const;
	bool find(Node * first, int key);
	int sum(Node * first);
	//pay attention to the passing by reference part below!
	void add(Node *& first, int data);
	Node * head;
	Node * first;
	int size;
};

#endif // _LINKED_LIST_
