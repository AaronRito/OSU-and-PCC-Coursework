#include "table.h"

//Please put the impelementation of the required functions here int 
int sumR(node * root)
{
	if (root == NULL)
	return 0;
	return (root->data + sumR(root->left) + sumR(root->right));
}
void copyLeaf(node * root, node *& newRoot) {
	
	if (root)
	{
		if (!root->left && !root->right)
		{
			//copy root
			addNode(&newRoot, root->data);
			copyLeaf(root->left, newRoot->left);
			copyLeaf(root->right, newRoot->right);
			
		}
		else
		{
			copyLeaf(root->left, newRoot);
			copyLeaf(root->right, newRoot);
		
		}
	}
	else 
	{
		newRoot = NULL;
	}

}
void addNode(node ** root, int key) {
	node * temp = NULL;
	if(!(*root))
	{
		temp = (node *)new node;
		temp->left = temp->right = NULL;
		temp->data = key;
		*root = temp;
		return;
	}
	if (key < (*root)->data)
		addNode(&(*root)->left, key);
	else
		addNode(&(*root)->right, key);
}
void removeEven(node *& root) {
	int num = root->data;
	cout << "Data to be removed: " << num << endl;
	
		if (!root->left && !root->right)
		{
			//cout << "NO CHILDREN" << endl;
			delete root;
			root = NULL;
		}
		//no left child
		else if (!root->left && root->right)
		{
			//cout << "NO LEFT CHILD" << endl;
			
			node * temp = root->right;
			root->data = temp->data;
			if (temp->left)
				root->left = temp->left;
			if (temp->right)
				root->right = temp->right;
			else
				root->right = NULL;
			delete temp;
		}
		//no right child
		else if (!root->right && root->left)
		{
			//cout << "NO RIGHT CHILD" << endl;
			node * temp = root->left;
			root->data = temp->data;
			if(temp->right)
				root->right = temp->right;
			if(temp->left)
				root->left = temp->left;
			else
				root->left = NULL;
			delete temp;
		}
		//two children
		else
		{
			//cout << "TWO ANNOYING CHILDREN TO BE FED TO " << endl;
			node * temp = root->right;
			node * spot = NULL;
			while(temp->left)
			{
				spot = temp;
				temp = temp->left;
			}
			root->data = temp->data;
			if (spot && temp->right)
			{
				spot->left = temp->right;
				delete temp;
			}
			else if(spot && !temp->right)
			{
				delete temp;
				spot->left = NULL;
			}
			else if (!spot)
			{
				root->data = temp->data;
				if (temp->left)
					root->left = temp->left;
				if(temp->right)
					root->right = temp->right;
				else
					root->right = NULL;
				delete temp;
			}	
		}
	//cout << "END REMOVEEVEN" << endl;
}
aaron.rito@syccuxas01:~/cs260/final> ./main
Welcome to the Proficiency Demo!

Inorder traversal: 1  62  64  76  100  100  118  129  138  156  170  249

Level 1: 138
Level 2: 118 and 156
Level 3: 1 and 129
Level 4: 76
Level 5: 64 and 100
Level 6: 62
Level 6: 100
Level 3: 170
Level 4: 249


This tree contains 12 items
The sum of the data is: 1363
The copy of the leaves is:


The resulting tree after your function ran is:
Inorder traversal: 249

Level 1: 249


This tree contains 1 items


The resulting tree after your function ran is:
Inorder traversal: 1  62  64  76  100  100  118  129  138  156  170  249

Level 1: 138
Level 2: 118 and 156
Level 3: 1 and 129
Level 4: 76
Level 5: 64 and 100
Level 6: 62
Level 6: 100
Level 3: 170
Level 4: 249

