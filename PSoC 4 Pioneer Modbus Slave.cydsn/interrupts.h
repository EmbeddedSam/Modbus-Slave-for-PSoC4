/* ========================================
 *
 * Copyright Sam Walsh, 2014
 * All Rights Reserved.
 *
 * interrupts.h Contains all the interrupts variables
 *
 * ========================================
*/
#include <cytypes.h>
#include <cyfitter.h>
#include <ModbusUART.h>

CY_ISR_PROTO(messageReceived_isr);
CY_ISR_PROTO(endOfMessage_isr);
/* [] END OF FILE */
