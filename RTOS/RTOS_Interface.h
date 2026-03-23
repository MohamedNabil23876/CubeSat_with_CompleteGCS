/*
 * RTOS_Interface.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: nabil
 */

#ifndef RTOS_RTOS_INTERFACE_H_
#define RTOS_RTOS_INTERFACE_H_


u8 RTOS_u8CreatTasck(void ( * Copy_Handler)(void),u8 Copy_u8Periodicity, u8 copy_u8Priority, u8 Copy_u8FriestD);

void schduler (void);

u8 RTOS_u8DeletTask (u8 copy_u8Priority);

u8 RTOS_u8SuspendTask (u8 copy_u8Priority);

u8 RTOS_u8ResumeTask (u8 copy_u8Priority);



#endif /* RTOS_RTOS_INTERFACE_H_ */
