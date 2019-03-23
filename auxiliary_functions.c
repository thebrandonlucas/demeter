#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "auxiliary.h"
#include "product.h"

char *mallocopy(char* a, char* b, size_t n); 

Productptr loadProductData(char* filename, Productptr root) {
	FILE* filestream;
	char buffer[BUFFER_SIZE];
	filestream = fopen(filename, "r");
	//fgets(buffer, sizeof(buffer), filestream);
	char *token;
	int n = 500; 
	Productptr tempnode = palloc();
	while (fgets(buffer, sizeof(buffer), filestream) != NULL) {
		token = strtok(buffer, "~"); 
		//printf("%s\n", token); 
		tempnode->NBD_Number = atoi(token); token = strtok(NULL, "~");
		tempnode->long_name = mallocopy(tempnode->long_name, token, n);  token = strtok(NULL, "~");
		tempnode->manufacturer = mallocopy(tempnode->manufacturer, token, 500); token = strtok(NULL, "~");
		tempnode->energy = atof(token); token = strtok(NULL, "~");
		tempnode->carbs = atof(token); token = strtok(NULL, "~");
		tempnode->fat = atof(token); token = strtok(NULL, "~");
		tempnode->protein = atof(token); token = strtok(NULL, "~");
		tempnode->serving_size = atof(token); token = strtok(NULL, "~");
		tempnode->serving_size_units = mallocopy(tempnode->serving_size_units, token, n); token = strtok(NULL, "~");
		// catch potential null values, place in identifier -999, FIXME: would 0.0 suffice?
		tempnode->household_serving_size = token != NULL ? atof(token) : -999.0; token = strtok(NULL, "~");
		tempnode->household_serving_size_units = token != NULL ? mallocopy(tempnode->household_serving_size_units, token, n) : "None";
		root = treeInsert(root, tempnode);
	}
	return root;
}

void printMainMenu() {
	system("clear"); 
	printf("1 - List Your Summary\n");
	printf("2 - Add Meal\n");
	printf("3 - Update Meal\n");
	printf("4 - Delete Meal\n");
	printf("5 - Exit\n\n");
}

void printLoginMenu() {
	system("clear"); 
	printf("1 - Login\n"); 
	printf("2 - New User\n"); 
	printf("\nPlease choose an option: "); 
}

void printPasswordMenu() {

}

void createNewUser() {
	char *username = ""; 
	char *password; 
	system("clear"); 
	printf("Welcome!\n\n"); 
	printf("Please create a username and password\n\n");
	printf("Username: ");
	scanf("%s", username); 
	//printf("Password: "); 
	//password = getpass("Password: "); 
	//scanf("%s", &password); 

	// TODO: ADD PASSWORD CHECK AND MAKE SURE USERNAME AND PASSWORD ARE SAME
	printf("Success! Created new diary for %s", username); 
}

char *mallocopy(char* a, char* b, size_t n) {
	a = (char*)malloc(n * sizeof(char));
	strncpy(a, b, n - 1); a[n - 1] = 0;
	return a; 
}