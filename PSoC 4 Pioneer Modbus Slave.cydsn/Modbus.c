/* ========================================
 *
 * Copyright Sam Walsh, 2014
 * All Rights Reserved.
 *
 * Modbus.c all of the modbus and communication functions
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

#define SlaveAddress 1 //Change this to whatever you want
#define CHECK_BIT(var,pos) !!((var) & (1 << (pos)))

unsigned int  holdingReg[50];
unsigned char coils[50];
unsigned char received[125];
unsigned char response[125]; //Enough to return all holding-r's

//Global variables (going to definitely use these)//
volatile uint8 newMessage = 1;
volatile uint8 middleOfMessage = 0;
volatile uint8 z = 0;
volatile uint8 messageLengthNotChanged = 0;
volatile uint8 messageLength = 0;
volatile uint8 oldMessageLength = 0;
volatile uint8 timerCount = 0;
volatile uint8 middleMessageCount = 0;
volatile uint8 newMessageCount = 0;
volatile uint8 oldPin = 0;
volatile uint8 modbusMessage = 0;
volatile uint8 turnLineAround = 0;

void decodeMessage(void)
{
    if(middleOfMessage)
    {
        received[z] = ModbusUART_UartGetChar();
        z++;
        middleMessageCount ++;
        messageLengthNotChanged = 0;
        messageLength = z;
    }
    
    if(newMessage)
    {
        received[z] = ModbusUART_UartGetChar();
        z++;
        messageLength = z;
        middleOfMessage = 1;
        newMessage = 0;
        MessageTimer_Start();
        EndOfMessage_StartEx(endOfMessage_isr);
        newMessageCount ++;
        messageLengthNotChanged = 0;

    }
}

void checkIfEndOfMessage(void)
{
    if(turnLineAround > 0)
    {
        turnLineAround -= 1;
        if(turnLineAround == 0)
        {
          MessageTimer_Stop();
          EndOfMessage_Stop();
          writeEnable_Write(0); //turn line around
          turnLineAround = 0;
        }
        else
        {
            MessageTimer_Start();
            EndOfMessage_StartEx(endOfMessage_isr);   
        }      
    }
    if(turnLineAround == 0)
    if(middleOfMessage)
    {
        if(oldMessageLength == messageLength)
        {
            messageLengthNotChanged++;
        }
        if(messageLengthNotChanged == 5)
        {
            //We are at the end of the message
            newMessage = 1;
            modbusMessage = 1; //for main loop
            middleOfMessage = 0;
            messageLengthNotChanged = 0;
            z=0;
            MessageTimer_Stop();
            EndOfMessage_Stop();
            /*Clear received array */
            //memset(&received[0], 0, sizeof(received));
        }
        else
        {
            MessageTimer_Start();
            EndOfMessage_StartEx(endOfMessage_isr); 
        }
    }
        oldMessageLength = messageLength; 
        timerCount ++; //debugging counter to find out how many times the loop occurred.
}

void processMessage(void)
{
    if(received[0] == SlaveAddress){
        if(checkCRC() == 1){        
		if(received[1] == 0x01){
            readCoil();
        }
        else if(received[1] == 0x02){
            readInputCoil();
        }
        else if(received[1] == 0x03){
            readReg();
        }
        else if(received[1] == 0x04){
            readInputReg();
        }
        else if(received[1] == 0x05){
            writeCoil();
        }	  
        else if(received[1] == 0x06){
            writeReg();
        }
        else if(received[1] == 0x10){
            writeMultipleRegs();
        }
        else if(received[1] == 0x0F){
            writeMultipleCoils();
        }
        else{
         //   response[0] = 0; //error this does nothing though..
        }
    }
  }
  modbusMessage = 0;
}

