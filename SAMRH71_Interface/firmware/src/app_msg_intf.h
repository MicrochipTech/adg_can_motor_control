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

#ifndef _MSG_INTF_
#define _MSG_INTF_

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------*/
/*         Defines                                                              */
/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
/*         Types                                                                */
/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
/*         Exported functions                                                   */
/*------------------------------------------------------------------------------*/

void APP_MSG_INTF_RH_LedsGet(void);

void APP_MSG_INTF_RH_LedsSet(uint8_t led_state);

void APP_MSG_INTF_RH_PbUpdate(uint8_t push_button);

void APP_MSG_INTF_64S_LedsUpdate(uint8_t leds);

void APP_MSG_INTF_64S_PbUpdate(uint8_t push_buttons);

void APP_MSG_INTF_64S_LedsGet(void);

void APP_MSG_INTF_64S_LedsSet(uint8_t led_state);

void APP_MSG_INTF_64MC_StatusUpdate(uint8_t speedTarget, uint8_t direction, uint8_t speedMeasure, uint8_t potentiometer);

void APP_MSG_INTF_64MC_TargetSet(uint8_t speed, uint8_t direction);

void APP_MSG_INTF_V71MC_StatusUpdate(uint8_t speedTarget, uint8_t speedMeasure, uint8_t potentiometer);

void APP_MSG_INTF_V71MC_TargetSet(uint8_t speed);

#ifdef __cplusplus
}
#endif
#endif /* #ifndef _MSG_INTF_ */
