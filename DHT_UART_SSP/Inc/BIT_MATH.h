/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  BIT_MATH
 *       Module:  -
 *
 *  Description:  Header file for bit math operations    
 *  
 *********************************************************************************************************************/
#ifndef BIT_MATH_H
#define BIT_MATH_H


/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  Bit MACROS
 *********************************************************************************************************************/
//#define SET_BIT(VAR,BIT) 		(VAR|=(1<<(BIT)))
#define CLR_BIT(VAR,BIT) 		(VAR&=~(1<<(BIT)))
#define GET_BIT(VAR,BIT) 		((VAR&(1<<BIT))>>BIT)
#define TOG_BIT(VAR,BIT) 		(VAR^=(1<<(BIT)))


/**********************************************************************************************************************
 *  Register MACROS
 *********************************************************************************************************************/
#define SET_REG(VAR) 				 	VAR=0xFFFFFFFF
#define CLR_REG(VAR) 		    	  	VAR=0x00000000
#define MSKP_REG(VAR,START_BIT,VALUE)  (VAR=((VAR&~(0x00000000<<START_BIT))|(VALUE<<START_BIT)))
#define GET_BYTE(VAR,START_BIT)        ((VAR&(0XFF<<START_BIT))>>START_BIT)

#define GET_5BIT(VAR,START_BIT)        ((VAR&(0X1F<<START_BIT))>>START_BIT)
#define GET_4BIT(VAR,START_BIT)        ((VAR&(0X0F<<START_BIT))>>START_BIT)
#define GET_3BIT(VAR,START_BIT)        ((VAR&(0X07<<START_BIT))>>START_BIT)
/**********************************************************************************************************************
 * Masking Macros
 *********************************************************************************************************************/
#define MSK_1BIT(VAR,START_BIT,VALUE)   (VAR=((VAR&~(1<<START_BIT))|(VALUE<<START_BIT)))
#define MSK_2BIT(VAR,START_BIT,VALUE)  (VAR=((VAR&~(0x3<<START_BIT))|(VALUE<<START_BIT)))
#define MSK_3BIT(VAR,START_BIT,VALUE)  (VAR=((VAR&~(0x7<<START_BIT))|(VALUE<<START_BIT)))
#define MSK_4BIT(VAR,START_BIT,VALUE)  (VAR=((VAR&~(0xF<<START_BIT))|(VALUE<<START_BIT)))
#define MSK_5BIT(VAR,START_BIT,VALUE)  (VAR=((VAR&~(0x1F<<START_BIT))|(VALUE<<START_BIT)))
#define MSK_6BIT(VAR,START_BIT,VALUE)  (VAR=((VAR&~(0x3F<<START_BIT))|(VALUE<<START_BIT)))
#define MSK_7BIT(VAR,START_BIT,VALUE)  (VAR=((VAR&~(0x7F<<START_BIT))|(VALUE<<START_BIT)))
#define MSK_BYTE(VAR,START_BIT,VALUE)  (VAR=((VAR&~(0xFF<<START_BIT))|(VALUE<<START_BIT)))
#define MSK_9BIT(VAR,START_BIT,VALUE)  (VAR=((VAR&~(0x1FF<<START_BIT))|(VALUE<<START_BIT)))
#define MSK_2BYTE(VAR,START_BIT,VALUE) (VAR=((VAR&~(0xFFFF<<START_BIT))|(VALUE<<START_BIT)))
#define MSK_12BIT(VAR,START_BIT,VALUE)  (VAR=((VAR&~(0xFFF<<START_BIT))|(VALUE<<START_BIT)))

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

 
#endif  /* BIT_MATH_H */

/**********************************************************************************************************************
 *  END OF FILE: BIT_MATH.h
 *********************************************************************************************************************/
