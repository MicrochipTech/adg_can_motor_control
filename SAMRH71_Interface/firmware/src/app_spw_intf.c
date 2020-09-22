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
#include "string.h"
#include "definitions.h"
#include "app_msg_intf.h"
#include "app_spw_intf.h"

/*----------------------------------------------------------------------------
 *        Variables
 *----------------------------------------------------------------------------*/

/* Tx buffer of data */
uint8_t __attribute__((aligned (32)))__attribute__((space(data), section (".ram_nocache"))) appSpwTxDataBuffer[APP_SPW_TX_NUM_PACKET][APP_SPW_DATA_SIZE_BYTES] = {0};

/* Tx send list */
SPW_PKTTX_SEND_LIST_ENTRY __attribute__((aligned (32)))__attribute__((space(data), section (".ram_nocache"))) appSpwTxPckSendList[APP_SPW_TX_NUM_PACKET] = {0};

/* Rx buffer of data */
uint8_t __attribute__((aligned (32)))__attribute__((space(data), section (".ram_nocache"))) appSpwRxDataBuffer[APP_SPW_RX_RECV_LIST][APP_SPW_RX_PACKET_SIZE_BYTES] = {0};

/* Rx packet information list */
SPW_PKTRX_INFO __attribute__((aligned (32)))__attribute__((space(data), section (".ram_nocache"))) appSpwRxPckInfo[APP_SPW_RX_RECV_LIST][APP_SPW_RX_PACKET_NUM] = {0};

/* Rx packet status */
SPW_PKTRX_PREV_STATUS appSpwRxRecvPckStatus[APP_SPW_RX_RECV_LIST] = {0};

/* Store the current state of receive buffer list */
volatile APP_SPW_INTF_RX_LIST_DESC appSpwRxBufferListDesc = {0};

/* Store the current SpaceWire Link used for transmit */
volatile APP_SPW_INTF_ACTIVE_LINK appSpwActiveLink = APP_SPW_INTF_ACTIVE_LINK_NONE;

/*----------------------------------------------------------------------------
 *        Local Functions
 *----------------------------------------------------------------------------*/

/* static void APP_SPW_INTF_DecodeMsg(uint8_t* msg, uint32_t msg_size)

  Summary:
    Decode received message on SpaceWire bus.

  Description:
    Decode raw message and call the corresponding message interface function with
    decoded parameters.

  Parameters:
    msg - Pointer to received data buffer.
    msg_size - Length of data buffer in number of bytes.

  Return:
    None.
*/
static void APP_SPW_INTF_DecodeMsg(uint8_t* msg, uint32_t msg_size)
{
    (void)(msg_size);

    // Identify message type in first received byte
    uint8_t msg_id = msg[0];
    switch (msg_id)
    {
      case APP_SPW_MSG_ID_64MC_MOTOR_CMD:
      {
          APP_MSG_INTF_64MC_TargetSet(msg[1], msg[2]);
      }
      break;

      case APP_SPW_MSG_ID_64MC_LED_GET:
      {
          APP_MSG_INTF_64S_LedsGet();
      }
      break;

      case APP_SPW_MSG_ID_64MC_LED_SET:
      {
          APP_MSG_INTF_64S_LedsSet(msg[1]);
      }
      break;

      case APP_SPW_MSG_ID_RH_LED_GET:
      {
          APP_MSG_INTF_RH_LedsGet();
      }
      break;

      case APP_SPW_MSG_ID_RH_LED_SET:
      {
          APP_MSG_INTF_RH_LedsSet(msg[1]);
      }
      break;

      case APP_SPW_MSG_ID_V71MC_MOTOR_CMD:
      {
          APP_MSG_INTF_V71MC_TargetSet(msg[1]);
      }
      break;

      default:
        break;
    }
}

