//*****************************************************************************
//*****************************    C Source Code    ***************************
//*****************************************************************************
//  DESIGNER NAME:  TBD
//
//       LAB NAME:  TBD
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
#include "adc.h"

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
    OPA0_init();
    ADC_init(ADC12_MEMCTL_VRSEL_INTREF_VSSA);
    I2C_init();
    lcd1602_init();
    launchpad_gpio_init();
    clock_init_40mhz();
    // Endless loop to prevent program from ending
 while (1);

} /* main */

void run_lab8_p1(void){
    bool done = false;
    uint16_t Adc_value = ADC0_in(7);
    while(!done){
        Adc_value = ADC0_in(7)
        if (Adc_value > 50){
            lcd_write_string("Status: Light");
        }else {
            lcd_write_string("Status: Dark");
        }
        lcd_set_ddram_addr(LCD_LINE2_ADDR);
        lcd_write_string("ADC =");
        lcd_write_doublebyte(Adc_value);
    }
}
void OPA0_init(void)
{
    OPA0->GPRCM.RSTCTL = (OA_RSTCTL_KEY_UNLOCK_W | OA_RSTCTL_RESETSTKYCLR_CLR |
                          OA_RSTCTL_RESETASSERT_ASSERT);
    OPA0->GPRCM.PWREN = (OA_PWREN_KEY_UNLOCK_W | OA_PWREN_ENABLE_ENABLE);

    clock_delay(24);

    OPA0->CFGBASE |= ((uint32_t) OA_CFGBASE_GBW_HIGHGAIN);

    OPA0->CFG |= (OA_CFG_GAIN_MINIMUM | OA_CFG_MSEL_NC | OA_CF_NSEL_EXTPIN0 |
                  OA_CFG_PSEL__EXTPIN0 | OA_CFG_OUTPIN_ENABLED | OA_CFG_CHOP_OFF);
                  )
    OPA0->CTL |= OA_CTL_ENABLE_ON;
}
