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
	//Productptr root = NULL; 
	printLoadingMenu();
	root = loadProductData(productFile, root); 
	Productptr pnode = root->left; 
	printf("%d %d", root->NBD_Number, pnode->parent->NBD_Number); 
	printLoginMenu(); 
	int choice; 
	if (scanf("%d", &choice) != 1) {
		printf("Please enter an integer corresponding to the correct\n");
		printf("choice. Error...Exiting\n");
		exit(0); 
	} 

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
	//free(username); 
	//free(filename); 
	//fclose(diary); 
	return 0; 
}