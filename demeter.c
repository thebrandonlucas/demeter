#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "product.h" 
#include "auxiliary.h"
#include "diary.h"

int main() {
	char *productFile = "food_database.csv";
	root = loadProductData(productFile, root); 
	chooseLoginMenuOption(); 
	writeDiary(); 
	return 0; 
}