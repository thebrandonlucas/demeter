#include "product.h"

#ifndef AUX_H
#define AUX_H
// Loads data from the food_database.csv file into the tree
// starting at root
Productptr loadProductData(char* filename, Productptr root); 

// Displays the starting menu
void printMainMenu();

#endif
