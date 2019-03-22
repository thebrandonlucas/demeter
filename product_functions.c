#include <stdlib.h>
// TODO: delete stdio after deleting preorder
#include <stdio.h>
#include "product.h"

/*
	This file provides the definitions for functions
	used in the maintenance of the product AVL tree. 
*/

int max(int a, int b) {
	return (a > b) ? a : b; 
}

int treeHeight(Productptr root) {
	if (root == NULL)
		return 0; 
	return root->treeHeight; 
}

Productptr palloc(void) {
	return (Productptr)malloc(sizeof(ProductNode)); 
}

Productptr newProductNode(Productptr tempnode) {
	Productptr pnode = palloc(); 

	pnode->NBD_Number = tempnode->NBD_Number;
	pnode->long_name = tempnode->long_name;
	pnode->manufacturer = tempnode->manufacturer;
	pnode->energy = tempnode->energy;
	pnode->carbs = tempnode->carbs;
	pnode->fat = tempnode->fat;
	pnode->protein = tempnode->protein;
	pnode->serving_size = tempnode->serving_size;
	pnode->serving_size_units = tempnode->serving_size_units;
	pnode->household_serving_size = tempnode->household_serving_size;
	pnode->household_serving_size_units = tempnode->household_serving_size_units;

	// pnode first added as leaf
	pnode->treeHeight = 1; 
	pnode->left = NULL; 
	pnode->right = NULL; 
	return(pnode); 
}

// FIXME: Should I put all the variables that need to go into
// the node in the insert function call? That's ugly, but
// using another pointer for it uses extra memory
// TODO: Change tempnode to "data" or some better name
Productptr insert(Productptr pnode, Productptr tempnode) {
	//printf("hello"); 
	int key = tempnode->NBD_Number; 
	if (pnode == NULL)
		return newProductNode(tempnode); 

	if (key < pnode->NBD_Number)
		pnode->left = insert(pnode->left, tempnode);
	else if (key > pnode->NBD_Number)
		pnode->right = insert(pnode->right, tempnode);
	else
		return pnode;

	// update height of ancestor node 
	pnode->treeHeight = 1 + max(treeHeight(pnode->left), treeHeight(pnode->right)); 

	// get balance factor to check whether this node is now unbalanced
	int balanceFactor = getBalanceFactor(pnode); 

	//// left left case
	if (balanceFactor > 1 && key < pnode->left->NBD_Number)
		return rightRotate(pnode); 

	// right right case 
	if (balanceFactor < -1 && key > pnode->right->NBD_Number)
		return leftRotate(pnode); 

	// left right case 
	if (balanceFactor > 1 && key > pnode->left->NBD_Number) {
		pnode->left = leftRotate(pnode->left); 
		return rightRotate(pnode); 
	}

	// right left case 
	if (balanceFactor < -1 && key < pnode->right->NBD_Number) {
		pnode->left = rightRotate(pnode->right); 
		return rightRotate(pnode); 
	}
	
	// return the original node
	return pnode;
}

Productptr rightRotate(Productptr y) {
	Productptr x = y->left; 
	Productptr beta = x->right; 
	
	// rotate and update the height
	x->right = y; 
	y->left = beta; 
	y->treeHeight = max(treeHeight(y->left), treeHeight(y->right)) + 1; 
	x->treeHeight = max(treeHeight(x->left), treeHeight(x->right)) + 1; 

	return x; 
}

Productptr leftRotate(Productptr x) {
	Productptr y = x->right; 
	Productptr beta = y->left; 

	// rotate and update height
	y->left = x; 
	x->right = beta; 
	x->treeHeight = max(treeHeight(x->left), treeHeight(x->right)) + 1;
	y->treeHeight = max(treeHeight(y->left), treeHeight(y->right)) + 1;

	return y; 
}

int getBalanceFactor(Productptr N) {
	if (N == NULL)
		return 0;
	return treeHeight(N->left) - treeHeight(N->right);
}

// A utility function to print preorder traversal 
// of the tree. 
// The function also prints height of every node 
// TODO: delete this function when done with project
void preOrder(Productptr root)
{
	if (root != NULL)
	{
		printf("%d ", root->NBD_Number);
		preOrder(root->left);
		preOrder(root->right);
	}
}