#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

Productptr loadProductData(char* filename, Productptr root) {
	FILE* filestream;
	char buffer[BUFFER_SIZE];
	filestream = fopen(filename, "r");
	//fgets(buffer, sizeof(buffer), filestream);
	char* token;
	Productptr tempnode = palloc(); 
	while (fgets(buffer, sizeof(buffer), filestream) != NULL) {
		token = strtok(buffer, "~");
		tempnode->NBD_Number = atoi(token); token = strtok(NULL, "~");
		tempnode->long_name = token; token = strtok(NULL, "~");
		tempnode->manufacturer = token; token = strtok(NULL, "~");
		tempnode->energy = atof(token); token = strtok(NULL, "~");
		tempnode->carbs = atof(token); token = strtok(NULL, "~");
		tempnode->fat = atof(token); token = strtok(NULL, "~");
		tempnode->protein = atof(token); token = strtok(NULL, "~");
		tempnode->serving_size = atof(token); token = strtok(NULL, "~");
		tempnode->serving_size_units = token; token = strtok(NULL, "~");
		// catch potential null values, place in identifier -999, FIXME: would 0.0 suffice?
		tempnode->household_serving_size = token != NULL ? atof(token) : -999.0; token = strtok(NULL, "~");
		tempnode->household_serving_size_units = token; token = strtok(NULL, "~"); 
		root = insert(root, tempnode); 
	}
	return root; 
}

void printMenu() {
	printf("1 - List Your Summary\n"); 
	printf("2 - Add Meal\n"); 
	printf("3 - Update Meal\n"); 
	printf("4 - Delete Meal\n"); 
	printf("5 - Exit\n\n"); 
}

int main() {
	system("clear"); 
	char* productFile = "food_database.csv";
	Productptr root = NULL; 
	root = loadProductData(productFile, root); 

	preOrder(root); 
	return 0; 
}


