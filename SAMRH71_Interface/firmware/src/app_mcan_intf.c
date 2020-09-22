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
#include "app_msg_intf.h"
#include "app_mcan_intf.h"

/*----------------------------------------------------------------------------
 * Locals
 *----------------------------------------------------------------------------*/

/* MCAN1 RAM message buffer */
uint8_t MCAN1MessageRAM[MCAN1_MESSAGE_RAM_CONFIG_SIZE] __attribute__((aligned (32)))__attribute__((space(data), section (".ram_nocache")));

/*----------------------------------------------------------------------------
 * Local functions
 *----------------------------------------------------------------------------*/

/* void APP_MCAN_INTF_MsgSend(uint32_t id, uint8_t* msgData, uint8_t messageLength)

  Summary:
    Send given message to the CAN bus. 

  Description:
    Send given message to the CAN bus in normal mode using the Tx FIFO Data Frame
    message attribute.

  Parameters:
    id - CAN message identifier. 
    msgData - Pointer to source data buffer.
    msgLength - Length of data buffer in number of bytes.

  Return:
    None.
*/
static void APP_MCAN_INTF_MsgSend(uint32_t id, uint8_t* msgData, uint8_t msgLength)
{
    if (MCAN1_MessageTransmit(id, msgLength, msgData, MCAN_MODE_NORMAL, MCAN_MSG_ATTR_TX_FIFO_DATA_FRAME) == false)
    {
        SYS_CONSOLE_PRINT("MCAN1 TX Failed\r\n");
    }
}

