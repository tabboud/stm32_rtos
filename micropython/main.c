/*
 * main.c
 *
 *  This is the main entry point for running micropython
 *  micropython in a FreeRTOS thread
 *
 */

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "mptask.h"

/******************************************************************************
 DECLARE PRIVATE CONSTANTS
 ******************************************************************************/

/******************************************************************************
 DECLARE PRIVATE FUNCTIONS
 ******************************************************************************/

/******************************************************************************
 DECLARE PRIVATE DATA
 ******************************************************************************/

/******************************************************************************
 DECLARE PUBLIC DATA
 ******************************************************************************/
#ifdef DEBUG
TaskHandle_t mpTaskHandler = NULL;  // used to reference the created task
#endif

/******************************************************************************
 DEFINE PUBLIC FUNCTIONS
 ******************************************************************************/

// Place this function in the '.boot' section
__attribute__((section (".boot")))
int main(void) {
    uint8_t ret;

    // Initialize the clocks and interrupt system
    SystemInit();
    SystemCoreClockUpdate();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);


// Create the task for micropython to run in
#ifdef DEBUG
    ret = xTaskCreate(TASK_Micropython, "MicroPy", MICROPY_TASK_STACK_SIZE, NULL, MICROPY_TASK_PRIORITY, mpTaskHandler);
    configASSERT(mpTaskHandler);
#else
    ret = xTaskCreate(TASK_Micropython, "MicroPy", MICROPY_TASK_STACK_SIZE, NULL, MICROPY_TASK_PRIORITY, NULL);
#endif

    if (ret == pdPASS) {
        vTaskStartScheduler();  // should never return
    } else {
        //TODO: blink some LEDs to indicate fatal system error
    }

    for (;;);
}



/*
 *  Application exceptions
 *
 *
 */
void vApplicationTickHook(void) {
}

void vApplicationMallocFailedHook(void) {
  taskDISABLE_INTERRUPTS();
  for(;;);
}

void vApplicationIdleHook(void) {
}

void vApplicationStackOverflowHook(xTaskHandle pxTask, signed char *pcTaskName) {
  (void) pcTaskName;
  (void) pxTask;
  /* Run time stack overflow checking is performed if
     configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
     function is called if a stack overflow is detected. */
  taskDISABLE_INTERRUPTS();
  for(;;);

}
