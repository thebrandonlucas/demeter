#ifndef DIARY_H
#define DIARY_H

/*
	This file defines all global variables, in addition
	to all functions for files relating to manipulating
	the user diary. 
*/

// A standard generic buffer size used 
// throughout the program
#define BUFFER_SIZE 1024

// A descriptive shorthand for the diary struct type
typedef struct diary DiaryNode; 

// A global username variable
extern char username[50];

// A global filename variable
extern char filename[50]; 

// A global diary file variable pointer
extern FILE *diaryFile; 

// The global user diary, written to file
// at the end of the program
extern DiaryNode *diary;

// A global variable use
//extern char userInput[BUFFER_SIZE]; 

// The diary function definition
// Saves the number of entries, 
// an array of user add/update times, 
// and an array of product entries
typedef struct diary {
	int numEntries;
	char **time;
	ProductNode **entries;
} DiaryNode;

// Load data from .log file into diary
void loadDiary(FILE *diaryFile);

// List current entries in diary
void listAllEntries();

// Build a longest common subsequence table for 
// better search results
int buildLCSTable(int n, int m, int L[n][m], char *X, char *Y); 

// Prompt and search for an element in the diary
// Returns a node with corresponding element
char *searchDiary(char *option); 

// Add a new entry to a diary
void addDiaryEntry(char *option);

// Delete a diary entry
void deleteDiaryEntry(char *option);

// Update a diary entry
void updateDiaryEntry(); 

// Write diary data to file at program end
void writeDiary(); 
#endif