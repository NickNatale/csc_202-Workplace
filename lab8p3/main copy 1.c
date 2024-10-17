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
#include "ti/devices/msp/m0p/mspm0g350x.h"

//-----------------------------------------------------------------------------
// Define function prototypes used by the program
//-----------------------------------------------------------------------------
void OPA0_init(void);
void run_lab8_p2(void);
void GROUP1_IRQHandler(void);
//-----------------------------------------------------------------------------
// Define symbolic constants used by the program
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Define global variables and structures here.
// NOTE: when possible avoid using global variables
//-----------------------------------------------------------------------------
bool g_SW1_pressed = false;
bool g_SW2_pressed = false;
//adc/455 makes 0-8
// Define a structure to hold different data types

int main(void)
{
    launchpad_gpio_init();
    I2C_init();
    lcd1602_init();
    clock_init_40mhz();
    dipsw_init();
    led_init();
    led_enable();
    ADC0_init(ADC12_MEMCTL_VRSEL_INTREF_VSSA);
    GPIOB->POLARITY31_16 = GPIO_POLARITY31_16_DIO18_RISE;
    GPIOB->CPU_INT.ICLR = GPIO_CPU_INT_ICLR_DIO18_CLR;
    GPIOB->CPU_INT.IMASK = GPIO_CPU_INT_IMASK_DIO18_SET;
    NVIC_SetPriority(GPIOB_INT_IRQn, 2);
    NVIC_EnableIRQ(GPIOB_INT_IRQn);
    GPIOA->POLARITY15_0 = GPIO_POLARITY15_0_DIO15_RISE;
    GPIOA->CPU_INT.ICLR = GPIO_CPU_INT_ICLR_DIO15_CLR;
    GPIOA->CPU_INT.IMASK = GPIO_CPU_INT_IMASK_DIO15_SET;
    NVIC_SetPriority(GPIOA_INT_IRQn, 2);
    NVIC_EnableIRQ(GPIOA_INT_IRQn);
    run_lab8_p2();
    // Endless loop to prevent program from ending
 while (1){
 }

} /* main */

void run_lab8_p2(void){

    bool done = false;
    msec_delay(20);
    uint16_t Adc_value = ADC0_in(7);
    while(!done){
        if (g_SW1_pressed){
        printf("SW1 detected\n");
        g_SW1_pressed = false;
        done = true;
        }
        if (g_SW2_pressed){
        printf("SW2 detected\n");
        g_SW2_pressed = false;
        }
        Adc_value = ADC0_in(7);
        uint8_t i = 0;
        leds_off();
        for (uint8_t LED_num = Adc_value / 455; LED_num > i; i++){
            led_on(i);
        }
        lcd_set_ddram_addr(LCD_LINE1_ADDR);
        lcd_write_string("ADC =");
        lcd_write_doublebyte(Adc_value);
    }
    lcd_clear();
    lcd_write_string("Program Stopped");
    leds_off();
}

void GROUP1_IRQHandler(void)
{
    uint32_t group_iidx_status;
    uint32_t gpio_mis;

    do {
        group_iidx_status = CPUSS->INT_GROUP[1].IIDX;
        switch (group_iidx_status)
        {
            case(CPUSS_INT_GROUP_IIDX_STAT_INT1):
                gpio_mis = GPIOB->CPU_INT.MIS;
                if ((gpio_mis & GPIO_CPU_INT_MIS_DIO18_MASK) == GPIO_CPU_INT_MIS_DIO18_SET){
                    g_SW1_pressed = true;
                    GPIOB->CPU_INT.ICLR = GPIO_CPU_INT_ICLR_DIO18_CLR;
                }
                break;
            case (CPUSS_INT_GROUP_IIDX_STAT_INT0):
                gpio_mis = GPIOA->CPU_INT.MIS;
                if ((gpio_mis & GPIO_CPU_INT_MIS_DIO15_MASK) == GPIO_CPU_INT_MIS_DIO15_SET)
                {
                    uint8_t temp_in_F = 0;
                    float temp = 0;
                    uint16_t temp_val = 0;
                    g_SW2_pressed = true;
                    GPIOA->CPU_INT.ICLR = GPIO_CPU_INT_ICLR_DIO21_CLR;
                    lcd_set_ddram_addr(LCD_LINE2_ADDR);
                    lcd_write_string("Temp = ");
                    temp_val = ADC0_in(5);
                    temp = thermistor_calc_temperature(temp_val);
                    temp_in_F = (temp * 9/5) + 32;
                    lcd_write_doublebyte(temp_in_F);
                    lcd_write_char(0xDF);
                    lcd_write_string("F");
                }
                break; 

            default:
                break;
        }
    }while (group_iidx_status != 0);
}