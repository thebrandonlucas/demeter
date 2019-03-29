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
	char *token;
	diary->numEntries = 0;
	rewind(diaryFile); 
	fgets(buffer, 5, diaryFile);
	diary->numEntries = atoi(buffer);
	// alloc error?
	diary->time = malloc(sizeof(char*)*BUFFER_SIZE);
	diary->entries = malloc(sizeof(Productptr*) * diary->numEntries); 
	if (diary->entries == NULL) {
		printf("Error: out of memory\n"); 
		exit(0); 
	}
	for (int i = 0; i < diary->numEntries; i++) {
		diary->time[i] = malloc(sizeof(char)*BUFFER_SIZE);
		fgets(buffer, BUFFER_SIZE, diaryFile);
		// remove newline
		token = strtok(buffer, "~"); 
		strncpy(diary->time[i], token, strlen(token)); 
		// this will be the food item name
		token = strtok(NULL, "~"); 
		diary->entries[i] = palloc();
		pnode = treeSearch(root, token); 
		diary->entries[i] = pnode; 
	}
	// for deallocation
	//for (int i = 0; i < diary->numEntries; i++) {
	//	free(diary->time[i]); 
	//	free(diary->entries[i]); 
	//}
	//free(diary->entries); 
	//free(diary->time); 
}

void listAllEntries() {
	char header[BUFFER_SIZE] = ""; 
	char str[BUFFER_SIZE] = "";
	strncat(str, username, strlen(username));
	strncat(str, "'s Summary", strlen(username));
	if (diary->numEntries <= 0) {
		system("clear"); 
		printMenuHeader(str); 
		printf("You have no entries.\nGo back and click 'ADD' to start!\n"); 
		printf("Press ENTER to continue: "); 
		readString(str, stdin); 
		return; 
	}
	// Print entries starting from most recent
	for (int i = diary->numEntries - 1; i >= 0; i--) {
		system("clear"); 
		printMenuHeader(header);
		printf("\t\tFood Entries\n\n");
		pnode = treeSearch(root, diary->entries[i]->long_name);
		printUnderscores();
		printf("%d - %s\n\n", diary->numEntries - i, diary->entries[i]->long_name); 
		printf("Entry Date: %s\n", diary->time[i]);
		printf("Manufacturer: %s\n", diary->entries[i]->manufacturer);
		printf("\n~~~ Nutrition Info (per serving) ~~~\n\n");
		printf("Calories: %.2f\n", diary->entries[i]->energy);
		printf("Carbs: %.2f\n", diary->entries[i]->carbs);
		printf("Protein: %.2f\n", diary->entries[i]->protein);
		printf("Fat: %.2f\n\n", diary->entries[i]->fat);
		printUnderscores();
		// Allow scrolling functionality
		if (i == 0) 
			printf("Last item, press ENTER to return: "); 
		else {
			printf("Press 'm' to return to main menu\n");
			printf("Press ENTER to continue scrolling: ");
		}
		readString(str, stdin);
		if (str[0] == '\n')
			continue;
		else if (str[0] == 'm')
			return; 
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
				L[i][j] = maximum(L[i - 1][j], L[i][j - 1]);
		}
	}
	matchCount = L[n][m]; 
	return  matchCount; 
}

char *searchDiary(char *option) {
	char *userInput = (char*)malloc(sizeof(char)*BUFFER_SIZE);
	system("clear");
	printMenuHeader("");
	printf("Search Diary: ");
	fgets(userInput, BUFFER_SIZE, stdin);
	uppercase(userInput);
	return userInput; 
}

