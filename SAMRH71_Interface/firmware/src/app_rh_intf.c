/* ----------------------------------------------------------------------------- */
/*                Microchip Microcontroller Software Support                     */
/*                       SAM Software Package License                            */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/* Copyright (c) 2019 Microchip Technology Inc. and its subsidiaries.            */
/*                                                                               */
/* Subject to your compliance with these terms, you may use Microchip software   */
/* and any derivatives exclusively with Microchip products. It is your           */
/* responsibility to comply with third party license terms applicable to your    */
/* use of third party software (including open source software) that may         */
/* accompany Microchip software.                                                 */
/*                                                                               */
/* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER       */
/* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED  */
/* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR */
/* PURPOSE.                                                                      */
/*                                                                               */
/* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,     */
/* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND         */
/* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS     */
/* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE       */
/* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN   */
/* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,  */
/* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.                   */
/* ----------------------------------------------------------------------------- */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "definitions.h"
#include "app_rh_intf.h"
#include "app_msg_intf.h"

/*----------------------------------------------------------------------------
 *        Locals
 *----------------------------------------------------------------------------*/

/* Store the last button status to detect Push Button state changes */
volatile uint8_t lastButtonStatus = 0;

/* Store the current LEDs states */
volatile uint8_t ledsStatus = 0;

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/* void APP_RH_INTF_LedsSet(uint8_t leds)

  Summary:
    Set SAMRH71 LEDs states.

  Parameters:
    leds - LEDs states bitfield to set. Corresponding bit set to 1 for LED on, 0 for LED off.

  Return:
    None.
*/
void APP_RH_INTF_LedsSet(uint8_t leds)
{
    if ( (leds & APP_RH_INTF_ID_LED0) == APP_RH_INTF_ID_LED0)
        LED0_On();
    else
        LED0_Off();
    
    if ( (leds & APP_RH_INTF_ID_LED1) == APP_RH_INTF_ID_LED1)
        LED1_On();
    else
        LED1_Off();
    
    if ( (leds & APP_RH_INTF_ID_LED2) == APP_RH_INTF_ID_LED2)
        LED2_On();
    else
        LED2_Off();
    
    if ( (leds & APP_RH_INTF_ID_LED3) == APP_RH_INTF_ID_LED3)
        LED3_On();
    else
        LED3_Off();
    
    ledsStatus = leds;
}

/* ----------------------------------------------------------------------------- */
/* void APP_RH_INTF_LedsGet(void)

  Summary:
    Get SAMRH71 LEDs states.

  Parameters:
    None.

  Return:
    LEDs state bitfield. Corresponding bit set to 1 for LED on, 0 for LED off.
*/
uint8_t APP_RH_INTF_LedsGet(void)
{
    return ledsStatus;
}

/* ----------------------------------------------------------------------------- */
/* void APP_RH_INTF_Init(void)

  Summary:
    Initialize SAMRH71 interface for LEDs and Push Buttons states.

  Parameters:
    None.

  Return:
    None.
*/
void APP_RH_INTF_Init(void)
{
    lastButtonStatus = 0;
    ledsStatus = 0;
}


/* ----------------------------------------------------------------------------- */
/* void APP_RH_INTF_Loop(void)

  Summary:
    Pool for new Push Button event.

  Parameters:
    None.

  Return:
    None.
*/
void APP_RH_INTF_Loop(void)
{
    uint8_t buttonStatus = 0;
    if ( PB0_Get() == PB0_STATE_PRESSED )
        buttonStatus |= APP_RH_INTF_ID_BUTTON0;
    if ( PB1_Get() == PB0_STATE_PRESSED )
        buttonStatus |= APP_RH_INTF_ID_BUTTON1;
    if ( PB2_Get() == PB0_STATE_PRESSED )
        buttonStatus |= APP_RH_INTF_ID_BUTTON2;
    
    if (buttonStatus != lastButtonStatus)
    {
        APP_MSG_INTF_RH_PbUpdate(buttonStatus);
        lastButtonStatus = buttonStatus;
    }
}
