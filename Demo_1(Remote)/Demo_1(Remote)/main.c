/*
 * Demo_1(Remote).c
 *
 * Created: 3/2/2024 0:35:12
 * Author : twcha
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>

unsigned char buffer[50];
int state,numx,numy = 0;
int ready = 1;
int i = 0;
unsigned char receive,key = 0;

void send(unsigned char ch){
	while(! (UCSR0A & (1<<UDRE0)));
	UDR0 = ch;
}

int main(void)
{	
	UCSR0B = (1<<TXEN0)|(1<<RXEN0);//Enable |(1<<RXCIE0)
	UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);//Char size = 8
	UBRR0L = 0x08;//X = f/(16*Baud rate)-1
	// baud rate = 115200
	
	sei();
	
	ADCSRA = 0x8F;
	ADMUX = 0x40;
	ADCSRA |= (1<<ADSC);
	
    /* Replace with your application code */
    while (1) 
    {
		if(ready == 1){
			if(i == 0)
			memset(buffer, 0, sizeof(buffer));
			if(i<sizeof(buffer)-1){
				sprintf(buffer, "X%dY%dZ", numx, numy);
				send(buffer[i++]);
			}else{
				i = 0;
				ready = 0;
			}
			
		}
		if((UCSR0A & (1<<RXC0))){
			key = UDR0;
			receive = 0;
			ready = 1;
		}
    }		
}


ISR(ADC_vect)
{
	if(ADMUX == 0x40){
		numx = ADC/(double)1023*100;
		ADMUX = 0x41;
	}
	else if(ADMUX == 0x41){
		numy = ADC/(double)1023*100;
		ADMUX = 0x40;
	}
	ADCSRA |=(1<<ADSC);
}
