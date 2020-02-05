/*
 * heating-controller-bypass.c
 * Author : Michał Butkiewicz
 */ 
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>

#define TEMP PA0 /* input */
#define CHCK PA7 /* input */
#define SEG0 PA1
#define SEG1 PA2
#define REL PA5
#define LED3 PB6 /* BLUE - pump work detected */
#define LED2 PB5 /* RED - c.h. controller not working */
#define BCD_A PB0
#define BCD_B PB1
#define BCD_C PB2
#define BCD_D PB3

/* add 8MHz clock */

void portInit(void);
void adcInit(void);
void timerInit(void);


int main(void)
{
    portInit();
    
    while (1) 
    {
    }
}

void portInit(void){

	PORTA = (1<<SEG0) | (1<<SEG1) | (1<<REL);
	DDRA =  (0<<TEMP) | (0<<CHCK) | (1<<SEG0) | (1<<SEG1) | (1<<REL);
	
	PORTB = (1<<LED3) | (1<<LED2) | (0<<BCD_D) | (0<<BCD_C) | (0<<BCD_B) | (0<<BCD_A);
	DDRB = (1<<LED3) | (1<<LED2) | (1<<BCD_D) | (1<<BCD_C) | (1<<BCD_B) | (1<<BCD_A);
}

void adcInit(void){
	/* 
		ADC = (Vin*1024)/Vref 
		Vref = 2.56V
		LM35temp = 0.25*ADC+2 (temp is 10mV/degC, range 2-150degC)
	*/
}

void timerInit(void){
	/* 7seg toggle time - 50ms */
	/* refresh time - 3s */
}
