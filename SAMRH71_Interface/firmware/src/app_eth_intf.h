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

#ifndef _APP_ETH_INTF_
#define _APP_ETH_INTF_

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include <stdint.h>
#include "app_msg_intf.h"

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------*/
/*         Defines                                                              */
/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
/*         Types                                                                */
/*------------------------------------------------------------------------------*/
  
// *****************************************************************************
/* Application status summary of all connected CAN Nodes

  Summary:
    Holds status of all connected CAN Nodes

  Description:
    This structure holds the status of all connected CAN Nodes.

  Remarks:
    None.
 */
typedef struct{
  /* The RH LEDs state Bitfield (bit set to 1 for LED on) */
  uint8_t rh_leds;
  /* The RH Push Buttons state Bitfield (bit set to 1 for pushed) */
  uint8_t rh_push_buttons;
  /* The ATmega64M1 Sensor CAN Node LEDs state Bitfield (bit set to 1 for LED on) */
  uint8_t sensor_leds;
  /* The ATmega64M1 Sensor CAN Node Push Buttons state Bitfield (bit set to 1 for pushed) */
  uint8_t sensor_push_buttons;
  /* The ATmega64M1 Motor Control CAN Node target speed */
  uint8_t at64_mc_target;
  /* The ATmega64M1 Motor Control CAN Node measured speed */
  uint8_t at64_mc_meas;
  /* The ATmega64M1 Motor Control CAN Node motor direction */
  uint8_t at64_mc_dir;
  /* The ATmega64M1 Motor Control CAN Node potentiometer value */
  uint8_t at64_mc_pot;
  /* The SAMV71 Motor Control CAN Node target speed */
  uint8_t v71_mc_target;
  /* The SAMV71 Motor Control CAN Node measured speed */
  uint8_t v71_mc_meas;
  /* The SAMV71 Motor Control CAN Node potentiometer value */
  uint8_t v71_mc_pot;
}APP_ETH_INTF_STATUS;

/*------------------------------------------------------------------------------*/
/*         Exported functions                                                   */
/*------------------------------------------------------------------------------*/

APP_ETH_INTF_STATUS* APP_ETH_INTF_StatusGetPtr(void);

void APP_ETH_INTF_RH_LedsUpdate(uint8_t leds);

void APP_ETH_INTF_RH_PbUpdate(uint8_t pushButtons);

void APP_ETH_INTF_RH_LedToogle(uint8_t ledId);

void APP_ETH_INTF_64S_LedsUpdate(uint8_t leds);

void APP_ETH_INTF_64S_PbUpdate(uint8_t pushButtons);

void APP_ETH_INTF_64S_LedToogle(uint8_t ledId);

void APP_ETH_INTF_64MC_StatusUpdate(uint8_t speedTarget, uint8_t direction, uint8_t speedMeasure, uint8_t potentiometer);

void APP_ETH_INTF_64MC_SpeedDecrease(void);

void APP_ETH_INTF_64MC_SpeedIncrease(void);

void APP_ETH_INTF_64MC_DirectionInvert(void);

void APP_ETH_INTF_V71MC_StatusUpdate(uint8_t speedTarget, uint8_t speedMeasure, uint8_t potentiometer);

void APP_ETH_INTF_V71MC_SpeedDecrease(void);

void APP_ETH_INTF_V71MC_SpeedIncrease(void);

#ifdef __cplusplus
}
#endif
#endif /* #ifndef _APP_ETH_INTF_ */
