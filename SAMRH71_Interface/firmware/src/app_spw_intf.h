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

#ifndef _SPW_INTF_
#define _SPW_INTF_

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
  
/* Data size of sent packets in bytes */
#define APP_SPW_DATA_SIZE_BYTES             (8)

/* Number of Rx receiver list */
#define APP_SPW_RX_RECV_LIST                (20)

/* Number of Rx packet in receiver list */
#define APP_SPW_RX_PACKET_NUM               (1)

/* Size of Rx packet in receiver list in bytes*/
#define APP_SPW_RX_PACKET_SIZE_BYTES        (64*APP_SPW_RX_PACKET_NUM)

/* Router Packet receiver port for USB Brick Mk3*/
#define APP_SPW_ROUTER_USB_BRICK_PORT       (3)

/* Number of Tx packet in transmitter list */
#define APP_SPW_TX_NUM_PACKET               (1)

/*------------------------------------------------------------------------------*/
/*         Types                                                                */
/*------------------------------------------------------------------------------*/

/* Application circular buffer descriptor object for receive buffer ID list

   Summary:
    Application circular buffer descriptor object for receive buffer.

   Description:
    This data structure defines an circular buffer descriptor for receive buffers.

   Remarks:
    None.
*/
typedef struct
{
    uint16_t tail;
    uint16_t head;
    uint8_t full;
} APP_SPW_INTF_RX_LIST_DESC;

/*------------------------------------------------------------------------------*/
/* Application SpaceWire message ID type

  Summary:
    Application SpaceWire message ID enumeration

  Description:
    This enumeration defines the SpaceWire message ID exchanged between the board
    and the remote UI.  These states determine the content of the following bytes in
    the receive or sent message.
*/
typedef enum
{
    APP_SPW_MSG_ID_64MC_MOTOR_STATUS = 0,
    APP_SPW_MSG_ID_64MC_MOTOR_CMD,
    APP_SPW_MSG_ID_64MC_LED_GET,
    APP_SPW_MSG_ID_64MC_LED_STATUS,
    APP_SPW_MSG_ID_64MC_LED_SET,
    APP_SPW_MSG_ID_64MC_PB_STATUS,
    APP_SPW_MSG_ID_RH_LED_GET,
    APP_SPW_MSG_ID_RH_LED_STATUS,
    APP_SPW_MSG_ID_RH_LED_SET,
    APP_SPW_MSG_ID_RH_PB_STATUS,
    APP_SPW_MSG_ID_V71MC_MOTOR_STATUS,
    APP_SPW_MSG_ID_V71MC_MOTOR_CMD,
}APP_SPW_MSG_ID;

/*------------------------------------------------------------------------------*/
/* Application SpaceWire active link

  Summary:
    Application SpaceWire active link enumeration

  Description:
    This enumeration defines the SpaceWire active link states.
*/
typedef enum
{
    APP_SPW_INTF_ACTIVE_LINK_NONE = 0,
    APP_SPW_INTF_ACTIVE_LINK_1,
    APP_SPW_INTF_ACTIVE_LINK_2,
}APP_SPW_INTF_ACTIVE_LINK;

/*------------------------------------------------------------------------------*/
/*         Exported functions                                                   */
/*------------------------------------------------------------------------------*/

void APP_SPW_INTF_RH_LedsUpdate(uint8_t leds);

void APP_SPW_INTF_RH_PbUpdate(uint8_t push_buttons);

void APP_SPW_INTF_64S_LedsUpdate(uint8_t leds);

void APP_SPW_INTF_64S_PbUpdate(uint8_t push_buttons);

void APP_SPW_INTF_64MC_StatusUpdate(uint8_t speedTarget, uint8_t direction, uint8_t speedMeasure, uint8_t potentiometer);

void APP_SPW_INTF_V71MC_StatusUpdate(uint8_t speedTarget, uint8_t speedMeasure, uint8_t potentiometer);

void APP_SPW_INTF_Init(void);

void APP_SPW_INTF_Pool(void);

#ifdef __cplusplus
}
#endif
#endif /* #ifndef _SPW_INTF_ */
