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
#include "app_mcan_intf.h"
#include "app_spw_intf.h"
#include "app_rh_intf.h"
#include "app_eth_intf.h"

/*----------------------------------------------------------------------------
 *        Macro
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/* void APP_MSG_INTF_RH_LedsGet(void)

  Summary:
    Get the LEDs state on SAMRH71.

  Description:
    Get the LEDs state on SAMRH71 and update the status on connected UI.

  Parameters:
    None.

  Return:
    None.
*/
void APP_MSG_INTF_RH_LedsGet(void)
{
    APP_SPW_INTF_RH_LedsUpdate(APP_RH_INTF_LedsGet());
    APP_ETH_INTF_RH_LedsUpdate(APP_RH_INTF_LedsGet());
}

/* ----------------------------------------------------------------------------- */
/* void APP_MSG_INTF_RH_LedsSet(uint8_t led_state)

  Summary:
    Set the LEDs state for SAMRH71.

  Description:
    Set the LEDs state for SAMRH71 and update it on connected UI.

  Parameters:
    led_state - Bitfield of LEDs state to set.

  Return:
    None.
*/
void APP_MSG_INTF_RH_LedsSet(uint8_t led_state)
{
    APP_RH_INTF_LedsSet(led_state);
    
    /* Refresh LEDs states on all interfaces */
    APP_SPW_INTF_RH_LedsUpdate(led_state);
    APP_ETH_INTF_RH_LedsUpdate(led_state);
}

/* ----------------------------------------------------------------------------- */
/* void APP_MSG_INTF_RH_PbUpdate(uint8_t push_button)

  Summary:
    Update the SAMRH71 Push buttons status on connected UI.

  Parameters:
    push_button - Bitfield of Push buttons status.

  Return:
    None.
*/
void APP_MSG_INTF_RH_PbUpdate(uint8_t push_button)
{
    APP_SPW_INTF_RH_PbUpdate(push_button);
    APP_ETH_INTF_RH_PbUpdate(push_button);
}

/* ----------------------------------------------------------------------------- */
/* void APP_MSG_INTF_64S_LedsUpdate(uint8_t leds)

  Summary:
    Update the ATmega64M1 Sensor CAN Node LEDs status on connected UI.

  Parameters:
    leds - Bitfield of LEDs status.

  Return:
    None.
*/
void APP_MSG_INTF_64S_LedsUpdate(uint8_t leds)
{
    APP_ETH_INTF_64S_LedsUpdate(leds);
    APP_SPW_INTF_64S_LedsUpdate(leds);
}

/* ----------------------------------------------------------------------------- */
/* void APP_MSG_INTF_64S_PbUpdate(uint8_t push_buttons)

  Summary:
    Update the ATmega64M1 Sensor CAN Node Push buttons status on connected UI.

  Parameters:
    push_buttons - Bitfield of Push buttons status.

  Return:
    None.
*/
void APP_MSG_INTF_64S_PbUpdate(uint8_t push_buttons)
{
    APP_ETH_INTF_64S_PbUpdate(push_buttons);
    APP_SPW_INTF_64S_PbUpdate(push_buttons);
}

/* ----------------------------------------------------------------------------- */
/* void APP_MSG_INTF_64S_LedsGet(void)

  Summary:
    Send LEDs get status message to the ATmega64M1 Sensor CAN Node.

  Parameters:
    None.

  Return:
    None.
*/
void APP_MSG_INTF_64S_LedsGet(void)
{
    APP_MCAN_INTF_64S_LedsGet();
}

/* ----------------------------------------------------------------------------- */
/* void APP_MSG_INTF_64S_LedsSet(uint8_t led_state)

  Summary:
    Send the LEDs set message to the ATmega64M1 Sensor CAN Node.

  Parameters:
    led_state - Bitfield of LEDs state to set.

  Return:
    None.
*/
void APP_MSG_INTF_64S_LedsSet(uint8_t led_state)
{
    APP_MCAN_INTF_64S_LedsSet(led_state);
}

/* ----------------------------------------------------------------------------- */
/* void APP_MSG_INTF_64MC_StatusUpdate(uint8_t speedTarget, uint8_t direction, uint8_t speedMeasure, uint8_t potentiometer)

  Summary:
    Update the ATmega64M1 Motor Control CAN Node motor status on connected UI.

  Parameters:
    speedTarget - The speed target command.
    direction - The motor direction.
    speedMeasure - The measured speed.
    potentiometer - The potentiometer value.

  Return:
    None.
*/
void APP_MSG_INTF_64MC_StatusUpdate(uint8_t speedTarget, uint8_t direction, uint8_t speedMeasure, uint8_t potentiometer)
{
    APP_ETH_INTF_64MC_StatusUpdate(speedTarget, direction, speedMeasure, potentiometer);
    APP_SPW_INTF_64MC_StatusUpdate(speedTarget, direction, speedMeasure, potentiometer);
}

/* ----------------------------------------------------------------------------- */
/* void APP_MSG_INTF_64MC_TargetSet(uint8_t speed, uint8_t direction)

  Summary:
    Send the speed and direction set message to the ATmega64M1 Motor Control CAN Node.

  Parameters:
    speed - motor speed target.
    direction - motor direction.

  Return:
    None.
*/
void APP_MSG_INTF_64MC_TargetSet(uint8_t speed, uint8_t direction)
{
    APP_MCAN_INTF_64MC_TargetSet(speed, direction);
}

/* ----------------------------------------------------------------------------- */
/* void APP_MSG_INTF_V71MC_StatusUpdate(uint8_t speedTarget, uint8_t speedMeasure, uint8_t potentiometer)

  Summary:
    Update the SAMV71 Motor Control CAN Node motor status on connected UI.

  Parameters:
    speedTarget - The speed target command.
    speedMeasure - The measured speed.
    potentiometer - The potentiometer value.

  Return:
    None.
*/
void APP_MSG_INTF_V71MC_StatusUpdate(uint8_t speedTarget, uint8_t speedMeasure, uint8_t potentiometer)
{
    APP_ETH_INTF_V71MC_StatusUpdate(speedTarget, speedMeasure, potentiometer);
    APP_SPW_INTF_V71MC_StatusUpdate(speedTarget, speedMeasure, potentiometer);
}

/* ----------------------------------------------------------------------------- */
/* void APP_MSG_INTF_V71MC_TargetSet(uint8_t speed)

  Summary:
    Send the speed set message to the SAMV71 Motor Control CAN Node.

  Parameters:
    speed - motor speed target.

  Return:
    None.
*/
void APP_MSG_INTF_V71MC_TargetSet(uint8_t speed)
{
    APP_MCAN_INTF_V71MC_TargetSet(speed);
}
