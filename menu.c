#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "product.h"
#include "diary.h"
#include "auxiliary.h"

void printMainMenu(); 
void printLoginMenu(); 
void printPasswordMenu(); 
void printMenuHeader(char *header); 

void printMainMenu() {
	system("clear");
	printMenuHeader("MAIN MENU");
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

//void printLoginValidationMenu() {
//	system("clear"); 
//	printMenuHeader(); 
//	printf("Enter username: "); 
//}

void printLoadingMenu() {
	system("clear"); 
	printf("Loading. Pleeeeease wait."); 
	system("clear"); 
}

void printMenuHeader(char *header) {
	printf("* * * Demeter Nutrition Tracker * * *\n");
	printf("\t\t%s\n\n", header); 
}

void printMenuOptionError() {
	system("clear"); 
	printf("Error. Please enter an integer corresponding\n");
	printf("to the correct choice.\n");
	printf("\nPress ENTER to continue"); 
	//exit(0);
}

void readMenuInput(int *choice) {
	char *ptr;
	char str[BUFFER_SIZE];
	//*choice = 0; 
	//printf("asdf"); 
	while (fgets(str, sizeof(char*), stdin)) {
		*choice = strtol(str, &ptr, 10);
		if (*choice == 0)
			printMenuOptionError();
		else
			break; 
	}
}

void printRepeatOption(char *option) {
	system("clear"); 
	//uppercase(option); 
	printMenuHeader(option); 
	printf("Would you like to %s another item? (y/n): ", option); 
}

void printConfirmation(char *option, char* time, char *name) {
	system("clear");
	//uppercase(option); 
	printMenuHeader(option); 
	printf("\tEntry Date: %s\n\tItem: %s\n\n", time, name); 
	printf("Are you sure you want to %s this item? (y/n): ", option); 
}

//void printMenuOptionHelper() {
//	printf("For instruction help, press 'h'\n"); 
//}

void printMenuOptions() {
	printf("\n\n\n\n\nGo to main menu - 'm'\t"); 
	printf("Save and exit   - 'e'\n");
}

void printUser() {
	printf("\t\n\n%s", username); 
}

void printStars() {
	printf("******************************\n\n"); 
}