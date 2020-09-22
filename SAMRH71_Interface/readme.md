![Microchip logo](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_logo.png)

# SAMRH71-EK Node in CAN Demo example

This example contains the software running on SAMRH71-EK board in the CAN demo setup. It is used to control several CAN Nodes (Motor control and sensors) through a web page interface or SpaceWire protocol.

- [SAMRH71-EK Node in CAN Demo example](#samrh71-ek-node-in-can-demo-example)
  - [CAN Demo Example Summary](#can-demo-example-summary)
  - [Building The Application](#building-the-application)
  - [Harmony Configurations](#harmony-configurations)
  - [Hardware Setup](#hardware-setup)
  - [Running The Application](#running-the-application)

---

## CAN Demo Example Summary

This demo was implemented using the Harmony 3 framework. It was created similarly to the net example "Web Net Server Non-volatile Memory (NVM) MPFS configuration" and was modified to:
* Be loaded in SAMRH71-EK external PROM and executed in internal FlexRAM.
* Add CAN communication with connected nodes.
* Add a custom web page interface.
* Add SpaceWire communication for a remote UI.

---

## Building The Application 
To build the application, open the project file in MPLABX IDE.

**Application Path:**   
* **For SAMRH71F20-EK board** :firmware\sam_rh71_ek.X

---

## Harmony Configurations 

Refer to the MHC project graph for the components used and the respective configuration options.

* PIO configuration
    * External memory controller (HEMC) pins are configured and HSMC timings settings are adjusted.
    * The pins used by peripherals are configured for FLEXCOM1 and MCAN1.
* FLEXCOM Peripheral:
    * FLEXCOM1
        * This peripheral is used in UART configuration for standard print and application logs.
* HEMC Peripheral:
    * Peripheral configured to initialize HSMC timings.
* TC0 Peripheral:
    * Timer configured to provide Time System Service.

*Important Note*: This example use an advanced version of Harmony NET repository. It is not possible to regenerate the code using the currently released version.

*Note*: As the current implementation of the HEMC module does not have a "MEMORY" capability, the HEFC module is used to connect to the MEMORY driver. For that purpose, the address set in "NVM Media Start Address" is an address located in HEMC memory (PROM memory on NSC0).

---

## Hardware Setup

1. Project sam_rh71_ek.X
    * Hardware Used
        * SAM RH71 Evaluation Kit
        * Debugger probe for SAMRH71-EK (ICD4, J32, SAM-ICE, ...)
    * Hardware Setup
        * Connect the debugger probe to J33 on the SAMRH71-EK board
        * Connect the J15 USB port of the board to a computer using a mini USB cable.
        * For the TCP/IP demonstrations, both the target board and the host computer should be on the same network. The host computer can be connected to a router via an Ethernet cable or Wi-Fi. The target board should be connected to the router via an Ethernet cable.
            * *Notes*
                * All the TCP/IP Application Demonstration projects that are part of this distribution use the Microchip hardware development boards. They are pre-configured with specific PHY Drivers. The default PHY driver can be changed as some of the hardware boards support different PHY daughter boards. To use a different PHY for a specific board, use MPLAB® Harmony Configurator (MHC) to select and configure the PHY. Make sure that correct PHY address and configuration flags are used for the specific PHY daughter board. The MII/RMII and I/O configuration flags should match the hardware for the PHY board.
                * The TCP/IP application demonstrations assume that IPv4 is enabled. If IPv4 is not enabled in MHC, the code in app.c will not build and needs to be updated to remove the IPv4 dependencies.
                * All demos have DHCP enabled, and expect a DHCP server to be available. If there is no DHCP server, then the default static IP address will be used: 192.168.100.11. If this static address does not match your network settings, use MPLAB® Harmony Configurator (MHC) to modify the static IP address of the network interface.
                * The NetBIOS name of the TCP/IP application is specified during the initialisation of TCP/IP stack. It is the hostName member of TCPIP_HOSTS_CONFIGURATION structure. The NetBIOS service must be enabled in demonstration configuration, for the TCP/IP demonstration to respond to NetBIOS queries. Alternatively, use the IPv4 or IPv6 address (if IPv6 is enabled) of the board directly.
                * The IPv4 and IPv6 addresses can be obtained by running the TCP/IP Discovery utility on the computer. It requires the TCP/IP Announce module enabled in demonstration configuration, through MHC.
        * Connect the MCAN1 header pin to the CAN network and start the CAN Nodes on that network.
        * Connect one of the SpaceWire Links to a STAR-Dundee SpaceWire Brick Mk3. 

---

## Running The Application

1. Build the application using the MPLAB X IDE.
2. Load the application in SAMRH71-EK external PROM memory using custom or Bootloader project (Available on demand).
3. Open a standard terminal application on the computer (like Hyper-terminal or Tera Term) and configure the virtual COM port.
4. Set the serial baud rate to 115200 baud in the terminal application.
5. Restart the demonstration by pressing the 'RESET' button on the board.
6. See that the initialization prints on the serial port terminal.
7. When the DHCP client is enabled in the demonstration, wait for the DHCP server to assign an IP address for the development board. This will be printed on the serial port terminal.
8. On the web page, use the interface to modify the available parameters in the CAN Nodes (LEDs status, motor speed or direction)