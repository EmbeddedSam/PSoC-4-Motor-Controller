/* ========================================
 *
 * Copyright Sam Walsh, 2015
 * All Rights Reserved.
 *
 * main.c
 *
 * ========================================
*/
#include <project.h>
#include <interrupts.h>
#include <modbus.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define  forever    1
#define  forwards   1
#define  backwards  0

/* Function Prototypes */
void updateEncoder(void);
void updateModbusPackets(void);
float calculateSpeed(void);
int calculatePID(float, float);
void scaleModbusPIDConstants(void);

/* Modbus Variables */
extern unsigned int  holdingReg[50];
extern unsigned char coils[50];
extern unsigned char received[125];
extern unsigned char response[125]; //Enough to return all holding-r's
extern uint8 modbusMessage;

/* Typedef modbus packet */
struct ModbusData {
   int encoderCount;
   int16 encoderHigh, encoderLow;
   uint16 speedRPSScaler;
   int16 speedRPS;
   int16 speedRPM;
   uint16 motorCurrentScaler;
   int16 motorCurrent;
   uint16 PIDScaler;
   float Kp,Ki,Kd; 
   int16 setpointSpeedRPM;
};
struct ModbusData mb;

/* Encoder Variables */
extern volatile uint8 encoderInterruptFlag, speedInterruptFlag;
uint8 encA,encB; 
static int8 lookup[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0}; //used for encoder values 
uint8 enc_val,pidspeed; //to store the bit values of the encoders
int8  op;
int   interruptCount = 0;
int   encoderCount,pastEncoderCount;
float speedRPS,speedRPM;
uint16 ADCResult = 0;
float  ADCVoltage = 0;

/* Main loop */
int main()
{   
    /*Clear received array */
    memset(&received[0], 0, sizeof(received));
       
    /* Start the SCB UART, Timer and its interrupt */
    ModbusUART_Start();
    MessageReceived_StartEx(messageReceived_isr);  
    writeEnable_Write(0); // receive mode
    
    /* Start the encoder interrupt */
    EncoderInterrupt_StartEx(encoder_isr);
    SpeedInterrupt_StartEx(speed_isr);
    SpeedTimer_Start();
    MotorPWM_Start();
    MotorPWM_WritePeriod(255);
    MotorCurrentADC_Start();
    MotorCurrentADC_StartConvert();
    MotorCurrentADC_IsEndConversion(MotorCurrentADC_WAIT_FOR_RESULT);
    
    CyGlobalIntEnable; /* comment this line to disable global interrupts. */
    
    /* Setup Scaling factors for Modbus */ 
    mb.speedRPSScaler = 1000;
    mb.motorCurrentScaler = 100;
    mb.PIDScaler = 1000;
    scaleModbusPIDConstants();
    
    while(forever)
    {       
        if(modbusMessage)
        {
          processMessage();
        }
        
        if(encoderInterruptFlag)
        {
            updateEncoder(); 
            encoderInterruptFlag = 0;
        } 
        
        if(speedInterruptFlag)
        {          
            speedRPS = calculateSpeed();
            mb.speedRPS = (int)(speedRPS * mb.speedRPSScaler);
            mb.speedRPM = speedRPS * 60;              
            speedInterruptFlag = 0;
            
            //everything after this point is pid additions 18/02/15
            mb.setpointSpeedRPM = holdingReg[12];
            pidspeed = calculatePID(abs(mb.speedRPM),abs(mb.setpointSpeedRPM));
            holdingReg[13] = pidspeed;
            //check direction
            if(mb.setpointSpeedRPM > 0){Direction_Write(forwards);}
            else{Direction_Write(backwards);}
            
            MotorPWM_WriteCompare(pidspeed);    
        }
        
        ADCResult  = MotorCurrentADC_GetResult16(0);
        ADCVoltage = MotorCurrentADC_CountsTo_Volts(0, ADCResult);
        mb.motorCurrent = ADCVoltage * mb.motorCurrentScaler;
         
        updateModbusPackets();  
    }
}

void updateEncoder(void)
{
    enc_val  = enc_val << 2;            //store last 2 values 
    enc_val &= 0x0F;
    encA     = ChannelA_Read();
    encB     = ChannelB_Read();
    encA    &= 0x01; 
    encB    &= 0x01;                    //mask off everything except bit 1;
    enc_val |= ((encA << 1) | encB);    //shift A, merge with B then merge both with past values
    op = lookup[enc_val];
    mb.encoderCount += op;              //store count in 32 bit value
    mb.encoderLow = mb.encoderCount & 0xffff; //store in 2 bytes for modbus
    mb.encoderHigh = (mb.encoderCount >> 16) & 0xff; 
    //This bit is just for debugging to make sure the bytes go back into a 32 bit value
    encoderCount = 0;
    encoderCount |= mb.encoderLow;
    encoderCount |= ((mb.encoderCount << 16) & 0xff);
    
}

float calculateSpeed(void)
{
    //Velocity(RPS) = ((current count/pulses per revolution))/Time interval
    int counts;
    float speed, timePeriod; //used for doing the calcs
    counts = mb.encoderCount - pastEncoderCount;
    timePeriod = (float)SpeedTimer_ReadPeriod()/1000.0; //(1KHz clock)
    speed = (counts/333.33)/timePeriod;
    pastEncoderCount = mb.encoderCount; //used for speed calculation
    return speed;
}

void scaleModbusPIDConstants(void)
{
    //Need to actually read the holding registers and do the divide but for now lets
    //leave this as just setting the values.
    mb.Kp = 2;
    mb.Ki = 0;
    mb.Kd = 0;
}

int calculatePID(float currentValue, float setpoint)
{
    static float integral   = 0;
    static float derivative = 0;
    static float lastError = 0;

    float error, fcontrol = 0.0;
    int   control = 0;
    
    error = setpoint - currentValue;
    integral = (integral + error);
    integral = 0.6 * integral; //damping integral 
	derivative = (error - lastError);
	fcontrol =  (mb.Kp * error); 
	fcontrol += (mb.Kd * derivative);
	fcontrol += (mb.Ki * integral);
    control = (int)fcontrol;
    if(control > 255)
    {
        control = 255;
    }
    else if (control < 0)
    {
        control = 0;
    }
    return control;   
}


void updateModbusPackets(void)
{
    holdingReg[0] = mb.encoderLow;
    holdingReg[1] = mb.encoderHigh;
    holdingReg[2] = mb.speedRPSScaler;
    holdingReg[3] = mb.speedRPS;
    holdingReg[4] = mb.speedRPM;
    //holdingReg[5] = duty cycle
    //holdingReg[6] = direction
    holdingReg[7] = mb.motorCurrent;
    //holdingReg[8]  = PIDScaler
    //holdingReg[9]  = Kp
    //holdingReg[10] = Ki
    //holdingReg[11] = Kd
    //holdingReg[12] = setpointRPM
    holdingReg[13] = pidspeed;
    //holdingReg[14] = disable

}


