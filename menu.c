#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "product.h"
#include "diary.h"
#include "auxiliary.h"

void printMainMenu(); 
void printLoginMenu(); 
void printPasswordMenu(); 
void printMenuHeader(); 

void printMainMenu() {
	system("clear");
	printMenuHeader();
	printf("1 - List Your Summary\n");
	printf("2 - Add Meal\n");
	printf("3 - Delete Meal\n");
	printf("4 - Update Meal\n");
	printf("5 - Exit\n\n");
}

void printLoginMenu() {
	system("clear");
	printMenuHeader(); 
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

void printMenuHeader() {
	printf("* * * Demeter Nutrition Tracker * * *\n\n");
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
	printf("Would you like to %s another item? (y/n): ", option); 
}