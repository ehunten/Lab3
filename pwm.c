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

    //RPD1Rbits.RPD1R = 0b1011;

    IFS0bits.T2IF = 0;          // Put the flag down
    TMR2 = 0;                   //Clear TMR2
    PR2 = 10000;                //Set PRvalue
    T2CONbits.TCKPS = PRESC1;   //Set prescalar
    T2CONbits.TCS = 0;          //Set Oscillator


    //OCM2
    RPD3Rbits.RPD3R = 0b1011; //map OC2 to RD3
    RPC13Rbits.RPC13R = 0b1011; // map OC2 to RC13
    OC2CONbits.ON = 0;      //turn off
    //OC2R = 1023;
    OC2RS = 10000;              //dual compare mode
    OC2CONbits.OCM = 6;     //PWM mode no fault pin
   // OC2CONSET = 0x8000;
    OC2CONbits.OCTSEL = 0;
    
    OC2CONbits.ON = 1;      //turn it on

    
    
//OCM1
    RPG0Rbits.RPG0R = 0b1011;   //map OC1 to RG0
    RPF1Rbits.RPF1R = 0b1011;   //map OC1 to RF1
    
    OC1CONbits.ON = 0;
    OC1CONbits.OCTSEL = 0;
    //OC1R = 0;
    OC1RS = 10000;
    OC1CONbits.OCM = 6;
    OC1CONbits.ON = 1;
<<<<<<< HEAD

=======
    //OC1CONSET = 0x8000;
    
        T2CONbits.ON = 1;          //turn timer on
}
>>>>>>> origin/dev

/*
 Enable motor 1: RG13
 Output 1 motor 1: RG0
 Output 2 motor 1: RF1
 
 Enable motor 2: RD12
 Output 1 motor 2: RD3
 Output 2 motor 2: RC13
 
 */
<<<<<<< HEAD
}
=======

void initHbridge() {
    
    TRISGbits.TRISG13 = 0;
    TRISDbits.TRISD12 = 0;
    
    LATGbits.LATG13 = 0;
    LATDbits.LATD12 = 1;
    
}
>>>>>>> origin/dev
