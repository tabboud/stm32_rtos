/* main.c
 *
 * Developed by: Tony Abboud
 *
 * Example code to blink two onboard LEDs
 * on two different threads
 *
 */

#include "ch.h"
#include "hal.h"
#include <string.h>
#include <stdlib.h>
#include "main.h"


//Get working area for thread
static THD_WORKING_AREA(waBlinkLight, 128);

// Sample thread to blink an LED
static THD_FUNCTION(BlinkLight, arg){
    (void)arg;
    chRegSetThreadName("blinker");

	//Settings LED4
	palSetPadMode(GPIOD, GPIOD_LED4, PAL_MODE_OUTPUT_PUSHPULL);

    while(1){
        palSetPad(GPIOD, GPIOD_LED4);
        chThdSleepMilliseconds(1000);
        palClearPad(GPIOD, GPIOD_LED4);
        chThdSleepMilliseconds(1000);
    }
}


int main(void) {
	halInit();
	chSysInit();

	// Create serial thread
	chThdCreateStatic(waBlinkLight, sizeof(waBlinkLight), NORMALPRIO, BlinkLight, NULL);

	// Settings for GPIOD Led 3
  	palSetPadMode(GPIOD, GPIOD_LED3, PAL_MODE_OUTPUT_PUSHPULL);

    while(1){
        palSetPad(GPIOD, GPIOD_LED3);       // Blink Orange LED
        chThdSleepMilliseconds(100);
        palClearPad(GPIOD, GPIOD_LED3);
        chThdSleepMilliseconds(100);
    }
}
