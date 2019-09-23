

#include "button.h"




void Button_Init(void)
{
    /*
     * initialize port f
     */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}


void Button_press(void)
{

    if(TimeState == END_TIME)
    {
        if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) == 0)
        {
            UARTCharPut(UART3_BASE, START_TIME);
            TimeState = START_TIME;
            UARTprintf("Measure start\n");
            while(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) == 0);
        }
        else
        {
            /*Do nothing*/
        }
    }
    else if(TimeState == START_TIME)
    {
        if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) ==0)
        {
            UARTCharPut(UART3_BASE, END_TIME);
            RecentTime = UARTCharGet (UART3_BASE);
            RecentSpeed = UARTCharGet (UART3_BASE );
            Distance += ((RecentTime-OldTime)*OldSpeed);
            OldSpeed = RecentSpeed;
            OldTime = RecentTime;
            UARTprintf("Time now: %d\n", RecentTime);
            UARTprintf("All Distance: %d\n", Distance);

            while(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 0);
        }
        else
        {
            /*Do Nothing*/
        }
    }

}
