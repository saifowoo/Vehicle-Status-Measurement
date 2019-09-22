/*******************************************************************************
 * File Name    : UART.h                                                      *
 * Description  : Source file for UART module                                  *
 * Created on   : 9/21/2019 4:00 PM                                            *
 * Author       : Ahmed Ekram, Ahmed Gaber (Bopbo) and Saif El-Deen Moustafa   *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include <stdbool.h>

#include "driverlib/sysctl.h"
#include "driverlib/debug.h"

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"

#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"

#include "inc/hw_timer.h"
#include "driverlib/timer.h"

#include "inc/hw_uart.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"

extern volatile uint8_t status;
/******************************************************************************
 *                         The UART1 initialization.                           *
 *******************************************************************************/
extern void UARTInit0 (void);
/*******************************************************************************/

/******************************************************************************
 *                         The UART1 initialization.                           *
 *******************************************************************************/
extern void UARTInit1 (void);
/*******************************************************************************/

/******************************************************************************
 *                        The UART0 interrupt handler.                          *
 *******************************************************************************/
//extern void UARTIntHandler (void);
/*******************************************************************************/

/******************************************************************************
 *                        The UART1 interrupt handler.                          *
 *******************************************************************************/
//extern void UARTIntHandler1 (void);
/*******************************************************************************/

/******************************************************************************
 *                        Send a string to the UART.                           *
 *******************************************************************************/
void UARTSend (const uint8_t *pui8Buffer, uint32_t ui32Count);
/*******************************************************************************/

#endif /* UART_H_ */
