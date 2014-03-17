/* ========================================
 *
 * Copyright Sam Walsh, 2014
 * All Rights Reserved.
 *
 * Modbus.h Contains all the modbus function prototypes
 *
 * ========================================
*/
#include <project.h>
#include <cydevice_trm.h>
#include <CyLib.h>
#include <interrupts.h>
#include <ModbusUART.h>
#include <MessageTimer.h>

//Function prototypes//
void decodeMessage(void);
void checkIfEndOfMessage(void);
void processMessage(void);
unsigned int generateCRC(unsigned char messageLength);
unsigned char checkCRC(void);

void readReg(void);        
void readInputReg(void);
void writeReg(void);
void writeMultipleRegs(void);
void readCoil(void);
void readInputCoil(void);
void writeCoil(void);
void writeMultipleCoils(void);

void responseFinished(int delay);


/* [] END OF FILE */
