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

#ifndef _RH_INTF_
#define _RH_INTF_

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

/* Define the switch button PB0 flag */
#define APP_RH_INTF_ID_BUTTON0                     (0x01)
/* Define the switch button PB1 flag */
#define APP_RH_INTF_ID_BUTTON1                     (0x02)
/* Define the switch button PB2 flag */
#define APP_RH_INTF_ID_BUTTON2                     (0x04)

/* Define the LED0 flag */
#define APP_RH_INTF_ID_LED0                        (0x01)
/* Define the LED1 flag */
#define APP_RH_INTF_ID_LED1                        (0x02)
/* Define the LED2 flag */
#define APP_RH_INTF_ID_LED2                        (0x04)
/* Define the LED3 flag */
#define APP_RH_INTF_ID_LED3                        (0x08)

/*------------------------------------------------------------------------------*/
/*         Types                                                                */
/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
/*         Exported functions                                                   */
/*------------------------------------------------------------------------------*/


void APP_RH_INTF_LedsSet(uint8_t leds);

uint8_t APP_RH_INTF_LedsGet(void);

void APP_RH_INTF_Init(void);

void APP_RH_INTF_Loop(void);

#ifdef __cplusplus
}
#endif
#endif /* #ifndef _RH_INTF_ */
