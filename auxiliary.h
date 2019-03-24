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

// Print menu to create new user diary
void createNewUserDiary();

// Choose a menu option and perform the appropriate action
int chooseMainMenuOption(); 

// Login functionality for returning users
void login(); 

// Allocate for string size and copy to new string
char *mallocopy(char *a, char *b, size_t n); 

// Check if a file exists
int fileExists(char *filename); 
#endif
