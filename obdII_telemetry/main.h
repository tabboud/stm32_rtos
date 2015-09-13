#ifndef MAIN_H
#define MAIN_H

/*ELM AT COMMANDS*/
#define ELM_RESET           "ATZ\r"
#define PROTOCOL_SELECT     "ATSP0\r"
#define ADD_LINES           "ATL1\r"
#define ENGINE_RPM          "010C\r"
#define VEHICLE_SPEED       "010D\r"
// #define MAF_RATE            "0110\r"
// #define FUEL_STATUS         "012F\r"
// #define ENGINE_TEMP         "0105\r"    
#define TOTAL_CMDS 2

// Setup commands data structure
const char *OBDII_Setup[3] = {
    ELM_RESET,
    PROTOCOL_SELECT,
    ADD_LINES
};

// Commands data structure
const char *OBDII_Commands[TOTAL_CMDS] = {
    ENGINE_RPM,
    VEHICLE_SPEED
};


// Function definitions
void init_USART(void);          // Initialize the Usart
void send_command(const char * s);
void send_output(const char * s);
char *itost(char *dst, int num); 
int extract_result(char *response, int bytes);  // return an integer representation of the hex bytes returned from OBDII
#endif