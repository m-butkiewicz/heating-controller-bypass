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
#define LED3_BLUE PB6 /* BLUE - pump work detected */
#define LED2_RED PB5 /* RED - c.h. controller not working */
#define BCD_A PB0
#define BCD_B PB1
#define BCD_C PB2
#define BCD_D PB3

#define TIMER_OVF_FACTOR 6

void portInit(void);
void adcInit(void);
void timerInit(void);

void segment0_on(void);
void segment0_off(void);
void segment1_on(void);
void segment1_off(void);
void relay_on(void);
void relay_off(void);
void led3Blue_on(void);
void led3Blue_off(void);
void led2Red_on(void);
void led2Red_off(void);

int counter = 0;
int timerLock = 0;

ISR (TIMER1_OVF_vect) {
	counter++;
	if (counter == TIMER_OVF_FACTOR) {
		counter = 0;
		timerLock = 1;
	}
}

int main(void)
{
	uint16_t temperature = 0;
	
    portInit();
	adcInit();
	timerInit();
    
	segment0_off();
	segment1_off();
	
    while (1) 
    {
		if (timerLock) {
			timerLock = 0;
		}
		displayTemperature(temperature);
    }
}

void portInit(void){

	PORTA = (1<<SEG0) | (1<<SEG1) | (1<<REL);
	DDRA =  (0<<TEMP) | (0<<CHCK) | (1<<SEG0) | (1<<SEG1) | (1<<REL);
	
	PORTB = (1<<LED3_BLUE) | (1<<LED2_RED) | (0<<BCD_D) | (0<<BCD_C) | (0<<BCD_B) | (0<<BCD_A);
	DDRB = (1<<LED3_BLUE) | (1<<LED2_RED) | (1<<BCD_D) | (1<<BCD_C) | (1<<BCD_B) | (1<<BCD_A);
}

void segment0_on(void) {PORTA |= (0<<SEG0);}
void segment0_off(void) {PORTA |= (1<<SEG0);}
void segment1_on(void) {PORTA |= (0<<SEG1);}
void segment1_off(void) {PORTA |= (1<<SEG1);}
void relay_on(void) {PORTA |= (0<<REL);}
void relay_off(void) {PORTA |= (1<<REL);}
void led3Blue_on(void) {PORTB |= (0<<LED3_BLUE);}
void led3Blue_off(void) {PORTB |= (1<<LED3_BLUE);}
void led2Red_on(void) {PORTB |= (0<<LED2_RED);}
void led2Red_off(void) {PORTB |= (1<<LED2_RED);}

void adcInit(void){
	
	/* Internal 2.56V AREF with external cap */
	ADMUX = (1<<REFS1) | (1<<REFS0);
	/* Prescaler F_CPU/64 (125kHz) */
	ADCSR = (1<<ADPS2) | (1<<ADPS1);
	ADCSR |= (1<<ADEN);
	
}

uint16_t adcRead(void) {
	
	ADCSR |= (1<<ADSC);
	while (ADCSR & (1<ADSC));
	return (ADC);
}

uint16_t covertAdcToTemp(uint16_t adc) {
	
	/* 
		ADC = (Vin*1024)/Vref 
		Vref = 2.56V
		LM35temp = 0.25*ADC+2 (temp is 10mV/degC, range 2-150degC)
	*/
	return (0.25*adc + 2);
}

void display(uint16_t number) {
	PORTB |= (number & 0x0F);
}

void displayTemperature(uint16_t temperature) {
	
	if (temperature < 0) {return;}
	if (temperature < 10) {
		segment1_off();
		segment0_on()
		display(temperature);
		return;
	} 
	
	if (temperature > 99) {temperature = 99;}
	
	segment1_off()	
	segment0_on();
	display(temperature%10);
	segment0_off();
	segment1_on();
	display(temperature/10);	
}


void timerInit(void){
	
	/* refresh time - 3s */
	TIMSK |= (1<<TOIE1);
	sei();
	TCCR1B |= (1<<CS13) | (1<<CS12) | (1<<CS11) | (1<<CS10); 
}
