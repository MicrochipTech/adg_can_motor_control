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
#include "app_eth_intf.h"

/*----------------------------------------------------------------------------
 *        Macro
 *----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
 *         Variables
 *---------------------------------------------------------------------------*/

/* Current local status about connected CAN nodes for Ethernet WebServer requests */
static APP_ETH_INTF_STATUS appEthCurrentStatus;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/* ----------------------------------------------------------------------------- */
/* APP_ETH_INTF_STATUS* APP_ETH_INTF_StatusGetPtr(void)

  Summary:
    Get pointer of the instance containing status of connected CAN nodes.

  Description:
    Get pointer of the instance containing status of connected CAN nodes.

  Parameters:
    None.

  Return:
    Pointer of the instance containing status of connected CAN nodes.
*/
APP_ETH_INTF_STATUS* APP_ETH_INTF_StatusGetPtr(void)
{
    return &appEthCurrentStatus;
}

/* ----------------------------------------------------------------------------- */
/* APP_ETH_INTF_RH_LedsUpdate(uint8_t leds)

  Summary:
    Update the LEDs status for SAMRH71.

  Description:
    Store the LEDs status for SAMRH71 that will be
    transmit during webpages refresh request.

  Parameters:
    leds - LEDs state bitfield.

  Return:
    None.
*/
void APP_ETH_INTF_RH_LedsUpdate(uint8_t leds)
{
    appEthCurrentStatus.rh_leds = leds;
}

/* ----------------------------------------------------------------------------- */
/* void APP_ETH_INTF_RH_PbUpdate(uint8_t pushButtons)

  Summary:
    Update the Push Buttons status for SAMRH71.

  Description:
    Store the Push Buttons status for SAMRH71 that will be
    transmit during webpages refresh request.

  Parameters:
    pushButtons - Push Buttons state bitfield.

  Return:
    None.
*/
void APP_ETH_INTF_RH_PbUpdate(uint8_t pushButtons)
{
    appEthCurrentStatus.rh_push_buttons = pushButtons;
}

/* ----------------------------------------------------------------------------- */
/* void APP_ETH_INTF_RH_LedToogle(uint8_t ledId)

  Summary:
    Toggle LED with given identifier on SAMRH71 board.

  Description:
    Toggle LED with given identifier on SAMRH71 board and update the
    current status through message interface.

  Parameters:
    ledId - The LED id to toggle.

  Return:
    None.
*/
void APP_ETH_INTF_RH_LedToogle(uint8_t ledId)
{
    APP_MSG_INTF_RH_LedsSet(appEthCurrentStatus.rh_leds ^ ( 1 << ledId));
}

/* ----------------------------------------------------------------------------- */
/* APP_ETH_INTF_64S_LedsUpdate(uint8_t leds)

  Summary:
    Update LEDs status for ATmega64M1 Sensor CAN Node.

  Description:
    Store the received LEDs status from ATmega64M1 Sensor CAN Node that will be
    transmit during webpages refresh request.

  Parameters:
    leds - LEDs state bitfield.

  Return:
    None.
*/
void APP_ETH_INTF_64S_LedsUpdate(uint8_t leds)
{
    appEthCurrentStatus.sensor_leds = leds;
}

/* ----------------------------------------------------------------------------- */
/* APP_ETH_INTF_64S_PbUpdate(uint8_t pushButtons)

  Summary:
    Update Push Buttons status for ATmega64M1 Sensor CAN Node.

  Description:
    Store the received Push Buttons status from ATmega64M1 Sensor CAN Node that will be
    transmit during webpages refresh request.

  Parameters:
    pushButtons - Push Buttons state bitfield.

  Return:
    None.
*/
void APP_ETH_INTF_64S_PbUpdate(uint8_t pushButtons)
{
    appEthCurrentStatus.sensor_push_buttons = pushButtons;
}

/* ----------------------------------------------------------------------------- */
/* void APP_ETH_INTF_64S_LedToogle(uint8_t ledId)

  Summary:
    Toggle LED with given identifier on ATmega64M1 Sensor CAN Node.

  Description:
    Toggle LED with given identifier on ATmega64M1 Sensor CAN Node and update the
    current status through message interface.

  Parameters:
    ledId - The LED id to toggle.

  Return:
    None.
*/
void APP_ETH_INTF_64S_LedToogle(uint8_t ledId)
{
    APP_MSG_INTF_64S_LedsSet(appEthCurrentStatus.sensor_leds ^ ( 1 << ledId));
}

/* ----------------------------------------------------------------------------- */
/* void APP_ETH_INTF_64MC_StatusUpdate(uint8_t speedTarget, uint8_t direction, uint8_t speedMeasure, uint8_t potentiometer)

  Summary:
    Update status for ATmega64M1 Motor Control CAN Node.

  Description:
    Store the received status from ATmega64M1 Motor Control CAN Node that will be
    transmit during webpages refresh request.

  Parameters:
    speedTarget - The speed target command.
    direction - The motor direction.
    speedMeasure - The measured speed.
    potentiometer - The potentiometer value.

  Return:
    None.
*/
void APP_ETH_INTF_64MC_StatusUpdate(uint8_t speedTarget, uint8_t direction, uint8_t speedMeasure, uint8_t potentiometer)
{
  appEthCurrentStatus.at64_mc_target = speedTarget;
  appEthCurrentStatus.at64_mc_meas = speedMeasure;
  appEthCurrentStatus.at64_mc_dir = direction;
  appEthCurrentStatus.at64_mc_pot = potentiometer;
}

