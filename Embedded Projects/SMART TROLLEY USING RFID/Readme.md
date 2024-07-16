# RFID Based Inventory Management System

## Overview

This project utilizes an LPC21xx microcontroller to implement an RFID-based Inventory Management System. The system integrates various components such as RFID modules, LCD displays, UART communication, and external switches to track and manage inventory items. It offers functionalities for scanning products, updating prices, and displaying real-time data, enhancing inventory control efficiency.

## Components Used

- **LPC21xx Microcontroller**: Controls system operations and interfaces with peripherals.
- **LCD Display**: Provides visual feedback on scanned products, prices, and system status.
- **RFID Module**: Reads RFID tags attached to products for identification.
- **UART Module**: Enables serial communication for debugging and external interaction.
- **External Switches (SW1, SW2)**: Trigger events like finalizing bills and product removal through interrupts.

## Functionality

### Main Program (`main.c`)

The `main` function initializes UART communication and interrupt handling. It continuously scans for RFID-tagged products (`pen` and `book`). Upon detecting a product, it updates the total price based on predefined values for each product type (`pen` or `book`). The LCD displays real-time updates of scanned products and their respective prices.

### Interrupt Handlers (`EXT_INT.c`)

- **`EXT0_ISR`**: Handles interrupts triggered by SW1. It finalizes the current bill by displaying the total price on the LCD.
- **`EXT1_ISR`**: Manages interrupts from SW2, which allows removing products from the inventory. It resets the price when a product is scanned for removal and updates the LCD accordingly.

### UART Communication (`UART0_Header.h` and `UART0_Header.c`)

Defines functions for initializing UART communication, transmitting data (`UART0_TX`), receiving data (`UART0_RX`), and transmitting strings (`UART0_STR`). These functions facilitate debugging messages and external communication, enhancing system monitoring and interaction capabilities.

## Setup

1. **Hardware Setup**:
   - Connect the LPC21xx microcontroller with the LCD display, RFID module, UART interface, and external switches based on the provided circuit diagram.
   - Ensure proper pin configuration (`PINSEL`) for UART and interrupt handling.

2. **Software Dependencies**:
   - Install necessary headers (`LCD_Header.h`, `UART0_Header.h`, `EXT_INT.h`) for accessing LCD functions, UART communication, and interrupt handling.
   - Implement functions (`LCD_Header.c`, `UART0_Header.c`, `EXT_INT.c`) corresponding to LCD display management, UART operations, and interrupt service routines.

3. **Execution**:
   - Upload the compiled code (`main.c`, `EXT_INT.c`, `UART0_Header.c`) to the LPC21xx microcontroller using appropriate tools (e.g., LPCXpresso).
   - Power on the system and observe the LCD for real-time updates when scanning RFID-tagged products or triggering external switches.

## Conclusion

The RFID Based Inventory Management System enhances efficiency in tracking inventory through automated RFID scanning and real-time updates. It provides a robust platform for managing product additions, removals, and price calculations, ensuring accurate and responsive inventory control.
