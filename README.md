# Introduction
For my Reaction Time Game project, I utilized the EduBase board and the TM4C123GH6PM microcontroller 
with drivers that we created in lab class. I made use of the PWM example that was demonstrated in the lecture, the PMOD BTN driver, the Timer_0A driver, and the seven-segment display driver. 
The count variable, which was shown on the seven-segment display, was incremented by me using the timer driver to cause interrupts every millisecond. Two LEDs were powered by the PWM driver. 
The timer begins counting when the green LED turns on, after the red LED signals that the game has begun. To end the game as soon as possible, the player must now press the button.

# Results 
The project ran into a display issue where the timer reset at 999 rather than reaching the desired 5000. Following an examination of the timer and main code, 
the seven-segment display driver code was found to be the source of the issue. 
In particular, a for loop that iterates through count_value's digits needed to be modified. The timer was able to reach the full 5000 count without being prematurely 
reset once all four digits were adjusted and shown appropriately.

The Tiva TM4C123G LaunchPad with EduBase board, an online game played with a wired mouse, and the same game played with a wireless mouse 
were the three testing methods used to evaluate reaction times in order to assess performance. 
To examine the variations in performance between these input techniques, MATLAB was used to illustrate the results.

The Tiva TM4C123G LaunchPad outperformed other options by removing the several latency layers seen in online settings. Even while the cable mouse had a somewhat lower latency 
than its wireless version, the microcontroller's hardware timers that didn't depend on CPU load made it the most precise. Because of its design, the microcontroller can attain 
accuracy at the microsecond level that is unmatched by conventional computer peripherals.
![graph](https://github.com/user-attachments/assets/eadd77a6-2e87-420f-8eaf-55d207ea7111)

# Background and Methodology
The Reaction Time Game implementation showcases fundamental embedded systems principles through various interfaces. Physical input comes via GPIO-connected buttons, 
while visual feedback is provided through two LED indicators. For timing precision, the system employs millisecond-accurate timers that generate random delays and measure player reactions. 
Visual indication relies on PWM technology to control LED activation states during different game phases, while the interrupt-driven architecture ensures instantaneous response 
to player actions without continuous polling, optimizing both timing accuracy and processor efficiency.

The project is built around the TM4C123GH6PM microcontroller as its central processing unit. Input functionality is handled by the Digilent PMODBTN MODULE featuring dedicated 
start and reaction buttons. Visual feedback comes from dual-purpose LEDs – red illuminates during the waiting phase while 
green signals when players should react. Game results appear on the Edubase board's integrated seven-segment display. All components connect through a breadboard circuit 
assembly with appropriate wiring. Software development occurs within the Keil µVision integrated development environment.

The timing system leverages a General-Purpose Timer Module configured for millisecond resolution, capable of generating randomized delays between 500-7000ms between game phases. 
LED control is managed through PWM modules that adjust duty cycles to determine which indicator remains active. The system's responsiveness comes from the Nested Vectored Interrupt Controller, 
programmed to manage both hardware interrupts from button interactions and software interrupts from timers. The entire gameplay flow follows state machine principles, transitioning systematically 
from waiting state through reaction phase to final result presentation.

# Functional Block Diagram

![Block diagram](https://github.com/user-attachments/assets/98291f65-8d54-4de0-86a0-490a2112502c)

# Table of Components Used

| Component       | Quantity           | Manufacturer              |
|-----------------|-----------------------|-----------------------|
| TM4C123GH6PM microcontroller | 1        |Texas Instruments        |
| EduBase board     | 1                   |Trainer4Edu       |
| PMOD BTN Module   | 1                   |Digilent Inc    |
| LEDs              | 2                   | N/A      |

# Table of Pinout Used

| Pin Number      | Function              | Description          |
|-----------------|-----------------------|----------------------|
| Pin 1           | Function 1            | Description 1        |
| Pin 2           | Function 2            | Description 2        |
| ...             | ...                   | ...                  |
