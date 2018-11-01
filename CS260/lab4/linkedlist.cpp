#include <iostream>
#include "linkedlist.h"
#include <cstring>

LinkedList::LinkedList()
{
	head  = nullptr;
	size = 0;
}
//destructor
LinkedList::~LinkedList()
{
	Node * curr = first;
	while (curr)				//loop through deleteing each node until curr = null
	{
		first = curr->next;		//assign the head to the next item in the list	
		delete curr;
		curr = first;			//update the pointer
	}
}

bool LinkedList::add(int key)
{
	if (head != NULL)
	{
		add(head, key);
		return true;
	}
	else
	{
		head = new Node;
		head->aData = key;
		head->next = NULL;
		return true;
	}
return true;	
}

bool LinkedList::find(int key)
{
	
	if (head && head->aData == key)
	{
		return true;
	}
	else if (find(head, key))
	{
		return true;
	}
	else
		return false;
};
bool LinkedList::find(Node * first, int key)
{
	if (first == NULL)
		return false;
	else if (first->aData == key)
		return true;
	else
		(find(first->next, key));
return false;	
}
bool LinkedList::del(int key)
{
	if (del(head, key))
	{
		return true;
	}
	else
	{
		del(head->next, key);
		return true;
	}
		return false;
}
bool LinkedList::del(Node * first, int key)
{
	if (first == NULL)
	{
		return false;
	}
	if (first->aData == key)
	{
		Node * curr;
		curr = head;
		head = first->next;
		first = first->next;
		delete curr;
		return true;
	}
	if (first->next && first->next->aData == key)
	{
		Node * curr;
		curr = first->next;
		first->next = first->next->next;
		delete curr;
		return true;
	}
return false;
};

void LinkedList::print() const
{
	//invoke recursive private member function
	print(head);
}
void LinkedList::print(Node * first) const
{
	if (first)
	{
		cout << first->aData << endl;
		//recursive call to print the rest of the list
		print(first->next);
	}
}
void LinkedList::add(Node *& first, int data)
{
	
	if (first->next == NULL)//the end of the list
	{	
		first->next = new Node;
		first->next->aData = data;
		first->next->next = NULL;
		
	}
	else
	{
		//recursive call to append to the smaller list
		 add(first->next, data);
	}
}
bool operator<(const LinkedList& d1, char d2[1])
{
	char name1[10];
	char name2[10];


	if (strcmp(name1, name2) < 0)
		return true;
	else
		return false;
}
std::ostream& operator<<(std::ostream& out, LinkedList& list)
{
	list.print();
	return out;
};
int LinkedList::sum(void)
{
	
	int sum = 0;
	while (head->aData)
	{
		sum = sum + head->aData;
	}
	return sum;
}