void readCoil(void)
{
/******************************************************************************/
/* Reads a coil and then responds                                             */
/******************************************************************************/
  unsigned int rc_Address = 0;
  unsigned int rc_numCoils = 0;
  unsigned int crc = 0;

  unsigned char howManyBytes = 0;
  unsigned char remainder = 0;
  unsigned char lsb = 0;
  unsigned char i,j,k,l = 0;

  //Combine address bytes
  rc_Address = received[2];
  rc_Address <<=8;
  rc_Address |= received[3];

  //Combine number of coils bytes
  rc_numCoils = received[4];
  rc_numCoils <<= 8;
  rc_numCoils |= received[5];

  response[0] = SlaveAddress;
  response[1] = 0x01;

  howManyBytes = rc_numCoils/8;
  remainder = rc_numCoils % 8;

  if(remainder){
    howManyBytes += 1;
  }
  response[2] = howManyBytes;

  l = rc_Address;
  k = 3; //start at response 3

  for(i=howManyBytes; i!=0; i--){
    if(i>1){
      for(j=0;j!=8;j++){
	if(coils[l]){
          lsb = 1;
	}
	else{
          lsb = 0;
	}
	response[k] ^= (lsb << j);
	l++;
      }
      k++;
    }
    else{
      for(j=0;j!=remainder;j++){
      if(coils[l]){
        lsb = 1;
      }
      else{
        lsb = 0;
      }
      response[k] ^= (lsb << j);
      l++;
      }
      k++;
    }
  }
  crc = generateCRC(k+2);

  response[k] = crc >> 8;
  response[k+1] = crc;

  writeEnable_Write(1); // turn line round to write

  for(i=0;i!=k+3;i++){
     ModbusUART_UartPutChar(response[i]);
  }
  responseFinished(k+3);
}

void readInputCoil(void)
{
/******************************************************************************/
/* Reads a coil and then responds                                             */
/******************************************************************************/
  unsigned int rc_Address = 0;
  unsigned int rc_numCoils = 0;
  unsigned int crc = 0;

  unsigned char howManyBytes = 0;
  unsigned char remainder = 0;
  unsigned char lsb = 0;
  unsigned char i,j,k,l = 0;

  //Combine address bytes
  rc_Address = received[2];
  rc_Address <<=8;
  rc_Address |= received[3];

  //Combine number of coils bytes
  rc_numCoils = received[4];
  rc_numCoils <<= 8;
  rc_numCoils |= received[5];

  response[0] = SlaveAddress;
  response[1] = 0x02;

  howManyBytes = rc_numCoils/8;
  remainder = rc_numCoils % 8;

  if(remainder){
    howManyBytes += 1;
  }
  response[2] = howManyBytes;

  l = rc_Address;
  k = 3; //start at response 3

  for(i=howManyBytes; i!=0; i--){
		if(i>1){
      for(j=0;j!=8;j++){
				if(coils[l]){
					lsb = 1;
				}
				else{
          lsb = 0;
				}
				response[k] ^= (lsb << j);
				l++;
	    }
			k++;
	  }
		else{
			for(j=0;j!=remainder;j++){
				if(coils[l]){
					lsb = 1;
				}
				else{
          lsb = 0;
				}
        response[k] ^= (lsb << j);
				l++;
			}
			k++;
		}
  }
  crc = generateCRC(k+2);

  response[k] = crc >> 8;
  response[k+1] = crc;

  writeEnable_Write(1); // turn line round to write

  for(i=0;i!=k+3;i++){
     ModbusUART_UartPutChar(response[i]);
  }
  responseFinished(k+3);

}

void readInputReg(void)
{
  unsigned int rr_Address = 0;
  unsigned int rr_numRegs = 0;
  unsigned char j = 3;
  unsigned int crc = 0;
  unsigned int i = 0;

  //Combine address bytes
  rr_Address = received[2];
  rr_Address <<= 8;
  rr_Address |= received[3];

  //Combine number of regs bytes
  rr_numRegs = received[4];
  rr_numRegs <<= 8;
  rr_numRegs |= received[5];

  response[0] = SlaveAddress;
  response[1] = 0x04;
  response[2] = rr_numRegs*2; //2 bytes per reg

  for(i=rr_Address;i<(rr_Address + rr_numRegs);i++){
    if(holdingReg[i] > 255){
      //Need to split it up into 2 bytes
      response[j] = holdingReg[i] >> 8;
      j++;
      response[j] = holdingReg[i];
      j++;
    }
    else{
      response[j] = 0x00;
      j++;
      response[j] = holdingReg[i];
      j++;
    }
  }
  crc = generateCRC(j+2);
  response[j] = crc >> 8;
  j++;
  response[j] = crc;
  j+=2;

  writeEnable_Write(1); // turn line round to write

  for(i=0;i!=j;i++){
     ModbusUART_UartPutChar(response[i]);
  }
  responseFinished(9);
  i=0;  
  j=0;
}


