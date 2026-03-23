/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  NVIC_program_c
 *       Module:  -
 *
 *  Description:  c program for NVIC functions   
 *  
 *********************************************************************************************************************/

 /**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include"NVIC_private.h"
#include"NVIC_config.h"
#include"NVIC_interface.h"
Group_Sub_t Group_Sub_Type ;
void NVIC_voidEnablePerInt (NVIC_Per Copyu8Per){
	SET_BIT(NVIC_ISER->ISER[Copyu8Per/32],Copyu8Per%32);
}
void NVIC_voidDisablePerInt (NVIC_Per Copyu8Per){
	SET_BIT(NVIC_ICER->ICER[Copyu8Per/32],Copyu8Per%32);
}

void NVIC_voidSetPerPendingReg (NVIC_Per Copyu8Per){
		SET_BIT(NVIC_ISPR->ISPR[Copyu8Per/32],Copyu8Per%32);

}

void NVIC_voidClrPerPendingReg (NVIC_Per Copyu8Per){
		SET_BIT(NVIC_ICPR->ICPR[Copyu8Per/32],Copyu8Per%32);

}

NVIC_Flag NVIC_u8ReadFlag(NVIC_Per Copyu8Per){
	NVIC_Flag Flag = 0;
	Flag = GET_BIT(NVIC_IABR->IABR[Copyu8Per/32],Copyu8Per%32);
	return Flag ;
}

void SCB_voidNVICPriorityConfig(Group_Sub_t  Copyu8GST){
	MSK_2BYTE(SCB_AIRCR,AIRCR_VECTKEY_Bit,VECTKEY);
	MSK_3BIT(SCB_AIRCR,AIRCR_PRIGROUP_Bit,Copyu8GST);
	Group_Sub_Type=Copyu8GST;
}

void NVIC_voidSetPriorityModeG16_S0(NVIC_Per Copyu8Per,u8 Copyu8Group){
	if(Group_Sub_Type=G16_S0){
			MSK_4BIT(NVIC_IPR->IPR[Copyu8Per/4],4+(8*(Copyu8Per%4)),Copyu8Group);

	}
	
}
void NVIC_voidSetPriorityModeG8_S2(NVIC_Per Copyu8Per,u8 Copyu8Group,u8 Copyu8Sub){
	if(Group_Sub_Type=G8_S2){
	MSK_3BIT(NVIC_IPR->IPR[Copyu8Per/4],5+(8*(Copyu8Per%4)),Copyu8Group);
		MSK_1BIT(NVIC_IPR->IPR[Copyu8Per/4],4+(8*(Copyu8Per%4)),Copyu8Sub);
	}
	
}
void NVIC_voidSetPriorityModeG4_S4(NVIC_Per Copyu8Per,u8 Copyu8Group,u8 Copyu8Sub){
	if(Group_Sub_Type=G4_S4){
		MSK_2BIT(NVIC_IPR->IPR[Copyu8Per/4],6+(8*(Copyu8Per%4)),Copyu8Group);
		MSK_2BIT(NVIC_IPR->IPR[Copyu8Per/4],4+(8*(Copyu8Per%4)),Copyu8Sub);
	}
	
}
void NVIC_voidSetPriorityModeG2_S8(NVIC_Per Copyu8Per,u8 Copyu8Group,u8 Copyu8Sub){
	if(Group_Sub_Type=G2_S8){
		MSK_1BIT(NVIC_IPR->IPR[Copyu8Per/4],7+(8*(Copyu8Per%4)),Copyu8Group);
		MSK_3BIT(NVIC_IPR->IPR[Copyu8Per/4],4+(8*(Copyu8Per%4)),Copyu8Sub);
	}
	
}
void NVIC_voidSetPriorityModeG0_S16(NVIC_Per Copyu8Per,u8 Copyu8Sub){
	if(Group_Sub_Type=G0_S16){
		MSK_4BIT(NVIC_IPR->IPR[Copyu8Per/4],4+(8*(Copyu8Per%4)),Copyu8Sub);
		
	}
	
}
