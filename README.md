# Introduction
For my Reaction Time Game project, I utilized the EduBase board and the TM4C123GH6PM microcontroller 
with drivers that we created in lab class. I made use of the PWM example that was demonstrated in the lecture, the PMOD BTN driver, the Timer_0A driver, and the seven-segment display driver. 
The count variable, the value displayed on the seven-segment display, was incremented by interrupts from the timer driver every millisecond. Two LEDs were powered by the PWM driver. 
When the red LED indicates that the game has started, the green LED goes on, and the timer starts counting. The player now has to use the stop button to quickly stop the game.

# Results 
Three testing techniques were utilized to measure reaction times in order to evaluate performance: the Tiva TM4C123G LaunchPad with EduBase board, 
An online reaction game ([Human Benchmark - Reaction Time Test](https://humanbenchmark.com/tests/reactiontime)) was played with a wired mouse, and the same game was played with a wireless mouse. 
The findings were displayed using MATLAB in order to investigate the differences in performance between these input methods.
([video demonstration](https://youtu.be/zzkDvnV2Ua8))

The Tiva TM4C123G LaunchPad outperformed other options by removing the several latency layers seen in online settings. Even while the cable mouse had a somewhat lower latency 
than its wireless version, the microcontroller's hardware timers that didn't depend on CPU load made it the most precise. Because of its design, the microcontroller can attain 
accuracy at the microsecond level that is unmatched by conventional computer peripherals.

![graph](https://github.com/user-attachments/assets/eadd77a6-2e87-420f-8eaf-55d207ea7111)

# Background and Methodology
The implementation of the Reaction Time Game uses a variety of interfaces to demonstrate basic embedded systems concepts. 
A PMOD BTN module was connected to GPIO pins so that the debouncing filter could be utilized to guarantee precise button presses, and two LED indicators offer a visual response.
To ensure timing accuracy, the system uses millisecond-accurate clocks that detect player reactions and create random delays. 
In order to optimize timing accuracy and processing efficiency, the interrupt-driven architecture guarantees an instantaneous 
reaction to player actions without constant polling, while a visual indicator uses PWM pins to manage LED activation statuses during various game phases.

The microcontroller TM4C123GH6PM is the foundation of the project. The Digilent PMODBTN MODULE manages input and is designed to start and stop the game. 
Two LEDs provide visual feedback: one is green when players should react, and the other is red when they are waiting. On the integrated seven-segment display of the Edubase board, 
game results are displayed. The Keil µVision development environment was used to create the software.

A general-purpose timer module with millisecond resolution is used in the timing system. A function was added to provide randomized delays between game phases that range from 500 to 7000 ms. 
The PWM pins are toggled by functions designed to control LEDs. The Nested Vectored Interrupt Controller, which is designed to handle software interrupts from timers
as well as hardware interrupts from button touches, is what gives the system its responsiveness.

# Block Diagram
![Block diagram](https://github.com/user-attachments/assets/98291f65-8d54-4de0-86a0-490a2112502c)

# Components Used

| Component       | Quantity           | Manufacturer              |
|-----------------|-----------------------|-----------------------|
| TM4C123GH6PM microcontroller | 1        |Texas Instruments        |
| EduBase board     | 1                   |Trainer4Edu       |
| PMOD BTN Module   | 1                   |Digilent Inc    |
| LEDs              | 2                   | N/A      |

# Pinout Used

| PMOD BTN Pin     | TM4C123GH6PM           
|-----------------|-----------------------
| Pin 1 (BTN0)          | PD2           | 
| Pin 2 (BTN1)          | PD3           | 
| Pin 5 (GND)           | GND           |
| Pin 6 (VCC)           | VCC (3.3V)    | 

| PWM     | TM4C123GH6PM           
|-----------------|-----------------------
| Resistor          | PE4          | 
| Resistor          | PE5          | 

