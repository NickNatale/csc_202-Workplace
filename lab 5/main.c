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
#include "LaunchPad.h"


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
