#include <avr/io.h>
#include "avr/interrupt.h"
volatile int delay_flag=0;
volatile int stop_flag=0;
void delay_0_2_sec();
void delay_1_sec();
void delay_5_sec();
int main()
{
	DDRB=0xFF;
	DDRC=0xFF;
	TIMSK1=(1<<OCIE1A);
	EICRA=0x0C;
	EIMSK = (1<<INT1);
	sei ();
	while(1){
		
		while(stop_flag%2==0);
		
		
		if(stop_flag%2==0){
			PORTB=0x00;//STATE1
			PORTC=0x00;
			stop_flag=0;
			continue;
		}
		else{
		PORTB=0x11;//STATE1
		PORTC|=(1<<4);
		for(int i=1;i<=5;i++){
		OCR1A = 15624;//16M*1/1024-1
		TCCR1A = 0x00;//CTC MODE
		TCCR1B = 0x0D;
		while(delay_flag==0){
			if(stop_flag%2==0)break;
		}
		delay_flag=0;
		}
		
		}
		
		
		if(stop_flag%2==0){
			PORTB=0x00;
			PORTC=0x00;
			stop_flag=0;
			continue;
		}
		else{
		PORTC&=~(1<<4);
		PORTB=0x21;
		PORTC|=(1<<4);//STATE2	
		
		
					OCR1A = 15624;//16M*1/1024-1
					TCCR1A = 0x00;//CTC MODE
					TCCR1B = 0x0D;
					while(delay_flag==0){
						if(stop_flag%2==0)break;
					};
					delay_flag=0;	
		}
		
		
		
		if(stop_flag%2==0){
			PORTB=0x00;
			PORTC=0x00;
			stop_flag=0;
			continue;
		}
		else{
		PORTC&=~(1<<4);
		PORTB=0x09;
		PORTC|=(1<<4);//STATE3	
		
							OCR1A = 15624;//16M*1/1024-1
							TCCR1A = 0x00;//CTC MODE
							TCCR1B = 0x0D;
							while(delay_flag==0){
								if(stop_flag%2==0)break;
							};
							delay_flag=0;	
		}
		
		if(stop_flag%2==0){
			PORTB=0x00;
			PORTC=0x00;
			continue;
		}
		else{
			PORTC&=~(1<<4);
			PORTB=0x0D;
			PORTC|=(1<<4);//STATE4
			
								OCR1A = 15624;//16M*1/1024-1
								TCCR1A = 0x00;//CTC MODE
								TCCR1B = 0x0D;
								while(delay_flag==0){
									if(stop_flag%2==0)break;
								};
								delay_flag=0;
		}	
		
		if(stop_flag%2==0){
			PORTB=0x00;
			PORTC=0x00;
			continue;
		}
		else{
		PORTC&=~(1<<4);
		PORTB=0x0A;
		PORTC|=(1<<5);//STATE5
		
		for(int i=1;i<=5;i++){				
				OCR1A = 15624;//16M*1/1024-1
				TCCR1A = 0x00;//CTC MODE
				TCCR1B = 0x0D;
				while(delay_flag==0){
					if(stop_flag%2==0)break;
				};
				delay_flag=0;	
			}

		}		
		
		if(stop_flag%2==0){
			PORTB=0x00;
			PORTC=0x00;
			continue;
		}
		else{
			PORTB=0x0C;
			PORTC|=(1<<5);//STATE6
			delay_0_2_sec();
			PORTC^=(1<<5);
			delay_0_2_sec();
			PORTC^=(1<<5);
			delay_0_2_sec();//0.2sec
			PORTC^=(1<<5);
			delay_0_2_sec();//0.2sec
			PORTB=0x09;
			PORTC&=~(1<<5);
			PORTC|=(1<<4);//STATE7
			delay_0_2_sec();
		}		
		
		if(stop_flag%2==0){
			PORTB=0x00;
			PORTC=0x00;
			continue;
		}
		else{
		PORTC&=~(1<<4);
		PORTB=0x29;
		PORTC|=(1<<4);//STATE8
		
							OCR1A = 15624;//16M*1/1024-1
							TCCR1A = 0x00;//CTC MODE
							TCCR1B = 0x0D;
							while(delay_flag==0){
								if(stop_flag%2==0)break;
							};
							delay_flag=0;
		}
	}
}
ISR (INT1_vect){
	stop_flag=stop_flag+1;
	PORTB=0x00;
	PORTC=0x00;
}
ISR(TIMER1_COMPA_vect){
	delay_flag=1;
}
void delay_1_sec(){
	OCR1A = 15624;//16M*1/1024-1
	TCCR1A = 0x00;//CTC MODE
	TCCR1B = 0x0D;
	while(delay_flag==0){
		if(stop_flag%2==0)return;
		};
	delay_flag=0;
}
void delay_5_sec(){
	for(int i=0;i<5;i++){
		delay_1_sec();
	}
}
void delay_0_2_sec(){
	OCR1A = 3124;//16M*1/1024-1
	TCCR1A = 0x00;//CTC MODE
	TCCR1B = 0x0D;
	while(delay_flag==0);
	delay_flag=0;
}