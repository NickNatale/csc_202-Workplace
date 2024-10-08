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
void run_lab6_p2(void);
void run_lab6_p3(void);
void run_lab6_p4(void);
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
    keypad_init();

    
    /* clear and set pos to 1: lcd_clear();*/
    /* write the message: lcd_write_doublebyte(value 16 bit)*/
    /* set position  for next line: lcd_set_ddram_addr(LCD_LINE2_ADDR + LCD_CHAR_POSITION_4); */
    /* write message 2: lcd_write_string(msg2); */

    /* for(idx = 0 to 25)
        write_char('A' + i)
        if(idx == LCD_CHAR_PER_LCD_LINE -1)
            */
    run_lab6_p1();
    while(is_pb_up(PB2_IDX));
    msec_delay(20);
    while (is_pb_down(PB2_IDX));
    msec_delay(20);
    lcd_clear();
    lcd_write_string("Running Part 2");
    msec_delay(1000);
    run_lab6_p2();
    lcd_set_ddram_addr(LCD_LINE2_ADDR + LCD_CHAR_POSITION_4);
    lcd_write_string("Press PB2");
    while(is_pb_up(PB2_IDX));
    msec_delay(20);
    while (is_pb_down(PB2_IDX));
    msec_delay(20);
    lcd_clear();
    lcd_write_string("Running Part 3");
    msec_delay(1000);
    run_lab6_p3();
    lcd_set_ddram_addr(LCD_LINE2_ADDR + LCD_CHAR_POSITION_4);
    lcd_write_string("Press PB2");
    while(is_pb_up(PB2_IDX));
    msec_delay(20);
    while (is_pb_down(PB2_IDX));
    msec_delay(20);
    lcd_clear();
    lcd_write_string("Running Part 4");
    msec_delay(1000);
    run_lab6_p4();
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
    lcd_clear(); //clear lcd
    //each of the following while loops are to wait for debounce
    //and wait for the button to be released before continuing
    lcd_set_ddram_addr(LCD_LINE1_ADDR + LCD_CHAR_POSITION_4);
    lcd_write_quadbyte(thirtytwo_bit_num);
    while(is_pb_up(PB1_IDX));
    msec_delay(20);
    while (is_pb_down(PB1_IDX));
    msec_delay(20);
    // 16 bit num
    lcd_clear();
    lcd_set_ddram_addr(LCD_LINE2_ADDR + LCD_CHAR_POSITION_7);
    lcd_write_doublebyte(sixteen_bit_num);
    while(is_pb_up(PB1_IDX));
    msec_delay(20);
    while (is_pb_down(PB1_IDX));
    msec_delay(20);
    //eight bit num
    lcd_clear();
    lcd_set_ddram_addr(LCD_LINE1_ADDR + LCD_CHAR_POSITION_8);
    lcd_write_byte(eight_bit_num);
    while(is_pb_up(PB1_IDX));
    msec_delay(20);
    while (is_pb_down(PB1_IDX));
    msec_delay(20);
    lcd_clear();
    lcd_write_string("Part 2 Finished.");
}
void run_lab6_p3(void){
    lcd_clear(); // clear lcd
    uint8_t timer_count = 100; //set timer
    while(timer_count > 0){
        // clears then writes the current timer to the center of line 1
        lcd_clear();
        lcd_set_ddram_addr(LCD_LINE1_ADDR + LCD_CHAR_POSITION_8);
        lcd_write_byte(timer_count -1);
        msec_delay(200);
        timer_count -= 1;
        if (timer_count == 0){
            // if timer runs out reset
            timer_count = 100;
        }else if ((is_pb_down(PB1_IDX))) {
            while(is_pb_up(PB1_IDX));
            msec_delay(20);
            while (is_pb_down(PB1_IDX));
            msec_delay(20);
            timer_count = 100;
        }
        if (is_pb_down(PB2_IDX)) {
            while(is_pb_up(PB2_IDX));
            msec_delay(20);
            while (is_pb_down(PB2_IDX));
            msec_delay(20);
            timer_count = 0;
        }
    }
    lcd_clear();
    lcd_write_string("Part 3 Finished.");
}
void run_lab6_p4(void){
    lcd_clear();
    uint8_t keypress = 0;
    uint8_t idx = 0;
    bool done = false;
    while(done == false){
        keypress = keypad_scan();
        wait_no_key_pressed();
        if (keypress != 16) {
            hex_to_lcd(keypress);
            idx++;
        }
        if(idx > 16){
            lcd_set_ddram_addr(idx);
        }
        if (idx > 32) {
            lcd_clear();
            idx = 0;
            lcd_set_ddram_addr(idx);
            hex_to_lcd(keypress);
        }
        if(is_pb_down(PB1_IDX)){
            lcd_clear();
            idx = 0;
            lcd_set_ddram_addr(idx);
            hex_to_lcd(keypress);
        }
        if(is_pb_down(PB2_IDX)){
            done = true;
            lcd_clear();
            lcd_write_string("Program Stopped");
        }
    }

}