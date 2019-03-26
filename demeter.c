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
	chooseLoginMenuOption(); 
	cleanup(); 
	return 0; 
}