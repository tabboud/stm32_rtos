/*
 *  mptask.h
 *
 *
 *
 */

#ifndef MPTASK_H_
#define MPTASK_H_

/******************************************************************************
 DEFINE CONSTANTS
 ******************************************************************************/
#define MICROPY_TASK_PRIORITY                   (2)
#define MICROPY_TASK_STACK_SIZE                 ((6 * 1024) + 512)

/******************************************************************************
 DECLARE PUBLIC FUNCTIONS
 ******************************************************************************/
extern void TASK_Micropython (void *pvParameters);

#endif /* MPTASK_H_ */
