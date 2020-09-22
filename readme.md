![Microchip logo](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_logo.png)

# CAN network and Motor Control Demo Examples

This repository contains the MPLAB® Harmony 3 examples for CAN network and Motor Control Demo.

- [Contents Summary](#contents-summary)
- [CAN and Motor Control Demo Summary](#can-and-motor-control-demo-summary)
- [Hardware Setup](#hardware-setup)
- [Running The Application](#running-the-application)

---

## Contents Summary

| Folder               | Description                                               |
| ---                  | ---                                                       |
| SAMRH71_Interface    | SAMRH71 CAN interface application                         |
| SAMV71RT_MCLV2_Node  | SAMRV71RT motor control node application                  |

---

## CAN network and Motor Control Demo Summary

This demo uses a CAN network to exchange command and control messages in between Microchip evaluation kits.
The SAMRH71F20-EK board hosts the user interface (through a web interface or SpaceWire messages) to interact with the SAMV71RT motor control node.

Each node has it's own MPLABX project and readme documentation:
* [SAMRH71_Interface](SAMRH71_Interface/readme.md)
* [SAMV71RT_MCLV2_Node](SAMV71RT_MCLV2_Node/readme.md)

---

## Hardware Setup

Power-up and connect the board CAN interfaces together as describe in "Hardware Setup" section for each project:
* [SAMRH71_Interface - Hardware Setup](SAMRH71_Interface/readme.md#hardware-setup)
* [SAMV71RT_MCLV2_Node - Hardware Setup](SAMV71RT_MCLV2_Node/readme.md#hardware-setup)

---

## Running The Application

Refer to sections "Running The Application" for each projects:
* [SAMRH71_Interface - Running The Application](SAMRH71_Interface/readme.md#running-the-application)
* [SAMV71RT_MCLV2_Node - Running The Application](SAMV71RT_MCLV2_Node/readme.md#running-the-application)