void readReg(void)
{
  unsigned int rr_Address = 0;
  unsigned int rr_numRegs = 0;
  unsigned char j = 3;
  unsigned int crc = 0;
  unsigned int i = 0;

  //Combine address bytes
  rr_Address = received[2];
  rr_Address <<= 8;
  rr_Address |= received[3];

  //Combine number of regs bytes
  rr_numRegs = received[4];
  rr_numRegs <<= 8;
  rr_numRegs |= received[5];

  response[0] = SlaveAddress;
  response[1] = 0x03;
  response[2] = rr_numRegs*2; //2 bytes per reg

  for(i=rr_Address;i<(rr_Address + rr_numRegs);i++){
    if(holdingReg[i] > 255){
      //Need to split it up into 2 bytes
      response[j] = holdingReg[i] >> 8;
      j++;
      response[j] = holdingReg[i];
      j++;
    }
    else{
      response[j] = 0x00;
      j++;
      response[j] = holdingReg[i];
      j++;
    }
  }
  crc = generateCRC(j+2);
  response[j] = crc >> 8;
  j++;
  response[j] = crc;
  j+=2;

  writeEnable_Write(1); // turn line round to write

  for(i=0;i!=j;i++){
     ModbusUART_UartPutChar(response[i]);
  }
  responseFinished(j);
  j=0;  
}

void writeReg(void)
{
/******************************************************************************/
/* Works out which reg to write and then responds                             */
/******************************************************************************/
  unsigned int wr_AddressLow = 0;
  unsigned int wr_AddressHigh = 0;
  unsigned int wr_Address = 0;

  unsigned int wr_valToWrite = 0;
  unsigned int wr_valToWriteLow = 0;
  unsigned int wr_valToWriteHigh = 0;

  unsigned int crc = 0;
  unsigned int i = 0;

  //Combine address bytes
  wr_Address = received[2];
  wr_Address <<= 8;
  wr_Address |= received[3];

  wr_AddressLow = received[3]; //useful to store
  wr_AddressHigh = received[2];

  //Combine value to write regs
  wr_valToWrite = received[4];
  wr_valToWrite <<= 8;
  wr_valToWrite |= received[5];

  wr_valToWriteLow = received[5];
  wr_valToWriteHigh = received[4];

  holdingReg[wr_Address] = wr_valToWrite;

  response[0] = SlaveAddress;
  response[1] = 0x06;
  response[3] = wr_AddressLow; //2 bytes per reg
  response[2] = wr_AddressHigh;

//TO DO CHECK VALUE IS ACTUALLY WRITTEN//
  response[4] = wr_valToWriteHigh;
  response[5] = wr_valToWriteLow;

  crc = generateCRC(8);

  response[6] = crc >> 8;
  response[7] = crc;

  writeEnable_Write(1); // turn line round to write

  for(i=0;i!=9;i++){
     ModbusUART_UartPutChar(response[i]);
  }
  responseFinished(9);
  i=0;  
}

