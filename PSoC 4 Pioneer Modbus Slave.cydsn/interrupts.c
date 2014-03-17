/* ========================================
 *
 * Copyright Sam Walsh, 2014
 * All Rights Reserved.
 *
 * Interrupts.c Contains all the interrupts, put your own in here..
 *
 * ========================================
*/
#include <project.h>
#include <cydevice_trm.h>
#include <CyLib.h>
#include <interrupts.h>
#include <ModbusUART.h>
#include <MessageTimer.h>
#include <Modbus.h>

volatile uint8 messageTimerFlag;
volatile uint8 messageReceivedFlag;

extern unsigned char response[125]; //Enough to return all holding-r's
extern unsigned char received[125]; //Enough to write all holding-r's 


CY_ISR(messageReceived_isr) 
{
    decodeMessage();  
    //Clear the interrupt//
    uint32 source;
    messageReceivedFlag = 1;
    source = ModbusUART_GetRxInterruptSourceMasked();
    ModbusUART_ClearRxInterruptSource(source);
}

CY_ISR(endOfMessage_isr) 
{
    checkIfEndOfMessage();
    //Clear the interrupt//
    uint32 source = 0;
    messageTimerFlag = 1;
    source = MessageTimer_GetInterruptSource();
    MessageTimer_ClearInterrupt(source);
}

/* [] END OF FILE */
