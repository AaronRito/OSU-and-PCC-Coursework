#include "table.h"

int size(node *root) 
{
	 if(root == NULL) 
	 return 0;
	 else 
         return (size(root->left) + size(root->right) + 1);
}
int sumR(node * root) 
{
	if (root == NULL)
	return 0;
	return (root->data + sumR(root->left) + sumR(root->right));	
}
int height(node * root)
{
	if (root == NULL)
        return -1;
	return (1 + max(height(root->left), height(root->right)));
}
int treeHeight(node * root)
{
   if (root == NULL)
   {
      return -1;
   }

   int left = treeHeight(root->left);
   int right = treeHeight(root->right); 

   return 1 + std::max(left, right);
}
