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
volatile uint8 encoderInterruptFlag;
volatile uint8 speedInterruptFlag;

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

CY_ISR(encoder_isr) 
{
   encoderInterruptFlag = 1;
   EncoderInterruptPin_ClearInterrupt(); //should get us out of the interrupt

}

CY_ISR(speed_isr) 
{
   speedInterruptFlag = 1;
   SpeedTimer_ReadStatusRegister(); //should get us out of the interrupt
}

/* [] END OF FILE */
