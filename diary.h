#ifndef DIARY_H
#define DIARY_H

#define BUFFER_SIZE 1024

typedef struct diary *Diaryptr; 

extern char *username;
extern char *filename; 
extern FILE *diaryFile; 
extern Diaryptr diary; 
extern char *userInput; 
extern int *choice; 

typedef struct diary {
	int numEntries; 
	char **time;
	Productptr *entries; 
} Diary;

// load data from file into diary
void loadDiary(FILE *diaryFile);

// List current entries in diary
void listAllEntries();

// Build a longest common subsequence table for 
// better search results
int buildLCSTable(int n, int m, int L[n][m], char *X, char *Y); 

// Print diary search results for delete and update
void printDiarySearchResults(char *key);

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