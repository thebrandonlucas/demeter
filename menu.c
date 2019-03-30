#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "product.h"
#include "diary.h"
#include "auxiliary.h"

void printMainMenu(); 
void printLoginMenu(); 
void printMenuHeader(char *header); 

void printMainMenu(/*char *statusMessage*/) {
	system("clear");
	printMenuHeader("MAIN MENU");
	//if (status != "")
	//	printf("Successfully performed %s", statusMessage); 
	printf("1 - List Your Summary\n");
	printf("2 - Add Meal\n");
	printf("3 - Delete Meal\n");
	printf("4 - Update Meal\n");
	printf("5 - Save and Exit\n\n");
}

void printLoginMenu() {
	system("clear");
	printMenuHeader("LOGIN"); 
	printf("1 - Login\n");
	printf("2 - New User\n");
	printf("3 - Exit\n"); 
	printf("\nPlease choose an option: ");
}

void printMenuHeader(char *header) {
	printf("* * * Demeter Nutrition Tracker * * *\n");
	printf("\t\t%s\n\n", header); 
}

void printMenuOptionError() {
	system("clear"); 
	printMenuHeader("ERROR"); 
	printf("Error. Please enter an integer corresponding\n");
	printf("to the correct choice.\n");
	printf("\nPress ENTER to continue: "); 
}

void printRepeatOption(char *option, char *name) {
	system("clear"); 
	printMenuHeader(option); 
	if (strncmp(option, "ADD", strlen(name)) == 0)
		printf("%sED %s\n\n", option, name);
	else
		printf("%sD %s\n\n", option, name); 
	printf("Would you like to %s another item? (y/n): ", option);
}

void printConfirmation(char *option, char* time, char *name) {
	system("clear");
	printMenuHeader(option); 
	printf("\tEntry Date: %s\n\tItem: %s\n\n", time, name); 
	printf("%s this item? (y/n): ", option); 
}

void printSearchResults(char searchResults[5][BUFFER_SIZE]) {
	printUnderscores(); 
	printf("\n");
	for (int i = 0; i < 5; i++)
		printf("%d - %s\n\n", i + 1, searchResults[i]);
	printUnderscores(); 
}

void printUnderscores() {
	printf("_____________________________\n\n"); 
}