/* ----------------------------------------------------------------------------- */
/* static void APP_SPW_INTF_ProcessBufferId(uint32_t buffer_id)

  Summary:
    Process packets received in SpaceWire PKTRX buffer.

  Description:
    Decode raw message in packets received in SpaceWire PKTRX buffer and 
    call the corresponding message interface function with decoded parameters.

  Parameters:
    buffer_id - The PKTRX buffer index in buffer list to process.

  Return:
    None.
*/
static void APP_SPW_INTF_ProcessBufferId(uint32_t buffer_id)
{
    uint16_t packet, num_packet = 0;
    SPW_PKTRX_PREV_STATUS status = appSpwRxRecvPckStatus[buffer_id];

    // If status lock : previous status is updated
    if (status & SPW_PKTRX_PREV_STATUS_LOCKED)
    {
        // Get number of received messages
        num_packet = SPW_PKTRX_PREV_STATUS_GET_COUNT(status);
        if (num_packet > 0)
        {
            for (packet = 0; packet < num_packet; packet++)
            {
                // Check received packet is not split
                if (appSpwRxPckInfo[buffer_id][packet].Split)
                {
                    SYS_CONSOLE_PRINT(" -I- Packet %u split\n", (unsigned int) packet);
                }

                uint8_t* packetDataAddr = (uint8_t*)(appSpwRxPckInfo[buffer_id][packet].DAddr);
                uint32_t packetDataSize = appSpwRxPckInfo[buffer_id][packet].DSize;

                APP_SPW_INTF_DecodeMsg( (uint8_t*) (packetDataAddr), packetDataSize);
            }
        }
    }
    else
    {
        SYS_CONSOLE_PRINT(" -E- No lock in status : 0x%x\n", (unsigned int)status);
    }
}

/* ----------------------------------------------------------------------------- */
/* void APP_SPW_INTF_LinkInterruptErrors(uint32_t errors)

  Summary:
    Function called by the application to print the description of the link
    interrupt errors.
    This function also modify the current active Link for transmission if this
    one is disconnected.

  Description:
    Print the description of the errors that are set in the given bit field.

  Parameters:
    errors - Bit field of the SPW interrupt status that contains errors.

  Remarks:
    None.
*/
static void APP_SPW_INTF_LinkInterruptErrors(uint32_t errors)
{
    if ((errors & SPW_LINK_INT_MASK_DISERR) == SPW_LINK_INT_MASK_DISERR)
    {
        SYS_CONSOLE_PRINT("  Link interface disconnection error detected.\r\n");
        appSpwActiveLink = APP_SPW_INTF_ACTIVE_LINK_NONE;
    }
    if ((errors & SPW_LINK_INT_MASK_PARERR) == SPW_LINK_INT_MASK_PARERR)
        SYS_CONSOLE_PRINT("  Link interface parity error detected.\r\n");
    if ((errors & SPW_LINK_INT_MASK_ESCERR) == SPW_LINK_INT_MASK_ESCERR)
        SYS_CONSOLE_PRINT("  Link interface ESC error detected.\r\n");
    if ((errors & SPW_LINK_INT_MASK_CRERR) == SPW_LINK_INT_MASK_CRERR)
        SYS_CONSOLE_PRINT("  Link interface credit error detected.\r\n");
    if ((errors & SPW_LINK_INT_MASK_LINKABORT) == SPW_LINK_INT_MASK_LINKABORT)
    {
        SYS_CONSOLE_PRINT("  Link state has made a transition from Run to Error Reset\r\n");
        appSpwActiveLink = APP_SPW_INTF_ACTIVE_LINK_NONE;
    }
    if ((errors & SPW_LINK_INT_MASK_EEPTRANS) == SPW_LINK_INT_MASK_EEPTRANS)
        SYS_CONSOLE_PRINT("  EEP transmitted.\r\n");
    if ((errors & SPW_LINK_INT_MASK_EEPREC) == SPW_LINK_INT_MASK_EEPREC)
        SYS_CONSOLE_PRINT("  EEP received.\r\n");
    if ((errors & SPW_LINK_INT_MASK_DISCARD) == SPW_LINK_INT_MASK_DISCARD)
        SYS_CONSOLE_PRINT("  Transmit packet discarded.\r\n");
}

