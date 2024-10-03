//*****************************************************************************
//*****************************    C Source Code    ***************************
//*****************************************************************************
//  DESIGNER NAME:  Nick natale
//
//       LAB NAME:  lab 6
//
//      FILE NAME:  main.c
//
//-----------------------------------------------------------------------------
//
// DESCRIPTION:
//    This program serves as a way to interface with the LCD on the launchboard
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
void run_lab6_p1(void);

//-----------------------------------------------------------------------------
// Define symbolic constants used by the program
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Define global variables and structures here.
// NOTE: when possible avoid using global variables
//-----------------------------------------------------------------------------


// Define a structure to hold different data types

int main(void)
{
    clock_init_40mhz();
    launchpad_gpio_init();
    I2C_init();
    lcd1602_init();
    dipsw_init();

    
    /* clear and set pos to 1: lcd_clear();*/
    /* write the message: lcd_write_doublebyte(value 16 bit)*/
    /* set position  for next line: lcd_set_ddram_addr(LCD_LINE2_ADDR + LCD_CHAR_POSITION_4); */
    /* write message 2: lcd_write_string(msg2); */

    /* for(idx = 0 to 25)
        write_char('A' + i)
        if(idx == LCD_CHAR_PER_LCD_LINE -1)
            */
    run_lab6_p1();
 // Endless loop to prevent program from ending
    while (1);

} /* main */

void run_lab6_p1(){
    lcd_clear();
    uint8_t idx = 0;
    for(idx = 0; idx <= 25; idx++){
        lcd_write_char('A' + idx);
        if(idx == CHARACTERS_PER_LCD_LINE - 1){
            lcd_set_ddram_addr(LCD_LINE2_ADDR + LCD_CHAR_POSITION_4);
        }
    }
}

void run_lab6_p2(void){
    uint32_t thirtytwo_bit_num = 1234567890;
    uint16_t sixteen_bit_num = 12345;
    uint8_t eight_bit_num = 123;
    lcd_clear();
    lcd_write_quadbyte(thirtytwo_bit_num);
    lcd_set_ddram_addr(LCD_LINE2_ADDR + LCD_CHAR_POSITION_4);
    lcd_write_doublebyte(sixteen_bit_num);
    lcd_set_ddram_addr(LCD_LINE1_ADDR + LCD_CHAR_POSITION_4);
    lcd_write_byte(eight_bit_num);
    while(is_pb_down(0) == false)
    {
        
    }

}
