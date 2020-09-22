/*******************************************************************************
 Interface definition of HEFC PLIB.

 Company:
    Microchip Technology Inc.

 File Name:
    plib_hefc.h

 Summary:
    Interface definition of HEFC Plib.

 Description:
    This file defines the interface for the HEFC Plib.
    It allows user to Program, Erase and lock the on-chip FLASH memory.
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef HEFC_H    // Guards against multiple inclusion
#define HEFC_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus // Provide C++ Compatibility
    extern "C" {
#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Interface
// *****************************************************************************
// *****************************************************************************
#define HEFC_SECTORSIZE              4096
#define HEFC_PAGESIZE                256
#define HEFC_LOCKSIZE                256
#define HEFC_START_ADDRESS           0x60040000
#define HEFC_MEDIA_SIZE              64
#define HEFC_ERASE_BUFFER_SIZE       4096

typedef enum
{
    HEFC_ERROR_NONE = 0x1,
    /*In-valid command*/
    HEFC_CMD_ERROR = 0x2,
    /*Flash region is locked*/
    HEFC_LOCK_ERROR = 0x4,
    /*Flash Encountered an write error*/
    HEFC_WRITE_ERROR = 0x10,
} HEFC_ERROR;


void HEFC_Initialize(void);

bool HEFC_Read( uint32_t *data, uint32_t length, uint32_t address );

bool HEFC_SectorErase( uint32_t address );

bool HEFC_PageWrite( uint32_t *data, uint32_t address );

HEFC_ERROR HEFC_ErrorGet( void );

bool HEFC_IsBusy(void);

void HEFC_RegionLock(uint32_t address);

void HEFC_RegionUnlock(uint32_t address);


// DOM-IGNORE-BEGIN
#ifdef __cplusplus // Provide C++ Compatibility
}
#endif
// DOM-IGNORE-END

#endif