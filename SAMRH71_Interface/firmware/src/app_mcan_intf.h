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

#ifndef _MCAN_INTF_
#define _MCAN_INTF_

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

/* ATmega64M1 Motor Control CAN Node message ID for status */
#define APP_MCAN_INTF_64MC_STATUS_ID          (0x120)
/* ATmega64M1 Motor Control CAN Node message ID for command */
#define APP_MCAN_INTF_64MC_CMD_ID             (0x100)

/* ATmega64M1 Sensor CAN Node message ID for status */
#define APP_MCAN_INTF_64S_STATUS_ID           (0x0A0)
/* ATmega64M1 Sensor CAN Node message ID for command */
#define APP_MCAN_INTF_64S_CMD_ID              (0x090)

/* SAMV71 Motor Control CAN Node message ID for status */
#define APP_MCAN_INTF_V71MC_STATUS_ID         (0x220)
/* SAMV71 Motor Control CAN Node message ID for command */
#define APP_MCAN_INTF_V71MC_CMD_ID            (0x200)

/* ATmega64M1 Sensor CAN Node message type LED status id */
#define APP_MCAN_INTF_64S_MSG_LED_STATUS      (0)
/* ATmega64M1 Sensor CAN Node message type LED set id */
#define APP_MCAN_INTF_64S_MSG_LED_SET         (1)
/* ATmega64M1 Sensor CAN Node message type LED get id */
#define APP_MCAN_INTF_64S_MSG_LED_GET         (2)
/* ATmega64M1 Sensor CAN Node message type Push Buttons status id */
#define APP_MCAN_INTF_64S_MSG_PB_STATUS       (3)

/*------------------------------------------------------------------------------*/
/*         Types                                                                */
/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
/*         Exported functions                                                   */
/*------------------------------------------------------------------------------*/

void APP_MCAN_INTF_64MC_TargetSet(uint8_t speed, uint8_t direction);

void APP_MCAN_INTF_64S_LedsGet(void);

void APP_MCAN_INTF_64S_LedsSet(uint8_t led_state);

void APP_MCAN_INTF_V71MC_TargetSet(uint8_t speed);

void APP_MCAN_INTF_Init(void);

void APP_MCAN_INTF_Pool(void);

#ifdef __cplusplus
}
#endif
#endif /* #ifndef _MCAN_INTF_ */
