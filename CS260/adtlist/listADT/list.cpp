#include "list.h"

List::List() : head(nullptr)
{
}

List::List(const List& aList) : head(nullptr)
{
	int		index;
	Data	s;
	for (index = 0; index < aList.size; index++)
	{
		aList.get(index, s);
		this->add(s);
	}
}

List::~List()
{
	/*
	Node * curr = head;
	while (curr)
	{
		head = curr->next;
		delete curr;
		curr = head;
	}
	*/
	destroyList(head);
}

void List::destroyList(Node*& currHead)
{
	if (currHead == nullptr)
		return;
	Node * temp = currHead->next;
	delete currHead;
	destroyList(temp);
}

bool List::get(int index, Data& aData) const
{
	if (index < 0 || index >= size)
		return false;
	Node * curr = head;
	int i = 0;
	while (curr && i < index)
	{
		curr = curr->next;
		i++;
	}
	aData = curr->aData;
	return true;
}

void List::add(const Data& aData)
{
	Node * prev = nullptr;
	Node * curr = head;	
	Node * newNode = new Node(aData);

	while (curr && isLessThanByGpa(curr->aData, aData)/*curr->aData < aData*/)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!prev)
	{
		head = newNode;
	}
	else
	{
		prev->next = newNode;
	}	
	newNode->next = curr;
	size++;
}

void List::listAll() const
{
	for (Node * curr = head; curr; curr = curr->next)
	{
		cout << curr->aData << endl;
	}
}

void List::listAllRecursive() const
{
	listAllRecursive(head);
}

void List::listAllRecursive(Node * currHead) const
{
	if (currHead)
	{
		listAllRecursive(currHead->next);
		cout << currHead->aData << endl;
		
	}
}

int List::getSize() const
{
	return getSize(head);
}

int List::getSize(Node * currHead) const
{
	if (!currHead)
		return 0;
	return getSize(currHead->next) + 1;
}

void List::addRecursive(const Data& aData)
{
	addRecursive(head, aData);
	size++;
}

void List::addRecursive(Node*& currHead, const Data& aData)
{
	if (!currHead)
	{
		currHead = new Node(aData);
	}
	else if (aData < currHead->aData)
	{
		Node * newNode = new Node(aData);
		newNode->next = currHead;
		currHead = newNode;
	}
	else
	{
		addRecursive(currHead->next, aData);
	}
}
ostream& operator<< (ostream& out, const List& aList)
{
	//aList.listAll();
	aList.listAllRecursive();
	return out;
}