# Smart_Streetlight_fault_detection_system 🌃

An embedded systems simulation of a smart city street lighting network using a PIC18F4520 microcontroller. The system autonomously switches street lamps on and off based on ambient light levels and features real-time fault detection to report broken bulbs over UART serial communication.

## 🛠️ Tech Stack & Tools
*   **Microcontroller:** PIC18F4520
*   **Compiler:** Microchip C18 Compiler
*   **Simulation Environment:** Proteus VSM
*   **Languages:** C
*   **Interfaces:** ADC, UART, GPIO

## ✨ Key Features
*   **LDR Voltage Divider:** Dynamically measures ambient light levels to determine Day/Night states using the PIC18's 10-bit ADC.
*   **Automated Actuation:** Powers a network of 7 street lamps (LEDs) simultaneously via PORTB when the ADC value crosses the darkness threshold.
*   **Individual Fault Detection:** Monitors 7 independent logic states on PORTD to simulate bulb integrity. 
*   **UART Telemetry:** Streams real-time system status and specific lamp failure alerts (e.g., `---> Lamp 3 is broken`) to a central Virtual Terminal at 9600 baud.
