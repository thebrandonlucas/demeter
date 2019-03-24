#ifndef PRODUCT_H
#define PRODUCT_H
#define BUFFER_SIZE 1024
//#define PRODUCTS_SIZE 228805
//#define DERIVATION_CODE_DESCRIPTION_SIZE 9
//#define SERVING_SIZE 237911
//#define NUTRIENTS_SIZE 1048576

typedef struct pnode *Productptr;

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
	Productptr left; 
	Productptr right; 
	Productptr parent; 
} ProductNode;

extern Productptr root; 

// Serves as double-inclusion guard
// A function for finding the max element in a tree
int max(int a, int b);

// A function for finding the height of the tree
int treeHeight(Productptr root);

// A function to allocate a new product
Productptr palloc(void);

// A function to create a new product node
Productptr newProductNode(Productptr tempnode);

// Find node with the matching NBD_Number (key)
Productptr treeSearch(Productptr root, char *key); 

// Insert function
Productptr treeInsert(Productptr pnode, Productptr tempnode);

// Delete a node
Productptr treeDelete(Productptr root, int key); 

// Update contents of node with key
Productptr treeUpdate(Productptr root, Productptr newData, int key);

// Auxiliary rotate functions
Productptr rightRotate(Productptr y); 
Productptr leftRotate(Productptr x);

// To get the Minimum and Maximum nodes
Productptr treeMinimum(Productptr pnode); 
Productptr treeMaximum(Productptr pnode); 

// Get successor and predecessor nodes
Productptr treeSuccessor(Productptr pnode); 
Productptr treePredecessor(Productptr pnode);

// balance factor of node N
int getBalanceFactor(Productptr N); 

// TODO: DELETE
void preOrder(Productptr root); 
#endif