/* ----------------------------------------------------------------------------- */
/* static void APP_SPW_INTF_PrepareAndStartSendList(uint8_t* buffer, uint8_t size)

   Summary:
    Transmit the given buffer to SpaceWire active Link.

   Description:
    If there is an active Link, prepare and start a new send list to be transmitted
    immediately with one packet containing the given buffer. 

  Parameters:
    buffer - Pointer to data buffer.
    size - Length of data buffer in number of bytes.

   Remarks:
    None.
*/
static void APP_SPW_INTF_PrepareAndStartSendList(uint8_t* buffer, uint8_t size)
{
    if (appSpwActiveLink != APP_SPW_INTF_ACTIVE_LINK_NONE)
    {
        /* Clear data buffer */
        memset(&(appSpwTxDataBuffer[0]), 0, sizeof(appSpwTxDataBuffer));

        /* Copy message */
        memcpy(&(appSpwTxDataBuffer[0]), buffer, size);

        // Prepare next send list without router bytes.
        SPW_PKTTX_SetNextSendList(
            NULL,
            &(appSpwTxPckSendList[0]),
            APP_SPW_TX_NUM_PACKET,
            false,
            SPW_PKTTX_NXTSEND_START_NOW,
            0);
    }
}

/* ----------------------------------------------------------------------------- */
/* static void APP_SPW_INTF_SetNextReceiveBuffer(uint16_t bufferId, SPW_PKTRX_NXTBUF_START startMode)

   Summary:
    Set next receive buffer ID with staring condition.

   Description:
    This function will set the next receive buffer ID for packet reception using
    the given start condition (NOW or LATER).

   Parameters:
    bufferId - the ID of the buffer to set as next receive buffer.
    startMode - the start mode for the receive buffer (NOW or LATER).

   Remarks:
    None.
*/
static void APP_SPW_INTF_SetNextReceiveBuffer(uint16_t bufferId, SPW_PKTRX_NXTBUF_START startMode)
{
    SPW_PKTRX_SetNextBuffer(
        &(appSpwRxDataBuffer[bufferId][0]),
        APP_SPW_RX_PACKET_SIZE_BYTES,
        &(appSpwRxPckInfo[bufferId][0]),
        APP_SPW_RX_PACKET_NUM,
        false,
        startMode,
        0);
}

/* ----------------------------------------------------------------------------- */
/* static void APP_SPW_INTF_InitRx(void)

   Summary:
    Initialize SPW packet reception circular buffer and start the receptions
    with the first buffers.

   Description:
    This function initialize SPW packet reception using the circular buffer
    descriptor to set the two first buffer as current and next buffers.

   Remarks:
    None.
*/
static void APP_SPW_INTF_InitRx(void)
{
    uint16_t next_buffer = 0;

    appSpwRxBufferListDesc.tail = 0;
    appSpwRxBufferListDesc.head = 0;
    appSpwRxBufferListDesc.full = 0;

    /* Disable discard mode to stall incoming packets */
    SPW_PKTRX_SetDiscard(false);

    /* Set list element 0 in Next buffer with start condition now */
    next_buffer = appSpwRxBufferListDesc.head;
    APP_SPW_INTF_SetNextReceiveBuffer(next_buffer, SPW_PKTRX_NXTBUF_START_NOW);

    /* Wait list become active */
    while ((SPW_PKTRX_StatusGet() & SPW_PKTRX_STATUS_ACT) == 0);

    /* Set list element 1 in Next buffer with start condition later (on current buffer deactivation) */
    next_buffer = (appSpwRxBufferListDesc.head + 1);
    APP_SPW_INTF_SetNextReceiveBuffer(next_buffer, SPW_PKTRX_NXTBUF_START_LATER);

    /* Enable packet RX interrupts */
    SPW_PKTRX_InterruptEnable(SPW_PKTRX_INT_MASK_DEACT | SPW_PKTRX_INT_MASK_EOP);
}

