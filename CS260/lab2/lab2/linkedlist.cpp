#include "linkedlist.h"
using namespace std;


LinkedList::LinkedList()
{
	First = nullptr;
	size = 0;
}
//destructor
LinkedList::~LinkedList()
{
	Node * curr = First;
	while (curr)							//loop through deleteing each node until curr = null
	{
		First = curr->next;		//assign the head to the next item in the list	
		delete curr;
		curr = First;					//update the pointer
	}
}
//add
bool LinkedList::add(char key)
{
	Node * curr = First;
	Node * prev = NULL;
	char name;
	name = key;
	while (curr != NULL && curr->data < name)
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr)
		return false;
	else
	{
		Node * newNode = new Node;
		newNode->data = name;
		newNode->next = curr;
		if (!prev)		
			First = newNode;
		else
			prev->next = newNode;
		size++;
		return true;
	}
}

bool LinkedList::find(char key)
{
	Node * curr = First;
	Node * prev = NULL;

	while (curr != NULL && curr->data != key)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
	{
		return false;
	}
	else
		return true;
};
bool LinkedList::del(char key)
{
	Node * curr = First;
	Node * prev = NULL;
	bool found = false;

	while (curr != NULL && curr->data < key)
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr)
	{
		if (!prev)
			First = curr->next;
		else
			prev->next = curr->next;
		found =  true;	
	}
	if (found)
	{
		delete(curr);
		size--;
	}
	return found;
};
std::ostream& operator<<(std::ostream& out, LinkedList& list)
{	
		list.print();
		return out;	
};
void LinkedList::print()
{
	Node *curr;
	curr = First;
	while (curr)
	{
		cout << curr->data << ",";
		curr = curr->next;
	}
	cout << endl;

}

bool operator< (const LinkedList& d1, char d2[1])
{
	char name1[10];
	char name2[10];
	

	if (strcmp(name1, name2) < 0)
		return true;
	else
		return false;
}