void writeMultipleRegs(void)
{
/******************************************************************************/
/* Works out which reg to write and then responds                             */
/******************************************************************************/
  unsigned int wmr_Address = 0;
  unsigned int wmr_AddressHigh = 0;
  unsigned int wmr_AddressLow = 0;
  unsigned int wmr_numRegs = 0;
  unsigned int wmr_numRegsHigh = 0;
  unsigned int wmr_numRegsLow = 0;
  unsigned int wmr_numBytes = 0;
  unsigned int wmr_numBytesTST = 0;
  unsigned int valToWrite = 0;
//  unsigned int valToWriteHigh = 0;
//  unsigned int valToWriteLow = 0;

  unsigned char j = 0;
  unsigned int crc = 0;
  unsigned int i = 0;

  //Combine address bytes
  wmr_Address = received[2];
  wmr_Address <<= 8;
  //add address high and low bits
  wmr_Address |= received[3];
  wmr_AddressHigh = received[2];
  wmr_AddressLow = received[3];


  //Combine number of regs bytes
  wmr_numRegs = received[4];
  wmr_numRegs <<= 8;
  wmr_numRegs |= received[5];
  wmr_numRegsHigh = received[4];
  wmr_numRegsLow = received[5];

  wmr_numBytes = received[6];

  j = 7;

  //the following lines haven't been tested yet but were suggested
  //in a pull request, If you have any problems revert back to wmr_numBytes 
  //in the for loop from TST (the lines commented below)

  wmr_numBytesTST = wmr_numBytes /2;   

  for(i=0;i<wmr_numBytesTST;i++)
  {
    valToWrite = received[j];
    valToWrite <<= 8;
    j++;
    valToWrite |= received[j];
    j++;

    holdingReg[wmr_Address + i] = valToWrite;
  }

  //for(i=0;i<wmr_numBytes;i++)
  //{
  // valToWrite = received[j];
  //  valToWrite <<= 8;
  //  j++;
  //  valToWrite |= received[j];
  //  j++;

  //  holdingReg[wmr_Address + i] = valToWrite;
  //}


  response[0] = SlaveAddress;
  response[1] = 0x10;
  response[2] = wmr_AddressHigh;
  response[3] = wmr_AddressLow;
  response[4] = wmr_numRegsHigh;
  response[5] = wmr_numRegsLow;

  crc = generateCRC(8);

  response[6] = crc >> 8;
  response[7] = crc;

  writeEnable_Write(1); // turn line round to write

  for(i=0;i!=9;i++){
     ModbusUART_UartPutChar(response[i]);
  }
  responseFinished(9);
  i=0;  

  j=0;
  
}


void writeCoil(void)
{
/******************************************************************************/
/* Writes to a coil and then responds                                         */
/******************************************************************************/
  unsigned int wc_AddressLow = 0;
  unsigned int wc_AddressHigh = 0;
  unsigned int wc_Address = 0;

  unsigned int wc_valToWrite = 0;
  unsigned int wc_valToWriteLow = 0;
  unsigned int wc_valToWriteHigh = 0;
  int i = 0;
  unsigned int crc = 0;

  //Combine address bytes
  wc_Address = received[2];
  wc_Address <<= 8;
  wc_Address |= received[3];

  wc_AddressLow = received[3]; //useful to store
  wc_AddressHigh = received[2];

  //Combine value to write regs
  wc_valToWrite = received[4];
  wc_valToWrite <<= 8;
  wc_valToWrite |= received[5];

  wc_valToWriteLow = received[5];
  wc_valToWriteHigh = received[4];

  if(wc_valToWrite){
    coils[wc_Address] = 0xFF;
  }
  else{
    coils[wc_Address] = 0x00;
  }

  response[0] = SlaveAddress;
  response[1] = 0x05;
  response[3] = wc_AddressLow; //2 bytes per reg
  response[2] = wc_AddressHigh;

//TO DO CHECK VALUE IS ACTUALLY WRITTEN//
  response[4] = wc_valToWriteHigh;
  response[5] = wc_valToWriteLow;

  crc = generateCRC(8);

  response[6] = crc >> 8;
  response[7] = crc;

  writeEnable_Write(1); // turn line round to write

  for(i=0;i!=9;i++){
     ModbusUART_UartPutChar(response[i]);
  }
  responseFinished(10);
  i=0;  
}

