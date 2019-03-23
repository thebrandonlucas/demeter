#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
#include "auxiliary.h"

int main() {
	system("clear"); 
	char* productFile = "food_database.csv";
	Productptr root = NULL; 
	root = loadProductData(productFile, root); 
	return 0; 
}