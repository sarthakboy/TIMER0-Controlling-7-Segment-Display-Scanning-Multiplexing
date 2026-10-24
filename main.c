/*
 * TIMER07-Segment Display.c
 *
 * Created: 10/23/2026 7:22:25 PM
 * Author : 91989
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <util/delay.h>
int seg_cc[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x40};

void display_Date(uint32_t date, uint8_t mode){   // ? uint32_t, not int
	uint8_t d1 = date / 100000;
	uint8_t d2 = (date / 10000) % 10;
	uint8_t m1 = (date / 1000) % 10;
	uint8_t m2 = (date / 100) % 10;
	uint8_t y1 = (date / 10) % 10;
	uint8_t y2 = date % 10;
	if(mode == 0){
	// Digit at PD7 (leftmost)
	PORTD = 0xFF;
	PORTD &= ~(1 << PD7);
	PORTC = seg_cc[d1];
	
	}
	else if(mode == 1){ 
	// PD6
	PORTD = 0xFF;
	PORTD &= ~(1 << PD6);
	PORTC = seg_cc[d2];
	}
	else if(mode == 2){
	// PD5 (dash)
	PORTD = 0xFF;
	PORTD &= ~(1 << PD5);
	PORTC = seg_cc[10];
	}
	else if(mode ==3){
	// PD4
	PORTD = 0xFF;
	PORTD &= ~(1 << PD4);
	PORTC = seg_cc[m1];
	}
	else if(mode == 4){
	// PD3
	PORTD = 0xFF;
	PORTD &= ~(1 << PD3);
	PORTC = seg_cc[m2];
	}
	else if(mode ==5){
	// PD2 (dash)
	PORTD = 0xFF;
	PORTD &= ~(1 << PD2);
	PORTC = seg_cc[10];
	}
	else if(mode ==6){
	// PD1 — year tens
	PORTD = 0xFF;
	PORTD &= ~(1 << PD1);
	PORTC = seg_cc[y1];
	}
	else if(mode == 7){
	// PD0 (rightmost) — year ones
	PORTD = 0xFF;
	PORTD &= ~(1 << PD0);
	PORTC = seg_cc[y2];
	}
}

uint8_t mode;
ISR(TIMER0_OVF_vect){
	TCNT0 = 6;
	display_Date(120408, mode);
	mode++;
	if(mode ==8){
		mode = 0;
	}

}


int main(void)
{
	DDRC = 0xFF;
	DDRD = 0xFF;
	PORTD = 0XFE;
	PORTC = seg_cc[3];
    /* Replace with your application code */
	TCCR0 = (1<<CS01)|(1<<CS00);
	TCNT0 = 6;
	TIFR = (1<<TOV0);
	TIMSK |=(1<<TOIE0);
	sei();
	

    while (1) 
    {
		
    }
}

