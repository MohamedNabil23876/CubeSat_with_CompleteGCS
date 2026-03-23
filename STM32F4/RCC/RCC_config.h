/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  RCC_config_H
 *       Module:  -
 *
 *  Description:   header for the RCC comfigration types     
 *  
 *********************************************************************************************************************/
#ifndef  RCC_CONFIG_H
#define  RCC_CONFIG_H


/**********************************************************************************************************************
 * RCC CLOCK TYPE Config
 *********************************************************************************************************************/
#define RCC_CLOCK_TYPE   RCC_HSE_CRYSTAL
/*options :  [RCC_HSE_CRYSTAL   RCC_HSE_RC   RCC_HSI     RCC_PLL   ] */

/**********************************************************************************************************************
 * PLL Config 
 *********************************************************************************************************************/
#define RCC_PLL_SRC  
/*options :  [PLL_SRC_HSI   PLL_SRC_HSE]  PLL and PLLI2S clock source */
#define RCC_PLLM_VALUE  
/*Division factor for the main PLL (PLL) and audio PLL (PLLI2S) input clock
       PLLM Range [ 0x2 < PLLM < 0x63]          */
#define RCC_PLLN_VALUE  
/*PLL Multiplication factor for VCO
       PLLN Range [50 < PLLN < 432]          */
#define RCC_PLLP_VALUE  
/*division factor for PLL Output
       PLLP options [2  4  6  8]          */
#define RCC_PLLQ_VALUE  
/*(PLL) division factor for USB OTG FS, SDIO and random number generator  clock
       PLLQ Range   [0x2  < PLLQ  < 0x15  ]       */

#define CSS 
/*options :  [ON   OFF]  Clock security system */
#endif