void writeMultipleCoils(void)
{
/******************************************************************************/
/* Reads a coil and then responds                                             */
/******************************************************************************/
  unsigned int wmc_Address = 0;
  unsigned int wmc_AddressHigh = 0;
  unsigned int wmc_AddressLow = 0;
  unsigned int wmc_numCoils = 0;
  unsigned int wmc_numCoilsHigh = 0;
  unsigned int wmc_numCoilsLow = 0;
 // unsigned int wmc_numBytes;
  unsigned int crc = 0;

  unsigned char howManyBytes = 0;
  unsigned char remainder = 0;
//  unsigned char lsb = 0;
  unsigned char i,j,l = 0;
  //unsigned char k;

  //Combine address bytes
  wmc_Address = received[2];
  wmc_AddressHigh = received[2];
  wmc_Address <<=8;
  wmc_Address |= received[3];
  wmc_AddressLow = received[3];

  //Combine number of coils bytes
  wmc_numCoils = received[4];
  wmc_numCoilsHigh = received[4];
  wmc_numCoils <<= 8;
  wmc_numCoils |= received[5];
  wmc_numCoilsLow = received[5];

//  wmc_numBytes = received[6];

  response[0] = SlaveAddress;
  response[1] = 0x0F;

  howManyBytes = wmc_numCoils/8;
  remainder = wmc_numCoils % 8;

  if(remainder){
    howManyBytes += 1;
  }
  response[2] = wmc_AddressHigh;
  response[3] = wmc_AddressLow;

  response[4] = wmc_numCoilsHigh;
  response[5] = wmc_numCoilsLow;

  l = wmc_Address;
  //k = 3; //start at response 3

//  unsigned char bitSet;
  unsigned char valToWrite;
  unsigned char q = 7; //count through vals to write
  

  for(i=howManyBytes; i!=0; i--){
    valToWrite = received[q];
    q++;
    if(i>1){
      for(j=0;j!=8;j++){
	if(CHECK_BIT(valToWrite, j)){
          coils[l] = 1;
	}
	else{
          coils[l] = 0; //need to sort out remainder stuff

	}
	l++;
      }
    }
    else{
      for(j=0;j!=remainder;j++){
      if(CHECK_BIT(valToWrite, j)){
          coils[l] = 1;
      }
      else{
        coils[l] = 0;
      }
      l++;
      }
    }
  }
  crc = generateCRC(8);

  response[6] = crc >> 8;
  response[7] = crc;

  writeEnable_Write(1); // turn line round to write

  for(i=0;i!=9;i++){
     ModbusUART_UartPutChar(response[i]);
  }
  responseFinished(10);
  i=0;  
}

unsigned int generateCRC(unsigned char messageLength)
{
unsigned int crc = 0xFFFF;
unsigned int crcHigh = 0;
unsigned int crcLow = 0;
int i,j = 0;

  for(i=0;i<messageLength-2;i++){
    crc ^= response[i];
    for(j=8; j!=0; j--){
      if((crc & 0x0001) != 0){
        crc >>= 1;
        crc ^= 0xA001;
      }
      else{
        crc >>= 1;
      }
    }
  }
//bytes are wrong way round so doing a swap here..
crcHigh = (crc & 0x00FF) <<8;
crcLow = (crc & 0xFF00) >>8;
crcHigh |= crcLow;
crc = crcHigh;
return crc;
}

unsigned char checkCRC(void)
{
  unsigned int crc = 0xFFFF;
  unsigned int crcHigh = 0;
  unsigned int crcLow = 0;
  int i,j = 0;

    for(i=0;i<messageLength-2;i++){
      crc ^= received[i];
      for(j=8; j!=0; j--){
        if((crc & 0x0001) != 0){
          crc >>= 1;
          crc ^= 0xA001;
        }
        else{
          crc >>= 1;
        }
      }
    }
  //bytes are wrong way round so doing a swap here..
  crcHigh = (crc & 0x00FF);
  crcLow = (crc & 0xFF00) >>8;
  if((crcHigh == received[i])&&(crcLow == received[i+1]))
  {
    return 1;
  }
  else{
    return 0;
  }


}

void responseFinished(int delay)
{
    //delay = 833*delay;
    //CyDelayUs(delay);
    //writeEnable_Write(0); //turn line back to normal
    //delay = delay;
    memset(&response[0], 0, sizeof(response)); //clear response
    turnLineAround = delay+11;
    MessageTimer_Start(); //start timer to go off, 833uS * amount of bytes and turn line back around, 
    //the timer shouldn't be needed but the UART seems to not be operating synchronously.
    EndOfMessage_StartEx(endOfMessage_isr); 
}