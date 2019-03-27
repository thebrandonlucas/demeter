#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "menu.h"
#include "product.h"
#include "auxiliary.h"
#include "diary.h"

char *username;
char *filename; 
FILE *diaryFile; 
Diaryptr diary; 
char *userInput; 
int *choice; 

void loadDiary(FILE *diaryFile) {
	char buffer[BUFFER_SIZE] = ""; 
	char *token = (char*)malloc(sizeof(char)*BUFFER_SIZE); 
	diary->numEntries = 0;
	rewind(diaryFile); 
	fgets(buffer, 5, diaryFile);
	diary->numEntries = atoi(buffer);
	diary->entries = (Productptr)malloc(diary->numEntries * sizeof(Productptr)); 
	if (diary->entries == NULL) {
		printf("Error: out of memory\n"); 
		exit(0); 
	}
	for (int i = 0; i < diary->numEntries; i++) {
		diary[i].time = (char*)malloc(sizeof(char)*BUFFER_SIZE); 
		fgets(buffer, BUFFER_SIZE, diaryFile);
		// remove newline
		token = strtok(buffer, "~"); 
		diary[i].time = token; 
		// this will be the food item name
		token = strtok(NULL, "~"); 
		Productptr pnode = palloc(); 
		if (pnode == NULL) {
			printf("Error: out of memory\n");
			exit(0);
		}
		pnode = treeSearch(root, token); 
		diary[i].entries = pnode; 
	}
	//free(buffer); 
	free(token); 
}

void listAllEntries() {
	system("clear"); 
	char str[BUFFER_SIZE] = ""; 
	strncat(str, username, BUFFER_SIZE);
	strncat(str, "'S SUMMARY", BUFFER_SIZE);
	printMenuHeader(str); 
	if (diary->numEntries <= 0) {
		printf("You have no entries.\nGo back and click 'ADD' to start!"); 
		printf("Press ENTER to continue: "); 
		return; 
	}
	printf("\t\tFood Entries\n\n"); 
	for (int i = diary->numEntries - 1; i >= 0; i--) {
		pnode = treeSearch(root, diary[i].entries->long_name);
		printStars();
		printf("Entry Date: %s\n", diary[i].time);
		printf("Entry Name: %s\n", diary[i].entries->long_name);
		printf("Manufacturer: %s\n", diary[i].entries->manufacturer);
		printf("\n~~~ Nutrition Info ~~~\n\n");
		printf("Calories: %f\n", diary[i].entries->energy);
		printf("Carbs: %f\n", diary[i].entries->carbs);
		printf("Protein: %f\n", diary[i].entries->protein);
		printf("Fat: %f\n\n", diary[i].entries->fat);
		printStars();
		if (i % 2 == 0) {
			readString(str, stdin);
			if (str[0] == '\n')
				continue;
			else if (str[0] == 'm')
				return; 
		}
	}
}

int buildLCSTable(int n, int m, int L[n][m], char *X, char *Y) {
	int matchCount;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (i == 0 || j == 0)
				L[i][j] = 0;
			else if (X[i] == Y[j]) {
				L[i][j] = L[i - 1][j - 1] + 1;
			}
			else 
				L[i][j] = max(L[i - 1][j], L[i][j - 1]);
		}
	}
	matchCount = L[n][m]; 
	return  matchCount; 
}

void printDiarySearchResults(char *key) {
	//Productptr returnedDiary = palloc(); 
	//returnedDiary = searchDiary(key);
	//printf("adsf%s", returnedDiary->long_name); 
}

char *searchDiary() {
	char *userInput = (char*)malloc(sizeof(char)*BUFFER_SIZE);
	system("clear");
	printMenuHeader("");
	printf("Search Diary: ");
	fgets(userInput, BUFFER_SIZE, stdin);
	uppercase(userInput);
	return userInput; 
}

