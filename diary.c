#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "product.h"
#include "diary.h"

//Diaryptr diary; 
char *username;
char *filename; 
FILE *diary; 

void listAllEntries() {

}

void addDiaryEntry() {
	char *userInput = (char*)malloc(sizeof(char)); 
	system("clear");
	printMenuHeader();
	printf("Search foods: ");
	scanf("%s", userInput); 
	printf("%s", root->long_name); 
	Productptr pnode = palloc(); 
	pnode = treeSearch(root, userInput);
	printf("%s", pnode->long_name); 
}

