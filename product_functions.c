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
	Productptr pnode = (Productptr)malloc(sizeof(ProductNode)); 

	pnode->NBD_Number = NBD_Number; 
	pnode->long_name = NULL;
	pnode->manufacturer = NULL;
	pnode->energy = NULL;
	pnode->carbs = NULL;
	pnode->fat = NULL;
	pnode->protein = NULL;
	pnode->serving_size = NULL;
	pnode->serving_size_units = NULL;
	pnode->household_serving_size = NULL;
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

Productptr insert(Productptr pnode, int NBD_Number) {
	// 1) Do a typical BST insert
	if (node == NULL)
		return newProductNode(NBD_Number); 
}