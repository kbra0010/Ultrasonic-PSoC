/*******************************************************************************
* File Name: RX_Tie_High.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_RX_Tie_High_H) /* Pins RX_Tie_High_H */
#define CY_PINS_RX_Tie_High_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RX_Tie_High_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RX_Tie_High__PORT == 15 && ((RX_Tie_High__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RX_Tie_High_Write(uint8 value);
void    RX_Tie_High_SetDriveMode(uint8 mode);
uint8   RX_Tie_High_ReadDataReg(void);
uint8   RX_Tie_High_Read(void);
void    RX_Tie_High_SetInterruptMode(uint16 position, uint16 mode);
uint8   RX_Tie_High_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RX_Tie_High_SetDriveMode() function.
     *  @{
     */
        #define RX_Tie_High_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RX_Tie_High_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RX_Tie_High_DM_RES_UP          PIN_DM_RES_UP
        #define RX_Tie_High_DM_RES_DWN         PIN_DM_RES_DWN
        #define RX_Tie_High_DM_OD_LO           PIN_DM_OD_LO
        #define RX_Tie_High_DM_OD_HI           PIN_DM_OD_HI
        #define RX_Tie_High_DM_STRONG          PIN_DM_STRONG
        #define RX_Tie_High_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RX_Tie_High_MASK               RX_Tie_High__MASK
#define RX_Tie_High_SHIFT              RX_Tie_High__SHIFT
#define RX_Tie_High_WIDTH              1u

/* Interrupt constants */
#if defined(RX_Tie_High__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RX_Tie_High_SetInterruptMode() function.
     *  @{
     */
        #define RX_Tie_High_INTR_NONE      (uint16)(0x0000u)
        #define RX_Tie_High_INTR_RISING    (uint16)(0x0001u)
        #define RX_Tie_High_INTR_FALLING   (uint16)(0x0002u)
        #define RX_Tie_High_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RX_Tie_High_INTR_MASK      (0x01u) 
#endif /* (RX_Tie_High__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RX_Tie_High_PS                     (* (reg8 *) RX_Tie_High__PS)
/* Data Register */
#define RX_Tie_High_DR                     (* (reg8 *) RX_Tie_High__DR)
/* Port Number */
#define RX_Tie_High_PRT_NUM                (* (reg8 *) RX_Tie_High__PRT) 
/* Connect to Analog Globals */                                                  
#define RX_Tie_High_AG                     (* (reg8 *) RX_Tie_High__AG)                       
/* Analog MUX bux enable */
#define RX_Tie_High_AMUX                   (* (reg8 *) RX_Tie_High__AMUX) 
/* Bidirectional Enable */                                                        
#define RX_Tie_High_BIE                    (* (reg8 *) RX_Tie_High__BIE)
/* Bit-mask for Aliased Register Access */
#define RX_Tie_High_BIT_MASK               (* (reg8 *) RX_Tie_High__BIT_MASK)
/* Bypass Enable */
#define RX_Tie_High_BYP                    (* (reg8 *) RX_Tie_High__BYP)
/* Port wide control signals */                                                   
#define RX_Tie_High_CTL                    (* (reg8 *) RX_Tie_High__CTL)
/* Drive Modes */
#define RX_Tie_High_DM0                    (* (reg8 *) RX_Tie_High__DM0) 
#define RX_Tie_High_DM1                    (* (reg8 *) RX_Tie_High__DM1)
#define RX_Tie_High_DM2                    (* (reg8 *) RX_Tie_High__DM2) 
/* Input Buffer Disable Override */
#define RX_Tie_High_INP_DIS                (* (reg8 *) RX_Tie_High__INP_DIS)
/* LCD Common or Segment Drive */
#define RX_Tie_High_LCD_COM_SEG            (* (reg8 *) RX_Tie_High__LCD_COM_SEG)
/* Enable Segment LCD */
#define RX_Tie_High_LCD_EN                 (* (reg8 *) RX_Tie_High__LCD_EN)
/* Slew Rate Control */
#define RX_Tie_High_SLW                    (* (reg8 *) RX_Tie_High__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RX_Tie_High_PRTDSI__CAPS_SEL       (* (reg8 *) RX_Tie_High__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RX_Tie_High_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RX_Tie_High__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RX_Tie_High_PRTDSI__OE_SEL0        (* (reg8 *) RX_Tie_High__PRTDSI__OE_SEL0) 
#define RX_Tie_High_PRTDSI__OE_SEL1        (* (reg8 *) RX_Tie_High__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RX_Tie_High_PRTDSI__OUT_SEL0       (* (reg8 *) RX_Tie_High__PRTDSI__OUT_SEL0) 
#define RX_Tie_High_PRTDSI__OUT_SEL1       (* (reg8 *) RX_Tie_High__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RX_Tie_High_PRTDSI__SYNC_OUT       (* (reg8 *) RX_Tie_High__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RX_Tie_High__SIO_CFG)
    #define RX_Tie_High_SIO_HYST_EN        (* (reg8 *) RX_Tie_High__SIO_HYST_EN)
    #define RX_Tie_High_SIO_REG_HIFREQ     (* (reg8 *) RX_Tie_High__SIO_REG_HIFREQ)
    #define RX_Tie_High_SIO_CFG            (* (reg8 *) RX_Tie_High__SIO_CFG)
    #define RX_Tie_High_SIO_DIFF           (* (reg8 *) RX_Tie_High__SIO_DIFF)
#endif /* (RX_Tie_High__SIO_CFG) */

/* Interrupt Registers */
#if defined(RX_Tie_High__INTSTAT)
    #define RX_Tie_High_INTSTAT            (* (reg8 *) RX_Tie_High__INTSTAT)
    #define RX_Tie_High_SNAP               (* (reg8 *) RX_Tie_High__SNAP)
    
	#define RX_Tie_High_0_INTTYPE_REG 		(* (reg8 *) RX_Tie_High__0__INTTYPE)
#endif /* (RX_Tie_High__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RX_Tie_High_H */


/* [] END OF FILE */
