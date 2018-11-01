#include "table.h"

//Please put the impelementation of the required functions here
#include "table.h"
int getMin(node * root)
{	if(!root)
		return 0;
	if(root->left) 
		return getMin(root->left);
	return root->data;
}
int getMax(node * root)
{
	if(!root)
		return 0;
	else
	return max(root->data, max(getMax(root->left), getMax(root->right)));
}	
bool removeLargest(node *& root)
{
	if (!root)
		return false;
	else if (!root->left && !root->right)
	{	
		//cout << "LOWEST NODE HAD NO CHILDREN" << endl;
		delete root;
		root = NULL;
		return true;
	}
	else if (root->left && !root->right)
	{	
		node * temp = root->left;
		root->data = temp->data;
		if (!temp->left && !temp->right)
		{
			//cout << "LOWEST NODE left CHILD HAS NO CHILDREN" << endl;
			delete temp; 
			root->left = NULL; 
			return true;
		}
		else
		{	
			//cout << "LOWEST NODE left CHILD HAD A CHILD" << endl;
			if (temp->left)
				root->left = temp->left;
			else 
				root->left = NULL;
			if (temp->right)
				root->right = temp->right;
			else 
				root->right = NULL;
			delete temp;
			return true;
		}
	}
	else
		return (removeLargest(root->right));
}
bool retrieve(node * root, int  key) 
{
	if (!root)
	{	
		cout << "Empty list" << endl;
		return false;
	}
	else
	{
		int temp = root->data;
		if (temp == key)
		{
			cout << "Item found: " << temp << endl;
			return true;
		}
		else if (temp < key)
		{
			return retrieve(root->right, key);
		}
		else
		{
			return retrieve(root->left, key);
		}
	}
}

bool remove(node *& root)
{
	if (!root)
		return false;
	if (root->data % 2  == 0)
	{
		removeEven(root);
		return remove(root);
	}
		return (remove(root->left), remove(root->right));
}

void removeEven(node *& root)
{	
	int num = root->data;
	cout << "Data to be removed: " << num <<  endl;
	
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
			//cout << "TWO ANNOYING CHILDREN TO BE FED TO LIONS" << endl;
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
int numberOfNodes(node *root) {
	 if(root == NULL)
	 return 0;
	 else
         return (numberOfNodes(root->left) + numberOfNodes(root->right) + 1);
}

int sumR(node * root) {
	if (root == NULL)
	return 0;
	return (root->data + sumR(root->left) + sumR(root->right));
}

int height(node * root) {
	if (root == NULL)
        return 0 ;
	return (1 + max(height(root->left), height(root->right)));
}

int treeHeight(node * root) {
   if (root == NULL)
   {
      return 0;
   }
   int left = treeHeight(root->left);
   int right = treeHeight(root->right);
   return 1 + std::max(left, right);
}

bool removeSmallest(node *& root)
{
	if (!root)
		return false;
	else if (!root->left && !root->right)
	{	
		//cout << "LOWEST NODE HAD NO CHILDREN" << endl;
		delete root;
		root = NULL;
		return true;
	}
	else if (!root->left && root->right)
	{	
		node * temp = root->right;
		root->data = temp->data;
		if (!temp->left && !temp->right)
		{
			//cout << "LOWEST NODE RIGHT CHILD HAS NO CHILDREN" << endl;
			delete temp; 
			root->right = NULL; 
			return true;
		}
		else
		{	
			//cout << "LOWEST NODE RIGHT CHILD HAD A CHILD" << endl;
			if (temp->right)
				root->right = temp->right;
			else 
				root->right = NULL;
			if (temp->left)
				root->left = temp->left;
			else 
				root->left = NULL;
			delete temp;
			return true;
		}
	}
	else
		return (removeSmallest(root->left));
}	
void addNode(node ** root, int key)
{
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
