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
void printMenuHeader(char *heaader); 
void chooseMainMenuOption(); 

void init() {
	username = (char*)malloc(sizeof(char)*BUFFER_SIZE); 
	filename = (char*)malloc(sizeof(char)*BUFFER_SIZE);
	diary = (Diaryptr)malloc(sizeof(Diaryptr));
	userInput = (char*)malloc(sizeof(char)*BUFFER_SIZE);
	choice = malloc(sizeof(int)); 
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
	//free(tempnode); 
	return root;
}

void createNewUserDiary() {
	int fileAlreadyExists = 1; 
	while (fileAlreadyExists == 1) {
		system("clear");
		printMenuHeader("CREATE NEW USER"); 
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
	diaryFile = fopen(filename, "w");
	// number of entries for new file is 0
	fputs("0\n", diaryFile);
	loadDiary(diaryFile); 
	printMenuHeader("CREATE NEW USER"); 
	printf("Success! Created new diary for %s\n\n", username); 
	printf("Press any key to continue: "); 
	getchar(); getchar(); 
	fclose(diaryFile); 
	// TODO: free username and filename at end of program
}

void login() {
	int fileAlreadyExists = 0;
	while (fileAlreadyExists == 0) {
		//char str[BUFFER_SIZE]; 
		system("clear");
		printMenuHeader("LOGIN");
		printf("Sign-in\n\n");
		printf("Press '0' to return to go back.\n\n"); 
		printf("Enter username: ");
		//scanf("%s", username);
		readString(username, stdin); 
		if (username[0] == '0') {
			chooseLoginMenuOption(); 
		}
		sscanf(username, "%s", username); 
		strcpy(filename, username);
		strcat(filename, ".log");
		// TODO: ADD PASSWORD CHECK AND MAKE SURE USERNAME AND PASSWORD ARE SAME
		strcpy(filename, username);
		strcat(filename, ".log");
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
		readMenuInput(choice);
		switch (*choice) {
		case 1:
			login();
			chooseMainMenuOption();
			break;
		case 2:
			createNewUserDiary();
			chooseMainMenuOption();
			break;
		case 3:
			exit(0);
			break;
		default:
			system("clear");
			printMenuHeader("ERROR");
			printf("Please enter one of the integer options above\n");
			printf("Press ENTER to continue: ");
			getchar();
		}
	}
}

void chooseMainMenuOption() {
	while (1) {
		printMainMenu();
		printf("Choose an option: ");
		readMenuInput(choice);
		switch (*choice) {
			//case 0: 
			//	login(); 
			case 1:
				listAllEntries();
				break;
			case 2:
				addDiaryEntry();
				break;
			case 3:
				deleteDiaryEntry();
				break;
			case 4:
				updateDiaryEntry();
				break;
			case 5:
				return;
			default:
				system("clear"); 
				printMenuHeader("ERROR"); 
				printf("Please enter an integer from above. ");
				getchar(); 
		}
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
		printf("Error. Please enter no more than 1024 characters."); 
	}
//	if (str[0] == 'm' || str[0] == 'M') {
//		printMainMenu(); 
//		chooseMainMenuOption(); 
//	} else if (str[0] == 'e' || str[0])
}

//char *removeSpaces(char *str) {
//	char *dest = str;
//	while (*str != 0) {
//		if (*str != ' ') {
//			*dest = *str;
//			dest += 1; 
//		}
//		str += 1;
//	}
//	*dest = 0;
//	return dest; 
//}

void cleanup() {
	writeDiary();
	free(username);
	free(filename);
	free(diary);
	free(userInput);
	free(root);
	free(pnode);
	free(choice);
}