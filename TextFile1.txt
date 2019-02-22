#include "pic24_all.h"
/// LED1
#define CONFIG_LED1() CONFIG_RB14_AS_DIG_OUTPUT()
#define LED1 _LATB14 // led1 state
/// Switch1 configuration
inline void CONFIG_SW1() {
	CONFIG_RB13_AS_DIG_INPUT(); // use RB13 for switch input
	ENABLE_RB13_PULLUP(); // enable the pullup
}

#define SW1 _RB13 // switch state
#define SW1_PRESSED() (SW1==0) // switch test
#define SW1_RELEASED() (SW1==1) // switch test
/// Switch2 configuration
inline void CONFIG_SW2() {
	CONFIG_RB12_AS_DIG_INPUT(); // use RB12 for switch input
	ENABLE_RB12_PULLUP(); // enable the pullup
}
#define SW2 _RB12 // switch state
int changeToGrayCode(char bin) {
	char gray; 
	gray = bin >> 1; 
	gray = bin ^ gray; 
	return gray; 
} 

typedef enum {
	STATE_RESET = 0,
	STATE_WAIT_FOR_PRESS1,
	STATE_WAIT_FOR_RELEASE1,
	STATE_WAIT_FOR_PRESS2,
	STATE_WAIT_FOR_RELEASE2,
	STATE_BLINK,
	STATE_WAIT_FOR_RELEASE3
} STATE;

int main (void) {
	STATE e_mystate;
	configBasic(HELLO_MSG);
	/** GPIO config ***************************/
	CONFIG_SW1(); // configure switch
	CONFIG_SW2(); // configure switch
	CONFIG_LED1(); // configure the LED
	DELAY_US(1); // give pullups a little time
	/**** Toggle LED each time switch is pressed and released *************/
	e_mystate = STATE_WAIT_FOR_PRESS1;

	while (1) {
	//	printNewState(e_mystate); //debug message when state changes
		switch (e_mystate) {
			case STATE_WAIT_FOR_PRESS1:
				LED1 = '000'; //turn off the LED
				if (SW1_PRESSED()) e_mystate = STATE_WAIT_FOR_RELEASE1;
				break;
			case STATE_WAIT_FOR_RELEASE1:
				if (SW1_RELEASED()) e_mystate = STATE_WAIT_FOR_PRESS2;
				break;
			case STATE_WAIT_FOR_PRESS2:
				LED1 = '111'; //turn on the LED
				if (SW1_PRESSED()) e_mystate = STATE_WAIT_FOR_RELEASE2;
				break;
			case STATE_WAIT_FOR_RELEASE2:
				if (SW1_RELEASED()) {
					//decide where to go
				if (SW2) e_mystate = STATE_BLINK;
					else e_mystate = STATE_WAIT_FOR_PRESS1;
				}
				break;
			case STATE_BLINK:
				LED1 = !LED1; // Blink while not pressed
				DELAY_MS(100); // Blink delay
				if (SW1_PRESSED()) e_mystate = STATE_WAIT_FOR_RELEASE3;
				break;
			case STATE_WAIT_FOR_RELEASE3:
				LED1 = 1; // Freeze LED1 at 1
				if (SW1_RELEASED()) e_mystate = STATE_WAIT_FOR_PRESS1;
				break;
			default:
				e_mystate = STATE_WAIT_FOR_PRESS1;
		} // end switch(e_mystate)
		DELAY_MS(15); // Debounce		
	} // end while (1)
}