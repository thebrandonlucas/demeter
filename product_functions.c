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

ProductNode *root = NULL;
ProductNode *pnode = NULL;

int maximum(int a, int b) {
	return (a > b) ? a : b; 
}

int treeHeight(ProductNode *root) {
	if (root == NULL)
		return 0; 
	return root->treeHeight; 
}

ProductNode *palloc(void) {
	ProductNode *pnode = malloc(sizeof(ProductNode));
	if (pnode == NULL) {
		printf("Error: out of memory\n");
		printf("Exiting...\n"); 
		exit(0);
	}
	return pnode; 
}

void pfree(ProductNode *root) {
	ProductNode *temp = palloc();
	if (root != NULL) {
		temp = root->left; 
		free(root->left); 
		pfree(temp->left); 
		temp = root->right; 
		free(root->right); 
		pfree(root->right); 
	}
	free(temp); 
}

ProductNode *newProductNode(ProductNode *tempnode) {
	ProductNode *pnode = palloc();

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

ProductNode *treeSearch(ProductNode *root, char *key) {
	char rootName[BUFFER_SIZE] = ""; char keyName[BUFFER_SIZE] = ""; 
	strncpy(rootName, root->long_name, strlen(root->long_name));
	strncpy(keyName, key, strlen(root->long_name));
	stripSpace(rootName); stripSpace(keyName);
	uppercase(rootName); uppercase(keyName);
	if (strncmp(keyName, rootName, strlen(keyName)) == 0)
		return root;
	if (strncmp(keyName, rootName, strlen(rootName)) < 0) {
		if (root->left == NULL) return root;
		return treeSearch(root->left, key);
	}
	if (root->right == NULL) return root;
	return treeSearch(root->right, key);
}

// TODO: Change tempnode to "data" or some better name
ProductNode *treeInsert(ProductNode *pnode, ProductNode *tempnode) {
	char *key = tempnode->long_name; 
	if (pnode == NULL)
		return newProductNode(tempnode); 

	ProductNode *temp;
	if (strncmp(key, pnode->long_name, strlen(key)) < 0) {
		temp = treeInsert(pnode->left, tempnode);
		pnode->left = temp; 
		temp->parent = pnode; 
	}
	else if (strncmp(key, pnode->long_name, strlen(key)) > 0) {
		temp = treeInsert(pnode->right, tempnode);
		pnode->right = temp;
		temp->parent = pnode;
	}
	else {
		return pnode;
	}

	// update height of ancestor node 
	pnode->treeHeight = 1 + maximum(treeHeight(pnode->left), treeHeight(pnode->right));

	// get balance factor to check whether this node is now unbalanced
	int balanceFactor = getBalanceFactor(pnode); 

	// left left case
	if (balanceFactor > 1 && strncmp(key, pnode->left->long_name, strlen(key)) < 0)
		return rightRotate(pnode); 

	// right right case 
	if (balanceFactor < -1 && strncmp(key, pnode->right->long_name, strlen(key)) > 0)
		return leftRotate(pnode); 

	// left right case 
	if (balanceFactor > 1 && strncmp(key, pnode->left->long_name, strlen(key)) > 0) {
		pnode->left = leftRotate(pnode->left); 
		return rightRotate(pnode); 
	}

	// right left case 
	if (balanceFactor < -1 && strncmp(key, pnode->right->long_name, strlen(key)) < 0) {
		pnode->right = rightRotate(pnode->right); 
		return leftRotate(pnode); 
	}
	
	// return the original node
	return pnode;
}

void deallocateTree(ProductNode *root) {
	if (root == NULL)
		return; 
	deallocateTree(root->left); 
	deallocateTree(root->right); 
	free(root); 
}

void deallocateChar(char *time) {
	if (time == NULL)
		return; 
	free(time); 
}

// TODO: change pnode to node
//Productptr treeDelete(Productptr pnode, int key) {
//	if (pnode == NULL)
//		return pnode; 
//	if (key < pnode->NBD_Number)
//		pnode->left = treeDelete(pnode->left, key);
//	else if (key > pnode->NBD_Number)
//		pnode->right = treeDelete(pnode->right, key); 
//	else {
//		 if node has only one child or no child
//		if ((pnode->left == NULL) || (pnode->right == NULL)) {
//			Productptr temp = pnode->left ? pnode->left : pnode->right; 
//
//			 no children
//			if (temp == NULL) {
//				temp = pnode;
//				pnode = NULL; 
//			}
//			 one child
//			else 
//				*pnode = *temp; 
//			free(temp); 				
//		}
//		 node with two children
//		else {
//			Productptr temp = treeMinimum(pnode->right); 
//
//			pnode->NBD_Number = temp->NBD_Number;
//			pnode->long_name = temp->long_name;
//			pnode->manufacturer = temp->manufacturer;
//			pnode->energy = temp->energy;
//			pnode->carbs = temp->carbs;
//			pnode->fat = temp->fat;
//			pnode->protein = temp->protein;
//			pnode->serving_size = temp->serving_size;
//			pnode->serving_size_units = temp->serving_size_units;
//			pnode->household_serving_size = temp->household_serving_size;
//			pnode->household_serving_size_units = temp->household_serving_size_units;
//
//			pnode->right = treeDelete(pnode->right, temp->NBD_Number); 
//		}
//	}
//
//	if (pnode == NULL)
//		return pnode; 
//
//	pnode->treeHeight = max(treeHeight(pnode->left), treeHeight(pnode->right)) + 1; 
//	int balanceFactor = getBalanceFactor(pnode); 
//
//	 if tree becomes unbalanced, do one of the four cases
//	 left left case
//	if (balanceFactor > 1 && getBalanceFactor(pnode->left) >= 0)
//		return rightRotate(pnode); 
//	 right right case
//	if (balanceFactor < -1 && getBalanceFactor(pnode->right) <= 0)
//		return leftRotate(pnode); 
//	 left right case
//	if (balanceFactor > 1 && getBalanceFactor(pnode->left) < 0) {
//		pnode->left = leftRotate(pnode->left); 
//		return rightRotate(pnode); 
//	}
//	 right left case
//	if (balanceFactor < -1 && getBalanceFactor(pnode->right) > 0) {
//		pnode->right = rightRotate(pnode->right); 
//		return leftRotate(pnode); 
//	}
//	return pnode; 
//}

// TODO: should I change NBD_number to "key" for consistency?
//Productptr treeUpdate(Productptr root, Productptr newData, int key) {
//
//}

ProductNode *rightRotate(ProductNode *y) {
	ProductNode *x = y->left;
	ProductNode *beta = x->right;
	
	// rotate and update the height
	x->right = y; 
	y->left = beta; 
	y->treeHeight = maximum(treeHeight(y->left), treeHeight(y->right)) + 1;
	x->treeHeight = maximum(treeHeight(x->left), treeHeight(x->right)) + 1;

	return x; 
}

ProductNode *leftRotate(ProductNode *x) {
	ProductNode *y = x->right;
	ProductNode *beta = y->left;

	// rotate and update height
	y->left = x; 
	x->right = beta; 
	x->treeHeight = maximum(treeHeight(x->left), treeHeight(x->right)) + 1;
	y->treeHeight = maximum(treeHeight(y->left), treeHeight(y->right)) + 1;

	return y; 
}

ProductNode *treeMinimum(ProductNode *pnode) {
	while (pnode->left != NULL)
		pnode = pnode->left; 
	return pnode; 
}

ProductNode *treeMaximum(ProductNode *pnode) {
	while (pnode->right != NULL)
		pnode = pnode->right;
	return pnode;
}

ProductNode *treeSuccessor(ProductNode *pnode) {
	if (pnode->right != NULL)
		return treeMinimum(pnode->right);
	ProductNode *y = pnode->parent;
	while (y != NULL && pnode == y->right) {
		pnode = y; 
		y = y->parent; 
	}
	return y; 
}

ProductNode *treePredecessor(ProductNode *pnode) {
	if (pnode->left != NULL)
		return treeMinimum(pnode->left);
	ProductNode *y = pnode->parent;
	while (y != NULL && pnode == y->left) {
		pnode = y; 
		y = y->parent; 
	}
	return y; 
}

int getBalanceFactor(ProductNode *N) {
	if (N == NULL)
		return 0;
	return treeHeight(N->left) - treeHeight(N->right);
}

// A utility function to print preorder traversal 
// of the tree. 
// The function also prints height of every node 
// TODO: delete this function when done with project
void preOrder(ProductNode *root)
{
	if (root != NULL)
	{
		printf("%s \n", root->long_name);
		preOrder(root->left);
		preOrder(root->right);
	}
}