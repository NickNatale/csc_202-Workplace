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
    motor0_pwm_init(4000, 0);
    keypad_init();


    run_lab8_p2();
    // Endless loop to prevent program from ending
 while (1){
 }

} /* main */

void run_lab8_p2(void){
    while (!done){
        uint8_t get_keypressed = keypad_scan();
        uint8_t key_multiple = 100/16;
        uint8_t duty_cycle = 0;
        if(get_keypressed != 16){
            duty_cycle = get_keypressed * key_multiple;
            lcd_write_byte(duty_cycle);
            lcd_write_string("%");
            motor0_set_pwm_dc(duty_cycle);
            wait_no_key_pressed();
        }
         switch (state){
            case(MOTOR_OFF1):
            //reads the low values on the switch
                led_off(LED_BAR_LD0_IDX);
                led_off(LED_BAR_LD1_IDX);
                if(g_SW2_pressed == true){
                    state = MOTOR_CW;
                    g_SW2_pressed = false;
                }
                if(g_SW1_pressed == true)
                {
                    break;
                }
            case(MOTOR_CW):
            // reads the high values on the switch
                led_on(LED_BAR_LD0_IDX);
                leds_on(LED_BAR_LD1_IDX);
                if(g_SW2_pressed == true){
                    state = MOTOR_OFF2;
                    g_SW2_pressed = false;
                }
                if(g_SW1_pressed == true)
                {
                    break;
                }
            case(MOTOR_OFF2):
            //displays the numbers on the 7seg display
                led_off(LED_BAR_LD0_IDX);
                led_off(LED_BAR_LD1_IDX);
                if(g_SW2_pressed == true){
                    state = MOTOR_CCW;
                    g_SW2_pressed = false;
                }
                if(g_SW1_pressed == true)
                {
                    break;
                }
                loop_count += 1;
            case(MOTOR_CCW):
                led_on(LED_BAR_LD1_IDX);
                led_off(LED_BAR_LD0_IDX);
                if(g_SW2_pressed == true){
                    state = MOTOR_OFF1;
                    g_SW2_pressed = false;
                }
                if(g_SW1_pressed == true)
                {
                    break;
                }
            default:
                leds_off();
                state = MOTOR_OFF1;
         }
         msec_delay(100);
         g_SW2_pressed = false;
    }
    
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
                    g_SW2_pressed = true;
                    GPIOA->CPU_INT.ICLR = GPIO_CPU_INT_ICLR_DIO21_CLR;
                }
                break; 

            default:
                break;
        }
    }while (group_iidx_status != 0);
}


