/*
 *  mptask.c
 *
 *
 *
 *  Author: Tony Abboud (tony.abboud54@gmail.com)
 */

#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "stm32f4xx_gpio.h"



/******************************************************************************
 DECLARE PRIVATE CONSTANTS
 ******************************************************************************/

/******************************************************************************
 DECLARE PRIVATE FUNCTIONS
 ******************************************************************************/
/*
STATIC void mptask_pre_init (void);
STATIC void mptask_init_sflash_filesystem (void);
STATIC void mptask_enter_ap_mode (void);
STATIC void mptask_create_main_py (void);
*/
/******************************************************************************
 DECLARE PUBLIC DATA
 ******************************************************************************/
#ifdef DEBUG
// OsiTaskHandle   svTaskHandle;
#endif

/******************************************************************************
 DECLARE PRIVATE DATA
 ******************************************************************************/
// static FATFS *sflash_fatfs;

static const char fresh_main_py[] = "# main.py -- put your code here!\r\n";
static const char fresh_boot_py[] = "# boot.py -- run on boot-up\r\n"
                                    "# can run arbitrary Python, but best to keep it minimal\r\n";

/******************************************************************************
 DECLARE PUBLIC FUNCTIONS
 ******************************************************************************/

void TASK_Micropython (void *pvParameters) {
  for (;;) {
    vTaskDelay(250 / portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
 }