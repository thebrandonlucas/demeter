#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h" 
#include "auxiliary.h"

//#include ""

int main() {
	system("clear"); 
	char *productFile = "food_database.csv";
	Productptr root = NULL; 
	//root = loadProductData(productFile, root); 

	printLoginMenu(); 
	int choice; 
	if (scanf("%d", &choice) != 1) {
		printf("Please enter an integer corresponding to the correct\n");
		printf("choice. Error...Exiting");
		exit(0); 
	} 

	switch(choice) {
		case 1: 
			printPasswordMenu();
		case 2: 
			createNewUser();
	}

	return 0; 
}