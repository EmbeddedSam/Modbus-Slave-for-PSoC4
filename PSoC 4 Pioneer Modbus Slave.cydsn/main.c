/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

uint8 volatile messageReceived = 0;

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    volatile uint8 messageReceived = 0;
    volatile uint8 endOfMessage,newMessage = 1;
    uint8 lastLed = 0;
    uint8 volatile ch;
    
    /* Start the SCB UART */
    ModbusUART_Start();
    
    /* Start the Interrupt */
    MessageReceived_Start();
    
    /* Transmit string through UART */
    ModbusUART_UartPutString("UART Initialised");

    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
    
    for(;;)
    {         
        if(messageReceived)
        {
          if(lastLed == 0)
            lastLed = 1;
          else
            lastLed = 0; 
        
          messageReceived = 0;
          ch = ModbusUART_UartGetChar();
          ModbusUART_UartPutChar(ch);
        
          RX_LED_Write(lastLed);       
        }
        
        
        
    }
}

/* [] END OF FILE */
