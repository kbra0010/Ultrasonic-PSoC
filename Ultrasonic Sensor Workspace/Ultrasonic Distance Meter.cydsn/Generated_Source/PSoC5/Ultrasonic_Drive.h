/*******************************************************************************
* File Name: Ultrasonic_Drive.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Ultrasonic_Drive_H)
#define CY_CLOCK_Ultrasonic_Drive_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void Ultrasonic_Drive_Start(void) ;
void Ultrasonic_Drive_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Ultrasonic_Drive_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void Ultrasonic_Drive_StandbyPower(uint8 state) ;
void Ultrasonic_Drive_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 Ultrasonic_Drive_GetDividerRegister(void) ;
void Ultrasonic_Drive_SetModeRegister(uint8 modeBitMask) ;
void Ultrasonic_Drive_ClearModeRegister(uint8 modeBitMask) ;
uint8 Ultrasonic_Drive_GetModeRegister(void) ;
void Ultrasonic_Drive_SetSourceRegister(uint8 clkSource) ;
uint8 Ultrasonic_Drive_GetSourceRegister(void) ;
#if defined(Ultrasonic_Drive__CFG3)
void Ultrasonic_Drive_SetPhaseRegister(uint8 clkPhase) ;
uint8 Ultrasonic_Drive_GetPhaseRegister(void) ;
#endif /* defined(Ultrasonic_Drive__CFG3) */

#define Ultrasonic_Drive_Enable()                       Ultrasonic_Drive_Start()
#define Ultrasonic_Drive_Disable()                      Ultrasonic_Drive_Stop()
#define Ultrasonic_Drive_SetDivider(clkDivider)         Ultrasonic_Drive_SetDividerRegister(clkDivider, 1u)
#define Ultrasonic_Drive_SetDividerValue(clkDivider)    Ultrasonic_Drive_SetDividerRegister((clkDivider) - 1u, 1u)
#define Ultrasonic_Drive_SetMode(clkMode)               Ultrasonic_Drive_SetModeRegister(clkMode)
#define Ultrasonic_Drive_SetSource(clkSource)           Ultrasonic_Drive_SetSourceRegister(clkSource)
#if defined(Ultrasonic_Drive__CFG3)
#define Ultrasonic_Drive_SetPhase(clkPhase)             Ultrasonic_Drive_SetPhaseRegister(clkPhase)
#define Ultrasonic_Drive_SetPhaseValue(clkPhase)        Ultrasonic_Drive_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(Ultrasonic_Drive__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Ultrasonic_Drive_CLKEN              (* (reg8 *) Ultrasonic_Drive__PM_ACT_CFG)
#define Ultrasonic_Drive_CLKEN_PTR          ((reg8 *) Ultrasonic_Drive__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Ultrasonic_Drive_CLKSTBY            (* (reg8 *) Ultrasonic_Drive__PM_STBY_CFG)
#define Ultrasonic_Drive_CLKSTBY_PTR        ((reg8 *) Ultrasonic_Drive__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Ultrasonic_Drive_DIV_LSB            (* (reg8 *) Ultrasonic_Drive__CFG0)
#define Ultrasonic_Drive_DIV_LSB_PTR        ((reg8 *) Ultrasonic_Drive__CFG0)
#define Ultrasonic_Drive_DIV_PTR            ((reg16 *) Ultrasonic_Drive__CFG0)

/* Clock MSB divider configuration register. */
#define Ultrasonic_Drive_DIV_MSB            (* (reg8 *) Ultrasonic_Drive__CFG1)
#define Ultrasonic_Drive_DIV_MSB_PTR        ((reg8 *) Ultrasonic_Drive__CFG1)

/* Mode and source configuration register */
#define Ultrasonic_Drive_MOD_SRC            (* (reg8 *) Ultrasonic_Drive__CFG2)
#define Ultrasonic_Drive_MOD_SRC_PTR        ((reg8 *) Ultrasonic_Drive__CFG2)

#if defined(Ultrasonic_Drive__CFG3)
/* Analog clock phase configuration register */
#define Ultrasonic_Drive_PHASE              (* (reg8 *) Ultrasonic_Drive__CFG3)
#define Ultrasonic_Drive_PHASE_PTR          ((reg8 *) Ultrasonic_Drive__CFG3)
#endif /* defined(Ultrasonic_Drive__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Ultrasonic_Drive_CLKEN_MASK         Ultrasonic_Drive__PM_ACT_MSK
#define Ultrasonic_Drive_CLKSTBY_MASK       Ultrasonic_Drive__PM_STBY_MSK

/* CFG2 field masks */
#define Ultrasonic_Drive_SRC_SEL_MSK        Ultrasonic_Drive__CFG2_SRC_SEL_MASK
#define Ultrasonic_Drive_MODE_MASK          (~(Ultrasonic_Drive_SRC_SEL_MSK))

#if defined(Ultrasonic_Drive__CFG3)
/* CFG3 phase mask */
#define Ultrasonic_Drive_PHASE_MASK         Ultrasonic_Drive__CFG3_PHASE_DLY_MASK
#endif /* defined(Ultrasonic_Drive__CFG3) */

#endif /* CY_CLOCK_Ultrasonic_Drive_H */


/* [] END OF FILE */
