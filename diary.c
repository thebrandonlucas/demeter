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
	char *buffer = (char*)malloc(sizeof(char));
	char *token = (char*)malloc(sizeof(char));
	diary->numEntries = 0;
	rewind(diaryFile); 
	fgets(buffer, 5, diaryFile);
	diary->numEntries = atoi(buffer);
	diary->entries = malloc(diary->numEntries * sizeof(Productptr)); 
	for (int i = 0; i < diary->numEntries; i++) {
		diary[i].time = (char*)malloc(sizeof(char)); 
		diary[i].entries = (Productptr)malloc(sizeof(Productptr));
		fgets(buffer, BUFFER_SIZE, diaryFile);
		// remove newline
		//token = strtok(buffer, "\n"); 
		token = strtok(buffer, "~"); 
		diary[i].time = token; 
		// this will be the food item name
		token = strtok(NULL, "~"); 
		Productptr pnode = palloc(); 
		pnode = treeSearch(root, token); 
		diary[i].entries = pnode; 
	}
}

void listAllEntries() {

}

void addDiaryEntry() {
	char *userInput = (char*)malloc(sizeof(char)); 
	int choice = 0; 
	system("clear");
	printMenuHeader();
	printf("Search foods: ");
	fgets(userInput, 1000, stdin); 
	uppercase(userInput); 
	Productptr pnode = palloc(); 
	pnode = treeSearch(root, userInput);
	printSearchResults(pnode); 
	printf("Select Item: "); 
	choice = readInt(stdin, ""); 
	time_t now; 
	time(&now); 
	diary->numEntries += 1; 
	//for (int i = 0; i < diary->numEntries; i++) {
		diary[diary->numEntries-1].time = strtok(ctime(&now), "\n");
		diary[diary->numEntries - 1].entries = pnode;
	//}
	writeDiary(); 
}

void writeDiary() {
	rewind(diaryFile); 
	fprintf(diaryFile, "%c\n", diary->numEntries + '0'); 
	char *temp = (char*)malloc(sizeof(char)); 
	for (int i = 0; i < diary->numEntries; i++) {
		//fprintf(diaryFile, "%s~", diary[i].time); 
		//fprintf(diaryFile, "%s", diary[i].entries->long_name); 
		//printf("%d\n", i); 
		strncpy(temp, diary[i].time, BUFFER_SIZE);
		strncat(temp, "~", BUFFER_SIZE);
		strncat(temp, diary[i].entries->long_name, BUFFER_SIZE);
		printf("%s", diary[i].time); 
		printf("%s", temp); 
		fprintf(diaryFile, "%s", temp); 
	}
	//fclose(diaryFile); 
}

