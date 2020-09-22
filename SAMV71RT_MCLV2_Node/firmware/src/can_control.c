/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    can_control.c

  Summary:
    Motor control CAN interface.

  Description:
    This file contains the implementation of the CAN interface.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include "can_control.h"
#include "mc_app.h"


// *****************************************************************************
// *****************************************************************************
// Defines
// *****************************************************************************
// *****************************************************************************
#define CAN_CTRL_STATUS_INTERVAL_MS 500

/* By observation the rotor speed goes from 287 RPM to 795 RPM which */
/* corresponds to setpoints going from 800 to 2220 */
#define CAN_CTRL_SPEED_MIN_RPM 287
#define CAN_CTRL_SPEED_MAX_RPM 795

#define CAN_CTRL_SETPOINT_MIN 800
#define CAN_CTRL_SETPOINT_MAX 2220

// *****************************************************************************
// *****************************************************************************
// Global variables
// *****************************************************************************
// *****************************************************************************
static volatile uint32_t gTicks = 0;
static uint32_t gLastTicks = 0;
static uint8_t gTarget = 0;
uint8_t gMcan1MessageRAM[MCAN1_MESSAGE_RAM_CONFIG_SIZE] __attribute__((aligned (32)))__attribute__((space(data), section (".ram_nocache")));

/******************************************************************************/
/* Function name: TickHandler                                                 */
/* Function parameters: Typical parameters                                    */
/* Function return: None                                                      */
/* Description: Timer 1 channel 0 callback function (1ms tick)                */
/******************************************************************************/
void TickHandler(TC_TIMER_STATUS status, uintptr_t context) {
    gTicks++;
}

/******************************************************************************/
/* Function name: CanCtrlInit                                                 */
/* Function parameters: None                                                  */
/* Function return: None                                                      */
/* Description: Initialize TC1/CH0 and the CAN message                        */
/******************************************************************************/
void CanCtrl_Init(void) {

    /* Start the 1ms tick counter */
    TC1_CH0_TimerCallbackRegister(TickHandler, (uintptr_t)NULL);
    TC1_CH0_TimerStart();
    gLastTicks = gTicks;

    /* Set Message RAM Configuration */
    MCAN1_MessageRAMConfigSet(gMcan1MessageRAM);

    /* Set a default speed 0 -> Stopped */
    MC_APP_MC_SetTarget(0, CAN_CTRL_SETPOINT_MIN, CAN_CTRL_SETPOINT_MAX);
}

/******************************************************************************/
/* Function name: CanCtrlSendStatus                                           */
/* Function parameters: None                                                  */
/* Function return: None                                                      */
/* Description: Report the status to the CAN host                             */
/******************************************************************************/
void CanCtrl_SendStatus(void) {
    uint32_t messageID = 0;
    uint8_t message[8] = {0};
    uint8_t messageLength = 0;

    /* Prepare the message to send */
    /* message[0]: Speed target */
    messageID = 0x220;
    messageLength = 8;
    message[0] = gTarget;
    message[1] = MC_APP_MC_GetSpeed(CAN_CTRL_SPEED_MIN_RPM, CAN_CTRL_SPEED_MAX_RPM);
    message[2] = MC_APP_MC_GetPot();

    if (MCAN1_InterruptGet(MCAN_INTERRUPT_TC_MASK)) {
        MCAN1_InterruptClear(MCAN_INTERRUPT_TC_MASK);
    }

    MCAN1_MessageTransmit(messageID, messageLength, message, MCAN_MODE_NORMAL, MCAN_MSG_ATTR_TX_FIFO_DATA_FRAME);
}


/******************************************************************************/
/* Function name: CanCtrlTask                                                 */
/* Function parameters: None                                                  */
/* Function return: None                                                      */
/* Description: CAN state machine function to be called in the main loop      */
/******************************************************************************/
void CanCtrl_Task(void) {
    uint32_t status = 0;
    uint8_t rx_message[8];
    uint32_t rx_messageID = 0;
    uint8_t rx_messageLength = 0;
    MCAN_MSG_RX_FRAME_ATTRIBUTE msgFrameAttr = MCAN_MSG_RX_DATA_FRAME;

    /* Report the status via CAN every CAN_INTF_STATUS_INTERVAL_MS */
    if (gTicks > (gLastTicks + CAN_CTRL_STATUS_INTERVAL_MS)) {
        CanCtrl_SendStatus();
        gLastTicks = gTicks;
    }

    /* Check if a message arrived in the FIFO 0 */
    /* Only if (rx_messageID == 0x200) as defined in Harmony */
    if (MCAN1_InterruptGet(MCAN_INTERRUPT_RF0N_MASK)) {
        MCAN1_InterruptClear(MCAN_INTERRUPT_RF0N_MASK);

        /* Check CAN Status */
        status = MCAN1_ErrorGet();

        if (((status & MCAN_PSR_LEC_Msk) == MCAN_ERROR_NONE) || ((status & MCAN_PSR_LEC_Msk) == MCAN_PSR_LEC_NO_CHANGE)) {
            memset(rx_message, 0x00, sizeof(rx_message));

            /* Receive FIFO 0 New Message */
            if (MCAN1_MessageReceive(&rx_messageID, &rx_messageLength, rx_message, 0, MCAN_MSG_ATTR_RX_FIFO0, &msgFrameAttr) == true) {
                /* New Message Received */
                status = MCAN1_ErrorGet();
                if (((status & MCAN_PSR_LEC_Msk) == MCAN_ERROR_NONE) || ((status & MCAN_PSR_LEC_Msk) == MCAN_PSR_LEC_NO_CHANGE)) {
                    /* Set the speed target */
                    gTarget = rx_message[0];
                    MC_APP_MC_SetTarget(gTarget, CAN_CTRL_SETPOINT_MIN, CAN_CTRL_SETPOINT_MAX);
                }
            }
        }
    }
}
