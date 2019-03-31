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

// Print the Demeter header
void printMenuHeader(char *header);

// Error message for bad user input 
void printMenuOptionError();

// Gives user option to repeat add, delete, or update
void printRepeatOption(char *option, char *name); 

// Confirm a delete or an add
void printConfirmation(char *option, char* time, ProductNode *pnode);

// Print the closest search results to user input
void printSearchResults(char searchResults[5][BUFFER_SIZE]); 

// Prints 30 underscores for aesthetics
void printUnderscores();
#endif