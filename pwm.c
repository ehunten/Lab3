/*
 * File:   pwm.c
 * Authors: Evelyn Hunten
 *
 * Created 3/10/16
 */

#include <xc.h>
#include "pwm.h"

#define PRESC1 3 //CHANGE THIS

void initPWM() {

    RPD1Rbits.RPD1R = 0b1011;

    IFS0bits.T2IF = 0;          // Put the flag down
    TMR2 = 0;                   //Clear TMR2
    PR2 = 10000;                //Set PRvalue
    T2CONbits.TCKPS = PRESC1;   //Set prescalar
    T2CONbits.TCS = 0;          //Set Oscillator
    T2CONbits.ON = 1;          //turn timer on

    
//OCM2
    OC2CONbits.ON = 0;      //turn off
    OC2RS = 5;              //dual compare mode
    OC2CONbits.OCM = 6;     //PWM mode no fault pin
    OC2CONbits.ON = 1;      //turn it on
    
//OCM1
    OC1CONbits.ON = 0;
    OC1RS = 5;
    OC1CONbits.OCM = 6;
    OC1CONbits.ON = 1;
}

/*
 Enable motor 1: RG13
 Output 1 motor 1: RG0
 Output 2 motor 1: RF1
 
 Enable motor 2: RD12
 Output 1 motor 2: RD6
 Output 2 motor 2: RC13
 
 */