//*****************************************************************************
//*****************************    C Source Code    ***************************
//*****************************************************************************
//  DESIGNER NAME:  Nick Natale
//
//       LAB NAME:  Lab 5
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


//-----------------------------------------------------------------------------
// Define function prototypes used by the program
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Define symbolic constants used by the program
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Define global variables and structures here.
// NOTE: when possible avoid using global variables
//-----------------------------------------------------------------------------
typedef enum 
{
     get_low,
     get_high,
     display
} fsm_states_t;
fsm_states_t state;

// Define a structure to hold different data types

int main(void)
{
    //initialize launchpad switches and buttons and keypad
    launchpad_gpio_init();
    lpsw_init();
    dipsw_init();
    keypad_init();
 // Endless loop to prevent program from ending
 while (1);

} /* main */

void run_lab_5(void){
    uint32_t loop_count = 0;
    uint32_t p1_iterations = 4;
    bool display_on = false;
    while (loop_count < p1_iterations) {
        while (is_pb_down == true) {
            if (display_on == false) {
                /* turn on display and show 3*/
                seg7_on(3,0);
                display_on = true;
            }else {
                /* turn off display*/
                display_on = false;
                seg7_off();
            }
            loop_count += 1;
            while(is_pb_down == true){
                msec_delay(10);
                // checks to see if button is being held down
            }
            msec_delay(10);
            /* delay of 10 ms*/
        }
    }

}
void run_lab_5p2(void){
    uint32_t loop_count = 0;
    uint8_t display_number = 0;
    uint8_t dip_sw_val = 0;
     while (loop_count < 4){
         switch (state){
            case(get_low):
                dip_sw_val = dipsw_read();
                 display_number |= dip_sw_val;
                if(is_lspw_down(LP_SW2_IDX) == true){
                    state = get_high;
                }
            case(get_high):
                dip_sw_val = dipsw_read();
                display_number |= (dip_sw_val << 4);
                if(is_lspw_down(LP_SW2_IDX) == true){
                    state = display;
                }
            case(display):
                if(is_pb_down == true){
                    seg7_on(display_number, SEG7_DIG2_ENABLE_IDX);
                    while(is_lspw_down == true){
                        msec_delay(10);
                    }
                } else{
                    seg7_on(display_number, SEG7_DIG0_ENABLE_IDX);
                    while(is_lspw_down == true){
                        msec_delay(10);
                    }
                }
                loop_count += 1;
         }
    }
}
