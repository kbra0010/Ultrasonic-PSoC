/*******************************************************************************
* File Name: Ultrasonic_Pulse_Counter_PM.c
* Version 1.0
*
* Description:
*  This file provides Low power mode APIs for Count7 component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Ultrasonic_Pulse_Counter.h"


Ultrasonic_Pulse_Counter_BACKUP_STRUCT Ultrasonic_Pulse_Counter_backup;


/*******************************************************************************
* Function Name: Ultrasonic_Pulse_Counter_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component configuration and non-retention registers.
*  This function is called by the Count7_Sleep() function.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  Ultrasonic_Pulse_Counter_backup - used to save component configuration and non-
*  retention registers before enter sleep mode.
*
*******************************************************************************/
void Ultrasonic_Pulse_Counter_SaveConfig(void) 
{
    Ultrasonic_Pulse_Counter_backup.count = Ultrasonic_Pulse_Counter_COUNT_REG;
}


/*******************************************************************************
* Function Name: Ultrasonic_Pulse_Counter_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for low power mode
*  operation. The Count7_Sleep() API saves the current component state using
*  Count7_SaveConfig() and disables the counter.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Ultrasonic_Pulse_Counter_Sleep(void) 
{
    if(0u != (Ultrasonic_Pulse_Counter_AUX_CONTROL_REG & Ultrasonic_Pulse_Counter_COUNTER_START))
    {
        Ultrasonic_Pulse_Counter_backup.enableState = 1u;
        Ultrasonic_Pulse_Counter_Stop();
    }
    else
    {
        Ultrasonic_Pulse_Counter_backup.enableState = 0u;
    }

    Ultrasonic_Pulse_Counter_SaveConfig();
}


/*******************************************************************************
* Function Name: Ultrasonic_Pulse_Counter_RestoreConfig
********************************************************************************
*
* Summary:
*  This function restores the component configuration and non-retention
*  registers. This function is called by the Count7_Wakeup() function.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  Ultrasonic_Pulse_Counter_backup - used to save component configuration and
*  non-retention registers before exit sleep mode.
*
*******************************************************************************/
void Ultrasonic_Pulse_Counter_RestoreConfig(void) 
{
    Ultrasonic_Pulse_Counter_COUNT_REG = Ultrasonic_Pulse_Counter_backup.count;
}


/*******************************************************************************
* Function Name: Ultrasonic_Pulse_Counter_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when
*  Count7_Sleep() was called. The Count7_Wakeup() function calls the
*  Count7_RestoreConfig() function to restore the configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Ultrasonic_Pulse_Counter_Wakeup(void) 
{
    Ultrasonic_Pulse_Counter_RestoreConfig();

    /* Restore enable state */
    if (Ultrasonic_Pulse_Counter_backup.enableState != 0u)
    {
        Ultrasonic_Pulse_Counter_Enable();
    }
}


/* [] END OF FILE */
