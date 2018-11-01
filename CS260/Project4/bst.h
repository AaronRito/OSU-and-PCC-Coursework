#ifndef BST_H
#define BST_H

#include "data.h"
#include "myutil.h"
#include <cstring>
class BST
{
public:
	BST();
	BST(char * fileName);
	BST(const BST& aTable);
	~BST();

	void insert(const aData& aData);
	bool remove(char * key1);
	bool retrieve(char * key, aData& aData)const;
	bool retrieveProd(char * key, aData& aData)const;
	void displayName(void)const;
	void displayProd(void)const;
	int getSize(void)const;
	void writeOut(char * fileName);
	const BST& operator= (const BST& aTable);

private:

	struct nameNode
	{
		aData item;
		nameNode * left, * right;
		nameNode(const aData& aData)
		{
			item = aData;
			left = right = NULL;
		}
	};
	nameNode * root;	
	int nameSize;	
	void insertName(nameNode*& root, const aData& aData);
	bool retrieveName(nameNode * root, char * key, aData& aData) const;
	bool remove(nameNode*& root, char * key);
	void deleteNode(nameNode *& target);
	void displayName(nameNode * root) const;
	void writeOut(ofstream& out, nameNode * root);
	void destroyTable(nameNode*& root);
	void copyTable(nameNode*& newRoot, nameNode * root);

	struct prodNode
	{
		aData item;
		prodNode * left, *right;
		prodNode(const aData& aData)
		{
			item = aData;
			left = right = NULL;
		}
	};
	prodNode * prodRoot;
	int prodSize;
	void insertProd(prodNode*& prodRoot, const aData& aData);
	bool retrieveProd(prodNode * prodRoot, char * key, aData& aData) const;
	bool removeProd(prodNode*& prodRoot, char * key);
	void deleteNodeProd(prodNode *& targetP);
	void displayProd(prodNode * prodRoot) const;
	void destroyTableProd(prodNode *& root);
	void copyTableProd(prodNode*& newRoot, prodNode * root);
};

#endif