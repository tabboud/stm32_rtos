# OBDII_Telemetry

This is an example project which shows how to communicate between the STM32F4-Discovery board and the OBDII port on a car
### Hardware
        - serial to usb device (cp2102)
        - OBDII reader
Here is what I used: [my_hardware](https://abboudscorner.wordpress.com/2014/02/21/stm32f4-car-telemetry-system/ "Title").
    
    Connections:
        PA2  -> OBDII_Rx 
        PA3  -> OBDII_Tx
        PB10 -> serial-to-usb_Rx
        PB11 -> serial-to-usb_Tx
    
### NOTES:
    - There are different protocols for OBDII and as such, 
      the commands may be different depending on the manufacturer
    - This was only tested on a 2010 mazda 3.