void addDiaryEntry() {
	while (1) {
		char userSearch[BUFFER_SIZE] = "";
		char userInput[BUFFER_SIZE] = ""; 
		char searchResults[5][BUFFER_SIZE] = { "" };
		int foodItem = 0; 
		system("clear");
		printMenuHeader("ADD");
		printf("Search foods: ");
		readString(userSearch, stdin);
		uppercase(userSearch);
		Productptr pnode = palloc();
		stripSpace(userSearch);
		pnode = treeSearch(root, userSearch);
		loadSearchResults(searchResults, pnode); 
		printSearchResults(searchResults);
		printf("\nPress '0' to go back to Main Menu.\n\n");
		printf("Select Item: ");
		readString(userInput, stdin); 
		if (userInput[0] == '0')
			break;
		else if (userInput[0] > '0' && userInput[0] <= '5') {
			foodItem = atoi(userInput);
			pnode = treeSearch(root, searchResults[foodItem - 1]);
		}
		else if (userInput[0] < '0' || userInput[0] > '5') {
			printMenuOptionError(); 
			getchar(); 
			addDiaryEntry(); 
		}
		time_t now;
		time(&now);
		printConfirmation("ADD", ctime(&now), searchResults[foodItem - 1]); 
		readString(userInput, stdin); 
		if (userInput[0] == 'n' || userInput[0] == 'N')
			break; 
		diary->numEntries += 1;
		diary[diary->numEntries - 1].time = strtok(ctime(&now), "\n");
		diary[diary->numEntries - 1].entries = pnode;
		printRepeatOption("add");
		readString(userInput, stdin);
		if (userInput[0] == 'n' || userInput[0] == 'N')
			break; 
	}
}

void deleteDiaryEntry() {
	while (1) {
		char *key = (char*)malloc(sizeof(char)*BUFFER_SIZE);
		//char *temp = (char*)malloc(sizeof(char)*BUFFER_SIZE);
		//char key[BUFFER_SIZE] = ""; 
		//char temp[BUFFER_SIZE] = ""; 
		char str[BUFFER_SIZE] = ""; 
		int highestMatchIndex, highestMatchCount = 0;
		key = searchDiary();
		system("clear"); 
		printMenuHeader("DELETE"); 
		for (int i = 0; i < diary->numEntries; i++) {
			int n = strlen(key);
			int m = strlen(diary[i].entries->long_name);
			int L[n + 1][m + 1];
			int tempMatchCount = buildLCSTable(n, m, L, key, diary[i].entries->long_name);
			if (tempMatchCount > highestMatchCount) {
				highestMatchCount = tempMatchCount;
				highestMatchIndex = i;
			}
		}
		printConfirmation("DELETE", diary[highestMatchIndex].time, diary[highestMatchIndex].entries->long_name);
		readString(str, stdin); 
		if (str[0] == 'y' || str[0] == 'Y') {
			// delete matching entry
			for (int i = highestMatchIndex; i < diary->numEntries - 1; i++) {
				diary[i].time = diary[i + 1].time;
				diary[i].entries = diary[i + 1].entries;
			}
			if (diary->numEntries > 0)
				diary->numEntries--;
			printRepeatOption("delete");
			readString(str, stdin);
			//fgets(str, BUFFER_SIZE, stdin);
		}
		free(key);
		break; 
	}
}

void updateDiaryEntry() {
	*choice = 1; 
	char str[BUFFER_SIZE] = ""; 
	while (*choice == 1) {
		//char key[BUFFER_SIZE];
		system("clear"); 
		printMenuHeader("UPDATE"); 
		deleteDiaryEntry();
		addDiaryEntry();
		//fgets(str, BUFFER_SIZE, stdin);
		printRepeatOption("UPDATE"); 
		readString(str, stdin);
		if (str[0] == 'n' || str[0] == 'N')
			*choice = 0;
		//free(key);
	}
	//printMainMenu(); 
	//chooseMainMenuOption(); 
}

void writeDiary() {
	char str[BUFFER_SIZE] = "";
	diaryFile = fopen(filename, "w"); 
	sprintf(str, "%d", diary->numEntries); 
	fprintf(diaryFile, "%s\n", str); 
	str[BUFFER_SIZE] = '\0';
	for (int i = 0; i < diary->numEntries; i++) {
		strncpy(str, diary[i].time, BUFFER_SIZE);
		strncat(str, "~", BUFFER_SIZE);
		strncat(str, diary[i].entries->long_name, BUFFER_SIZE);
		fprintf(diaryFile, "%s\n", str);
	}
	// figure out how to free that memory
	//pfree(root); 
	free(diary->entries); 
	fclose(diaryFile); 
}

