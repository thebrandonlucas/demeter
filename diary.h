#ifndef DIARY_H
#define DIARY_H

#define BUFFER_SIZE 1024

typedef struct diary DiaryNode; 

extern char username[50];
extern char filename[50]; 
extern FILE *diaryFile; 
extern DiaryNode *diary;
extern char userInput[BUFFER_SIZE]; 
//extern char choice; 

typedef struct diary {
	int numEntries;
	char **time;
	ProductNode **entries;
} DiaryNode;

// load data from file into diary
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