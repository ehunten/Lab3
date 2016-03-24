/*
 * File:   pwm.c
 * Authors: Evelyn Hunten
 *
 * Created 3/10/16
 */

#include <xc.h>
#include "pwm.h"

#define PRESC1 0 //CHANGE THIS

void initPWM() {

    IFS0bits.T2IF = 0;          // Put the flag down
    TMR2 = 0;                   //Clear TMR2
    PR2 = 1023;                //Set PRvalue
    T2CONbits.TCKPS = PRESC1;   //Set prescalar
    T2CONbits.TCS = 0;          //Set Oscillator
    T2CONbits.ON = 1;          //turn timer on

    
    //OCM2
    RPD1Rbits.RPD1R = 0b0;   //map OC2 to RD1 1100
    RPD5Rbits.RPD5R = 0b0;   //map OC2 to RD5 (ground right now)
    OC2CONbits.ON = 0;      //turn off
    OC2CONbits.OCTSEL = 0;  //using timer 2
    OC2R = 0;
    OC2RS = 0;              //dual compare mode
    OC2CONbits.OCM = 6;     //PWM mode no fault pin

    OC2CONbits.ON = 1;      //turn it on

    
    
//OCM1
    RPD1Rbits.RPD1R = 0b1100;   //map OC1 to RD1 1100
    RPD5Rbits.RPD5R = 0b1100;   //map OC1 to RD5 (ground right now)
    OC1CONbits.ON = 0;
    OC1CONbits.OCTSEL = 0;
    OC1R = 0;
    OC1RS = 0;
    OC1CONbits.OCM = 6;
    OC1CONbits.ON = 1;

    //OC1CONSET = 0x8000;

    
    
}

/*
 Enable motor 1: RG13
 Output 1 motor 1: RG0
 Output 2 motor 1: RF1
 
 Enable motor 2: RD12
 Output 1 motor 2: RD3
 Output 2 motor 2: RC13
 
 */


void initHbridge() {
    
    
    TRISGbits.TRISG13 = 0;
    TRISDbits.TRISD12 = 0;
    
    LATGbits.LATG13 = 1;
    LATDbits.LATD12 = 1;
    
}

void forward(int Duty){
    
    RPD1Rbits.RPD1R = 0b1100;   //map OC1 to RD1 1100
    RPD5Rbits.RPD5R = 0b1100;   //map OC1 to RD5 (ground right now)
    OC1CONbits.ON = 0;
    OC1CONbits.OCTSEL = 0;
    OC1R = 0;
    OC1RS = Duty;
    OC1CONbits.OCM = 6;
    OC1CONbits.ON = 1;
    
}

void backward(int Duty) {
        //OCM2
    RPD1Rbits.RPD1R = 0b1011;   //map OC1 to RD1 1100
    RPD5Rbits.RPD5R = 0b1011;   //map OC1 to RD5 (ground right now)
    OC2CONbits.ON = 0;      //turn off
    OC2CONbits.OCTSEL = 0;  //using timer 2
    OC2R = 0;
    OC2RS = Duty;              //dual compare mode
    OC2CONbits.OCM = 6;     //PWM mode no fault pin

    OC2CONbits.ON = 1;      //turn it on
    
}

void TestingDutyCycle(){
       unsigned int i = 0;

        
        forward(500);
        
        for(i=0;i<1000;i++)
        {
            delayUs(143);
        }   
        
        forward(750);
        
        for(i=0;i<1000;i++)
        {
            delayUs(143);
        }
        
        forward(1000);
        
        for(i=0;i<1000;i++)
        {
            delayUs(143);
        }
                
        backward(500);
               
        for(i=0;i<1000;i++)
        {
            delayUs(143);
        }
        
        backward(750);
               
        for(i=0;i<1000;i++)
        {
            delayUs(143);
        }
                
        backward(1000);
               
        for(i=0;i<1000;i++)
        {
            delayUs(143);
        }
}

