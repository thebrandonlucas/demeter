#ifndef DIARY_H
#define DIARY_H

typedef struct diary *Diaryptr; 

extern char *username;
extern char *filename; 
extern FILE *diaryFile; 
extern Diaryptr diary; 

typedef struct diary {
	int numEntries; 
	char *time;
	Productptr entries; 
} Diary;

// load data from file into diary
void loadDiary(FILE *diaryFile);

// List current entries in diary
void listAllEntries();

// Search for an item by name in the diary
void searchDiary(char *key);

// Print diary search results for delete and update
void printDiarySearchResults(char *key);

// Add a new entry to a diary
void addDiaryEntry(); 

// Delete a diary entry
void deleteDiaryEntry(); 

// Write diary data to file at program end
void writeDiary(); 
#endif