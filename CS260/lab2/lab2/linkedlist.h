#ifndef _LINKED_LIST_
#define _LINKED_LIST_
#include <iostream>
#include <fstream>

class LinkedList
{
public:
	LinkedList();
	~LinkedList();

	bool add(char key);
	bool find(char key);
	bool del(char key);
	void  print();
	friend std::ostream& operator<< (std::ostream& out, LinkedList& list);

private:
	struct Node
	{
		char data;
		Node * next;
	};
	Node * First;
	int size;
};
#endif // _LINKED_LIST_
