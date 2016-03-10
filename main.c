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


typedef enum stateTypeEnum{
    init, state
} stateType;

volatile stateType state = init;


int main(void)
{
    SYSTEMConfigPerformance(10000000);
    enableInterrupts();

    
}