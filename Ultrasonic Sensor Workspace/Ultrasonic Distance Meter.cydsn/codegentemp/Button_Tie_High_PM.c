/*******************************************************************************
* File Name: Button_Tie_High_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Button_Tie_High.h"

/* Check for removal by optimization */
#if !defined(Button_Tie_High_Sync_ctrl_reg__REMOVED)

static Button_Tie_High_BACKUP_STRUCT  Button_Tie_High_backup = {0u};

    
/*******************************************************************************
* Function Name: Button_Tie_High_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Button_Tie_High_SaveConfig(void) 
{
    Button_Tie_High_backup.controlState = Button_Tie_High_Control;
}


/*******************************************************************************
* Function Name: Button_Tie_High_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void Button_Tie_High_RestoreConfig(void) 
{
     Button_Tie_High_Control = Button_Tie_High_backup.controlState;
}


/*******************************************************************************
* Function Name: Button_Tie_High_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Button_Tie_High_Sleep(void) 
{
    Button_Tie_High_SaveConfig();
}


/*******************************************************************************
* Function Name: Button_Tie_High_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Button_Tie_High_Wakeup(void)  
{
    Button_Tie_High_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
