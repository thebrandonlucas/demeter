// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


// function declaration
char binToGray(char bin);

int main(void) {
	//CONFIG_LED1();
	//LED1 = 0;
	//while (1) { // Infinite while loop
	//	LED1 = !LED1; // Toggle LED1
	//	DELAY_MS(100); // Delay 100ms
	//}
	return 0;
}
// function definition
char binToGray(char bin) {
	char gray;
	// shift bit right 1
	gray = bin >> 1;
	// xor to get gray conversion
	gray = gray ^ bin;

	return gray;
}

