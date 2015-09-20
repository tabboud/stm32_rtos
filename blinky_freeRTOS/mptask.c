/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013, 2014 Damien P. George
 * Copyright (c) 2015 Daniel Campora
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
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
    GPIO_SetBits(GPIOD, GPIO_Pin_12);          // LED4 ON
    vTaskDelay(250 / portTICK_PERIOD_MS);
    GPIO_SetBits(GPIOD, GPIO_Pin_13);          // LED3 ON
    vTaskDelay(250 / portTICK_PERIOD_MS);
    GPIO_SetBits(GPIOD, GPIO_Pin_14);          // LED5 ON
    vTaskDelay(250 / portTICK_PERIOD_MS);
    GPIO_SetBits(GPIOD, GPIO_Pin_15);          // LED6 ON
    vTaskDelay(250 / portTICK_PERIOD_MS);
    GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);  // All LEDs are OFF.
    vTaskDelay(250 / portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
 }