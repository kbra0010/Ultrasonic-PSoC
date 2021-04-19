/*******************************************************************************
* File Name: Vssa_Buffer_PM.c
* Version 1.90
*
* Description:
*  This file provides the power management source code to the API for the 
*  OpAmp (Analog Buffer) component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Vssa_Buffer.h"

static Vssa_Buffer_BACKUP_STRUCT  Vssa_Buffer_backup;


/*******************************************************************************  
* Function Name: Vssa_Buffer_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration registers.
* 
* Parameters:
*  void
* 
* Return:
*  void
*
*******************************************************************************/
void Vssa_Buffer_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: Vssa_Buffer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration registers.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Vssa_Buffer_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: Vssa_Buffer_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Vssa_Buffer_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void Vssa_Buffer_Sleep(void) 
{
    /* Save OpAmp enable state */
    if((Vssa_Buffer_PM_ACT_CFG_REG & Vssa_Buffer_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        Vssa_Buffer_backup.enableState = 1u;
         /* Stops the component */
         Vssa_Buffer_Stop();
    }
    else
    {
        /* Component is disabled */
        Vssa_Buffer_backup.enableState = 0u;
    }
    /* Saves the configuration */
    Vssa_Buffer_SaveConfig();
}


/*******************************************************************************  
* Function Name: Vssa_Buffer_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Vssa_Buffer_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void Vssa_Buffer_Wakeup(void) 
{
    /* Restore the user configuration */
    Vssa_Buffer_RestoreConfig();

    /* Enables the component operation */
    if(Vssa_Buffer_backup.enableState == 1u)
    {
        Vssa_Buffer_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
