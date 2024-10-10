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
void run_lab7_p2(void);
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
    dipsw_init();
    led_disable();
    seg7_init();
    sys_tick_init(SYST_TICK_PERIOD_COUNT);
    I2C_init();
    lcd1602_init();


    run_lab7_p1();
    lcd_set_ddram_addr(LCD_LINE2_ADDR + LCD_CHAR_POSITION_4);
    lcd_write_string("Press PB2");
    while(is_pb_up(PB2_IDX));
    msec_delay(20);
    while (is_pb_down(PB2_IDX));
    msec_delay(20);
    lcd_clear();
    lcd_write_string("Running Part 2");
    msec_delay(1000);
    run_lab7_p2();
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

void run_lab7_p1(void)
{
    lcd_clear();
    bool done = false;
    while (!done) {
        uint32_t addr = 0;
        for (addr = 0x4F; addr >= 0x40 && !done; addr--){
            lcd_clear();
            lcd_set_ddram_addr(addr);
            lcd_write_string("Microcontrollers are fun.");
            msec_delay(100);
            if(is_pb_down(PB2_IDX)){
                while(is_pb_up(PB2_IDX));
                msec_delay(20);
                while(is_pb_down(PB2_IDX));
                done = true;
                lcd_clear();
                seg7_off();
                sys_tick_disable();
                lcd_write_string("Part 1 Done.");
            }
        }
        uint32_t idx = 0;
        while ("Microcontrollers are fun."[idx] != '\0' && !done) {
            lcd_clear();
            lcd_set_ddram_addr(0x40);
            lcd_write_string("Microcontrollers are fun." + idx);
            msec_delay(100);
            idx++;
            if(is_pb_down(PB2_IDX)){
                while(is_pb_up(PB2_IDX));
                msec_delay(20);
                while(is_pb_down(PB2_IDX));
                done = true;
                lcd_clear();
                seg7_off();
                sys_tick_disable();
                lcd_write_string("Part 1 Done.");
            }
        }
    }
}

void run_lab7_p2(void){
    lcd_clear();
    bool done = false;
    while (!done) {
        uint32_t addr = 0;
        for (addr = 0x4F; addr >= 0x40 && !done; addr--){
            lcd_clear();
            lcd_set_ddram_addr(addr);
            lcd_write_string("“Microcontrollers are fun. I love programming in MSPM0+ assembly code!!!");
            msec_delay(100);
            if(is_pb_down(PB2_IDX)){
                while(is_pb_up(PB2_IDX));
                msec_delay(20);
                while(is_pb_down(PB2_IDX));
                done = true;
                lcd_clear();
                seg7_off();
                sys_tick_disable();
                lcd_write_string("Part 2 Done.");
            }
        }
        uint32_t idx = 0;
        while ("“Microcontrollers are fun. I love programming in MSPM0+ assembly code!!!"[idx] != '\0' && !done) {
            lcd_clear();
            lcd_set_ddram_addr(0x40);
            lcd_write_string("“Microcontrollers are fun. I love programming in MSPM0+ assembly code!!!" + idx);
            msec_delay(100);
            idx++;
            if(is_pb_down(PB2_IDX)){
                while(is_pb_up(PB2_IDX));
                msec_delay(20);
                while(is_pb_down(PB2_IDX));
                done = true;
                lcd_clear();
                seg7_off();
                sys_tick_disable();
                lcd_write_string("Part 2 Done.");
            }
        }
    }
}