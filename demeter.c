#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "product.h" 
#include "auxiliary.h"
#include "diary.h"

int main() {
	system("clear"); 
	init(); 
	char *productFile = "food_database.csv";
	printLoadingMenu();
	fflush(stdout); 
	root = loadProductData(productFile, root); 
	while (1) {
		printLoginMenu();
		readMenuInput(choice);
		switch (*choice) {
			case 1:
				login();
				chooseMainMenuOption();
				break;
			case 2:
				createNewUserDiary();
				chooseMainMenuOption();
				break;
			case 3:
				exit(0);
				break; 
			default: 
				printf("Please enter one of the integer options above"); 
		}
	}
	cleanup(); 
	return 0; 
}