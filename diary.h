#ifndef DIARY_H
#define DIARY_H

typedef struct diary *Diaryptr; 

extern char *username;
extern char *filename; 
extern FILE *diary; 

typedef struct diary {
	int numEntries; 
	char *date;
	char *username; 
	char *filename; 
	Productptr *entries[]; 
} Diary;

// List current entries in diary
void listAllEntries();

// Add a new entry to a diary
void addDiaryEntry(); 
#endif