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
		//diary[i].entries = (Productptr)malloc(sizeof(Productptr));
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
		//printf("bbb%s", diary[i].entries->long_name); 
	}
	//free(buffer); 
	//free(token); 
}

void listAllEntries() {

}

void searchDiary(char *key) {
	int matchIndexCounts[diary->numEntries]; 
	int bestMatchIndex = 0; 
	int bestMatchIndexCount = 0; 
	//printf("asdfasdf"); 
	//printf("%d", strcmp(key, diary[0].entries->long_name)); 
	//for (int i = 0; i < diary->numEntries; i++) {
	//	matchIndexCounts[i] = 0;
	//	for (int j = 0; j < strlen(key); j++) {
	//		if (key[j] == diary[i].entries->long_name[j]) {
	//			matchIndexCounts[i]++; 
	//		}
	//	}
	//	//if (strcmp(key, diary[i].entries->long_name) == 0)
	//	//	return diary[i]; 
	//	//else if (strcmp(key, diary[i].entries->long_name) < 0) {
	//	//}
	//	if (matchIndexCounts[i] > bestMatchIndexCount) {
	//		bestMatchIndexCount = matchIndexCounts[i]; 
	//		bestMatchIndex = i; 
	//	}
	//	return diary[bestMatchIndex]; 
	//}
	//printf("aa%s", diary[0].entries->long_name);
	//for (int i = 0; i < diary->numEntries; i++) {
	//	printf("BEFORE %s\n", diary[i].entries->long_name);
	//}
	Productptr pnode = palloc();
	pnode = treeSearch(root, key);
	int deleteIndex = 0; 
	//printf("%s", diary[1].entries->long_name); 

	//for (int i = 0; i < diary->numEntries; i++) {
	//	printf("AFTER %s\n", diary[i].entries->long_name);
	//}


	//for (int i = 0; i < diary->numEntries; i++) {
	//	if (diary[i] == NULL) {
	//		continue; 
	//	}
	//	dia
	//}
	//printSearchResults(pnode);
	//return key; 
}

void printDiarySearchResults(char *key) {
	//Productptr returnedDiary = palloc(); 
	//returnedDiary = searchDiary(key);
	searchDiary(key); 
	//printf("adsf%s", returnedDiary->long_name); 
}

void addDiaryEntry() {
	char *userInput = (char*)malloc(sizeof(char)*BUFFER_SIZE); 
	int choice = 0; 
	system("clear");
	printMenuHeader();
	printf("Search foods: ");
	fgets(userInput, BUFFER_SIZE, stdin); 
	uppercase(userInput); 
	Productptr pnode = palloc(); 
	pnode = treeSearch(root, userInput);
	printSearchResults(pnode); 
	printf("Select Item: "); 
	choice = readInt(stdin, ""); 
	time_t now; 
	time(&now); 
	diary->numEntries += 1; 
	diary[diary->numEntries-1].time = strtok(ctime(&now), "\n");
	diary[diary->numEntries - 1].entries = pnode;
	writeDiary(); 
	free(userInput); 
}

void deleteDiaryEntry() {
	char *userInput = (char*)malloc(sizeof(char)*BUFFER_SIZE);
	system("clear"); 
	printMenuHeader(); 
	printf("Search Diary: "); 
	fgets(userInput, BUFFER_SIZE, stdin); 
	uppercase(userInput); 
	Productptr pnode = palloc(); 
	pnode = treeSearch(root, userInput); 
	for (int i = 0; i < diary->numEntries; i++) {
		if (strcmp(pnode->long_name, diary[i].entries->long_name) == 0) {
			//if (diary[i].numEntries != diary->numEntries + 1) {
			for (int j = i; j < diary->numEntries - 1; j++) {
				//printf("%s", diary[j + 1].time);
				diary[j].time = diary[j + 1].time;
				diary[j].entries = diary[j + 1].entries;
			}
			//}
			diary->numEntries--;
			break;
		}
	}
	writeDiary();
	free(userInput);
}

void writeDiary() {
	diaryFile = fopen(filename, "w"); 
	fprintf(diaryFile, "%c\n", diary->numEntries + '0'); 
	char *temp = (char*)malloc(sizeof(char)*BUFFER_SIZE); 
	for (int i = 0; i < diary->numEntries; i++) {
		strncpy(temp, diary[i].time, BUFFER_SIZE);
		strncat(temp, "~", BUFFER_SIZE);
		strncat(temp, diary[i].entries->long_name, BUFFER_SIZE);
		fprintf(diaryFile, "%s\n", temp); 
	}
	free(temp); 
	//for (int i = 0; i < diary->numEntries; i++) {
	//	free(diary[i].entries); 
	//}
	// figure out how to 
	//pfree(root); 
	free(diary->entries); 
	fclose(diaryFile); 
}

