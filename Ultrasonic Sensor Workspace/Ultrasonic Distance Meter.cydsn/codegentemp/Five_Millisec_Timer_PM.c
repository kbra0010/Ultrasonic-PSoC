/*******************************************************************************
* File Name: Five_Millisec_Timer_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Five_Millisec_Timer.h"

static Five_Millisec_Timer_backupStruct Five_Millisec_Timer_backup;


/*******************************************************************************
* Function Name: Five_Millisec_Timer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Five_Millisec_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Five_Millisec_Timer_SaveConfig(void) 
{
    #if (!Five_Millisec_Timer_UsingFixedFunction)
        Five_Millisec_Timer_backup.TimerUdb = Five_Millisec_Timer_ReadCounter();
        Five_Millisec_Timer_backup.InterruptMaskValue = Five_Millisec_Timer_STATUS_MASK;
        #if (Five_Millisec_Timer_UsingHWCaptureCounter)
            Five_Millisec_Timer_backup.TimerCaptureCounter = Five_Millisec_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Five_Millisec_Timer_UDB_CONTROL_REG_REMOVED)
            Five_Millisec_Timer_backup.TimerControlRegister = Five_Millisec_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Five_Millisec_Timer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Five_Millisec_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Five_Millisec_Timer_RestoreConfig(void) 
{   
    #if (!Five_Millisec_Timer_UsingFixedFunction)

        Five_Millisec_Timer_WriteCounter(Five_Millisec_Timer_backup.TimerUdb);
        Five_Millisec_Timer_STATUS_MASK =Five_Millisec_Timer_backup.InterruptMaskValue;
        #if (Five_Millisec_Timer_UsingHWCaptureCounter)
            Five_Millisec_Timer_SetCaptureCount(Five_Millisec_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Five_Millisec_Timer_UDB_CONTROL_REG_REMOVED)
            Five_Millisec_Timer_WriteControlRegister(Five_Millisec_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Five_Millisec_Timer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Five_Millisec_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Five_Millisec_Timer_Sleep(void) 
{
    #if(!Five_Millisec_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Five_Millisec_Timer_CTRL_ENABLE == (Five_Millisec_Timer_CONTROL & Five_Millisec_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Five_Millisec_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Five_Millisec_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Five_Millisec_Timer_Stop();
    Five_Millisec_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: Five_Millisec_Timer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Five_Millisec_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Five_Millisec_Timer_Wakeup(void) 
{
    Five_Millisec_Timer_RestoreConfig();
    #if(!Five_Millisec_Timer_UDB_CONTROL_REG_REMOVED)
        if(Five_Millisec_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Five_Millisec_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
