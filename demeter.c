#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define PRODUCTS_SIZE 228805
#define DERIVATION_CODE_DESCRIPTION_SIZE 9
#define SERVING_SIZE 237911
#define NUTRIENTS_SIZE 1048576


struct Product {
	int NBD_Number; 
	char* long_name; 
	// TODO: change back to char [2]?
	char* data_source;
	long int gtin_upc; 
	char* manufacturer; 
	char* date_modified; 
	char* date_available; 
	char* ingredients_english; 
};

void loadProductData(char* filename, int fileSize, struct Product *productList[]) {
	FILE* productFile;
	char buffer[BUFFER_SIZE];
	productFile = fopen(filename, "r");
	//fgets(buffer, sizeof(buffer), productFile);
	char* token;
	struct Product product = { .NBD_Number = 0, .long_name = "", .data_source = "", .gtin_upc = 0, 
								 .manufacturer = "", .date_modified = "", .date_available = "", 
								 .ingredients_english = ""};

	// place each line (struct) in array
	for (int i = 0; i < fileSize; i++) {
		fgets(buffer, sizeof(buffer), productFile);
		token = strtok(buffer, "~"); 
		product.NBD_Number = atoi(token); token = strtok(NULL, "~"); 
		product.long_name = token; token = strtok(NULL, "~"); 
		product.data_source = token; token = strtok(NULL, "~");  
		product.gtin_upc = atoi(token); token = strtok(NULL, "~");
		product.manufacturer = token; token = strtok(NULL, "~");
		product.date_modified = token; token = strtok(NULL, "~");
		product.date_available = token; token = strtok(NULL, "~");
		product.ingredients_english = token;
		productList[i] = &product; 
	}
	fclose(productFile);
	//printf("%s\n%s\n", productList[0].long_name, productList[PRODUCTS_SIZE - 1].long_name);
	return; 
}

void printMenu() {
	//WINDOW *w; 
	//char list[5][7] = { "One", "Two", "Three", "Four", "Five" }; 
	//char item[7]; 
	//int ch, i = 0, width = 7; 

	//initscr(); // Initialize window
	//w = newwin(10, 12, 1, 1); 
	//box(w, 0, 0); 
	//noecho(); // Don't echo any keypresses
	//curs_set(FALSE); // Don't display a cursor
	printf("1 - List Your Summary\n"); 
	printf("2 - Add Meal\n"); 
	printf("3 - Update Meal\n"); 
	printf("4 - Delete Meal\n"); 
	printf("5 - Exit\n\n"); 
	
	//sleep(1); 
	return; 
}

int main() {
	char* productFile = "food_database.csv";
	struct Product* productList[PRODUCTS_SIZE];
	//loadProductData(productFile, productList);
	loadProductData(productFile, PRODUCTS_SIZE, productList); 
	printMenu(); 
	//printf("Choose an option: "); 
	//int menuChoice; 
	//scanf("%d", &menuChoice); 

	//printf("You entered %d", menuChoice); 
	
	//switch (menuChoice) {

	//}

	//endwin(); // Restore normal terminal behavior

	return 0; 
}