/* ----------------------------------------------------------------------------- */
/* void APP_SPW_INTF_TxUpdateLinkState(void)

   Summary:
    Initialize SPW packet emission to start transmitting data on the first Link
    that is in Run mode.

   Description:
    This function initialize SPW packet emission by writing the initial data in
    TX buffer, preparing the send list and initiate the first send of data.

   Remarks:
    None.
*/
static void APP_SPW_INTF_TxUpdateLinkState(void)
{
    uint8_t linkRouterByte = 0;

    /* Check if SPW link are in Run state */
    if (SPW_LINK_GET_STATE(SPW_LINK_StatusGet(SPW_LINK_1)) == SPW_LINK_STATE_RUN)
    {
        appSpwActiveLink = APP_SPW_INTF_ACTIVE_LINK_1;
        linkRouterByte = SPW_ROUTER_LINK1_PORT;
    }
    else if (SPW_LINK_GET_STATE(SPW_LINK_StatusGet(SPW_LINK_2)) == SPW_LINK_STATE_RUN)
    {
        appSpwActiveLink = APP_SPW_INTF_ACTIVE_LINK_2;
        linkRouterByte = SPW_ROUTER_LINK2_PORT;
    }
    else
        appSpwActiveLink = APP_SPW_INTF_ACTIVE_LINK_NONE;

    if (appSpwActiveLink != APP_SPW_INTF_ACTIVE_LINK_NONE)
    {
        // Update send list
        appSpwTxPckSendList[0].RSize = 1;
        appSpwTxPckSendList[0].RB1 = linkRouterByte;
        appSpwTxPckSendList[0].HSize = 0;
        appSpwTxPckSendList[0].HAddr = 0;
        appSpwTxPckSendList[0].DSize = APP_SPW_DATA_SIZE_BYTES;
        appSpwTxPckSendList[0].DAddr = (unsigned int) &(appSpwTxDataBuffer[0][0]);

        SYS_CONSOLE_PRINT("SPW new active Link :%d\r\n", appSpwActiveLink);
    }
}

/*----------------------------------------------------------------------------
 *        Interrupt Handler
 *----------------------------------------------------------------------------*/

