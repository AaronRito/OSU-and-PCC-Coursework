#ifndef _LINKED_LIST_
#define _LINKED_LIST_

#include <iostream>
using namespace std;

class LinkedList
{
public:
	LinkedList();
	~LinkedList();

	bool add(char key);
	bool find(char key);
	bool del(char key);
	void print() const;
	//void append(int aData);

	friend std::ostream& operator<< (std::ostream& out, LinkedList& list);
private:
	struct Node
	{
		char  aData;
		Node * next;
	};
	bool del(Node * first, char key);
	void print(Node * first) const;
	//pay attention to the passing by reference part below!
	void add(Node * first, char data);
	Node * head;
	Node * first;
	int size;
};

#endif // _LINKED_LIST_