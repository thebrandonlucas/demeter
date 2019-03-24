#include <stdlib.h>
// TODO: delete stdio after deleting preorder
#include <stdio.h>
#include <string.h>
#include "product.h"
#include "auxiliary.h"

/*
	This file provides the definitions for functions
	used in the maintenance of the product AVL tree. 
*/

Productptr root = NULL; 

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

Productptr treeSearch(Productptr root, char *key) {
	if ((root->left == NULL || root->right == NULL) || strcmp(key, root->long_name) == 0)
		return root; 
	if (strcmp(key, root->long_name) < 0)
		return treeSearch(root->left, key);
	return treeSearch(root->right, key);
}

// TODO: Change tempnode to "data" or some better name
Productptr treeInsert(Productptr pnode, Productptr tempnode) {
	char *key = tempnode->long_name; 
	if (pnode == NULL)
		return newProductNode(tempnode); 

	Productptr temp; 
	if (strcmp(key, pnode->long_name) < 0) {
		temp = treeInsert(pnode->left, tempnode);
		pnode->left = temp; 
		temp->parent = pnode; 
	}
	else if (strcmp(key, pnode->long_name) > 0) {
		temp = treeInsert(pnode->right, tempnode);
		pnode->right = temp;
		temp->parent = pnode;
	}
	else {
		return pnode;
	}

	// update height of ancestor node 
	pnode->treeHeight = 1 + max(treeHeight(pnode->left), treeHeight(pnode->right)); 

	// get balance factor to check whether this node is now unbalanced
	int balanceFactor = getBalanceFactor(pnode); 

	// left left case
	if (balanceFactor > 1 && strcmp(key, pnode->left->long_name) < 0)
		return rightRotate(pnode); 

	// right right case 
	if (balanceFactor < -1 && strcmp(key, pnode->right->long_name) > 0)
		return leftRotate(pnode); 

	// left right case 
	if (balanceFactor > 1 && strcmp(key, pnode->left->long_name) > 0) {
		pnode->left = leftRotate(pnode->left); 
		return rightRotate(pnode); 
	}

	// right left case 
	if (balanceFactor < -1 && strcmp(key, pnode->right->long_name) < 0) {
		pnode->right = rightRotate(pnode->right); 
		return leftRotate(pnode); 
	}
	
	// return the original node
	return pnode;
}

// TODO: change pnode to node
Productptr treeDelete(Productptr pnode, int key) {
	if (pnode == NULL)
		return pnode; 
	if (key < pnode->NBD_Number)
		pnode->left = treeDelete(pnode->left, key);
	else if (key > pnode->NBD_Number)
		pnode->right = treeDelete(pnode->right, key); 
	else {
		// if node has only one child or no child
		if ((pnode->left == NULL) || (pnode->right == NULL)) {
			Productptr temp = pnode->left ? pnode->left : pnode->right; 

			// no children
			if (temp == NULL) {
				temp = pnode;
				pnode = NULL; 
			}
			// one child
			else 
				*pnode = *temp; 
			free(temp); 				
		}
		// node with two children
		else {
			Productptr temp = treeMinimum(pnode->right); 

			pnode->NBD_Number = temp->NBD_Number;
			pnode->long_name = temp->long_name;
			pnode->manufacturer = temp->manufacturer;
			pnode->energy = temp->energy;
			pnode->carbs = temp->carbs;
			pnode->fat = temp->fat;
			pnode->protein = temp->protein;
			pnode->serving_size = temp->serving_size;
			pnode->serving_size_units = temp->serving_size_units;
			pnode->household_serving_size = temp->household_serving_size;
			pnode->household_serving_size_units = temp->household_serving_size_units;

			pnode->right = treeDelete(pnode->right, temp->NBD_Number); 
		}
	}

	if (pnode == NULL)
		return pnode; 

	pnode->treeHeight = max(treeHeight(pnode->left), treeHeight(pnode->right)) + 1; 
	int balanceFactor = getBalanceFactor(pnode); 

	// if tree becomes unbalanced, do one of the four cases
	// left left case
	if (balanceFactor > 1 && getBalanceFactor(pnode->left) >= 0)
		return rightRotate(pnode); 
	// right right case
	if (balanceFactor < -1 && getBalanceFactor(pnode->right) <= 0)
		return leftRotate(pnode); 
	// left right case
	if (balanceFactor > 1 && getBalanceFactor(pnode->left) < 0) {
		pnode->left = leftRotate(pnode->left); 
		return rightRotate(pnode); 
	}
	// right left case
	if (balanceFactor < -1 && getBalanceFactor(pnode->right) > 0) {
		pnode->right = rightRotate(pnode->right); 
		return leftRotate(pnode); 
	}
	return pnode; 
}

// TODO: should I change NBD_number to "key" for consistency?
Productptr treeUpdate(Productptr root, Productptr newData, int key) {

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

Productptr treeMinimum(Productptr pnode) {
	while (pnode->left != NULL)
		pnode = pnode->left; 
	return pnode; 
}

Productptr treeMaximum(Productptr pnode) {
	while (pnode->right != NULL)
		pnode = pnode->right;
	return pnode;
}

Productptr treeSuccessor(Productptr pnode) {
	if (pnode->right != NULL)
		return treeMinimum(pnode->right);
	Productptr y = pnode->parent; 
	while (y != NULL && pnode == y->right) {
		pnode = y; 
		y = y->parent; 
	}
	return y; 
}

Productptr treePredecessor(Productptr pnode) {
	if (pnode->left != NULL)
		return treeMinimum(pnode->left);
	Productptr y = pnode->parent; 
	while (y != NULL && pnode == y->left) {
		pnode = y; 
		y = y->parent; 
	}
	return y; 
}

int getBalanceFactor(Productptr N) {
	if (N == NULL)
		return 0;
	return treeHeight(N->left) - treeHeight(N->right);
}

void printSearchResults(Productptr pnode) {
	Productptr temp = palloc();
	temp = pnode;
	int counter = 1; 
	printf("\n%d - %s\n\n", counter, pnode->long_name);
	for (int i = 0; i < 2; i++) {
		temp = treeSuccessor(temp);
		counter++; 
		printf("%d - %s\n\n", counter, temp->long_name);
	}
	for (int i = 0; i < 2; i++) {
		temp = treePredecessor(temp);
		counter++; 
		printf("%d - %s\n\n", counter, temp->long_name);
	}
}

// A utility function to print preorder traversal 
// of the tree. 
// The function also prints height of every node 
// TODO: delete this function when done with project
void preOrder(Productptr root)
{
	if (root != NULL)
	{
		printf("%s ", root->long_name);
		preOrder(root->left);
		preOrder(root->right);
	}
}