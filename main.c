/*******************************************************************************
 * File Name    : UART.c                                                       *
 * Description  : Source file for UART module                                  *
 * Created on   : 9/21/2019 4:00 PM                                            *
 * Author       : Ahmed Ekram, Ahmed Gaber (Bopbo) and Saif El-Deen Moustafa   *
 *******************************************************************************/

/*******************************************************************************
 *                          Included Libraries                                 *
 *******************************************************************************/
#include "timer.h"
#include "button.h"
#include "UART.h"


/******************************************************************************
 *     This example demonstrates how to send a string of data to the UART.     *
 *******************************************************************************/
int main (void)
{
    volatile static uint32_t x=0;
    // Enable the GPIO port that is used for the on-board LED.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //Unlocking switch lock
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK)= GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR)=0X01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK)=0;
    //GPIODirModeSet(GPIO_PORTF_BASE,GPIO_PIN_0,GPIO_DIR_MODE_IN);
    //GPIODirModeSet(GPIO_PORTF_BASE,GPIO_PIN_4,GPIO_DIR_MODE_IN);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_0 | GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
    // Set the clocking to run directly from the crystal.
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    // Enable the GPIO pins for the LED (PF2).
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_3);

    // Enable the peripherals used by this example.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    // Enable processor interrupts.
    IntMasterEnable();

    // Enable processor interrupts.
    UARTInit1 ();
    UARTInit0 ();
    Button_Init();
        while(1)
        {
            Button_press();
        }

}
/*******************************************************************************/
