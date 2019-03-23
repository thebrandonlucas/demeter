#ifndef AUX_H
#define AUX_H
#include "product.h"
/*
	This file contains defs for functions that
	help the main program load data and print menus
*/


// Loads data from the food_database.csv file into the tree
// starting at root
Productptr loadProductData(char* filename, Productptr root); 

// Displays the starting menu
void printMainMenu();

// Displays login menu
void printLoginMenu(); 

// Asks for username and password to login
void printPasswordMenu(); 

// Print menu to create new user diary
void createNewUserDiary();

// Allocate for string size and copy to new string
char *mallocopy(char* a, char* b, size_t n); 
#endif
