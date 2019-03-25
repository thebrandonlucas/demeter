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
	//Productptr root = NULL; 
	//printLoadingMenu();
	root = loadProductData(productFile, root); 
	//Productptr pnode = root->left; 
	//printf("%d %d", root->NBD_Number, pnode->parent->NBD_Number); 
	printLoginMenu(); 
	int choice; 
	choice = readInt(stdin, ""); 
	if (choice == 0)
		printChoiceSelectErrorMessage(); 
	switch(choice) {
		case 1: 
			login();
			printMainMenu(); 
			chooseMainMenuOption(); 
			break; 
		case 2: 
			createNewUserDiary();
			printMainMenu(); 
			chooseMainMenuOption(); 
			break; 
		case 3: 
			exit(0); 
	}
	free(username); 
	free(filename); 
	//free(diary); 
	return 0; 
}