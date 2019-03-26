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
	printLoginMenu();
	readMenuInput(choice); 
	switch(*choice) {
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
	writeDiary(); 
	free(username); 
	free(filename); 
	free(diary);
	free(userInput);
	free(root); 
	free(pnode); 
	free(choice); 
	return 0; 
}