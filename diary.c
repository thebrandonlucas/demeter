#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
	char *buffer = (char*)malloc(sizeof(char)*BUFFER_SIZE);
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
	//free(token); 
}

void listAllEntries() {

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
	printMenuHeader();
	printf("Search Diary: ");
	fgets(userInput, BUFFER_SIZE, stdin);
	uppercase(userInput);
	//Productptr pnode = palloc();
	//pnode = treeSearch(root, userInput);
	//char *temp = pnode->long_name; 
	//free(pnode); 
	return userInput; 
}

void addDiaryEntry() {
	*choice = 1; 
	while (*choice == 1) {
		char str[BUFFER_SIZE] = "";
		//int choice = 0; 
		system("clear");
		printMenuHeader();
		printf("Search foods: ");
		readString(str, stdin); 
		uppercase(str);
		Productptr pnode = palloc();
		pnode = treeSearch(root, str);
		printSearchResults(pnode);
		printf("Select Item: ");
		// TODO: make choice part of option
		//choice = readInt(stdin, ""); 
		readInt(stdin); 
		time_t now;
		time(&now);
		diary->numEntries += 1;
		diary[diary->numEntries - 1].time = strtok(ctime(&now), "\n");
		diary[diary->numEntries - 1].entries = pnode;
		//free(userInput);
		//free(pnode);
		printRepeatOption("add"); 
		//str = ""; 
		fgets(str, BUFFER_SIZE, stdin); 
		//printf("HELLO%s", str); 
		if (str[0] == 'n' || str[0] == 'N')
			*choice = 0; 
		//getchar(); getchar(); 
	}
}

void deleteDiaryEntry() {
	char *key = (char*)malloc(sizeof(char)*BUFFER_SIZE); 
	char *temp = (char*)malloc(sizeof(char)*BUFFER_SIZE);
	int highestMatchIndex, highestMatchCount = 0; 
	key = searchDiary();
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
	// delete matching entry
	for (int i = highestMatchIndex; i < diary->numEntries - 1; i++) {
		diary[i].time = diary[i + 1].time; 
		diary[i].entries = diary[i + 1].entries; 
	}
	diary->numEntries--; 
	//writeDiary();
	free(key);
	free(temp); 
}

void updateDiaryEntry() {
	char *key = (char*)malloc(sizeof(char)*BUFFER_SIZE);
	addDiaryEntry(); 
	deleteDiaryEntry(); 
	//writeDiary();
	free(key); 
}

void writeDiary() {
	diaryFile = fopen(filename, "w"); 
	fprintf(diaryFile, "%c\n", diary->numEntries + '0'); 
	char str[BUFFER_SIZE] = ""; 
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

