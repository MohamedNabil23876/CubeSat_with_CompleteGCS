/*
 * RTOS_Pri.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: nabil
 */

#ifndef RTOS_RTOS_PRI_H_
#define RTOS_RTOS_PRI_H_

typedef enum
{
	Suspended,
	Runing
}RunState;

typedef struct
{
	void (*TaskHandler) (void);
	u8        Periodicity      ;
	u8        FrisetDelay      ;
	RunState  Task_Run_State   ;
}Task;


#endif /* RTOS_RTOS_PRI_H_ */
