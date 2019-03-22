#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
//#include "product_functions.c"
//#include <menu.h>
//#include <ncurses.h>



void loadProductData(char* filename, int fileSize, Productptr productTree) {
	FILE* productFile;
	char buffer[BUFFER_SIZE];
	productFile = fopen(filename, "r");
	//fgets(buffer, sizeof(buffer), productFile);
	char* token;
	//struct Product product = { .NBD_Number = 0, .long_name = "", .manufacturer = "", .energy = 0.0,
	//							.carbs = 0.0, .fat = 0.0, .protein = 0.0, .serving_size = 0.0,
	//							.serving_size_units = "", .household_serving_size = "", 
	//							.household_serving_size_units =  };
	int i; 
	// initialize and allocate space
	//for (i = 0; i < fileSize; i++) {
	//	productList[i] = (Productptr)malloc(sizeof(ProductNode) * sizeof(productList[i]->long_name)); 
	//}
//
//	// place each line (struct) in array
//	for (int i = 0; i < fileSize; i++) {
//		fgets(buffer, sizeof(buffer), productFile);
//		/*printf("%s", buffer); */
//		token = strtok(buffer, "~");  /*printf("%s", token);*/
//		productList[i]->NBD_Number = atoi(token); token = strtok(NULL, "~"); /**token = '\0'; printf("%s", token); */
//		productList[i]->long_name = token; token = strtok(NULL, "~");  /**token = '\0';*//*printf("%s", productList[i]->long_name); */
//		productList[i]->manufacturer = token; token = strtok(NULL, "~");
//		productList[i]->energy = atof(token); token = strtok(NULL, "~");
//		productList[i]->carbs = atof(token); token = strtok(NULL, "~");
//		productList[i]->fat = atof(token); token = strtok(NULL, "~");
//		productList[i]->protein = atof(token); token = strtok(NULL, "~");
//		productList[i]->serving_size = atof(token); token = strtok(NULL, "~");/* *token = '\0';*/
//		productList[i]->serving_size_units = token; token = strtok(NULL, "~");
//		// check for nulls
//		if (token == NULL)
//			productList[i]->household_serving_size = 0.0; 
//		else 
//			productList[i]->household_serving_size = atof(token);
//		token = strtok(NULL, "~");
//		//if (token == NULL)
//			//productList[i]->household_serving_size_units = "None";
//		//else
//			productList[i]->household_serving_size_units = token; 
//
//		//printf("%d ", i); 
//		//printf("%s---%s***", token, productList[i]->long_name); 
//		//token = strtok(NULL, "~"); 
//		//*token = '\0';
//		//productList[i]->household_serving_size_units = token; 
//		//productList[i] = &product; 
//		//printf("%s", &product.long_name); 
//		//printf("%s", productList[i]->long_name); 
//	}
//	for (i = 0; i < fileSize; i++) {
//		//printf("%s ", productList[i]->long_name); 
//	}
//	/*for (i = 0; i < fileSize; i++) {
//		printf("**** %s || %s ****", productList[i]->long_name, productList[i]->manufacturer);
//	}*/
//	//printf("adsf %f asdf ", atof(temp)); 
//	// when 
//	//printf("%d %f %s %s", productList[224152]->NBD_Number, productList[224152]->household_serving_size, productList[224152]->household_serving_size_units, productList[224152]->long_name);
//	//printf("%d", productList[0]->NBD_Number); 
//	fclose(productFile);
//	//printf("%s\n%s\n", productList[0].long_name, productList[PRODUCTS_SIZE - 1].long_name);
	return; 
}

void printMenu() {
	//WINDOW *w;
	//char list[5][30] = { "1 - List Your Summary\n", "2 - Add Meal\n", "3 - Update Meal\n", "4 - Delete Meal\n", "5 - Exit\n\n" };
	//char item[7];
	//int ch, i = 0, width = 7;

	//initscr(); // Initialize window
	//w = newwin(15, 50, 1, 1);
	//box(w, 0, 0);
	//noecho(); // Don't echo any keypresses
	//curs_set(FALSE); // Don't display a cursor

	//// print all the menu items and highlight the first one
	//for (i = 0; i < 5; i++) {
	//	if (i == 0)
	//		wattron(w, A_STANDOUT); // highlight first item 
	//	else
	//		wattroff(w, A_STANDOUT);
	//	sprintf(item, "%-7s", list[i]);
	//	mvwprintw(w, i + 1, 2, "%s", item);
	//}

	//wrefresh(w); // update terminal screen 
	//i = 0;
	//noecho(); // disable echoing of characters on the screen 
	//keypad(w, TRUE); //enable keyboard input for the window 
	//curs_set(0); // hide the default screen cursor

	// get the input 
	//while ((ch = wgetch(w) != 'q')) {
	//	// right pad with spaces to make the items appear with even width 
	//	sprintf(item, "%-7s", list[i]); 
	//	mvwprintw(w, i + 1, 2, "%s", item); 
	//	// use a variable to increment or decrement the value based on the input 
	//	switch (ch) {
	//	case KEY_UP: 
	//		i--; 
	//		i = (i < 0) ? 4 : i; 
	//		break;
	//	case KEY_DOWN: 
	//		i++; 
	//		i = (i > 4) ? 0 : i; 
	//		break; 
	//	}
	//	// now highlight the next item in the list 
	//	wattron(w, A_STANDOUT); 

	//	sprintf(item, "%-7s", list[i]); 
	//	mvwprintw(w, i + 1, 2, "%s", item); 
	//	wattroff(w, A_STANDOUT); 
	//}
	//delwin(w);
	printf("1 - List Your Summary\n"); 
	printf("2 - Add Meal\n"); 
	printf("3 - Update Meal\n"); 
	printf("4 - Delete Meal\n"); 
	printf("5 - Exit\n\n"); 
	
	//sleep(1); 
	return; 
}

int main() {
	system("clear"); 
	char* productFile = "food_database.csv";
	//struct Product* productList[PRODUCTS_SIZE];
	//loadProductData(productFile, productList);
	//loadProductData(productFile, PRODUCTS_SIZE, productList); 
	
	printf("hello"); 
	Productptr root = NULL; 
	root = insert(root, 10); 
	printf("%d", root->NBD_Number); 
	//printMenu(); 
	//printf("hello%shello", productList[0]->long_name); 
	//printf("Choose an option: "); 
	//int menuChoice; 
	//scanf("%d", &menuChoice); 

	//printf("You entered %d\n", menuChoice); 
	//
	//switch (menuChoice) {
	//	
	//}

	//endwin(); // Restore normal terminal behavior

	return 0; 
}


