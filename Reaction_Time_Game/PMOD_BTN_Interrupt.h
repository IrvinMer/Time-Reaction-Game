/**
 * @file PMOD_BTN_Interrupt.h
 * @brief Header file for the PMOD_BTN_Interrupt driver.
 *
 * This file contains the function definitions for the PMOD_BTN_Interrupt driver.
 * It interfaces with the PMOD BTN module. The following pin is used:
 * - PMOD BTN0 (PD2)
 * - PMOD BTN1 (PD3)
 *
 * It configures the pins to trigger interrupts on rising edges. The PMOD BTN
 * push buttons operate in an active high configuration.
 *
 * @Irvin
 */

#include "TM4C123GH6PM.h"

// Declare pointer to the user-defined task
extern void (*PMOD_BTN_Task)(uint8_t pmod_btn_state);

/**
 * @brief Declares GPIO pins PD2 to PD3 to operate as interrupt enables. This pins work with PMOD buttons.
 * @param Use a pointer to point to the address of a function that takes a uint8_t variable.
 * 
 */
void PMOD_BTN_Interrupt_Init(void(*task)(uint8_t));

/**
 * @brief Reads the current state of the PMOD buttons.
 * @param Reads the status of PD2 to PD3.
 * @return returns the status as an uint8_t value. 
 */
uint8_t PMOD_BTN_Read(void);

/**
 * @brief Interrupt Service Routine for port D.
 * @param Thw ISR is triggered whenever any of the PMOD generates an edge detection. 
 */
void GPIO_Handler(void);