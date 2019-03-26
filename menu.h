#ifndef MENU_H
#define MENU_H
/*
	This file contains definitions for all of 
	the program's menu printing functions. 
*/

// Displays the starting menu
void printMainMenu();

// Displays login menu
void printLoginMenu();

// Asks for username and password to login
//void printLoginValidationMenu();

// Show food search options
//void printFoodSearchMenu(); 

// Inform the user of loading on startup
void printLoadingMenu(); 

// Print the Demeter header
void printMenuHeader();

// Error message for bad user input 
void printMenuOptionError();

// Helper function for reading and validating 
// user input
void readMenuInput(int *choice); 

// Gives user option to repeat action
void printRepeatOption(char *option); 
#endif