#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "product.h"
#include "auxiliary.h"
#include "diary.h"
#include "menu.h"

char *mallocopy(char* a, char* b, size_t n); 
int fileExists(char *filename); 
void printMenuHeader(char *header); 
void chooseMainMenuOption(); 

ProductNode *loadProductData(char* filename, ProductNode *root) {
	FILE* filestream;
	char buffer[BUFFER_SIZE];
	filestream = fopen(filename, "r");
	char *token;
	int n = 500; 
	ProductNode *tempnode = palloc();
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
		// catch potential null values, place in identifier -999
		tempnode->household_serving_size = token != NULL ? atof(token) : -999.0; token = strtok(NULL, "~");
		tempnode->household_serving_size_units = token != NULL ? mallocopy(tempnode->household_serving_size_units, token, n) : "None";
		root = treeInsert(root, tempnode);
	}
	return root;
}

//void loadSearchResultsPredecessor(char searchResults[5][BUFFER_SIZE], ProductNode *pnode) {
//	int i = 0; 
//	searchResults[i][0] = '\0'; 
//	strncpy(searchResults[i], pnode->long_name, strlen(pnode->long_name));
//	for (i = 1; i < 5; i++) {
//		searchResults[i][0] = '\0';
//		pnode = treePredecessor(pnode);
//		strncpy(searchResults[i], pnode->long_name, strlen(pnode->long_name));
//	}
//}

void loadSearchResultsSuccessor(char searchResults[5][BUFFER_SIZE], ProductNode *pnode) {
	int i = 0;
	searchResults[i][0] = '\0';
	strncpy(searchResults[i], pnode->long_name, strlen(pnode->long_name));
	for (i = 1; i < 5; i++) {
		searchResults[i][0] = '\0';
		pnode = treeSuccessor(pnode);
		strncpy(searchResults[i], pnode->long_name, strlen(pnode->long_name));
	}
}

void createNewUserDiary() {
	int fileAlreadyExists = 1; 
	while (fileAlreadyExists == 1) {
		system("clear");
		printMenuHeader("CREATE NEW USER"); 
		printf("Welcome!\n\n"); 
		printf("Please create a username and password\n\n");
		printf("Press '0' to go back.\n\n");
		printf("Username: ");
		readString(username, stdin);
		if (username[0] == '0') {
			chooseLoginMenuOption();
		}
		sscanf(username, "%s", username);
		strncpy(filename, username, 200); 
		strncat(filename, ".log", 250);
		fileAlreadyExists = fileExists(filename); 
		if (fileAlreadyExists == 1) {
			system("clear"); 
			printf("Error! File '%s' already exists. \nPlease choose another name.", filename);
			getchar(); 
		}
	}
	system("clear"); 
	diaryFile = fopen(filename, "w");
	// number of entries for new file is 0
	fputs("0\n", diaryFile);
	loadDiary(diaryFile); 
	fclose(diaryFile);
	printMenuHeader("CREATE NEW USER"); 
	printf("Success! Created new diary for %s\n\n", username); 
	printf("Press any key to continue: "); 
	getchar(); 
}

void login() {
	int fileAlreadyExists = 0;
	char *token; 
	while (fileAlreadyExists == 0) {
		while (1) {
			system("clear");
			printMenuHeader("LOGIN");
			printf("Sign-in\n\n");
			printf("Press '0' to go back.\n\n");
			printf("Enter username: ");
			readString(username, stdin);
			if (username[0] != '\n')
				break; 
		}
		token = strtok(username, "\n"); 
		if (username[0] == '0') 
			chooseLoginMenuOption(); 
		strncpy(username, token, 50); 
		strncpy(filename, username, 50); 
		strncat(filename, ".log", 54);
		fileAlreadyExists = fileExists(filename);
		if (fileAlreadyExists == 0) {
			system("clear");
			printMenuHeader("ERROR"); 
			printf("Error! User '%s' does not exist. \nPlease try again or enter new username. ", filename);
			getchar();
		}
	}
	diaryFile = fopen(filename, "r");
	loadDiary(diaryFile);
	fclose(diaryFile);
}

void chooseLoginMenuOption() {
	while (1) {
		printLoginMenu();
		char str[BUFFER_SIZE];
		readString(str, stdin);
		char choice = str[0];
		switch (choice) {
			case '1':
				login();
				chooseMainMenuOption();
				break;
			case '2':
				createNewUserDiary();
				chooseMainMenuOption();
				break;
			case '3':
				system("clear");
				printf("Happy Healthy Eating!\n");
				exit(0); 
				break; 
			default:
				system("clear");
				printMenuHeader("ERROR");
				printf("Make sure you're entering a SPECIFIED INTEGER!\n");
				printf("Press any key to continue: ");
				getchar();
		}
	}
}

void chooseMainMenuOption() {
	while (1) {
		printMainMenu();
		printf("Choose an option: ");
		char str[BUFFER_SIZE];
		readString(str, stdin);
		char choice = str[0];
		switch (choice) {
			case '1':
				listAllEntries();
				break;
			case '2':
				addDiaryEntry("ADD");
				break;
			case '3':
				deleteDiaryEntry("DELETE");
				break;
			case '4':
				updateDiaryEntry();
				break;
			case '5':
				system("clear"); 
				if (username != '\0')
					printf("Happy Healthy Eating, %s!\n", username);
				else
					printf("Happy Healthy Eating!\n"); 
				writeDiary();
				exit(0);
			default:
				system("clear"); 
				printMenuHeader("ERROR"); 
				printf("Make sure you're entering a SPECIFIED INTEGER!\n");
				printf("Press any key to continue: "); 
				getchar(); 
		}
	}
}

// TODO: DELETE THIS?
char *mallocopy(char* a, char* b, size_t n) {
	a = (char*)malloc(n * sizeof(char));
	strncpy(a, b, n - 1); a[n - 1] = 0;
	return a; 
}

int fileExists(char *filename) {
	FILE *file = fopen(filename, "r"); 
	if (file == NULL)
		return 0; 
	fclose(file); 
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

int readInt(FILE *input) {
	char str[BUFFER_SIZE]; 
	char *ptr;
	int num = 0;
	readString(str, input); 
	num = strtol(str, &ptr, 10); 
	return num; 
}

void readString(char str[], FILE *input) {
	while (fgets(str, BUFFER_SIZE, input) == NULL) {
		printMenuHeader("ERROR"); 
		printf("Error. Please enter no more than 1024 characters. ");
		getchar(); 
		system("clear"); 
	}
}

////https://stackoverflow.com/questions/7775138/strip-whitespace-from-a-string-in-place
//void stripSpace(char *str) {
//	for (size_t i = 0, j = 0; (str[j] = str[i]); j += !isspace(str[i++]));
//}

//https://stackoverflow.com/questions/122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way
void trimSpace(char *str) {
	char *end;

	// Trim leading space
	while (isspace((unsigned char)*str)) str++;

	if (*str == 0)  // All spaces?
		return;

	// Trim trailing space
	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end)) end--;

	// Write new null terminator character
	end[1] = '\0';
}