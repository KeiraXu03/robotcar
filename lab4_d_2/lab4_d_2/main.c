/*
 * lab4_d_2.c
 *
 * Created: 2023/11/17 10:12:05
 * Author : Zhuoning Xu
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char input_char;
unsigned char state = 0;
unsigned int i = 0;
unsigned char ch1;
unsigned char ch2;
void usart_init()
{
	UCSR0B = (1<<TXEN0) | (1<<RXEN0) | (1<<UDRIE0) | (1<<RXCIE0);
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00) | (1<<UMSEL01);
	UBRR0H = 0x00;
	UBRR0L = 0x67; //103, 9600dp
}


ISR (USART_UDRE_vect)
{
	if (state == 0)
	{
		UDR0 = 'a';   //Always input a
	}
	if (state == 1)
	{
		if (i < 10)
		{
			UDR0 = input_char;
			i++;
		}
		else
		{
			state = 2;
			i = 0;     //stop input
		}
	}
}

ISR (USART_RX_vect)
{
	input_char = UDR0;
	if (state == 0)
	{
		ch1 = input_char;
		state = 1;
	}
	if (state == 2)
	{
		ch2 = input_char;
		if (ch2 == ch1)
		{
			state = 0;
		}
	}
}

int main(void)
{
	usart_init();
	sei();
	
	while (1);
	return 0;
}
