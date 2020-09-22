![Microchip logo](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_logo.png)

# SAMV71 Motor Control CAN Node
This software example runs on a dsPICDEM MCLV-2 Development Board and is part of the CAN demo setup. It is based on the [pmsm_foc_smo_sam_e70_doc](https://microchip-mplab-harmony.github.io/motor_control/00070.html) Harmony 3 motor control example which was ported to the SAMV71 with the addition of a CAN interface. This node requires the master controller "SAMRH71-EK Interface"

- [SAMV71 Motor Control CAN Node](#samv71-motor-control-can-node)
  - [SAMV71 CAN Node Summary](#samv71-can-node-summary)
  - [Building The Application](#building-the-application)
  - [Harmony Configurations](#harmony-configurations)
  - [Hardware Setup](#hardware-setup)
  - [Running The Application](#running-the-application)

---

## SAMV71 CAN Node Summary
The original motor control interface (S2, S3, Pot) was disabled and replaced by CAN remote commands:
* Incoming frames (ID 0x200): [TargetSpeed, 0, 0, 0, 0, 0, 0, 0]
  * *TargetSpeed*: Target speed index [0, 255] with 0 meaning "off"
* Outgoing frames (ID 0x201): [TargetSpeed, MeasureSpeed, PotValue, 0, 0, 0, 0, 0] every 500ms
  * *TargetSpeed*: Target speed index [0, 255] with 0 meaning "off"
  * *MeasureSpeed*: Index corresponding to the measured angular speed [0, 255] (tracks to *TargetSpeed*)
  * *PotValue*: Index corresponding to the dsPICDEM MCLV-2 potentiometer position [0, 255] (not correlated with the motor control)

---

## Building The Application 
To build the application, open the project file in MPLABX IDE.

**Application Path:**   
* firmware\pmsm_foc_smo_sam_v71.X

---

## Harmony Configurations 
It is based on this project [pmsm_foc_smo_sam_e70_code](https://github.com/Microchip-MPLAB-Harmony/motor_control/tree/master/apps/pmsm_foc_smo_sam_e70) with the following additions:
* MCAN1 Peripheral:
    * 500kbps bitrate
    * One standard filter to only acknowledge message ID 0x200
* TC1 Peripheral:
    * Time System Service (1ms tick)
* PIO Configuration
    * "MCAN1_CANRX1" on PC12 (17)
    * "MCAN1_CANTX1" on PD12 (92)
* Clock Configuration
    * MCK selected on PCK5 (CANx)
* MPU Configuration
    * SRAM non-cacheable region @0x2045f000
    * *Note: This region is described in the project custom linker file*

---

## Hardware Setup
Project pmsm_foc_smo_sam_v71.X
* Hardware Used
    * [dsPICDEM MCLV-2 Development Board](https://www.microchip.com/developmenttools/ProductDetails/dm330021-2)
        * Custom ATSAMV71Q21B PIM board
        * [Long Hurst DMA0204024B101 Motor](https://www.microchip.com/DevelopmentTools/ProductDetails/PartNo/AC300022)
*  Hardware Setup
    * Connect the CAN interface to the "SAMRH71-EK Node"
    * Motor Connections:
        * Phase U - M1
        * Phase V - M2
        * Phase W - M3
    * Jumper Settings:
        * JP1 - Curr, JP2 - Curr, JP3 - Curr
        * In order to use RS232 port for X2CScope Communication JP4 - UART, JP5 - UART
        * In order to use USB port for X2CScope Communication JP4 - USB, JP5 - USB
    * Power the board with a 24V DC supply using J2 or BP1-BP2. For additional safety, it is recommended to use a current limited power supply while testing this software demonstration on a non-default hardware and motor

---

## Running The Application
1. Build and load the application using the MPLAB X IDE
2. Use the "SAMRH71-EK Interface" web interface to control the motor