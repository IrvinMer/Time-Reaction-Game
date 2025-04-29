/**
 * @file main.c
 *
 * @brief Main source code for the Reaction Timer Game.
 *
 * This program implements a reaction time testing game using the TM4C123G LaunchPad.
 * It interfaces with the following hardware:
 *  - User LED on breadboard
 *  - PMOD Button module (BTN1=Stop, BTN0=Start)
 *  - EduBase Board Seven-Segment Display (shows reaction time)
 *
 * Game operation:
 *  1. Press BTN0 to start - LED turns red for a random delay (500-7000ms)
 *  2. When LED turns green, react by pressing BTN1 as quickly as possible
 *  3. The display shows your reaction time count
 *
 * @note The program uses Timer 0A for periodic interrupts to handle timing operations.
 *
 * @author Irvin
 */
#include "TM4C123GH6PM.h"
#include "GPIO.h"
#include "SysTick_Delay.h"
#include "Seven_Segment_Display.h"
#include "Timer_0A_Interrupt.h"
#include "PMOD_BTN_Interrupt.h"
#include "PWM_Clock.h"
#include "PWM0_2.h"
#include "stdlib.h"  


void Timer_0A_Periodic_Task(void);         
void PMOD_BTN_Int_Handler(uint8_t pmod_btn_status);  


// Value shown on display
static uint32_t count = 0;   
// 0=off, 1=countdown, 2=running
uint8_t timer0A_enabled = 0;
// Countdown time in ms
uint32_t delay = 0;               

int main(void) 
{                                 
  Seven_Segment_Display_Init();                      
  SysTick_Delay_Init();                              
  PMOD_BTN_Interrupt_Init(&PMOD_BTN_Int_Handler);    
  Timer_0A_Interrupt_Init(&Timer_0A_Periodic_Task);  

  // Setup PWM for LED brightness control
  PWM_Clock_Init();
	// Start PWM at 0% duty
  PWM0_2_Init(62500, 0);                   

  while (1) {
    // Keep updating display with current count
    Seven_Segment_Display(count);
  }
}

void PMOD_BTN_Int_Handler(uint8_t pmod_btn_status)
{
  switch(pmod_btn_status)
  {
		// BTN0 (PD2) is pressed
    case 0x04:
		{			
			PWM0_2_Update_Duty_Cycle(56250);     
			 // Turn on Red LED light
      TURN_RED_LED_ON();    
			// Random wait time
      delay = (rand() % (7000 - 500 + 1)) + 500;  
			// Start countdown
      timer0A_enabled = 1;                        
      break;
		}
		// BTN1 (PD3) is pressed
    case 0x08:
		{	 // Stop the timer	
       timer0A_enabled = 0;                       
      break;
	}
  }
}

void Timer_0A_Periodic_Task(void) 
{
  // Handle countdown mode
  if (timer0A_enabled == 1)                
  {
    if (delay > 0)
    {
      delay--;                             
    }
    else
    {
			// Switch to green
      TURN_GREEN_LED_ON();
      // Start counter operation			
      timer0A_enabled = 2; 
			// Reset counter
      count = 0;                           
    }
  }

  // Handle normal operation mode
  if (timer0A_enabled == 2)                
  {
    count++;                   

      if (count >= 5000)                   
      {
        count = 0;
      }
    }
  }
