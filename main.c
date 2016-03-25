// ******************************************************************************************* //
//
// File:         main.c
// Date:         2/25/16
// Authors:      Evelyn Hunten
//
// Description: Part 1 for lab 2
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "adc.h"
#include "config.h"
#include "interrupt.h"
#include "lcd.h"
#include "pwm.h"
#include "timer.h"
#include "switch.h"


typedef enum stateTypeEnum{
    s1, s2, s3, s4, w1, w2, w3, w4
} stateType;

volatile stateType state = s1;

volatile float val = 0;


int main(void)
{
    SYSTEMConfigPerformance(40000000);
    enableInterrupts();
    initTimer1();
    initLCD();
    initADC();
    initHbridge();
    initPWM();
    initSwitch();
    TRISDbits.TRISD6 = 1;           // Configure switch as input
    TRISDbits.TRISD0 = 0;
    LATDbits.LATD0 = 0;
    
    clearLCD();

    
    while (1) {

        
        if (IFS0bits.AD1IF == 1) {
            IFS0bits.AD1IF = 0;
            val = ADC1BUF0;
            //OC1RS = ADCBUF0; //for part 2
            val = val/310.0; 
            readAdc(val);
        }
        
        switch(state) {
        case s1: forward();
                break;
        case s2: stop();
                break;
        case s3: backward();
            break;
        case s4: stop();
            break;
        }
        
        if (ADC1BUF0 < 550 && ADC1BUF0 > 450) {
            //FORWARD
            OC1RS = 700;
            OC3RS = 700;
        }
        
        else if (ADC1BUF0 < 450) {
            //TURN LEFT
            OC1RS = 700;
            OC3RS = ADC1BUF0(700/450);
        }
        
        else if (ADC1BUF0 > 600) {
            //TURN RIGHT
            OC1RS = (1023 - ADC1BUF0)(700/423);
            OC3RS = 700;  
        }
        
        
    }
     
}

void __ISR(_ADC_VECTOR, IPL7AUTO) _ADCInterrupt(void){
    //IFS0bits.AD1IF = 0;
}

//Timer interrupt
void __ISR(_TIMER_3_VECTOR, IPL7SRS) _T3Interrupt () {
    
    PORTD;
    if (PORTDbits.RD6 == 1) {
    IFS0bits.T3IF = 0;
        switch (state) {
            case w1: state = s2;
                break;
            case w2: state = s3;
                break;
            case w3: state = s3;
                break;
            case w4: state = s1;
                break;
        }
    }

}

//Button change notification
void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt () {
    
    IFS1bits.CNDIF = 0;                 // Put down the flag
    PORTD;
    
    LATDbits.LATD0 = 0;
    
    if (PORTDbits.RD6 == 0) {
        initTimer3();
        switch (state) {
            case s1: state = w1;
            break;
            case s2: state = w2;
            break;
            case s3: state = w3;
            break;
            case s4: state = w4;
            break;
        }
            
    }
    else if (PORTDbits.RD6 == 1) {
        IEC0bits.T3IE = 0;
        T3CONbits.ON = 0;
        switch (state) {
            case w1: state = s2;
                break;
            case w2: state = s3;
                break;
            case w3: state = s4;
                break;
            case w4: state = s1;
                break;
        }
    }
    
}