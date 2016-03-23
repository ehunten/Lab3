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


typedef enum stateTypeEnum{
    init
} stateType;

volatile stateType state = init;

volatile unsigned int val = 0;


int main(void)
{
    SYSTEMConfigPerformance(40000000);
    enableInterrupts();
    initADC();
    initLCD();
    TRISDbits.TRISD0 = 0; //RD0 - can use LED to see if stuff is working
    clearLCD();
    
    
    while (1) {
        
        
        
        
    }
    
    
}



void __ISR(_ADC_VECTOR, IPL7AUTO) _ADCInterrupt(void){
    IFS0bits.AD1IF = 0;
    val = ADC1BUF0;
}