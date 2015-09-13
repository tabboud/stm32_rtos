/* main.c
 *
 * Developed by: Tony Abboud
 *
 *  This module shows how to communicate with the OBDII
 *  port through a serial interface.
 *
 *  Hardware Needed:
 *      - serial to usb device (cp2102)
 *      - OBDII reader
 *
 *  Connections:
 *      PA2  -> OBDII_Rx 
 *      PA3  -> OBDII_Tx
 *      PB10 -> serial-to-usb_Rx
 *      PB11 -> serial-to-usb_Tx
 *
 * NOTES:
 *  - There are different protocols for OBDII and as such, this 
 *      was only tested on a 2010 mazda 3.
 *      The commands may be different depending on the manufacturer
 *
 */

#include "ch.h"
#include "hal.h"
#include "main.h"
#include <string.h>
#include <stdlib.h>


// Get working area for thread
static THD_WORKING_AREA(waTelemetry, 512);

static THD_FUNCTION(Telemetry, arg){
    (void)arg;
    chRegSetThreadName("telemetry");
    init_USART();
    // Local Variables
    char response[150];    //Stores the received string from OBDII
    int i;
    int veh_rpm, veh_speed;
    static int command_cnt = 0;

    // Arrays to hold the results
    char vehicle_speed[3] = "00";
    char vehicle_rpm[5] = "0000";

    // Send some setup commands to the car
    for (i=0; i<3; i++) {
        send_command(OBDII_Setup[i]);
        for(i=0; 1; i++)
            if((char)sdGet(&SD2) == '>')
                break;
    }

    // MAIN LOOP
    while (1){
        // reset the command counter
        if (command_cnt >= TOTAL_CMDS){
            command_cnt = 0;
        }

        send_command(OBDII_Commands[command_cnt]);
        for(i=0; 1; i++){
            response[i] = (char)sdGet(&SD2);    // keep reading char until '>'
            if(response[i] == '>')
                break;
        }
        response[i] = '\0';    

        // Switch on the command to send using 4th character since unique
        // (see main.h for commands)
        switch (response[3]) {
            case '0':   // MAF Rate (4 byte result)
                //TODO: implement MAF Rate
                break;
            case 'C':   // Engine RPM (4 byte result)
                veh_rpm = extract_result(response, 4) / 4;
                itost(vehicle_rpm, veh_rpm);
                send_output("vehicle RPM  :\n");
                send_output(vehicle_rpm);
                break;
            case 'D':   // Vehicle Speed (2 byte result)
                veh_speed = extract_result(response, 2) * 0.62137;
                // convert integer speed, into string for outputting
                itost(vehicle_speed, veh_speed);
                send_output("vehicle speed:\n");
                send_output(vehicle_speed);
                break;
            default: break;
        }
        send_output('\n');
        command_cnt++;

        // Delay some time to send next command
        chThdSleepMilliseconds(1000); // 1 second
    }
}


int main(void) {
	halInit();
	chSysInit();

	// Create serial thread
	chThdCreateStatic(waTelemetry, sizeof(waTelemetry), NORMALPRIO, Telemetry, NULL);

	// Settings for GPIOD Led 3
  	palSetPadMode(GPIOD, GPIOD_LED3, PAL_MODE_OUTPUT_PUSHPULL);

    while(1){
        palSetPad(GPIOD, GPIOD_LED3);       // Blink Orange LED
        chThdSleepMilliseconds(100);
        palClearPad(GPIOD, GPIOD_LED3);
        chThdSleepMilliseconds(100);
    }
}


/*******************
  Helper Functions
********************/
void send_command(const char * s){
    while (*s)
        sdPut(&SD2, *(s++));    //Send string on USART2 Tx to OBDII    
}


void send_output(const char * s){
    while (*s)
        sdPut(&SD3, *(s++));    //Send string on USART3 to console   
}


void init_USART(void){
    // Configure USART2 with default configuration (384008n1):
    //      PA2 ->  USART2_TX
    //      PA3 ->  USART2_RX
    palSetPadMode(GPIOA, 2, PAL_MODE_ALTERNATE(7));
    palSetPadMode(GPIOA, 3, PAL_MODE_ALTERNATE(7)); 
    sdStart(&SD2, NULL);

    // Configure USART3 with default configuration (384008n1):
    //      PB10 ->  USART3_TX
    //      PB11 ->  USART3_RX
    palSetPadMode(GPIOB, 10, PAL_MODE_ALTERNATE(7));
    palSetPadMode(GPIOB, 11, PAL_MODE_ALTERNATE(7)); 
    sdStart(&SD3, NULL);
    }


char *itost(char *dst, int num){
    // Determine the buf size needed to represent the number
    // Only support up to 4 sig figs
    int val=1, i=0;
    if (num >= 1000){
        val = 1000;     // num is 4 sig figs
    }
    else if (num >= 100){
        val = 100;      // 3 sig figs
    }
    else if (num >= 10){
        val = 10;       // 2 sig figs
    }else{
        val = 1;
    }
    
    for(i=0; val!=0; i++){
        dst[i] = (num/val)%10 + '0';
        val /= 10;
    }
    dst[i] = '\0';

    return dst;
}


int extract_result(char *response, int bytes){
    int j=0;
    char str[5];
    for (j=0; response[j]!='\0'; j++){     
        if(response[j]=='4' && response[j+1] == '1'){
            str[0] = response[j+6];
            str[1] = response[j+7];
            if(bytes == 4){
                str[2] = response[j+9];
                str[3] = response[j+10];
                str[4] = '\0';
            }
            else{
                str[2] = '\0';
            }
            break;                                              
        }
    }
    return strtol(str, NULL, 16);  //convert string Hex to an integer     
}   
