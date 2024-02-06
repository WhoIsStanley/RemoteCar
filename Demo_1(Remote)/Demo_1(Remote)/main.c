/*
 * Demo_1(Remote).c
 *
 * Created: 3/2/2024 0:35:12
 * Author : twcha
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

int numx,numy = 0;
unsigned char key = 0;

void send(unsigned char ch){
	while(! (UCSR0A & (1<<UDRE0)));
	UDR0 = ch;
}

 void delay()
 {
	 TCCR1A = 0b00000000;
	 TCCR1B = 0b00001011; // Prescaler = 64
	 OCR1A = 12500; // 1 / (16 MHz / 64) = 0.004 ms,  50ms / 0.004 ms = 12500
	 
	 unsigned char count = 0;
	 while (count < 5) // 20 x 50 ms = 1 s
	 {
		 while(!(TIFR1 & (1<<OCF1A))) ;
		 TIFR1 = (1<<OCF1A);
		 count++;
	 }
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
		
		if(numx > 60){
			send('d');
		}
		else if(numx < 40){
			send('b');
		}
		else if(numy > 60)
			send('a');
		else if(numy < 40)
			send('c');
		else
			send('e');
		delay();
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
