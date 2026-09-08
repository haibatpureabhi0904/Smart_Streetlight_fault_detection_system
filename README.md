# Smart Street Light Controller with Fault Indication (PIC18F4520) 🌃

An embedded C firmware implementation for the Microchip PIC18F4520 microcontroller designed to automate a 7-lamp street lighting system based on ambient light, with integrated real-time fault detection and UART serial diagnostics.
Designed and tested for PIC18 microcontrollers with complete schematic support for Proteus VSM simulation using the Microchip C18 compiler.

## Features

* **Automated Day/Night Cycle:** Utilizes the PIC18's internal 10-bit ADC to read analog voltage from an LDR voltage divider, determining ambient light thresholds.
* **Bitwise Output Control:** Controls 7 independent LED street lamps simultaneously using direct PORTB register masking (`LATB = 0x7F`) for highly efficient instruction cycles.
* **Real-time Fault Detection:** Evaluates independent sensor logic on PORTD using bitwise shifting to detect and isolate specific blown bulbs without halting the main loop.
* **UART Diagnostics:** Streams system status updates (e.g., `Status: Daytime`, `ALERT: Night - Lamp faults detected!`) and specific lamp failure alerts to a central monitoring terminal at 9600 baud.

## Hardware & Peripheral Mapping

### PIC18F4520 Pin Configuration

| Pin | Peripheral / Mode | Pull / Level | Description |
| --- | --- | --- | --- |
| RA0 (Pin 2) | ADC_Input (AN0) | Analog | Analog voltage input from LDR/10k resistor divider |
| RB0 - RB6 (Pins 33-39) | GPIO_Output | Push-Pull | Drives 7 Yellow LEDs (Street Lamps) |
| RD0 - RD6 (Pins 19-22, 27-29) | GPIO_Input | Digital | Fault simulation logic states (0 = OK, 1 = Fault) |
| RC6 (Pin 25) | UART_TX (Output) | Push-Pull | Virtual Terminal RXD Interface for serial diagnostics |

## Circuit Schematic (Proteus VSM)

### 1. Environmental Sensing & Lighting

| PIC18F4520 Pin | External Component | Function |
| --- | --- | --- |
| Pin 2 (RA0/AN0) | LDR & 10k Resistor Junction | Senses voltage drops as LDR resistance changes with light |
| Pins 33 - 39 (RB0 - RB6) | 7x Yellow LEDs (Anodes) | Represents the smart city street lamps |
| N/A (Cathodes) | 7x 330Ω Resistors to GND | Current limiting for the LED lamps |
| VCC / GND | TORCH_LDR / 10k Resistor | Completes the LDR voltage divider circuit |

### 2. UART Interfaces & Fault Sensors

| PIC18F4520 Pin | External Component | Connection Details |
| --- | --- | --- |
| Pin 25 (RC6/TX) | Virtual Terminal | TX pin of the PIC connected to the RXD pin of the terminal for serial logging |
| Pins 19-22, 27-29 (RD0 - RD6) | 7x LOGICSTATE | Directly connected to simulate active-high lamp failures |
