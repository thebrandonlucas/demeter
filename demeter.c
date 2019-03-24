#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "product.h" 
#include "auxiliary.h"
#include "diary.h"

int main() {
	system("clear"); 
	char *productFile = "food_database.csv";
	Productptr root = NULL; 
	//root = loadProductData(productFile, root); 

	printLoginMenu(); 
	char line[BUFFER_SIZE];
	int choice; 
	if (scanf("%d", &choice) != 1) {
		printf("Please enter an integer corresponding to the correct\n");
		printf("choice. Error...Exiting\n");
		exit(0); 
	} 

	switch(choice) {
		case 1: 
			login();
			break; 
		case 2: 
			createNewUserDiary();
			printMainMenu(); 
			chooseMainMenuOption(); 
			break; 
	}
	return 0; 
}