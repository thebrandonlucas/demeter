#ifndef MENU_H
#define MENU_H
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif
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
void printMenuHeader(char *header);

// Error message for bad user input 
void printMenuOptionError();

// Helper function for reading and validating 
// user input
void readMenuInput(int *choice); 

// Gives user option to repeat action
void printRepeatOption(char *option, char *name); 

// Confirm a delete or an update
void printConfirmation(char *option, char* time, char *name);

// Print the results of the closest search results
void printSearchResults(char searchResults[5][BUFFER_SIZE]); 

// Menu options to navigate the program
void printMenuOptions(); 

// Print the current username
void printUser(); 

// Prints 30 stars for aesthetics
void printUnderscores();
#endif