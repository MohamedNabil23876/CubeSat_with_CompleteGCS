/*********************************************************************************************************************
  *   FILE DESCRIPTION
  *  -------------------------------------------------------------------------------------------------------------------
  *         File:  GPIO_PRIVATE_H
  *       Module:  -
  *
  *  Description:   header for the GPIO registers and their bits    
  *  
  *********************************************************************************************************************/
#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H
 
 
 /**********************************************************************************************************************
 * REGISTERS DEFINITIONS
 *********************************************************************************************************************/
 
 
/*PORT A*/
 #define  GPIO_A_MODER				*((volatile u32*)0x40020000)
 #define  GPIO_A_OTYPER				*((volatile u32*)0x40020004)
 #define  GPIO_A_OSPEEDR			*((volatile u32*)0x40020008)
 #define  GPIO_A_PUPDR				*((volatile u32*)0x4002000C)
 #define  GPIO_A_IDR				*((volatile u32*)0x40020010)
 #define  GPIO_A_ODR				*((volatile u32*)0x40020014)
 #define  GPIO_A_BSRR				*((volatile u32*)0x40020018)
 #define  GPIO_A_LCKR				*((volatile u32*)0x4002001C)
 #define  GPIO_A_AFRL				*((volatile u32*)0x40020020)
 #define  GPIO_A_AFRH				*((volatile u32*)0x40020024)

/*PORT B*/
 #define  GPIO_B_MODER				*((volatile u32*)0x40020400)
 #define  GPIO_B_OTYPER				*((volatile u32*)0x40020404)
 #define  GPIO_B_OSPEEDR			*((volatile u32*)0x40020408)
 #define  GPIO_B_PUPDR				*((volatile u32*)0x4002040C)
 #define  GPIO_B_IDR				*((volatile u32*)0x40020410)
 #define  GPIO_B_ODR				*((volatile u32*)0x40020414)
 #define  GPIO_B_BSRR				*((volatile u32*)0x40020418)
 #define  GPIO_B_LCKR				*((volatile u32*)0x4002041C)
 #define  GPIO_B_AFRL				*((volatile u32*)0x40020420)
 #define  GPIO_B_AFRH				*((volatile u32*)0x40020424)
 
 /*PORT C*/
 #define  GPIO_C_MODER				*((volatile u32*)0x40020800)
 #define  GPIO_C_OTYPER				*((volatile u32*)0x40020804)
 #define  GPIO_C_OSPEEDR			*((volatile u32*)0x40020808)
 #define  GPIO_C_PUPDR				*((volatile u32*)0x4002080C)
 #define  GPIO_C_IDR				*((volatile u32*)0x40020810)
 #define  GPIO_C_ODR				*((volatile u32*)0x40020814)
 #define  GPIO_C_BSRR				*((volatile u32*)0x40020818)
 #define  GPIO_C_LCKR				*((volatile u32*)0x4002081C)
 #define  GPIO_C_AFRL				*((volatile u32*)0x40020820)
 #define  GPIO_C_AFRH				*((volatile u32*)0x40020824)

 


 

#endif  /* GPIO_PRIVATE_H */

/**********************************************************************************************************************
 *  END OF FILE: GPIO_PRIVATE_H
 *********************************************************************************************************************/