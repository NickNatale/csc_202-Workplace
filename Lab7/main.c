//*****************************************************************************
//*****************************    C Source Code    ***************************
//*****************************************************************************
//  DESIGNER NAME:  Nicholas Natale
//
//       LAB NAME:  Lab 7 p1
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
void run_lab7_p1(void);
void SysTick_Handler(void);
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

    led_init();
    led_disable();
    seg7_init();
    sys_tick_init(SYST_TICK_PERIOD_COUNT);
    lcd1602_init();

    run_lab7_p1();
 // Endless loop to prevent program from ending
 while (1);

} /* main */

void SysTick_Handler(void)
{
    static uint16_t delay_time = 1;
    static uint16_t code_index = 0;

    delay_time--;
    if (delay_time == 0)
    {
        seg7_on(seg7_letter_code[code_index], SEG7_DIG0_ENABLE_IDX);

        delay_time = delay_count[code_index];
        code_index++;

        if(code_index == NUM_STATES)
        {
            code_index == 0;
        }
    }
}
void GROUP1_IRQHandler(void)
{
    uint32_t group_iidx_status;
    uint32_t gpio_mis;

    do {
        group_iidx_status = CPUSS->INT_GROUP[1].IIDX
        switch (group_iidx_status)
        {
            case(CPUSS_INT_GROUP_IIDX_STAT_INT0):
                gpio_mis = GPIOA->CPU_INT.MIS;
                if ((gpio_mis & GPIO_CPU_INT_MIS_DIO18_MASK) == GPIO_CPU_INT_MIS_DIO18_SET){
                    g_SW1_pressed = true;
                    GPIOA->CPU_INT.ICLR = GPIO_CPU_INT_ICLR_DIO18_CLR;
                }
                break;
            case (CPUSS_INT_GROUP_IIDX_STAT_INT1):
                gpio_mis = GPIOB->CPU_INT.MIS;
                if ((gpio_mis & GPIO_CPU_INT_MIS_DIO21_MASK) == GPIO_CPU_INT_MIS_DIO21_SET)
                {
                    g_SW2_pressed = true;
                    GPIOB->CPU_INT.ICLR = GPIO_CPU_INT_ICLR_DIO21_CLR;
                }
                break;

            default:
                break;
        }
    }while (group_iidx_status != 0);
}

void run_lab7_p1(void)
{
    lcd_clear();
    bool done = false;
    while (!done) {
        uint32_t addr = 0;
        for (addr = 0x4F; addr >= 0x40; addr--){
            lcd_set_ddram_addr(addr);
            lcd_write_string("Microcontrollers are fun.");
            if(is_pb_down(PB2_IDX)){
                while(is_pb_down(PB2_IDX));
                done = true;
            }
        }
    }
        uint32_t idx = 0;
        while ("Microcontrollers are fun."[idx] != '\0') {
            lcd_set_ddram_addr(0x40);
            lcd_write_string("Microcontrollers are fun." + idx);
            idx++;
    }
    
    }



}