#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "auxiliary.h"
#include "product.h"
#include "menu.h"
#include "diary.h"

char *mallocopy(char* a, char* b, size_t n); 
int fileExists(char *filename); 
void printMenuHeader(); 

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

void createNewUserDiary() {
	username = (char*)malloc(sizeof(char)); 
	char *filename = (char*)malloc(sizeof(char)); 
	char line[BUFFER_SIZE];
	FILE *diary;
	int fileAlreadyExists; 
	system("clear"); 
	printf("Welcome!\n\n"); 
	printf("Please create a username and password\n\n");
	printf("Username: ");
	//username = fgets(username, sizeof(username), stdin); 
	scanf("%s", username); 
	//printf("Password: "); 
	//password = getpass("Password: "); 
	//scanf("%s", &password); 

	// TODO: ADD PASSWORD CHECK AND MAKE SURE USERNAME AND PASSWORD ARE SAME
	strcpy(filename, username); 
	strcat(filename, ".log");
	fileAlreadyExists = fileExists(filename); 
	// TODO: why not just check if user exists already by checking if matching file
	// exists?
	if (fileAlreadyExists == 0)
		diary = fopen(filename, "a+");
	else {
		printf("Error! File %s already exists. Exiting.", filename);
		exit(0); 
	}
	printf("Success! Created new diary for %s\n", username);
	printf("Press any key to continue: "); 
	getchar(); getchar(); 
	free(username); 
	free(filename); 
	//free(temp);
}

int chooseMainMenuOption() {
	int option; 
	printf("Choose an option: "); 
	//getchar(); 
	scanf("%d", &option); 
	
	switch (option) {
		case 1:
			listAllEntries(); 
			break; 
		case 2: 
			addDiaryEntry();
			break; 
		case 3: 

			break; 
		case 4: 

			break; 
	}
}

void login() {
	system("clear"); 
	printMenuHeader(); 
	printf("Enter username: "); 
	scanf("%s", username); 
	strcpy(filename, username); 
	strcat(filename, ".log"); 

}

char *mallocopy(char* a, char* b, size_t n) {
	a = (char*)malloc(n * sizeof(char));
	strncpy(a, b, n - 1); a[n - 1] = 0;
	return a; 
}

int fileExists(char *filename) {
	FILE *file = fopen(filename, "r"); 
	if (file == NULL)
		return 0; 
	return 1; 
}