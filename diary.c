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
		diary[i].time = (char*)malloc(sizeof(char)*100000); 
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
	}
	//free(buffer); 
	//free(token); 
}

void listAllEntries() {

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

void writeDiary() {
	diaryFile = fopen(filename, "w"); 
	//rewind(diaryFile); 
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
	//free(diary->entries); 
	//fclose(diaryFile); 
}

