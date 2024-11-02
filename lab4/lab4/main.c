
#include <avr/io.h>
#include <avr/interrupt.h>
void section_C();
void section_B();
void section_D();
volatile int receive_flag=0;
volatile int trans_flag=0;
volatile int Data_Register_Empty=0;
void usart_init(void)
{
	UCSR0B = (1<<TXEN0) | (1<<RXEN0);
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00) | (1<<UMSEL01);
	UBRR0H = 0x00;
	UBRR0L = 0x67; //103, 9600dp
	//UBRR0L = 0xCF
}

int main(void)
{
	sei();
	usart_init();
	//section_B();
	section_C();
	//section_D();
	return 0;
}
ISR(USART_RX_vect){
	receive_flag=1;
}
ISR(USART_TX_vect){
	trans_flag=1;
}
ISR(USART_UDRE_vect){
	Data_Register_Empty=1;
}
void section_D(){
	UCSR0B = (1<<TXEN0) | (1<<RXEN0);
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00) | (1<<UMSEL01);
	//UBRR0L = 0x67; //103
	UBRR0H=0x00;
	UBRR0L = 0xCF; //207
	sei();
	unsigned char beginning_str[12] = "We Are Ready";
	unsigned char repeated_str[4] = "Bye!";
	unsigned char i;
	//unsigned char ch;
	//ch=0;
	
	i=0;
	if(trans_flag==1){
		UDR0 = beginning_str[i];
	}


}
void section_C(){
	int flag=0;
	//int times=0;
	unsigned char ch;
	unsigned char ch2;
	while(1){
		if(flag==0){
			do{
				while(!(UCSR0A & (1<<UDRE0)));
				UDR0 = 'a';
			}while(!(UCSR0A & (1<<RXC0)));
			ch = UDR0;	
			flag=1;
			for(int i=0;i<10;i++){
				while (!(UCSR0A & (1<<UDRE0)));
				UDR0 = ch;
			}	
		}		
		if(flag==1){
			while (!(UCSR0A & (1<<RXC0)));
			ch2 = UDR0;
			if(ch2==ch)flag=0;
		}
			}
	}
void section_B(){
	unsigned char beginning_str[12] = "We Are Ready";
	unsigned char repeated_str[4] = "Bye!";
	unsigned char i;
	unsigned char ch;
	
	usart_init();
	for (i = 0; i < 12; i++)
	{
		while (!(UCSR0A & (1<<UDRE0)));
		UDR0 = beginning_str[i];
	}
	while (1)
	{
		//detect 'H'
		do {
			while (!(UCSR0A & (1<<RXC0)));
			ch = UDR0;
		} while (ch != 'H');
		
		//detect 'i'
		while (!(UCSR0A & (1<<RXC0)));
		ch = UDR0;
		if (ch != 'i')
		{
			continue;
		}
		
		//send "Bye!"
		for (i = 0; i < 4; i++)
		{
			while (!(UCSR0A & (1<<UDRE0)));
			UDR0 = repeated_str[i];
		}
	}
}