/* ----------------------------------------------------------------------------- */
/* void APP_ETH_INTF_64MC_SpeedDecrease(void)

  Summary:
    Decrease target speed on ATmega64M1 Motor Control CAN Node.

  Description:
    Decrease target speed on ATmega64M1 Motor Control CAN Node.

  Parameters:
    None.

  Return:
    None.
*/
void APP_ETH_INTF_64MC_SpeedDecrease(void)
{
    if (appEthCurrentStatus.at64_mc_target == 0xFF )
    {
        APP_MSG_INTF_64MC_TargetSet(0xF0, appEthCurrentStatus.at64_mc_dir);
    }
    else if (appEthCurrentStatus.at64_mc_target > 0x10 )
    {
        APP_MSG_INTF_64MC_TargetSet(appEthCurrentStatus.at64_mc_target - 0x10, appEthCurrentStatus.at64_mc_dir);
    }
}

/* ----------------------------------------------------------------------------- */
/* void APP_ETH_INTF_64MC_SpeedIncrease(void)

  Summary:
    Increase target speed on ATmega64M1 Motor Control CAN Node.

  Description:
    Increase target speed on ATmega64M1 Motor Control CAN Node.

  Parameters:
    None.

  Return:
    None.
*/
void APP_ETH_INTF_64MC_SpeedIncrease(void)
{
    if (appEthCurrentStatus.at64_mc_target < 0xF0)
    {
        APP_MSG_INTF_64MC_TargetSet(appEthCurrentStatus.at64_mc_target + 0x10, appEthCurrentStatus.at64_mc_dir);
    }
    else
    {
        APP_MSG_INTF_64MC_TargetSet(0xFF, appEthCurrentStatus.at64_mc_dir);
    }
}

/* ----------------------------------------------------------------------------- */
/* void APP_ETH_INTF_64MC_DirectionInvert(void)

  Summary:
    Invert motor direction on ATmega64M1 Motor Control CAN Node.

  Description:
    Invert motor direction on ATmega64M1 Motor Control CAN Node.

  Parameters:
    None.

  Return:
    None.
*/
void APP_ETH_INTF_64MC_DirectionInvert(void)
{
    if (appEthCurrentStatus.at64_mc_dir == 0)
    {
        APP_MSG_INTF_64MC_TargetSet(appEthCurrentStatus.at64_mc_target, 1);
    }
    else
    {
        APP_MSG_INTF_64MC_TargetSet(appEthCurrentStatus.at64_mc_target, 0);
    }
}

/* ----------------------------------------------------------------------------- */
/* void APP_ETH_INTF_V71MC_StatusUpdate(uint8_t speedTarget, uint8_t speedMeasure, uint8_t potentiometer)

  Summary:
    Update status for SAMV71 Motor Control CAN Node.

  Description:
    Store the received status from SAMV71 Motor Control CAN Node that will be
    transmit during webpages refresh request.

  Parameters:
    speedTarget - The speed target command.
    speedMeasure - The measured speed.
    potentiometer - The potentiometer value.

  Return:
    None.
*/
void APP_ETH_INTF_V71MC_StatusUpdate(uint8_t speedTarget, uint8_t speedMeasure, uint8_t potentiometer)
{
    appEthCurrentStatus.v71_mc_target = speedTarget;
    appEthCurrentStatus.v71_mc_meas = speedMeasure;
    appEthCurrentStatus.v71_mc_pot = potentiometer;
}

/* ----------------------------------------------------------------------------- */
/* void APP_ETH_INTF_V71MC_SpeedDecrease(void)

  Summary:
    Decrease target speed on SAMV71 Motor Control CAN Node.

  Description:
    Decrease target speed on SAMV71 Motor Control CAN Node.

  Parameters:
    None.

  Return:
    None.
*/
void APP_ETH_INTF_V71MC_SpeedDecrease(void)
{
    if (appEthCurrentStatus.v71_mc_target == 0xFF )
    {
        APP_MSG_INTF_V71MC_TargetSet(0xF0);
    }
    else if (appEthCurrentStatus.v71_mc_target > 0x3D )
    {
        APP_MSG_INTF_V71MC_TargetSet(appEthCurrentStatus.v71_mc_target - 0x10);
    }
    else
    {
        APP_MSG_INTF_V71MC_TargetSet(0);
    }
}

/* ----------------------------------------------------------------------------- */
/* void APP_ETH_INTF_V71MC_SpeedIncrease(void)

  Summary:
    Increase target speed on SAMV71 Motor Control CAN Node.

  Description:
    Increase target speed on SAMV71 Motor Control CAN Node.

  Parameters:
    None.

  Return:
    None.
*/
void APP_ETH_INTF_V71MC_SpeedIncrease(void)
{
    if (appEthCurrentStatus.v71_mc_target < 0x2D)
    {
        APP_MSG_INTF_V71MC_TargetSet(0x2D);
    }
    else if (appEthCurrentStatus.v71_mc_target < 0xF0)
    {
        APP_MSG_INTF_V71MC_TargetSet(appEthCurrentStatus.v71_mc_target + 0x10);
    }
    else
    {
        APP_MSG_INTF_V71MC_TargetSet(0xFF);
    }
}
