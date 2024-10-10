//*****************************************************************************
//*****************************    C Source Code    ***************************
//*****************************************************************************
//  DESIGNER NAME:  Nick Natale
//
//       LAB NAME:  7 p3
//
//      FILE NAME:  main.c
//
//-----------------------------------------------------------------------------
//
// DESCRIPTION:
//    This program serves as a ... 
//
//*****************************************************************************
//*****************************************************************************

//-----------------------------------------------------------------------------
// Loads standard C include files
//-----------------------------------------------------------------------------

#include <stdio.h>

//-----------------------------------------------------------------------------
// Loads MSP launchpad board support macros and definitions
//-----------------------------------------------------------------------------
#include <ti/devices/msp/msp.h>
#include "LaunchPad.h"
#include "clock.h"
#include "lcd1602.h"

//-----------------------------------------------------------------------------
// Define function prototypes used by the program
//-----------------------------------------------------------------------------
void SysTick_Handler(void);
void run_lab7_p3(void);
//-----------------------------------------------------------------------------
// Define symbolic constants used by the program
//-----------------------------------------------------------------------------
#define MSPM0_CLOCK_FREQUENCY                                             (40E6)
#define SYST_TICK_PERIOD                                              (10.25E-3)
#define SYST_TICK_PERIOD_COUNT        (SYST_TICK_PERIOD * MSPM0_CLOCK_FREQUENCY)
#define NUM_STATES                18


//-----------------------------------------------------------------------------
// Define global variables and structures here.
// NOTE: when possible avoid using global variables
//-----------------------------------------------------------------------------
const uint8_t seg7_letter_code[] =
{
    0x6D, 0x00, 0x6D, 0x00, 0x6D, 0x00,   //S
    0x3F, 0x00, 0x3F, 0x00, 0x3F, 0x00,   //O
    0x6D, 0x00, 0x6D, 0x00, 0x6D, 0x00    //S
};
const uint8_t delay_count[] =
{
    0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x18, // dots
    0x24, 0x24, 0x24, 0x24, 0x24, 0x24, // dash
    0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x30, // dots
};

// Define a structure to hold different data types

int main(void)
{
    clock_init_40mhz();
    launchpad_gpio_init();
    //inits
    led_init();
    dipsw_init();
    led_disable();
    seg7_init();
    sys_tick_init(SYST_TICK_PERIOD_COUNT);
    I2C_init();
    lcd1602_init();
 
 // Endless loop to prevent program from ending
    run_lab7_p3();
    while (1);

} /* main */

void SysTick_Handler(void)
{
    uint16_t delay_time = 1;
    uint16_t code_index = 0;
    uint16_t dip_num = dipsw_read();
    uint8_t display_num = 0;
    for (int i = 0; i < sizeof(int) * 8; i++)
    {
        if (dip_num & (1 << i)){
            display_num++;
        }
    }
    delay_time--;
    if (delay_time == 0)
    {
        seg7_off();
        seg7_hex(display_num, SEG7_DIG0_ENABLE_IDX);

        delay_time = delay_count[code_index];
        code_index++;

        if(code_index == NUM_STATES)
        {
            code_index == 0;
        }
    }
}

void run_lab7_p3(void){
    lcd_clear(); // clear lcd
    uint8_t timer_count = 0; //set timer
    while(timer_count < 100){
        // clears then writes the current timer to the center of line 1
        lcd_clear();
        lcd_set_ddram_addr(LCD_LINE1_ADDR + LCD_CHAR_POSITION_8);
        lcd_write_byte(timer_count);
        msec_delay(200);
        timer_count += 1;
        if (timer_count == 100){
            // if timer runs out reset
            timer_count = 0;
        }
    }
    lcd_clear();
    lcd_write_string("Part 3 Finished.");
}