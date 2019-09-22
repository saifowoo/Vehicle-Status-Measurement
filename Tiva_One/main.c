/*******************************************************************************
 * File Name    : main.c                                                       *
 * Description  : Source file for UART module                                  *
 * Created on   : 9/21/2019 4:00 PM                                            *
 * Author       : Ahmed Ekram, Ahmed Gaber (Bopbo) and Saif El-Deen Moustafa   *
 *******************************************************************************/

/*******************************************************************************
 *                          Included Libraries                                 *
 *******************************************************************************/
#include "UART.h"

#include "timer.h"

/******************************************************************************
 *     This example demonstrates how to send a string of data to the UART.     *
 *******************************************************************************/
volatile uint32_t Timer_Counter=0;
uint32_t Temp_Reading;
uint8_t speed=0;
volatile uint8_t status=0;
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
    Timer0_Init();
    // Prompt for text to be entered.
    UARTSend((uint8_t *)"Enter text: ", 12);
    //GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0XFF);
    // Loop forever echoing data through the UART.
    //UARTprintf("\nahmed\n");
    uint8_t initial_flag=0,i;
    while(1)
    {
      switch(status)
      {
      case 0:

        if(initial_flag==0)
        {
            for(i=0;i<9;i++)
            {
                while(UARTCharsAvail(UART0_BASE))
                {
                    // Read the next character from the UART and write it back to the UART.
                   // UARTCharPutNonBlocking(UART0_BASE,UARTCharGetNonBlocking(UART0_BASE));
                   Temp_Reading= UARTCharGet(UART0_BASE+UART_O_DR);
                    if(i==0)
                    {
                        Timer_Counter+=36000*Temp_Reading;
                    }
                    else if(i==1)
                    {
                        Timer_Counter+=3600*Temp_Reading;
                    }
                    else if(i==2)
                    {
                        Timer_Counter+=600*Temp_Reading;
                    }
                    else if(i==3)
                    {
                        Timer_Counter+=60*Temp_Reading;
                    }
                    else if(i==4)
                    {
                        Timer_Counter+=10*Temp_Reading;
                    }
                    else if(i==5)
                    {
                        Timer_Counter+=Temp_Reading;
                    }
                    else if(i==6)
                    {
                        speed+=100*Temp_Reading;
                    }
                    else if(i==7)
                    {
                        speed+=10*Temp_Reading;
                    }
                    else if(i==8)
                    {
                        speed+=1*Temp_Reading;
                    }

                    // Blink the LED to show a character transfer is occuring.
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);

                    // Delay for 1 millisecond.  Each SysCtlDelay is about 3 clocks.
                    SysCtlDelay(SysCtlClockGet() / (1000 * 3));

                    // Turn off the LED
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
                }
            }
            initial_flag=1;
        }
        else if(initial_flag==1)
        {
            if(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0)==0)
            {
                if(speed==255)
                {
                    speed=255;
                }
                else
                {
                    speed++;
                }
            }

            else if(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4)==0)
            {
                if(speed==0)
                {
                    speed=0;
                }
                else
                {
                    speed--;
                }
            }
        }
        break;
        case 1:
            UARTCharPut(UART1_BASE,Timer_Counter);
            UARTCharPut(UART1_BASE,speed);
            while(status==1)
            {
                if(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0)==0)
                {
                    if(speed==255)
                    {
                        speed=255;
                    }
                    else
                    {
                        speed++;
                    }
                    UARTCharPut(UART1_BASE,Timer_Counter);
                    UARTCharPut(UART1_BASE,speed);
                }
                else if(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4)==0)
                {
                    if(speed==0)
                    {
                        speed=0;
                    }
                    else
                    {
                        speed--;
                    }
                    UARTCharPut(UART1_BASE,Timer_Counter);
                    UARTCharPut(UART1_BASE,speed);
                }
            }
            break;
      }



//
//
//        if(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0)!=0)
//        {
//            x++;
//            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0xff);
//            //UARTSend(x, 12);
//            //UARTprintf("%d",x);
//        }
//        else
//        {
//            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2,0);
//        }
//        if(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4)!=0)
//        {
//            x--;
//            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0xff);
//            //  UARTprintf("%d",x);
//        }
//        else
//        {
//            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,0);
//        }
//        UARTCharPut(UART1_BASE,0x08);
//
//        // Delay for 1 millisecond.  Each SysCtlDelay is about 3 clocks.
//        SysCtlDelay(SysCtlClockGet() / (10));
    }
}
/*******************************************************************************/
