#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "auxiliary.h"
#include "product.h"
#include "menu.h"
#include "diary.h"

char *mallocopy(char* a, char* b, size_t n); 
int fileExists(char *filename); 
void printMenuHeader(); 

void init() {
	username = (char*)malloc(sizeof(char)*BUFFER_SIZE); 
	filename = (char*)malloc(sizeof(char)*BUFFER_SIZE); 
	diary = (Diaryptr)malloc(sizeof(Diaryptr));
}

Productptr loadProductData(char* filename, Productptr root) {
	FILE* filestream;
	char buffer[BUFFER_SIZE];
	filestream = fopen(filename, "r");
	char *token;
	int n = 500; 
	Productptr tempnode = palloc();
	while (fgets(buffer, sizeof(buffer), filestream) != NULL) {
		token = strtok(buffer, "~"); 
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
	int fileAlreadyExists = 1; 
	while (fileAlreadyExists == 1) {
		system("clear");
		printMenuHeader(); 
		printf("Welcome!\n\n"); 
		printf("Please create a username and password\n\n");
		printf("Username: ");
		scanf("%s", username); 

		// TODO: ADD PASSWORD CHECK AND MAKE SURE USERNAME AND PASSWORD ARE SAME
		strcpy(filename, username); 
		strcat(filename, ".log");
		fileAlreadyExists = fileExists(filename); 
		if (fileAlreadyExists == 1) {
			system("clear"); 
			printf("Error! File %s already exists. Please choose another name.", filename);
			getchar(); getchar(); 
		}
	}
	system("clear"); 
	diaryFile = fopen(filename, "w+");
	// number of entries for new file is 0
	fputs("0\n", diaryFile);
	//diary->numEntries = 0; 
	loadDiary(diaryFile); 
	printf("Success! Created new diary for %s\n", username);
	printf("Press any key to continue: "); 
	getchar(); getchar(); 
	// TODO: free username and filename at end of program
}

void login() {
	int fileAlreadyExists = 0;
	while (fileAlreadyExists == 0) {
		system("clear");
		printMenuHeader();
		printf("Sign-in\n\n");
		printf("Enter username: ");
		scanf("%s", username);
		//fgets(username, sizeof(username), stdin); 
		strcpy(filename, username);
		strcat(filename, ".log");

		// TODO: ADD PASSWORD CHECK AND MAKE SURE USERNAME AND PASSWORD ARE SAME
		strcpy(filename, username);
		strcat(filename, ".log");
		fileAlreadyExists = fileExists(filename);
		if (fileAlreadyExists == 0) {
			system("clear");
			printf("Error! User %s does not exist. Please try again or enter new username.", filename);
			getchar(); getchar();
		}
	}
	diaryFile = fopen(filename, "w+");
	// number of entries for new file is 0
	//fputs("0", diaryFile);
	loadDiary(diaryFile);
}

int chooseMainMenuOption() {
	int option; 
	//printf("Choose an option: "); 
	//getchar(); 
	//sscanf(stdin, "%d", &option); 
	option = readInt(stdin, "Choose an option: "); 
	
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

void uppercase(char *str) {
	int len = strlen(str); 
	for (int i = 0; i < len; i++) {
		if (islower(str[i])) {
			str[i] = toupper((unsigned char)str[i]);
		}
	}
}

// Borrowed from https://stackoverflow.com/questions/26583717/how-to-scanf-only-integer
int readInt(FILE *input, char *prompt) {
	char *ptr = (char*)malloc(sizeof(char));
	char *str = (char*)malloc(sizeof(char));
	int num;

	while (fgets(str, sizeof(char*), input)) {
		num = strtol(str, &ptr, 10); 
		if (ptr == str || *ptr != '\n')
			printf("%s", prompt);
		else
			break; 
	}
	return num; 
}

char *removeSpaces(char *str) {
	char *dest = str;
	while (*str != 0) {
		if (*str != ' ') {
			*dest = *str;
			dest += 1; 
		}
		str += 1;
	}
	*dest = 0;
	return dest; 
	//printf("%s", dest); 
	//*str = *dest; 
}