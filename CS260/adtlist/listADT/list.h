#ifndef LIST_H
#define LIST_H

#include "data.h"
class List
{
public:
	List();
	List(const List& aList);
	~List();

	void add(const Data& aData); 
	void addRecursive(const Data& aData);
	void listAll() const;
	void listAllRecursive() const;
	bool get(int index, Data& aData) const;
	int getSize() const;
	/*
	bool remove(const char key[], Data& aData);

	bool search(const char key[], List& matches) const;
	
	int size() const;
	const List& operator= (const List& aList);
	*/
	friend ostream& operator<< (ostream& out, const List& aList);
	

private:
	struct Node
	{
		Data aData;
		Node * next;
		Node(const Data& s)
		{
			aData = s;	//assuming = operator is overloaded for Data
			next = nullptr;
		}
	};
	Node * head;
	int size;

	void listAllRecursive(Node * currHead) const;
	int getSize(Node * currHead) const;
	void addRecursive(Node*& currHead, const Data& aData);
	void destroyList(Node*& currHead);
};
#endif