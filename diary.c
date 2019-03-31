#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "product.h"
#include "menu.h"
#include "auxiliary.h"
#include "diary.h"

char username[50] = "";
char filename[50] = ""; 
FILE *diaryFile; 
DiaryNode *diary;
char userInput[BUFFER_SIZE] = ""; 
//char choice; 

void loadDiary(FILE *diaryFile) {
	char buffer[BUFFER_SIZE] = ""; 
	char *token;
	diary = malloc(sizeof(DiaryNode));
	diary->numEntries = 0;
	rewind(diaryFile); 
	fgets(buffer, 5, diaryFile);
	diary->numEntries = atoi(buffer);
	diary->time = malloc(sizeof(char*)*BUFFER_SIZE);
	diary->entries = malloc(sizeof(ProductNode*) * diary->numEntries);
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
		diary->entries[i] = malloc(sizeof(struct pnode));
		diary->entries[i] = treeSearch(root, token);
	}
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
		printf("Serving Size: %.2f%s\n", diary->entries[i]->serving_size, diary->entries[i]->serving_size_units); 
		printf("\n~~~ Nutrition Info (per serving) ~~~\n\n");
		printf("Calories: %.2f\n", diary->entries[i]->energy);
		printf("Daily Value: %.2f%%\n\n", (diary->entries[i]->serving_size / 100) * diary->entries[i]->energy); 
		printf("Carbs: %.2f\n", diary->entries[i]->carbs);
		printf("Daily Value: %.2f%%\n\n", (diary->entries[i]->serving_size / 100) * diary->entries[i]->carbs);
		printf("Protein: %.2f\n", diary->entries[i]->protein);
		printf("Daily Value: %.2f%%\n\n", (diary->entries[i]->serving_size / 100) * diary->entries[i]->protein);
		printf("Fat: %.2f\n", diary->entries[i]->fat);
		printf("Daily Value: %.2f%%\n\n", (diary->entries[i]->serving_size / 100) * diary->entries[i]->fat);
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
	printMenuHeader(option);
	printf("Search Diary: ");
	// TODO: add readString here?
	fgets(userInput, BUFFER_SIZE, stdin);
	uppercase(userInput);
	return userInput; 
}

void addDiaryEntry(char *option) {
	while (1) {
		// Keep track of search and input separately
		char userSearch[BUFFER_SIZE] = "";
		char userInput[BUFFER_SIZE] = ""; 
		char searchResults[5][BUFFER_SIZE] = { "" };
		char *token; 
		int foodItem = 0; 
		system("clear");
		printMenuHeader(option);
		// Clear input buffer
		printf("Search foods: ");
		readString(userSearch, stdin);
		uppercase(userSearch);
		//trimSpace(userSearch);
		ProductNode *pnode = palloc();
		pnode = treeSearch(root, userSearch);
		loadSearchResultsSuccessor(searchResults, pnode); 
		while (1) {
			system("clear"); 
			printMenuHeader(option); 
			printSearchResults(searchResults);
			printf("\nPress 'm' to go back to Main Menu.\n\n");
			printf("Select Item: ");
			readString(userInput, stdin);
			if (userInput[0] == 'm')
				return;
			else if (userInput[0] > '0' && userInput[0] <= '5') { 
				foodItem = userInput[0] - '0';
				pnode = treeSearch(root, searchResults[foodItem - 1]);
				break; 
			}
			else if (userInput[0] < '0' || userInput[0] > '5') {
				printMenuOptionError();
				readString(userInput, stdin); 
				continue;
			}
		}
		time_t now;
		time(&now);
		token = strtok(ctime(&now), "\n"); 
		while (1) {
			printConfirmation(option, token, pnode);
			readString(userInput, stdin);
			if (userInput[0] != '\n')
				break;
		}
		token = strtok(userInput, "\n"); 
		strncpy(userInput, token, BUFFER_SIZE); 
		if (userInput[0] != 'y' && userInput[0] != 'Y')
			break;
		diary->numEntries += 1;
		diary->time[diary->numEntries - 1] = strtok(ctime(&now), "\n");
		diary->entries[diary->numEntries - 1] = pnode;
		while (1) {
			printRepeatOption(option, pnode->long_name);
			readString(userInput, stdin);
			if (userInput[0] != '\n')
				break;
		}
		token = strtok(userInput, "\n");
		strncpy(userInput, token, BUFFER_SIZE);
		if (userInput[0] != 'y' && userInput[0] != 'Y')
			break; 
	}
}

