#define BUFFER_SIZE 1024
#define PRODUCTS_SIZE 228805
#define DERIVATION_CODE_DESCRIPTION_SIZE 9
#define SERVING_SIZE 237911
#define NUTRIENTS_SIZE 1048576

typedef struct pnode *Productptr;

// A node to store attributes for each product
typedef struct pnode {
	int NBD_Number;
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
} ProductNode;

// Serves as double-inclusion guard
#ifndef PRODUCT_H
#define PRODUCT_H
// A function for finding the max element in a tree
int max(int a, int b);

// A function for finding the height of the tree
int height(Productptr root);

// A function to allocate a new product
Productptr palloc(void);

// A function to create a new product node
Productptr newProductNode(int NBD_Number);

// insert function
Productptr insert(Productptr pnode, Productptr tempnode);
#endif
