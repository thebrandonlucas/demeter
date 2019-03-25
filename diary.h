#ifndef DIARY_H
#define DIARY_H

typedef struct diary *Diaryptr; 

extern char *username;
extern char *filename; 
extern FILE *diaryFile; 
extern Diaryptr diary; 
extern char *userInput; 

typedef struct diary {
	int numEntries; 
	char *time;
	Productptr entries; 
} Diary;

// load data from file into diary
void loadDiary(FILE *diaryFile);

// List current entries in diary
void listAllEntries();

// Build a longest common subsequence table for 
// better search results
int buildLCSTable(int n, int m, int L[n][m], char *X, char *Y); 

// Get the size of the longest common subsequence
//int buildLCSStringSize(int L[][]);

// Print diary search results for delete and update
void printDiarySearchResults(char *key);

// Prompt and search for an element in the diary
// Returns a node with corresponding element
char *searchDiary(); 

// Add a new entry to a diary
void addDiaryEntry(); 

// Delete a diary entry
void deleteDiaryEntry(); 

// Update a diary entry
void updateDiaryEntry(); 

// Write diary data to file at program end
void writeDiary(); 
#endif