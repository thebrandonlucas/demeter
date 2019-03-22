#include <stdlib.h>
#include "product.h"

/*
	This file provides the definitions for functions
	used in the maintenance of the product AVL tree. 
*/

int max(int a, int b) {
	return (a > b) ? a : b; 
}

int height(Productptr root) {
	if (root == NULL)
		return 0; 
	return root->treeHeight; 
}

Productptr palloc(void) {
	return (Productptr)malloc(sizeof(ProductNode)); 
}

Productptr newProductNode(int NBD_Number) {
	Productptr pnode = palloc(); 
	//Productptr pnode = (Productptr)malloc(sizeof(ProductNode)); 

	pnode->NBD_Number = NBD_Number; 
	pnode->long_name = NULL;
	pnode->manufacturer = NULL;
	pnode->energy = 0.0;
	pnode->carbs = 0.0;
	pnode->fat = 0.0;
	pnode->protein = 0.0;
	pnode->serving_size = 0.0;
	pnode->serving_size_units = NULL;
	pnode->household_serving_size = 0.0;
	pnode->household_serving_size_units = NULL;
	//pnode->long_name = long_name;
	//pnode->manufacturer = manufacturer;
	//pnode->energy = energy;
	//pnode->carbs = carbs;
	//pnode->fat = fat;
	//pnode->protein = protein;
	//pnode->serving_size = serving_size;
	//pnode->serving_size_units = serving_size_units;
	//pnode->household_serving_size = household_serving_size;
	//pnode->household_serving_size_units = household_serving_size_units;

	// pnode first added as leaf
	pnode->treeHeight = 1; 
	pnode->left = NULL; 
	pnode->right = NULL; 
	return pnode; 
}

// FIXME: Should I put all the variables that need to go into
// the node in the insert function call? That's ugly, but
// using another pointer for it uses extra memory
Productptr insert(Productptr pnode, Productptr tempnode) {
	// 1) Do a typical BST insert
	if (pnode == NULL)
		return newProductNode(tempnode->NBD_Number); 
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

	// new pnode is a leaf
	pnode->treeHeight = 1; 
	pnode->left = NULL; 
	pnode->right = NULL; 
	return pnode; 
}