/* ----------------------------------------------------------------------------- */
/* static void APP_MCAN_INTF_MsgDecode(uint32_t msgId, uint8_t* msgData, uint8_t msgLength)

  Summary:
    Decode received message on CAN bus.

  Description:
    Decode raw message and call the corresponding message interface function with
    decoded parameters.

  Parameters:
    id - CAN message identifier.
    msgData - Pointer to received data buffer.
    msgLength - Length of data buffer in number of bytes.

  Return:
    None.
*/
static void APP_MCAN_INTF_MsgDecode(uint32_t msgId, uint8_t* msgData, uint8_t msgLength)
{
    (void)(msgLength);

    // Identify message type
    switch (msgId)
    {
      case APP_MCAN_INTF_64MC_STATUS_ID:
      {
        APP_MSG_INTF_64MC_StatusUpdate(
            msgData[0],
            msgData[1],
            msgData[2],
            msgData[3]
            );
      }
      break;

      case APP_MCAN_INTF_64S_STATUS_ID:
      {
          if ( msgData[0] == APP_MCAN_INTF_64S_MSG_LED_STATUS)
          {
              APP_MSG_INTF_64S_LedsUpdate(msgData[1]);
          }
          else if ( msgData[0] == APP_MCAN_INTF_64S_MSG_PB_STATUS)
          {
              APP_MSG_INTF_64S_PbUpdate(msgData[1]);
          }
      }
      break;

      case APP_MCAN_INTF_V71MC_STATUS_ID:
      {
        APP_MSG_INTF_V71MC_StatusUpdate(
            msgData[0],
            msgData[1],
            msgData[2]
            );
      }
      break;

      default:
        break;
    }
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/* void APP_MCAN_INTF_64MC_TargetSet(uint8_t speed, uint8_t direction)

  Summary:
    Set motor speed target and direction on ATmega64M1 Motor Control CAN Node.

  Description:
    Create and send CAN message to set motor speed target and direction 
    on ATmega64M1 Motor Control CAN Node.

  Parameters:
    speed - motor speed target.
    direction - motor direction.

  Return:
    None.
*/
void APP_MCAN_INTF_64MC_TargetSet(uint8_t speed, uint8_t direction)
{
    uint8_t motor_set_data[8] = {speed , direction, 0, 0, 0, 0, 0, 0};
    APP_MCAN_INTF_MsgSend(APP_MCAN_INTF_64MC_CMD_ID, &(motor_set_data[0]), 8);
}

/* ----------------------------------------------------------------------------- */
/* void APP_MCAN_INTF_64S_LedsGet(void)

  Summary:
    Send get LEDs command to ATmega64M1 Sensor CAN Node.

  Description:
    Create and send CAN message to get the LEDs status on ATmega64M1 Sensor CAN Node.

  Parameters:
    None.

  Return:
    None.
*/
void APP_MCAN_INTF_64S_LedsGet(void)
{
    uint8_t get_led_status_data[2] = {APP_MCAN_INTF_64S_MSG_LED_GET , 0xA5};
    APP_MCAN_INTF_MsgSend(APP_MCAN_INTF_64S_CMD_ID, &(get_led_status_data[0]), 2);
}

/* ----------------------------------------------------------------------------- */
/* void APP_MCAN_INTF_64S_LedsSet(void)

  Summary:
    Set LEDs command to ATmega64M1 Sensor CAN Node.

  Description:
    Create and send CAN message to set the LEDs state on ATmega64M1 Sensor CAN Node.

  Parameters:
    None.

  Return:
    None.
*/
void APP_MCAN_INTF_64S_LedsSet(uint8_t led_state)
{
    uint8_t set_led_status_data[2] = {APP_MCAN_INTF_64S_MSG_LED_SET, led_state};
    APP_MCAN_INTF_MsgSend(APP_MCAN_INTF_64S_CMD_ID, &(set_led_status_data[0]), 2);
}

/* ----------------------------------------------------------------------------- */
/* void APP_MCAN_INTF_V71MC_TargetSet(uint8_t speed)

  Summary:
    Set motor speed target on SAMV71 Motor Control CAN Node.

  Description:
    Create and send CAN message to set motor speed target on SAMV71 Motor
    Control CAN Node.

  Parameters:
    speed - motor speed target.

  Return:
    None.
*/
void APP_MCAN_INTF_V71MC_TargetSet(uint8_t speed)
{
    uint8_t motor_set_data[8] = {speed , 0, 0, 0, 0, 0, 0, 0};
    APP_MCAN_INTF_MsgSend(APP_MCAN_INTF_V71MC_CMD_ID, &(motor_set_data[0]), 8);
}

/* ----------------------------------------------------------------------------- */
/* void APP_MCAN_INTF_Init(void)

  Summary:
    Initialize CAN interface with CAN Nodes.

  Description:
    Initialize MCAN RAM message and get ATmega64M1 LEDs status.

  Parameters:
    None.

  Return:
    None.
*/
void APP_MCAN_INTF_Init(void)
{
    /* Set Message RAM Configuration */
    MCAN1_MessageRAMConfigSet(MCAN1MessageRAM);

    APP_MCAN_INTF_64S_LedsGet();
}

/* ----------------------------------------------------------------------------- */
/* void APP_MCAN_INTF_Pool(void)

  Summary:
    Pool for new received messages on CAN interface and check errors.

  Parameters:
    None.

  Return:
    None.
*/
void APP_MCAN_INTF_Pool(void)
{
    /* Poll for new CAN messages in RX FIFO */

    uint8_t rx_message[8];
    uint32_t rx_messageID = 0;
    uint8_t rx_messageLength = 0;
    MCAN_MSG_RX_FRAME_ATTRIBUTE msgFrameAttr = MCAN_MSG_RX_DATA_FRAME;

    /* Check CAN Status */
    MCAN_ERROR status = MCAN1_ErrorGet();

    if (((status & MCAN_PSR_LEC_Msk) == MCAN_ERROR_NONE) || ((status & MCAN_PSR_LEC_Msk) == MCAN_PSR_LEC_NO_CHANGE))
    {
        memset(rx_message, 0x00, sizeof(rx_message));

        /* Receive FIFO 0 New Message */
        if (MCAN1_MessageReceive(&rx_messageID, &rx_messageLength, rx_message, 0, MCAN_MSG_ATTR_RX_FIFO0, &msgFrameAttr) == true)  
        {
            status = MCAN1_ErrorGet();
            if (((status & MCAN_PSR_LEC_Msk) == MCAN_ERROR_NONE) || ((status & MCAN_PSR_LEC_Msk) == MCAN_PSR_LEC_NO_CHANGE))
            {
                APP_MCAN_INTF_MsgDecode(rx_messageID, rx_message, rx_messageLength);
            }
            else
            {
                SYS_CONSOLE_PRINT("MCAN: ERR RX:0x%08X\r\n", status);
            }
        }
    }
    else
    {
        SYS_CONSOLE_PRINT("MCAN: ERR LAST RX:0x%08X\r\n", status);
    }
}

