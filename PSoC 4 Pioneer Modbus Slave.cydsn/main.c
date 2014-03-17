/* ========================================
 *
 * Copyright Sam Walsh, 2014
 * All Rights Reserved.
 *
 * main.c put your code in here after the processMessage();
 *
 * ========================================
*/
#include <project.h>
#include <interrupts.h>
#include <modbus.h>
#define  forever    1

extern unsigned int  holdingReg[50];
extern unsigned char coils[50];
extern unsigned char received[125];
extern unsigned char response[125]; //Enough to return all holding-r's
extern uint8 modbusMessage;

//Main loop//
int main()
{   
    /*Clear received array */
    memset(&received[0], 0, sizeof(received));
       
    /* Start the SCB UART, Timer and its interrupt */
    ModbusUART_Start();
    MessageReceived_StartEx(messageReceived_isr);  
    
    writeEnable_Write(0); // receive mode

    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
    
    while(forever)
    {       
        if(modbusMessage)
        {
          processMessage();
        }
        
        //Put your code here, just make sure you use holdingRegs and coils for your variables
        //Eg "holdingReg[0] = temperature;"
        //or "coils[1] = switchVal or LED = coils[2];
    }
}

