#include "NVIC.h"


/*********************************************************************
*	Service Name: NVIC_EnableIRQ
*	Sync/Async: Synchronous
*	Reentrancy: reentrant
*	Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
*	Parameters (inout): None
*	Parameters (out): None
*	Return value: None
*	Description: Function to enable Interrupt request for specific IRQ
 **********************************************************************/
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num){
    uint8 Int_RegBit;                                               //Gets the interrupt bit number in higher registers
    if (IRQ_Num <= 31){
        NVIC_EN0_REG |= (1  << IRQ_Num);
    }
    else if (IRQ_Num > 31 && IRQ_Num <= 63){
        Int_RegBit = IRQ_Num - 32;
        NVIC_EN1_REG |= (1 << Int_RegBit);
    }
    else if (IRQ_Num > 63 && IRQ_Num <= 95){
        Int_RegBit = IRQ_Num - (32 * 2);
        NVIC_EN2_REG |= (1 << Int_RegBit);
    }
    else if (IRQ_Num > 95 && IRQ_Num <= 127)
    {
        Int_RegBit = IRQ_Num - (32 * 3);
        NVIC_EN3_REG |= (1 << Int_RegBit);
    }
    else if (IRQ_Num > 127 && IRQ_Num <= 138){
        Int_RegBit = IRQ_Num - (32 * 4);
        NVIC_EN4_REG |= (1 << Int_RegBit);
    }
}

/*********************************************************************
*	Service Name: NVIC_DisableIRQ
*	Sync/Async: Synchronous
*	Reentrancy: reentrant
*	Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
*	Parameters (inout): None
*	Parameters (out): None
*	Return value: None
*	Description: Function to Disable Interrupt request for specific IRQ
 **********************************************************************/
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num){
    uint8 Int_RegBit;                                                           //Gets the interrupt bit number in higher registers
    if (IRQ_Num <= 31){
        NVIC_DIS0_REG |= (1<<IRQ_Num);
    }
    else if (IRQ_Num > 31 && IRQ_Num <= 63){
        Int_RegBit = IRQ_Num - 32;
        NVIC_DIS1_REG |= (1 << Int_RegBit);
    }
    else if (IRQ_Num > 63 && IRQ_Num <= 95){
        Int_RegBit = IRQ_Num - (32 * 2);
        NVIC_DIS2_REG |= (1 << Int_RegBit);
    }
    else if (IRQ_Num > 95 && IRQ_Num <= 127)
    {
        Int_RegBit = IRQ_Num - (32 * 3);
        NVIC_DIS3_REG |= (1 << Int_RegBit);
    }
    else if (IRQ_Num > 127 && IRQ_Num <= 138){
        Int_RegBit = IRQ_Num - (32 * 4);
        NVIC_DIS4_REG |= (1 << Int_RegBit);
    }
}

/*********************************************************************
*	Service Name: NVIC_SetPriorityIRQ
*	Sync/Async: Synchronous
*	Reentrancy: reentrant
*	Parameters (in): IRQ_Num - Number of interrupt. IRQ_Priority - interrupt wanted prioirty
*	Parameters (inout): None
*	Parameters (out): None
*	Return value: None
*	Description: Function used to set a priority (0 - 7) to a specific interrupt
 **********************************************************************/
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority){
    uint8 volatile *RegPtr = ((volatile uint8 *)0xE000E400);                  //pointer to PRI0 Address
    RegPtr += IRQ_Num;                                                        //Incerementing the addrsss to the wanted register
    *RegPtr &= ~(7 << 5);                                                     //Clearing the previous priority value
    *RegPtr |= (IRQ_Priority << 5);                                           //Assign the new priority to the specified interrupt
}

/*********************************************************************
*	Service Name: NVIC_EnableException
*	Sync/Async: Synchronous
*	Reentrancy: reentrant
*	Parameters (in): Exception_Num - Number of wanted 
*	Parameters (inout): None
*	Parameters (out): None
*	Return value: None
*	Description: Function used to enable execptions interrupt
 **********************************************************************/
void NVIC_EnableException(NVIC_ExceptionType Exception_Num){
    switch (Exception_Num)
    {
    case 3:
        NVIC_SYSTEM_SYSHNDCTRL |= (1 << 16);
        break;
    case 4:
        NVIC_SYSTEM_SYSHNDCTRL |= (1 << 17);
        break;
    case 5:
        NVIC_SYSTEM_SYSHNDCTRL |= (1 << 18);
        break;
    case 9:
        SYSTICK_CTRL_REG |= (1 << 1);
        break;
    }
}

/*********************************************************************
*	Service Name: NVIC_DisableException
*	Sync/Async: Synchronous
*	Reentrancy: reentrant
*	Parameters (in): Exception_Num - Number of wanted 
*	Parameters (inout): None
*	Parameters (out): None
*	Return value: None
*	Description: Function used to Disable execptions interrupt
 **********************************************************************/
void NVIC_DisableException(NVIC_ExceptionType Exception_Num){
    switch (Exception_Num)
    {
    case 3:
        NVIC_SYSTEM_SYSHNDCTRL &= ~(1 << 16);
        break;
    case 4:
        NVIC_SYSTEM_SYSHNDCTRL &= ~(1 << 17);
        break;
    case 5:
        NVIC_SYSTEM_SYSHNDCTRL &= ~(1 << 18);
        break;
    case 9:
        SYSTICK_CTRL_REG &= ~(1 << 1);
        break;
    }
}

/*********************************************************************
*	Service Name: NVIC_SetPriorityException
*	Sync/Async: Synchronous
*	Reentrancy: reentrant
*	Parameters (in): Exception_Num - Number of wanted. Exception_Priority - Wanted priority value (0 : 7)
*	Parameters (inout): None
*	Parameters (out): None
*	Return value: None
*	Description: Function used to set priority to a specific exception
 **********************************************************************/
void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority){
    switch (Exception_Num)
    {
    case 3:
        NVIC_SYSTEM_PRI1_REG &= ~(7 << 5);                                      //Clearing Previous Priority values
        NVIC_SYSTEM_PRI1_REG |= (Exception_Priority << 5);                      //Assign the new priority
        break;
    case 4:
        NVIC_SYSTEM_PRI1_REG &= ~(13 << 5);
        NVIC_SYSTEM_PRI1_REG |= (Exception_Priority << 13);
        break;
    case 5:
        NVIC_SYSTEM_PRI1_REG &= ~(21 << 5);
        NVIC_SYSTEM_PRI1_REG |= (Exception_Priority << 21);
        break;
    case 6:
        NVIC_SYSTEM_PRI2_REG &= ~(7 << 29);
        NVIC_SYSTEM_PRI2_REG |= (Exception_Priority << 29);
        break;
    case 7:
        NVIC_SYSTEM_PRI3_REG &= ~(7 << 5);
        NVIC_SYSTEM_PRI3_REG |= (Exception_Priority << 5);
        break;
    case 8:
        NVIC_SYSTEM_PRI3_REG &= ~(7 << 21);
        NVIC_SYSTEM_PRI3_REG |= (Exception_Priority << 21);
        break;
    case 9:
        NVIC_SYSTEM_PRI3_REG &= ~(7 << 29);
        NVIC_SYSTEM_PRI3_REG |= (Exception_Priority << 29);
        break;
    }
}
