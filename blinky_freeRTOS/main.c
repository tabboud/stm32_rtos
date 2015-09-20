#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"


void init_GPIO(void){
    GPIO_InitTypeDef   GPIO_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    // GPIOD Peripheral clock enable.
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    // Configure LEDs
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void vTestBlinky(void* p){
  for (;;) {
    GPIO_SetBits(GPIOD, GPIO_Pin_15);          // LED4 ON
    vTaskDelay(500 / portTICK_PERIOD_MS);
    GPIO_SetBits(GPIOD, GPIO_Pin_13);          // LED3 ON
    vTaskDelay(500 / portTICK_PERIOD_MS);
    GPIO_SetBits(GPIOD, GPIO_Pin_14);          // LED5 ON
    vTaskDelay(500 / portTICK_PERIOD_MS);
    GPIO_SetBits(GPIOD, GPIO_Pin_12);          // LED6 ON
    vTaskDelay(500 / portTICK_PERIOD_MS);
    GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);  // All LEDs are OFF.
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
}

int main(void) {
  uint8_t ret;

  SystemInit();
  SystemCoreClockUpdate();

    /* Most systems default to the wanted configuration, with the noticeable exception of the STM32
   * driver library. If you are using an STM32 with the STM32 driver library then ensure all the
   * priority bits are assigned to be preempt priority bits by calling
   * NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4) before the RTOS is started.
   */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  init_GPIO();

  // Create a task
  ret = xTaskCreate(vTestBlinky, "BLINKY", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

  if (ret == pdTRUE) {
    // printf("System Started!\n");
    vTaskStartScheduler();  // should never return
  } else {
    // printf("System Error!\n");
    // --TODO blink some LEDs to indicate fatal system error
    GPIO_SetBits(GPIOD, GPIO_Pin_15);          // LED4 ON
  }

  for (;;);
}

void vApplicationTickHook(void) {
}

/* vApplicationMallocFailedHook() will only be called if
   configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
   function that will get called if a call to pvPortMalloc() fails.
   pvPortMalloc() is called internally by the kernel whenever a task, queue,
   timer or semaphore is created.  It is also called by various parts of the
   demo application.  If heap_1.c or heap_2.c are used, then the size of the
   heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
   FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
   to query the size of free heap space that remains (although it does not
   provide information on how the remaining heap might be fragmented). */
void vApplicationMallocFailedHook(void) {
  taskDISABLE_INTERRUPTS();
  for(;;);
}

/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
   task.  It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()).  If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
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
