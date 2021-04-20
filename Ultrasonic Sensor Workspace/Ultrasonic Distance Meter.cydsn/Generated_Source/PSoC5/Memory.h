/*******************************************************************************
* File Name: Memory.h
* Version 3.0
*
*  Description:
*   Provides the function definitions for the EEPROM APIs.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_EEPROM_Memory_H)
#define CY_EEPROM_Memory_H

#include "cydevice_trm.h"
#include "CyFlash.h"

#if !defined(CY_PSOC5LP)
    #error Component EEPROM_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void Memory_Enable(void) ;
void Memory_Start(void) ;
void Memory_Stop (void) ;
cystatus Memory_WriteByte(uint8 dataByte, uint16 address) \
                                            ;
uint8 Memory_ReadByte(uint16 address) ;
uint8 Memory_UpdateTemperature(void) ;
cystatus Memory_EraseSector(uint8 sectorNumber) ;
cystatus Memory_Write(const uint8 * rowData, uint8 rowNumber) ;
cystatus Memory_StartWrite(const uint8 * rowData, uint8 rowNumber) \
                                                ;
cystatus Memory_StartErase(uint8 sectorNumber) ;
cystatus Memory_Query(void) ;
cystatus Memory_ByteWritePos(uint8 dataByte, uint8 rowNumber, uint8 byteNumber) \
                                                ;


/****************************************
*           API Constants
****************************************/

#define Memory_EEPROM_SIZE            CYDEV_EE_SIZE
#define Memory_SPC_BYTE_WRITE_SIZE    (0x01u)

#define Memory_SECTORS_NUMBER         (CYDEV_EE_SIZE / CYDEV_EEPROM_SECTOR_SIZE)

#define Memory_AHB_REQ_SHIFT          (0x00u)
#define Memory_AHB_REQ                ((uint8)(0x01u << Memory_AHB_REQ_SHIFT))
#define Memory_AHB_ACK_SHIFT          (0x01u)
#define Memory_AHB_ACK_MASK           ((uint8)(0x01u << Memory_AHB_ACK_SHIFT))


/***************************************
* Registers
***************************************/
#define Memory_SPC_EE_SCR_REG                 (*(reg8 *) CYREG_SPC_EE_SCR)
#define Memory_SPC_EE_SCR_PTR                 ( (reg8 *) CYREG_SPC_EE_SCR)



/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/
#define Memory_ByteWrite                  Memory_ByteWritePos
#define Memory_QueryWrite                 Memory_Query

#endif /* CY_EEPROM_Memory_H */

/* [] END OF FILE */
