/*
 * heating-controller-bypass.c
 * Author : Michał Butkiewicz
 */ 

#include <avr/io.h>
#include "core.h"

void portInit(void);
void adcInit(void);
void timerInit(void);
int adcRead(void);

int main(void)
{
    portInit();
    
    while (1) 
    {
    }
}

void portInit(void){}
void adcInit(void){}
void timerInit(void){}
int adcRead(void){return 0;}