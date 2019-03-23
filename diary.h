#ifndef DIARY_H
#define DIARY_H
#include "product.h"

typedef struct diary *Diaryptr; 

typedef struct diary {
	int numEntries; 
	char *date;
	ProductNode *entries; 
} DiaryNode;
#endif