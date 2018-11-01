#include "BST.h"
#include <iostream>
#include <fstream>
using namespace std;

/************************
private:
	node * root;	
	int size;
************************/

/******************************************* EVERYTHING BELOW HERE WORKS**********************************************/
BST::BST() : root(NULL), nameSize(0), prodRoot(NULL), prodSize(0)
{
}

BST::BST(char * fileName) : root(NULL), nameSize(0), prodRoot(NULL), prodSize(0)
{
	ifstream in;
	aData currData;
	char name[MAX_CHAR], phone[MAX_CHAR], prod[MAX_CHAR], evt[MAX_CHAR];
	//initialize the table with the records in the file
	in.open(fileName);
	if(!in)
	{
		cerr << "fail to open " << fileName << " for input!" << endl;
		exit(1);
	}
	in.get(name, MAX_CHAR, ';');
	while(!in.eof())
	{
		//read in the attributes of current record
		in.ignore(MAX_CHAR, ';');
		in.get(phone, MAX_CHAR, ';');
		in.ignore(MAX_CHAR, ';');
		in.get(prod, MAX_CHAR, ';');
		in.ignore(MAX_CHAR, ';');
		in.get(evt, MAX_CHAR, '\n');
		in.ignore(MAX_CHAR, '\n');
		//populate current data 
		currData.setName (name);
		currData.setPhone(phone);
		currData.setProd(prod);
		currData.setEvt(evt);	
		//add current data to the table
		insert(currData);
		//start reading in next record 
		in.get(name, MAX_CHAR, ';');
	}
	in.close ();
}
void BST::insert (const aData& tData)
{	
	insertName(root, tData);
	insertProd(prodRoot, tData);
}

void BST::insertName (nameNode*& root, const aData& tData)
{
	char name1[MAX_CHAR];
	char name2[MAX_CHAR];
	if (root)
	{
		root->item.getName(name1);
		tData.getName(name2);
	}
	if(!root)
	{
		root = new nameNode(tData);
		nameSize++;
	}
	else if(strcmp(name1, name2) > 0 )
	{
		insertName(root->left, tData);
	}
	else
	{
		insertName(root->right, tData);
	}
}
void BST::insertProd(prodNode*& prodRoot, const aData& tData)
{
	char name1[MAX_CHAR];
	char name2[MAX_CHAR];
	if (prodRoot)
	{
		prodRoot->item.getProd(name1);
		tData.getProd(name2);
	}
	if (!prodRoot)
	{
		prodRoot = new prodNode(tData);
		prodSize++;
	}
	else if (strcmp(name1, name2) > 0)
	{
		insertProd(prodRoot->left, tData);
	}
	else
	{
		insertProd(prodRoot->right, tData);
	}
}

BST::BST(const BST& aTable) :root(NULL), nameSize(aTable.nameSize)
{
	*this = aTable;
}

const BST& BST::operator= (const BST& aTable)
{
	if (this == &aTable)
		return *this;
	else
	{
		//release dynamically allocated memory held by current object
		destroyTable(root);
		destroyTableProd(prodRoot);

		//copy the table
		copyTable(root, aTable.root);
		copyTableProd(prodRoot, aTable.prodRoot);
		return *this;
	}
}

void BST::copyTable(nameNode*& newRoot, nameNode * root)
{
	if (root)
	{
		//copy root
		newRoot = new nameNode(root->item);
		copyTable(newRoot->left, root->left);
		copyTable(newRoot->right, root->right);
	}
	else
	{
		newRoot = NULL;
	}
}
void BST::copyTableProd(prodNode*& newRoot, prodNode * root)
{
	if (root)
	{
		//copy root
		newRoot = new prodNode(root->item);
		copyTableProd(newRoot->left, root->left);
		copyTableProd(newRoot->right, root->right);
	}
	else
	{
		newRoot = NULL;
	}
}

BST::~BST()
{
	destroyTable(root);
	destroyTableProd(prodRoot);
}

void BST::destroyTable(nameNode *& root)
{
	if (root)
	{
		destroyTable(root->left);
		destroyTable(root->right);
		delete root;
		root = NULL;
	}
}

void BST::destroyTableProd(prodNode *& root)
{
	if (root)
	{
		destroyTableProd(root->left);
		destroyTableProd(root->right);
		delete root;
		root = NULL;
	}
}

bool BST::retrieve(char * key, aData & tData)const
{
	return retrieveName(root, key, tData);
}

bool BST::retrieveName(nameNode * root, char * key, aData& tData) const
{
	if (!root)
	{
		return false;
	}

	char name[100];
	root->item.getName(name);
	int temp = strcmp(name, key);
	if (temp == 0)
	{
		tData = root->item;
		return true;
	}
	else if (temp < 0)
	{
		return retrieveName(root->right, key, tData);
	}
	else
	{
		return retrieveName(root->left, key, tData);
	}
}
int BST::getSize(void) const
{
	return nameSize;
}