/* void APP_SPW_Callback(SPW_INT_MASK irqStatus, uintptr_t context)

  Summary:
    Function called by SPW PLIB.

  Description:
    This function will be called by SPW PLIB when interrupt has occurred.

  Remarks:
    None.
*/
void APP_SPW_Callback(SPW_INT_MASK irqStatus, uintptr_t context)
{
    if (irqStatus & SPW_INT_MASK_PKTTX1)
    {
        SPW_PKTTX_INT_MASK status = SPW_PKTTX_IrqStatusGetMaskedAndClear();

        if (status & SPW_PKTTX_INT_MASK_DEACT)
        {
            // Unlock previous buffer status
            SPW_PKTTX_UnlockStatus();
        }
    }

    if (irqStatus & SPW_INT_MASK_PKTRX1)
    {
        SPW_PKTRX_INT_MASK status = SPW_PKTRX_IrqStatusGetMaskedAndClear();

        if (status & SPW_PKTRX_INT_MASK_DEACT)
        {
            uint16_t next_buffer = ((appSpwRxBufferListDesc.head + 2) % APP_SPW_RX_RECV_LIST);
            if (next_buffer == appSpwRxBufferListDesc.tail)
            {
                if (appSpwRxBufferListDesc.full == 0)
                {
                    appSpwRxBufferListDesc.full = 1;
                }
            }
            else
            {
                uint16_t prev_rx_buff = appSpwRxBufferListDesc.head;
                // Increment head
                appSpwRxBufferListDesc.head = ((appSpwRxBufferListDesc.head + 1) % APP_SPW_RX_RECV_LIST);
                // set next buffer
                APP_SPW_INTF_SetNextReceiveBuffer(next_buffer, SPW_PKTRX_NXTBUF_START_LATER);
                // Get Status to unlock previous buffer
                appSpwRxRecvPckStatus[prev_rx_buff] = SPW_PKTRX_GetPreviousBufferStatus();
            }
        }
    }

    if (irqStatus & SPW_INT_MASK_LINK1)
    {
        SPW_LINK_INT_MASK status = SPW_LINK_IrqStatusGetMaskedAndClear(SPW_LINK_1);
        SYS_CONSOLE_PRINT("ERROR(s) on SPW Link 1 :\r\n");
        APP_SPW_INTF_LinkInterruptErrors(status);
    }

    if (irqStatus & SPW_INT_MASK_LINK2)
    {
        SPW_LINK_INT_MASK status = SPW_LINK_IrqStatusGetMaskedAndClear(SPW_LINK_2);
        SYS_CONSOLE_PRINT("ERROR(s) on SPW Link 2 :\r\n");
        APP_SPW_INTF_LinkInterruptErrors(status);
    }
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/* void APP_SPW_INTF_RH_LedsUpdate(uint8_t leds)

  Summary:
    Create and send SpaceWire message to notify SAMRH71 LEDs states update to the remote UI.

  Parameters:
    leds - LEDs bitfield states.

  Return:
    None.
*/
void APP_SPW_INTF_RH_LedsUpdate(uint8_t leds)
{
    uint8_t msg[APP_SPW_DATA_SIZE_BYTES] = {0};

    msg[0] = APP_SPW_MSG_ID_RH_LED_STATUS;
    msg[1] = leds;

    APP_SPW_INTF_PrepareAndStartSendList(&(msg[0]), 2);
}

/*------------------------------------------------------------------------------*/
/* void APP_SPW_INTF_RH_PbUpdate(uint8_t push_buttons)

  Summary:
    Create and send SpaceWire message to notify SAMRH71 Push Buttons update to the remote UI.

  Parameters:
    push_buttons - Push buttons bitfield states.

  Return:
    None.
*/
void APP_SPW_INTF_RH_PbUpdate(uint8_t push_buttons)
{
    uint8_t msg[APP_SPW_DATA_SIZE_BYTES] = {0};

    msg[0] = APP_SPW_MSG_ID_RH_PB_STATUS;
    msg[1] = push_buttons;

    APP_SPW_INTF_PrepareAndStartSendList(&(msg[0]), 2);
}

/*------------------------------------------------------------------------------*/
/* void APP_SPW_INTF_64S_LedsUpdate(uint8_t leds)

  Summary:
    Create and send SpaceWire message to notify ATmega64M1 Sensor CAN Node
    LEDs update to the remote UI.

  Parameters:
    leds - LEDs bitfield states.

  Return:
    None.
*/
void APP_SPW_INTF_64S_LedsUpdate(uint8_t leds)
{
    uint8_t msg[APP_SPW_DATA_SIZE_BYTES] = {0};

    msg[0] = APP_SPW_MSG_ID_64MC_LED_STATUS;
    msg[1] = leds;

    APP_SPW_INTF_PrepareAndStartSendList(&(msg[0]), 2);
}

/*------------------------------------------------------------------------------*/
/* void APP_SPW_INTF_64S_PbUpdate(uint8_t push_buttons)

  Summary:
    Create and send SpaceWire message to notify ATmega64M1 Sensor CAN Node
    Push Buttons update to the remote UI.

  Parameters:
    push_buttons - Push buttons bitfield states.

  Return:
    None.
*/
void APP_SPW_INTF_64S_PbUpdate(uint8_t push_buttons)
{
    uint8_t msg[APP_SPW_DATA_SIZE_BYTES] = {0};

    msg[0] = APP_SPW_MSG_ID_64MC_PB_STATUS;
    msg[1] = push_buttons;

    APP_SPW_INTF_PrepareAndStartSendList(&(msg[0]), 2);
}

/*------------------------------------------------------------------------------*/
/* void APP_SPW_INTF_64MC_StatusUpdate(uint8_t speedTarget, uint8_t direction, uint8_t speedMeasure, uint8_t potentiometer)

  Summary:
    Create and send SpaceWire message to notify ATmega64M1 Motor Control CAN Node
    status update to the remote UI.

  Parameters:
    speedTarget - The speed target command.
    direction - The motor direction.
    speedMeasure - The measured speed.
    potentiometer - The potentiometer value.

  Return:
    None.
*/
void APP_SPW_INTF_64MC_StatusUpdate(uint8_t speedTarget, uint8_t direction, uint8_t speedMeasure, uint8_t potentiometer)
{
    uint8_t msg[APP_SPW_DATA_SIZE_BYTES] = {0};

    // Populate Tx_data buffer
    msg[0] = APP_SPW_MSG_ID_64MC_MOTOR_STATUS;
    msg[1] = speedTarget;
    msg[2] = direction;
    msg[3] = speedMeasure;
    msg[4] = potentiometer;

    APP_SPW_INTF_PrepareAndStartSendList(&(msg[0]), 5);
}

/*------------------------------------------------------------------------------*/
/* void APP_SPW_INTF_V71MC_StatusUpdate(uint8_t speedTarget, uint8_t speedMeasure, uint8_t potentiometer)

  Summary:
    Create and send SpaceWire message to notify SAMV71 Motor Control CAN Node
    status update to the remote UI.

  Parameters:
    speedTarget - The speed target command.
    speedMeasure - The measured speed.
    potentiometer - The potentiometer value.

  Return:
    None.
*/
void APP_SPW_INTF_V71MC_StatusUpdate(uint8_t speedTarget, uint8_t speedMeasure, uint8_t potentiometer)
{
    uint8_t msg[APP_SPW_DATA_SIZE_BYTES] = {0};

    // Populate Tx_data buffer
    msg[0] = APP_SPW_MSG_ID_V71MC_MOTOR_STATUS;
    msg[1] = speedTarget;
    msg[2] = speedMeasure;
    msg[3] = potentiometer;

    APP_SPW_INTF_PrepareAndStartSendList(&(msg[0]), 4);
}

/* ----------------------------------------------------------------------------- */
/* void APP_MCAN_INTF_Init(void)

  Summary:
    Initialize SpaceWire interface.

  Description:
    Initialize SpaceWire interface for receiving with circular buffers and check
    Link states.

  Parameters:
    None.

  Return:
    None.
*/
void APP_SPW_INTF_Init(void)
{
    /* Add SPW interrupt callback */
    SPW_CallbackRegister(APP_SPW_Callback, (uintptr_t)NULL);
    
     /* Enable SPW Link interrupts */
    SPW_LINK_InterruptEnable(SPW_LINK_1 , SPW_LINK_INT_MASK_DISERR |
                                          SPW_LINK_INT_MASK_PARERR |
                                          SPW_LINK_INT_MASK_ESCERR |
                                          SPW_LINK_INT_MASK_CRERR |
                                          SPW_LINK_INT_MASK_LINKABORT |
                                          SPW_LINK_INT_MASK_EEPTRANS |
                                          SPW_LINK_INT_MASK_EEPREC |
                                          SPW_LINK_INT_MASK_DISCARD);
    SPW_LINK_InterruptEnable(SPW_LINK_2 , SPW_LINK_INT_MASK_DISERR |
                                          SPW_LINK_INT_MASK_PARERR |
                                          SPW_LINK_INT_MASK_ESCERR |
                                          SPW_LINK_INT_MASK_CRERR |
                                          SPW_LINK_INT_MASK_LINKABORT |
                                          SPW_LINK_INT_MASK_EEPTRANS |
                                          SPW_LINK_INT_MASK_EEPREC |
                                          SPW_LINK_INT_MASK_DISCARD);   

    APP_SPW_INTF_InitRx();

    /* Enable packet TX interrupts */
    SPW_PKTTX_InterruptEnable(SPW_PKTTX_INT_MASK_DEACT);

    APP_SPW_INTF_TxUpdateLinkState();
}

/* ----------------------------------------------------------------------------- */
/* void APP_MCAN_INTF_Pool(void)

  Summary:
    Pool for new received messages on SpaceWire interface.

  Parameters:
    None.

  Return:
    None.
*/
void APP_SPW_INTF_Pool(void)
{
    /* If no active link, pool links to detect Run state*/
    if (appSpwActiveLink == APP_SPW_INTF_ACTIVE_LINK_NONE)
    {
        APP_SPW_INTF_TxUpdateLinkState();
    }
    
    APP_SPW_INTF_RX_LIST_DESC tmpRxBufferListDesc = appSpwRxBufferListDesc;
    if ((tmpRxBufferListDesc.tail != tmpRxBufferListDesc.head) || (tmpRxBufferListDesc.full))
    {
        // If number of list buffer is 2, first unlock previous buffer
        if ( APP_SPW_RX_RECV_LIST == 2)
        {
            appSpwRxRecvPckStatus[tmpRxBufferListDesc.head] = SPW_PKTRX_GetPreviousBufferStatus();
        }

        // Treat received buffer
        APP_SPW_INTF_ProcessBufferId(tmpRxBufferListDesc.tail);

        // Clear buffer
        appSpwRxRecvPckStatus[tmpRxBufferListDesc.tail] = 0;
        memset(&(appSpwRxDataBuffer[tmpRxBufferListDesc.tail][0]), 0, sizeof(appSpwRxDataBuffer[tmpRxBufferListDesc.tail]));
        memset(&(appSpwRxPckInfo[tmpRxBufferListDesc.tail][0]), 0, sizeof(SPW_PKTRX_INFO) * APP_SPW_RX_PACKET_NUM);

        appSpwRxBufferListDesc.tail = (appSpwRxBufferListDesc.tail + 1) % APP_SPW_RX_RECV_LIST;

        // Set next buffer if none was set on last interrupt
        if (tmpRxBufferListDesc.full)
        {
            appSpwRxBufferListDesc.full = 0;
            // Increment head
            appSpwRxBufferListDesc.head = ((appSpwRxBufferListDesc.head + 1) % APP_SPW_RX_RECV_LIST);
            // Set next buffer
            uint16_t next_buffer = ((appSpwRxBufferListDesc.head + 1) % APP_SPW_RX_RECV_LIST);

            if ( APP_SPW_RX_RECV_LIST > 2)
            {
                APP_SPW_INTF_SetNextReceiveBuffer(next_buffer, SPW_PKTRX_NXTBUF_START_LATER);
                // Get Status to unlock previous buffer
                appSpwRxRecvPckStatus[tmpRxBufferListDesc.head] = SPW_PKTRX_GetPreviousBufferStatus();
            }
            else
            {
                SPW_PKTRX_NXTBUF_START nextStartCondition = SPW_PKTRX_NXTBUF_START_LATER;
                SPW_PKTRX_STATUS rx_status = SPW_PKTRX_StatusGet();
                if (rx_status & SPW_PKTRX_STATUS_LOCKED)
                {
                    appSpwRxBufferListDesc.full = 1;
                    nextStartCondition = SPW_PKTRX_NXTBUF_START_NOW;
                }
                APP_SPW_INTF_SetNextReceiveBuffer(next_buffer, nextStartCondition);
            }
        }
    }
}

