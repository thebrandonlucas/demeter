#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define PRODUCTS_SIZE 239090
#define DERIVATION_CODE_DESCRIPTION_SIZE 9
#define SERVING_SIZE 237911
#define NUTRIENTS_SIZE 1048576


struct Products {
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

// TODO: create a generalized function for reading CSV data of any parameters. (parseCSV)

//void parseRowCSV(char* filename, struct products* productList, int FILE_SIZE) {
//
//}

void loadProductData(char* filename, int fileSize, struct Products productList[]) {
//void loadFileData(char* filename, char* whichFile) {
	FILE* productInput;
	char buffer[BUFFER_SIZE];
	productInput = fopen(filename, "r");
	//struct products productList[PRODUCTS_SIZE];
	 //filter out columns
	fgets(buffer, sizeof(buffer), productInput);
	char* token;
	struct Products product = { .NBD_Number = 0, .long_name = "", .data_source = "", .gtin_upc = 0, 
								 .manufacturer = "", .date_modified = "", .date_available = "", 
								 .ingredients_english = ""};

	// place each line (struct) in array
	for (int i = 0; i < fileSize; i++) {
		// TODO: initialize to eliminate compiler warnings
		fgets(buffer, sizeof(buffer), productInput);
		token = strtok(buffer, ","); 
		// FIXME: this is the part you'll replace to refactor it
		product.NBD_Number = atoi(token); token = strtok(NULL, ",");
		product.long_name = token; token = strtok(NULL, ",");
		product.data_source = token; token = strtok(NULL, ",");
		product.gtin_upc = atoi(token); token = strtok(NULL, ",");
		product.manufacturer = token; token = strtok(NULL, ",");
		product.date_modified = token; token = strtok(NULL, ",");
		product.date_available = token; token = strtok(NULL, ",");
		product.ingredients_english = token;
		productList[i] = product; 
		printf("%s", productList[i].long_name); 
	}
	fclose(productInput); 
	//printf("%s\n%s\n", productList[0].long_name, productList[PRODUCTS_SIZE - 1].long_name);
	return; 
}

void printMenu() {
	printf("1 - List Your Summary\n"); 
	printf("2 - Add Meal\n"); 
	printf("3 - Update Meal\n"); 
	printf("4 - Delete Meal\n"); 
	printf("5 - Exit\n\n"); 
	return; 
}

int main() {
	char* productFile = "C:\\Users\\thebr\\Downloads\\BFPD_csv_07132018\\Products.csv"; 
	struct Products productList;
	//loadProductData(productFile, productList);
	loadProductData(productFile, PRODUCTS_SIZE, &productList); 
	printMenu(); 
	printf("Choose an option: "); 
	//int menuChoice; 
	//scanf("%d", &menuChoice); 

	//printf("You entered %d", menuChoice); 
	
	//switch (menuChoice) {

	//}
	return 0; 
}