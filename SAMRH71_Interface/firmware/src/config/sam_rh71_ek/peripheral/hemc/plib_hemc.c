/*****************************************************************************
  Company:
    Microchip Technology Inc.

  File Name:
    plib_hemc.c

  Summary:
    HEMC PLIB Source file

  Description:
    None

*******************************************************************************/

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
#include <string.h>
#include "device.h"
#include "plib_hemc.h"


// *****************************************************************************
// *****************************************************************************
// Section: Global Data
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: HEMC Implementation
// *****************************************************************************
// *****************************************************************************


void HSMC_Initialize( void )
{


    /* Chip Select CS0 Timings */
    /* Setup HSMC SETUP register */
    HSMC_REGS->HSMC_SETUP0= HSMC_SETUP0_NWE_SETUP(1) | HSMC_SETUP0_NCS_WR_SETUP(2) | HSMC_SETUP0_NRD_SETUP(1) | HSMC_SETUP0_NCS_RD_SETUP(2);

    /* Setup HSMC CYCLE register */
    HSMC_REGS->HSMC_CYCLE0= HSMC_CYCLE0_NWE_CYCLE(12) | HSMC_CYCLE0_NRD_CYCLE(12);

    /* Setup HSMC_PULSE register */
    HSMC_REGS->HSMC_PULSE0= HSMC_PULSE0_NWE_PULSE(10) | HSMC_PULSE0_NCS_WR_PULSE(8) | HSMC_PULSE0_NRD_PULSE(10) | HSMC_PULSE0_NCS_RD_PULSE(8);

    /* Setup HSMC MODE register */
    HSMC_REGS->HSMC_MODE0= HSMC_MODE0_EXNW_MODE(0) | HSMC_MODE0_DBW(0)   ;






}
void HEMC_Initialize( void )
{
    /* Read NCS0 Pin configuration for HECC */
    uint8_t eccEnableDefault = ( (HEMC_REGS->HEMC_HECC_CR0 & HEMC_HECC_CR0_ENABLE_Msk) >> HEMC_HECC_CR0_ENABLE_Pos);
    uint8_t eccAlgoDefault = ( (HEMC_REGS->HEMC_HECC_CR0 & HEMC_HECC_CR0_ECC12_ENABLE_Msk) >> HEMC_HECC_CR0_ECC12_ENABLE_Pos);

    /* Enable NCS0 configuration modification through registers */
    HEMC_REGS->HEMC_CR_NCS0 |= HEMC_CR_NCS0_WRITE_ECC_CONF(1);

    HEMC_REGS->HEMC_CR_NCS0 = HEMC_CR_NCS0_TYPE(0) |
                              HEMC_CR_NCS0_ADDBASE(0x0) |
                              HEMC_CR_NCS0_BANKSIZE(0x6) |
                              HEMC_CR_NCS0_WRITE_ECC_CONF(1) |
                              HEMC_CR_NCS0_ECC_ENABLE(eccEnableDefault) |
                              HEMC_CR_NCS0_ECC12_ENABLE(eccAlgoDefault);

    HSMC_Initialize();




} /* HEMC_Initialize */

// *****************************************************************************
/* Function:
    void HEMC_HeccGetStatus(void)

   Summary:
    Get the HECC status of the HEMC peripheral.

   Precondition:
    None.

   Parameters:
    None.

   Returns:
    Current status of the HEMC peripheral.
*/
HEMC_HECC_STATUS HEMC_HeccGetStatus(void)
{
    return (HEMC_HECC_STATUS)(HEMC_REGS->HEMC_HECC_SR);
}

// *****************************************************************************
/* Function:
    uint32_t* HEMC_HeccGetFailAddress(void)

   Summary:
    Get the last fail address were ECC error occurs in a HEMC memory.

   Precondition:
    None.

   Parameters:
    None.

   Returns:
    Pointer of fail address were fixable or unfixable error occured in a HEMC memory.
*/
uint32_t* HEMC_HeccGetFailAddress(void)
{
    return (uint32_t*)(HEMC_REGS->HEMC_HECC_FAILAR);
}

// *****************************************************************************
/* Function:
    void HEMC_HeccResetCounters(void)

   Summary:
    Reset Fix and NoFix error counters of the HEMC peripheral.

   Precondition:
    None.

   Parameters:
    None.

   Returns:
    None
*/
void HEMC_HeccResetCounters(void)
{
    HEMC_REGS->HEMC_HECC_CR0 |= (HEMC_HECC_CR0_RST_FIX_CPT_Msk | HEMC_HECC_CR0_RST_NOFIX_CPT_Msk);
    HEMC_REGS->HEMC_HECC_CR1 |= (HEMC_HECC_CR1_RST_FIX_CPT_Msk | HEMC_HECC_CR1_RST_NOFIX_CPT_Msk);
    HEMC_REGS->HEMC_HECC_CR2 |= (HEMC_HECC_CR2_RST_FIX_CPT_Msk | HEMC_HECC_CR2_RST_NOFIX_CPT_Msk);
}


/*******************************************************************************
 End of File
*/
