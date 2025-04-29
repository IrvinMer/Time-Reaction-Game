/**
 * @file PMOD_BTN_Interrupt.c
 *
 * @brief Implementation of interrupt handler for PMOD Button module
 *
 * This file contains functions to initialize and handle interrupts from
 * the PMOD Button module connected to PD2 (Start) and PD3 (Stop).
 * Used in the Reaction Timer Game to capture user input.
 *
 * @author Irvin
 */

#include "GPIO.h"
#include "PMOD_BTN_Interrupt.h"
#include "TM4C123GH6PM.h"

void (*PMOD_BTN_Task)(uint8_t pmod_btn_state);

void PMOD_BTN_Interrupt_Init(void (*task)(uint8_t)) 
{
  // Store user-defined callback function to be called when interrupt occurs
  PMOD_BTN_Task = task;

  // Enable clock for GPIO Port D
  SYSCTL->RCGCGPIO |= 0x08;

  // Configure PD2-PD3 as input pins
  GPIOD->DIR &= ~0x0C;

  // Disable alternate functions for PD2-PD3
  GPIOD->AFSEL &= ~0x0C;

  // Enable digital I/O for PD2-PD3
  GPIOD->DEN |= 0x0C;

  // Enable pull-down resistors for PD2-PD3
  GPIOD->PDR |= 0x0C;

  // Set PD2-PD3 as edge-sensitive 
  GPIOD->IS &= ~0x0C;

  // Configure interrupts to trigger on a single edge 
  GPIOD->IBE &= ~0x0C;

  // Set interrupts to trigger on rising edge 
  GPIOD->IEV |= 0x0C;

  // Clear any pending interrupts on PD2-PD3
  GPIOD->ICR |= 0x0C;

  // Enable interrupts for PD2-PD3
  GPIOD->IM |= 0x0C;

  // Clear priority bits for GPIOD interrupt (IRQ3)
  NVIC->IPR[0] &= ~0xE0000000;

  // Set priority level 1 for GPIOD interrupt (IRQ3)
  NVIC->IPR[0] |= (1 << 29);

  // Enable GPIOD interrupt (IRQ3) in the NVIC
  NVIC->ISER[0] |= (1 << 3);
}

uint8_t PMOD_BTN_Read(void) 
{
  uint8_t pmod_btn_state = GPIOD->DATA & 0x0C;

  // Return the status of the PMOD BTN module
  return pmod_btn_state;
}

void GPIOD_Handler(void) 
{
  // Check if the interrupt was triggered by PD2 to PD3
  if (GPIOD->MIS & 0x0C) 
	{
    // Execute the user-defined function
    (*PMOD_BTN_Task)(PMOD_BTN_Read());

    // Clear the interrupt flags for PD2 to PD3
    GPIOD->ICR |= 0x0C;
  }
}