void BST::writeOut(char * fileName)
{
	ofstream out;

	out.open(fileName);
	if (!out)
	{
		cerr << "fail to open " << fileName << " for output!" << endl;
		exit(1);
	}

	writeOut(out, root);
	out.close();
}
void BST::writeOut(ofstream& out, nameNode * root)
{
	if (root)
	{
		char name[MAX_CHAR], phone[MAX_CHAR], prod[MAX_CHAR], evt[MAX_CHAR];
		root->item.getName(name);
		root->item.getPhone(phone);
		root->item.getProd(prod);
		root->item.getEvt(evt);

		out << name << ';' << phone << ';' << prod << ';' << evt << '\n';

		writeOut(out, root->left);
		writeOut(out, root->right);
	}
}
bool BST::retrieveProd(char * key, aData & tData)const
{
	return retrieveProd(prodRoot, key, tData);
}

bool BST::retrieveProd(prodNode * root, char * key, aData& tData) const
{
	if (!root)
	{
		return false;
	}

	char name[100];
	root->item.getProd(name);
	int temp = strcmp(name, key);
	if (temp == 0)
	{
		tData = root->item;
		return true;
	}
	else if (temp < 0)
	{
		return retrieveProd(root->right, key, tData);
	}
	else
	{
		return retrieveProd(root->left, key, tData);
	}
}
void BST::displayName(void)const
{
	cout << "Data in the table: " << endl << endl;
	displayName(root);
}

void BST::displayName(nameNode * root)const
{
	if (root)
	{
		displayName(root->left);
		cout << '\t' << root->item << endl;
		displayName(root->right);
	}
}
void BST::displayProd(void)const
{
	cout << "Data in the table: " << endl << endl;
	displayProd(prodRoot);
}

void BST::displayProd(prodNode * root)const
{
	char name[MAX_CHAR], phone[MAX_CHAR], prod[MAX_CHAR], evt[MAX_CHAR];
	if (root)
	{
		displayProd(root->left);
		root->item.getName(name);
		root->item.getPhone(phone);
		root->item.getProd(prod);
		root->item.getEvt(evt);
		cout << '\t' << "Product: " <<  prod << '\t'<< "Name: " <<name << '\t'<< "Phone: " << phone << '\t'<< "Events: " << evt<< endl;
		displayProd(root->right);
	}
}

bool BST::remove(char * key)
{
	return remove(root, key);
}
bool BST::remove(nameNode*& root, char * key)
{
	if (!root)
		return false;
	char name[MAX_CHAR];
	char prod[MAX_CHAR];
	root->item.getName(name);
	int temp = strcmp(name, key);
	if (temp == 0)
	{
		root->item.getProd(prod);
		removeProd(prodRoot, prod);
		deleteNode(root);
		return true;
	}
	else if (temp < 0)
		return remove(root->right, key);
	else
		return remove(root->left, key);
}
bool BST::removeProd(prodNode*& root, char * key)
{
	if (!root)
		return false;
	char name[100];
	root->item.getProd(name);
	int temp = strcmp(name, key);
	if (temp == 0)
	{
		deleteNodeProd(root);
		return true;
	}
	else if (temp < 0)
		return removeProd(root->right, key);
	else
		return removeProd(root->left, key);
}
void BST::deleteNode(nameNode *& target)
{
	nameNode * temp;
	int nameDone = 0;
	//deleting from name tree
	while (!nameDone) {
		//a leaf
		if (!target->left && !target->right)
		{
			delete target;
			target = NULL;
		}
		//no left child
		else if (!target->left)
		{
			temp = target;
			target = target->right;
			temp->right = NULL;
			delete temp;
		}
		//no right child
		else if (!target->right)
		{
			temp = target;
			target = target->left;
			temp->left = NULL;
			delete temp;
		}
		//two children
		else
		{
			//find the inorder successor
			nameNode * prev = NULL;
			nameNode * curr = target->right;
			while (curr->left)
			{
				prev = curr;
				curr = curr->left;
			}

			//copy data at curr (the inorder successor) into target
			target->item = curr->item;

			//disconnect curr (the inorder successor)
			if (!prev)
				target->right = curr->right;
			else
				prev->left = curr->right; //the inorder successor could have a right child

										  //delete curr (the inorder successor)
			curr->right = NULL;
			delete curr;
		}
		nameSize--;
		nameDone = 1;
	}
}
void BST::deleteNodeProd(prodNode *& targetP)
{
	//deleting from product tree 
	prodNode * temp2;
	//a leaf
	if (!targetP->left && !targetP->right)
	{
		delete targetP;
		targetP = NULL;
	}
	//no left child
	else if (!targetP->left)
	{
		temp2 = targetP;
		targetP = targetP->right;
		temp2->right = NULL;
		delete temp2;
	}
	//no right child
	else if (!targetP->right)
	{
		temp2 = targetP;
		targetP = targetP->left;
		temp2->left = NULL;
		delete temp2;
	}
	//two children
	else
	{
		//find the inorder successor
		prodNode * prev2 = NULL;
		prodNode * curr2 = targetP->right;
		while (curr2->left)
		{
			prev2 = curr2;
			curr2 = curr2->left;
		}

		//copy data at curr (the inorder successor) into target
		targetP->item = curr2->item;

		//disconnect curr (the inorder successor)
		if (!prev2)
			targetP->right = curr2->right;
		else
			prev2->left = curr2->right; //the inorder successor could have a right child

										//delete curr (the inorder successor)
		curr2->right = NULL;
		delete curr2;
	}
	prodSize--;
}
if (temp->right)
	root->right = temp->right;
else
    root->right = NULL;
if (temp->left)
    root->left = temp->left;
else
    root->left = NULL;
delete temp;