void deleteDiaryEntry(char *option) {
	while (1) {
		char *key;
		char str[BUFFER_SIZE] = ""; 
		char *name; 
		char *token; 
		int highestMatchIndex, highestMatchCount = 0;
		if (diary->numEntries <= 0) {
			system("clear"); 
			printMenuHeader(option); 
			printf("You have no diary entries to delete!\nPress ENTER to continue: ");
			readString(str, stdin); 
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
		while (1) {
			printConfirmation("DELETE", diary->time[highestMatchIndex], diary->entries[highestMatchIndex]);
			readString(str, stdin);
			if (str[0] != '\n')
				break;
		}
		token = strtok(str, "\n"); 
		strncpy(str, token, BUFFER_SIZE); 
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
		else
			break; 
		while (1) {
			printRepeatOption(option, name);
			readString(str, stdin);
			if (str[0] != '\n')
				break; 
		}
		token = strtok(str, "\n"); 
		strncpy(str, token, BUFFER_SIZE); 
		if (str[0] != 'y' && str[0] != 'Y')
			break; 
	}
}

void updateDiaryEntry() {
	while (1) {
		// Delete 
		char *key;
		char str[BUFFER_SIZE] = "";
		char name[BUFFER_SIZE] = "";
		int highestMatchIndex, highestMatchCount = 0;
		if (diary->numEntries <= 0) {
			system("clear");
			printMenuHeader("UPDATE");
			printf("You have no diary entries to update!\nPress ENTER to continue: ");
			readString(str, stdin);
			break;
		}
		key = searchDiary("UPDATE");
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
		system("clear");
		printMenuHeader("UPDATE");
		//printf("\tEntry Date: %s\n\tItem: %s\n\n", diary->time[highestMatchIndex], diary->entries[highestMatchIndex]->long_name);
		printUnderscores();
		printf("%s\n\n", diary->entries[highestMatchIndex]->long_name);
		printf("Entry Date: %s\n", diary->time[highestMatchIndex]);
		printf("Manufacturer: %s\n", diary->entries[highestMatchIndex]->manufacturer);
		printf("Serving Size: %.2f%s\n", diary->entries[highestMatchIndex]->serving_size, diary->entries[highestMatchIndex]->serving_size_units);
		printf("\n~~~ Nutrition Info (per serving) ~~~\n\n");
		printf("Calories: %.2f\n", diary->entries[highestMatchIndex]->energy);
		printf("Daily Value: %.2f%%\n\n", (diary->entries[highestMatchIndex]->serving_size / 100) * diary->entries[highestMatchIndex]->energy);
		printf("Carbs: %.2f\n", diary->entries[highestMatchIndex]->carbs);
		printf("Daily Value: %.2f%%\n\n", (diary->entries[highestMatchIndex]->serving_size / 100) * diary->entries[highestMatchIndex]->carbs);
		printf("Protein: %.2f\n", diary->entries[highestMatchIndex]->protein);
		printf("Daily Value: %.2f%%\n\n", (diary->entries[highestMatchIndex]->serving_size / 100) * diary->entries[highestMatchIndex]->protein);
		printf("Fat: %.2f\n", diary->entries[highestMatchIndex]->fat);
		printf("Daily Value: %.2f%%\n\n", (diary->entries[highestMatchIndex]->serving_size / 100) * diary->entries[highestMatchIndex]->fat);
		printUnderscores();
		printf("UPDATE this item? (y/n): ");
		readString(str, stdin);
		if (str[0] == 'y' || str[0] == 'Y') {
			strncpy(name, diary->entries[highestMatchIndex]->long_name, BUFFER_SIZE); 
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
		else
			break; 

		// ADD
		char userSearch[BUFFER_SIZE] = "";
		char userInput[BUFFER_SIZE] = "";
		char searchResults[5][BUFFER_SIZE] = { "" };
		char *token;
		int foodItem = 0;
		system("clear");
		printMenuHeader("UPDATE");
		// Clear input buffer
		printf("Search replacement food: ");
		readString(userSearch, stdin);
		uppercase(userSearch);
		//stripSpace(userSearch);
		ProductNode *pnode = palloc();
		pnode = treeSearch(root, userSearch);
		loadSearchResultsSuccessor(searchResults, pnode);
		printSearchResults(searchResults);
		printf("\nPress 'm' to go back to Main Menu.\n\n");
		printf("Select Replacement Item: ");
		readString(userInput, stdin);
		if (userInput[0] == 'm')
			return;
		else if (userInput[0] > '0' && userInput[0] <= '5') {
			foodItem = userInput[0] - '0';
			pnode = treeSearch(root, searchResults[foodItem - 1]);
		}
		else if (userInput[0] < '0' || userInput[0] > '5') {
			printMenuOptionError();
			readString(userInput, stdin);
			continue;
		}
		time_t now;
		time(&now);
		token = strtok(ctime(&now), "\n");
		while (1) {
			system("clear");
			printMenuHeader("UPDATE");
			printUnderscores();
			printf("%s\n\n", pnode->long_name);
			printf("Entry Date: %s\n", token);
			printf("Manufacturer: %s\n", pnode->manufacturer);
			printf("Serving Size: %.2f%s\n", pnode->serving_size, pnode->serving_size_units);
			printf("\n~~~ Nutrition Info (per serving) ~~~\n\n");
			printf("Calories: %.2f\n", pnode->energy);
			printf("Daily Value: %.2f%%\n\n", (pnode->serving_size / 100) * pnode->energy);
			printf("Carbs: %.2f\n", pnode->carbs);
			printf("Daily Value: %.2f%%\n\n", (pnode->serving_size / 100) * pnode->carbs);
			printf("Protein: %.2f\n", pnode->protein);
			printf("Daily Value: %.2f%%\n\n", (pnode->serving_size / 100) * pnode->protein);
			printf("Fat: %.2f\n", pnode->fat);
			printf("Daily Value: %.2f%%\n\n", (pnode->serving_size / 100) * pnode->fat);
			printUnderscores();
			printf("UPDATE to this item? (y/n): ");
			readString(userInput, stdin);
			if (userInput[0] != '\n')
				break; 
		}
		token = strtok(userInput, "\n");
		strncpy(userInput, token, BUFFER_SIZE);
		if (userInput[0] != 'y' && userInput[0] != 'Y')
			break;
		diary->numEntries += 1;
		diary->time[diary->numEntries - 1] = strtok(ctime(&now), "\n");
		diary->entries[diary->numEntries - 1] = pnode;
		strncat(name, "\nto: \n", BUFFER_SIZE); 
		strncat(name, pnode->long_name, BUFFER_SIZE); 
		printRepeatOption("UPDATE", name);
		readString(userInput, stdin);
		if (userInput[0] != 'y' && userInput[0] != 'Y')
			break;
		// TODO: refactor into functions
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
	fclose(diaryFile); 
}

