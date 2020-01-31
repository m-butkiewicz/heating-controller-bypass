/*
 * heating-controller-bypass.c
 * Author : Michał Butkiewicz
 */ 

#include <avr/io.h>

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
	/*
		PB4 - 7seg T1 Switch
		PB5 - 7seg T2 Switch
		PA7 - BCD-D
		PA6 - BCD-C
		PA5 - BCD-B
		PA4 - BCD-A
		PA0 - ADC0 (input)
	*/
	PORTB = (1<<PB5) | (1<<PB4);
	DDRB = (1<<DDB5) | (1<<DDB4);
	PORTA = (0<<PA7) | (0<<PA6) | (0<<PA5) | (0<<PA4);
	DDRA = (1<<PA7) | (1<<PA6) | (1<<PA5) | (1<<PA4) | (0<<PA0);
}

void adcInit(void){
	/* 
		ADC = (Vin*1024)/Vref 
		Vin = (ADC*Vref)/1024
		Vref = 2.56V
	*/
}

void timerInit(void){
	/* 7seg toggle time - 50ms */
	/* refresh time - 3s */
}
