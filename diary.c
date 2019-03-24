#include <stdio.h>
#include <stdlib.h>
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
	char temp; 
	diary->numEntries = 0;
	rewind(diaryFile); 
	fgets(buffer, 10, diaryFile);
	diary->numEntries = atoi(buffer);
	diary->time = (char*)malloc(sizeof(char)*BUFFER_SIZE);
	for (int i = 0; i < diary->numEntries; i++) {
		diary[i].entries = malloc(diary->numEntries * sizeof(Productptr));
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
	//diary->numEntries = 1; 
}

