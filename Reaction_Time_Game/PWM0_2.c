/**
 * @file PWM0_2.c
 * 
 * @brief Source file for the PWM0_2 driver.
 * 
 * This file contains the function definitions for the PWM0_2 driver.
 * It uses the Module 0 PWM Generator 2 to generate a PWM signal using the PE4 pin (M0PWM4).
 * 
 * @note This driver assumes that the system clock's frequency is 50 MHz.
 * 
 * @note This driver assumes that the PWM_Clock_Init function has been called
 * before calling the PWM0_2_Init function.
 * 
 * @author Irvin 
*/

#include "PWM0_2.h"

void PWM0_2_Init(uint16_t period_constant, uint16_t duty_cycle)
{    
    // Return from the function if the specified duty_cycle is greater than
		// or equal to the given period. The duty cycle cannot exceed 99%.
    if (duty_cycle >= period_constant) return;

    // Enable the clock to PWM Module 0 by setting the
	  // R0 bit (Bit 0) in the RCGCPWM register
    SYSCTL->RCGCPWM |= 0x01;

    // Enable the clock to GPIO Port E by setting the
    // R4 bit (Bit 4) in the RCGCGPIO register
    SYSCTL->RCGCGPIO |= 0x10;

    // Configure the PE4 pin to use the alternate function (M0PWM4)
    // by setting Bit 4 in the AFSEL register
    GPIOE->AFSEL |= 0x10;

    // Clear the PMC4 field (Bits 19 to 16) in the PCTL register
    GPIOE->PCTL &= ~0x000F0000;

    // Configure the PE4 pin to operate as a Module 0 PWM4 pin (M0PWM4)
    // by writing 0x4 to the PMC4 field (Bits 19 to 16) in the PCTL register
    // The 0x4 value is derived from Table 23-5 in the TM4C123G Microcontroller Datasheet
    GPIOE->PCTL |= 0x00040000;

    // Enable the digital functionality for the PE4 pin
    // by setting Bit 4 in the DEN register
    GPIOE->DEN |= 0x10;

    // Configure GPIO Port E to use PE5 as a digital output pin (optional LED or control signal)
    // This pin is separate from the PWM functionality on PE4
    GPIOE->DIR |= 0x20;           
    GPIOE->DEN |= 0x20;           

    // Disable the Module 0 PWM Generator 2 block (PWM0_2) before 
    // configuration by clearing the ENABLE bit (Bit 0) in the PWM2CTL register
    PWM0->_2_CTL &= ~0x01;

    // Configure the counter for the PWM0_2 block to
    // use Count-Down mode by clearing the MODE bit (Bit 1)
    // in the PWM2CTL register. The counter will count from the load value
    // to 0, and then wrap back to the load value
    PWM0->_2_CTL &= ~0x02;

    // Set the ACTCMPAD field (Bits 7 to 6) to 0x3 in the PWM2GENA register
    // to drive the PWM signal high when the counter matches 
    // the comparator (i.e. the value in PWM2CMPA) while counting down
    PWM0->_2_GENA |= 0xC0;

    // Set the ACTLOAD field (Bits 3 to 2) to 0x2 in the PWM2GENA register
    // to drive the PWM signal low when the counter matches the value
    // in the PWM2LOAD register
    PWM0->_2_GENA |= 0x08;

    // Set the period by writing to the LOAD field (Bits 15 to 0) 
    // in the PWM2LOAD register. This determines the number of clock
    // cycles needed to count down to zero
    PWM0->_2_LOAD = (period_constant - 1);

    // Set the duty cycle by writing to the COMPA field (Bits 15 to 0)
    // in the PWM2CMPA register. When the counter matches the value in this register,
    // the PWM signal will be driven high
    PWM0->_2_CMPA = (duty_cycle - 1);

    // Enable the PWM0_2 block after configuration by setting the
    // ENABLE bit (Bit 0) in the PWM2CTL register
    PWM0->_2_CTL |= 0x01;

    // Enable the PWM0_2 signal to be passed to the PE4 pin (M0PWM4)
    // by setting the PWM4EN bit (Bit 4) in the PWMENABLE register
    PWM0->ENABLE |= 0x10;
}

void PWM0_2_Update_Duty_Cycle(uint16_t duty_cycle)
{
    // Set the duty cycle by writing to the COMPA field (Bits 15 to 0)
    // in the PWM2CMPA register. When the counter matches the value in this register,
    // the PWM signal will be driven high
    PWM0->_2_CMPA = (duty_cycle - 1);
}