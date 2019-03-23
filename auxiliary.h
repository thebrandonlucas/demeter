/*
	This file contains defs for functions that
	help the main program load data and print menus
*/

#ifndef AUX_H
#define AUX_H
// Loads data from the food_database.csv file into the tree
// starting at root
Productptr loadProductData(char* filename, Productptr root); 

// Displays the starting menu
void printMainMenu();

// Allocate for string size and copy to new string
char *mallocopy(char* a, char* b, size_t n); 
#endif