void addDiaryEntry(char *option) {
	while (1) {
		char userSearch[BUFFER_SIZE] = "";
		char userInput[BUFFER_SIZE] = ""; 
		char searchResults[5][BUFFER_SIZE] = { "" };
		int foodItem = 0; 
		system("clear");
		printMenuHeader(option);
		printf("Search foods: ");
		readString(userSearch, stdin);
		uppercase(userSearch);
		stripSpace(userSearch);
		Productptr pnode = palloc();
		// checkMemory();
		// modify palloc to check memory?
		pnode = treeSearch(root, userSearch);
		//printf("-- %s --\n", pnode->long_name);

		loadSearchResults(searchResults, pnode); 
		printSearchResults(searchResults);
		printf("\nPress '0' to go back to Main Menu.\n\n");
		printf("Select Item: ");
		readString(userInput, stdin); 
		if (userInput[0] == '0')
			return;
		else if (userInput[0] > '0' && userInput[0] <= '5') {
			foodItem = atoi(userInput);
			pnode = treeSearch(root, searchResults[foodItem - 1]);
		}
		else if (userInput[0] < '0' || userInput[0] > '5') {
			printMenuOptionError(); 
			getchar(); 
			addDiaryEntry(option); 
		}
		time_t now;
		time(&now);
		printConfirmation(option, ctime(&now), searchResults[foodItem - 1]);
		readString(userInput, stdin); 
		if (userInput[0] != 'y' || userInput[0] != 'Y')
			return;
		diary->numEntries += 1;
		diary->time[diary->numEntries - 1] = strtok(ctime(&now), "\n");
		diary->entries[diary->numEntries - 1] = pnode;
		printRepeatOption(option, pnode->long_name);
		readString(userInput, stdin);
		if (userInput[0] != 'n' || userInput[0] != 'N')
			break; 
	}
}

void deleteDiaryEntry(char *option) {
	while (1) {
		char *key;
		char str[BUFFER_SIZE] = ""; 
		char *name; 
		int highestMatchIndex, highestMatchCount = 0;
		system("clear");
		printMenuHeader("DELETE");
		if (diary->numEntries >= 0) {
			printf("You have no diary entries to delete!\nPress ENTER to continue: ");
			getchar();
			break;
		}
		key = searchDiary(option);
		for (int i = 0; i < diary->numEntries; i++) {
			int n = strlen(key);
			int m = strlen(diary->entries[i]->long_name);
			int L[n + 1][m + 1];
			int tempMatchCount = buildLCSTable(n, m, L, key, diary->entries[i]->long_name);
			if (tempMatchCount > highestMatchCount) {
				highestMatchCount = tempMatchCount;
				highestMatchIndex = i;
			}
		}
		printConfirmation("DELETE", diary->time[highestMatchIndex], diary->entries[highestMatchIndex]->long_name);
		readString(str, stdin); 
		if (str[0] == 'y' || str[0] == 'Y') {
			name = diary->entries[highestMatchIndex]->long_name; 
			// delete matching entry
			for (int i = highestMatchIndex; i < diary->numEntries - 1; i++) {
				diary->time[i] = diary->time[i + 1];
				diary->entries[i] = diary->entries[i + 1];
			}
			if (diary->numEntries > 0) {
				diary->numEntries--;
				free(diary->entries[diary->numEntries]); 
			}
		}
		printRepeatOption(option, name); 
	}
}

