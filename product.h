#ifndef PRODUCT_H
#define PRODUCT_H
//#define PRODUCTS_SIZE 228805
//#define DERIVATION_CODE_DESCRIPTION_SIZE 9
//#define SERVING_SIZE 237911
//#define NUTRIENTS_SIZE 1048576

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

extern ProductNode *root; 
extern ProductNode *pnode;

// Serves as double-inclusion guard
// A function for finding the max element in a tree
int maximum(int a, int b);

// A function for finding the height of the tree
int treeHeight(ProductNode *root);

// A function to allocate a new product
ProductNode *palloc(void);

// Free all nodes at end of program
void pfree(ProductNode *root);

// A function to create a new product node
ProductNode *newProductNode(ProductNode *tempnode);

// Find node with the matching NBD_Number (key)
ProductNode *treeSearch(ProductNode *root, char *key);

// Insert function
ProductNode *treeInsert(ProductNode *pnode, ProductNode *tempnode);

// Deallocate the tree
void deallocateTree(ProductNode *root);

void deallocateChar(char *time);

// Delete a node
//Productptr treeDelete(Productptr root, int key); 

// Update contents of node with key
ProductNode *treeUpdate(ProductNode *root, ProductNode *newData, int key);

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

// TODO: DELETE
void preOrder(ProductNode *root);
#endif
