#ifndef PRODUCT_H
#define PRODUCT_H

/*
	This file contains all of the functions
	dealing with operations on the AVL tree 
	of food products. 
*/

// A descriptive shorthand for the struct pnode, 
// or "product node", type
typedef struct pnode ProductNode;

// A node to store attributes for each product
typedef struct pnode {
	int NBD_Number;
	int key; 
	char* long_name;
	char* manufacturer;
	double energy;
	double carbs;
	double fat;
	double protein;
	double serving_size;
	char* serving_size_units;
	double household_serving_size;
	char* household_serving_size_units;

	// AVL tree attributes
	int treeHeight; 
	ProductNode *left;
	ProductNode *right;
	ProductNode *parent;
} ProductNode;

// A global variable to hold the root of the 
// AVL tree
extern ProductNode *root; 
extern ProductNode *pnode;

// A function for finding the max element in a tree
int maximum(int a, int b);

// A function for finding the height of the tree
int treeHeight(ProductNode *root);

// A function to allocate a new product
ProductNode *palloc(void);

// A function to create a new product node
ProductNode *newProductNode(ProductNode *tempnode);

// Find node with the matching string (key)
ProductNode *treeSearch(ProductNode *root, char *key);

// Insert a node into the tree
ProductNode *treeInsert(ProductNode *pnode, ProductNode *tempnode);

// Deallocate the tree
void deallocateTree(ProductNode *root);

// Auxiliary rotate functions
ProductNode *rightRotate(ProductNode *y);
ProductNode *leftRotate(ProductNode *x);

// To get the Minimum and Maximum nodes
ProductNode *treeMinimum(ProductNode *pnode);
ProductNode *treeMaximum(ProductNode *pnode);

// Get successor and predecessor nodes
ProductNode *treeSuccessor(ProductNode *pnode);
ProductNode *treePredecessor(ProductNode *pnode);

// Balance factor of node N
int getBalanceFactor(ProductNode *N);
#endif