void updateDiaryEntry() {
	while (1) {
		// Delete 
		char userSearch[BUFFER_SIZE] = "";
		char userInput[BUFFER_SIZE] = "";
		char searchResults[5][BUFFER_SIZE] = { "" };
		int foodItem = 0;
		char *name;
		char *key; 
		int highestMatchIndex, highestMatchCount = 0;
		system("clear");
		printMenuHeader("UPDATE");
		if (diary->numEntries >= 0) {
			printf("You have no diary entries to delete!\nPress ENTER to continue: ");
			getchar();
			break;
		}
		key = searchDiary("UPDATE");
		//Productptr pnode = palloc();
		//pnode = treeSearch(root, key);
		//system("clear");
		//printMenuHeader("UPDATE");
		for (int i = 0; i < diary->numEntries; i++) {
			int n = strlen(key);
			int m = strlen(diary->entries[i]->long_name);
			int L[n + 1][m + 1];
			int tempMatchCount = buildLCSTable(n, m, L, key, diary->entries[i]->long_name);
			if (tempMatchCount > highestMatchCount) {
				highestMatchCount = tempMatchCount;
				highestMatchIndex = i;
			}
		}
		//printConfirmation("UPDATE to", diary->time[highestMatchIndex], diary->entries[highestMatchIndex]->long_name);
		system("clear");
		printMenuHeader("UPDATE");
		printf("\tEntry Date: %s\n\tItem: %s\n\n", diary->time[highestMatchIndex], diary->entries[highestMatchIndex]->long_name);
		printf("UPDATE this item? (y/n): ");
		readString(userInput, stdin);
		if (userInput[0] == 'y' || userInput[0] == 'Y') {
			name = diary->entries[highestMatchIndex]->long_name;
			// delete matching entry
			for (int i = highestMatchIndex; i < diary->numEntries - 1; i++) {
				diary->time[i] = diary->time[i + 1];
				diary->entries[i] = diary->entries[i + 1];
			}
			if (diary->numEntries > 0) {
				diary->numEntries--;
				free(diary->entries[diary->numEntries]);
			}
		}
		
		// ADD
		// TODO: refactor into functions
		system("clear");
		printMenuHeader("UPDATE");
		printf("Search replacement food: ");
		//addDiaryEntry("UPDATE"); 
		//deleteDiaryEntry("UPDATE"); 
		readString(userSearch, stdin);
		uppercase(userSearch);
		stripSpace(userSearch);
		Productptr pnode = palloc();
		pnode = treeSearch(root, userSearch);
		loadSearchResults(searchResults, pnode);
		printSearchResults(searchResults);
		printf("\nPress 'm' to go back to Main Menu.\n\n");
		printf("Select Replacement Item: ");
		readString(userInput, stdin);
		if (userInput[0] == 'm')
			return;
		else if (userInput[0] > '0' && userInput[0] <= '5') {
			foodItem = atoi(userInput);
			pnode = treeSearch(root, searchResults[foodItem - 1]);
		}
		else if (userInput[0] < '0' || userInput[0] > '5') {
			printMenuOptionError();
			getchar();
			continue;
		}
		time_t now;
		time(&now);
		system("clear");
		printMenuHeader("UPDATE");
		printf("\tEntry Date: %s\n\tItem: %s\n\n", ctime(&now), searchResults[foodItem - 1]);
		printf("UPDATE to this item? (y/n): ");
		readString(userInput, stdin);
		if (userInput[0] != 'y' || userInput[0] != 'Y')
			return;
		diary->numEntries += 1;
		diary->time[diary->numEntries - 1] = strtok(ctime(&now), "\n");
		diary->entries[diary->numEntries - 1] = pnode;
		strncat(name, "\nto: \n", BUFFER_SIZE); 
		strncat(name, pnode->long_name, BUFFER_SIZE); 
		printRepeatOption("UPDATE", name);
		//printf(" to: \n%s", pnode->long_name); 
		readString(userInput, stdin);
		if (userInput[0] != 'y' || userInput[0] != 'Y')
			break;
	}
}

void writeDiary() {
	char str[BUFFER_SIZE] = "";
	diaryFile = fopen(filename, "w"); 
	sprintf(str, "%d", diary->numEntries); 
	fprintf(diaryFile, "%s\n", str); 
	str[BUFFER_SIZE] = '\0';
	for (int i = 0; i < diary->numEntries; i++) {
		strncpy(str, diary->time[i], BUFFER_SIZE);
		strncat(str, "~", BUFFER_SIZE);
		strncat(str, diary->entries[i]->long_name, BUFFER_SIZE);
		fprintf(diaryFile, "%s\n", str);
	}
	// figure out how to free that memory
	//pfree(root); 
	//free(diary->entries); 
	fclose(diaryFile); 
}

