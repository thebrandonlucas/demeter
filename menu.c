#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

void printMainMenu(); 
void printLoginMenu(); 
void printPasswordMenu(); 
void printMenuHeader(); 

void printMainMenu() {
	system("clear");
	printMenuHeader();
	printf("1 - List Your Summary\n");
	printf("2 - Add Meal\n");
	printf("3 - Update Meal\n");
	printf("4 - Delete Meal\n");
	printf("5 - Exit\n\n");
}

void printLoginMenu() {
	system("clear");
	printMenuHeader(); 
	printf("1 - Login\n");
	printf("2 - New User\n");
	printf("\nPlease choose an option: ");
}

//void printLoginValidationMenu() {
//	system("clear"); 
//	printMenuHeader(); 
//	printf("Enter username: "); 
//}

void printFoodSearchMenu() {
	system("clear"); 
	printMenuHeader(); 
	printf("Search foods: "); 
}

void printMenuHeader() {
	printf("* * * Demeter Nutrition Tracker -- Main Menu * * *\n\n");
}