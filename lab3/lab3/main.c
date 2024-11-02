/*
 * lab3.c
 *
 * Created: 2023/9/29 10:28:06
 * Author : Zhuoning Xu
 */ 
#include <avr/io.h>
#include "avr/interrupt.h"
void Section_A_CTC();
void Section_B_CTC();
void Section_C_CTC();
void Delay_1_Sec_CTC();
void Delay_5_Sec_CTC();
void traffic_light();
void Blink();
void traffic();
volatile int Times=0;
volatile int delay_flag=0;
volatile int stop_flag=0;
int main(void)
{
	DDRB=0xFF;
	DDRC=0xFF;
	PORTC=(1<<0);//low
	//Section_A_CTC();
	Section_B_CTC();
	//Section_C_CTC();
}
ISR (TIMER0_COMPA_vect){
	PORTC^=(1<<0);//toggle
	OCR0A=0x02;
}
ISR (INT0_vect){
	Times++;
	if(Times==3){
		PORTC^=(1<<0);
		Times=0;
	}
}
ISR (INT1_vect){
	Times++;
	if(Times%2==1){
		PORTB = 0x00;
		PORTC = 0x00;
	}
	else{
		PORTB = 0xFF;
		PORTC = 0xFF;
	}
}
void Section_B_CTC(){
	EICRA=0x03;
	EIMSK = (1<<INT0);
	sei ();
	traffic();
}
void Section_C_CTC(){
	EICRA=0x0C;
	EIMSK = (1<<INT1);
	sei ();
	traffic();	
}
void Section_A_CTC(void){
	OCR0A=0x02;//3 times
	TCCR0A=0x02;
	TCCR0B=0x07;//rising edge CTC mode
	TIMSK0 = (1<<OCIE0A);
	sei ();
	traffic();

}
void Delay_1_Sec_CTC(void){//delay 1 sec use CTC mode
	OCR1A = 15624;//16M*1/1024-1
	TCCR1A = 0x00;//CTC MODE
	TCCR1B = 0x0D;
	while(delay_flag==0){
		if(stop_flag%2==0)return;
	};
	delay_flag=0;
}
ISR(TIMER1_COMPA_vect){
	delay_flag=1;
}
void Delay_5_Sec_CTC(void){//delay 5 sec use CTC mode
		for(int i=0;i<5;i++){
			Delay_1_Sec_CTC();
		}
	}
void Blink(void){//delay 0.2 sec use normal mode
	TCNT1H = 0xF3;//TCNT1=62411,65536-16M*1/1024/5
	TCNT1L = 0xC8;
	TCCR1A = 0x00;//normal mode
	TCCR1B = 0x05;//pre-scaler 1024
	while((TIFR1&(1<<TOV1))==0);
	TCCR1B = 0;//stop
	TIFR1 = 0x01<<TOV1;//clear
}
void traffic(void){
	sei ();
	while(1){
		PORTB=0x11;//STATE1
		PORTC|=(1<<4);
		Delay_5_Sec_CTC();
		PORTC&=~(1<<4);
		PORTB=0x21;
		PORTC|=(1<<4);//STATE2
		Delay_1_Sec_CTC();
		PORTC&=~(1<<4);
		PORTB=0x09;
		PORTC|=(1<<4);//STATE3
		Delay_1_Sec_CTC();
		PORTC&=~(1<<4);
		PORTB=0x0D;
		PORTC|=(1<<4);//STATE4
		Delay_1_Sec_CTC();
		PORTC&=~(1<<4);
		PORTB=0x0A;
		PORTC|=(1<<5);//STATE5
		Delay_5_Sec_CTC();
		PORTB=0x0C;
		PORTC|=(1<<5);//STATE6
		Blink();
		PORTC^=(1<<5);
		Blink();
		PORTC^=(1<<5);
		Blink();//0.2sec
		PORTC^=(1<<5);
		Blink();//0.2sec
		PORTB=0x09;
		PORTC&=~(1<<5);
		PORTC|=(1<<4);//STATE7
		Delay_1_Sec_CTC();
		PORTC&=~(1<<4);
		PORTB=0x29;
		PORTC|=(1<<4);//STATE8
		Delay_1_Sec_CTC();
	}
	}
void traffic_light(void){
		{
		PORTB=0x11;//STATE1
		PORTC|=(1<<4);
		Delay_5_Sec_CTC();
		PORTC&=~(1<<4);
		PORTB=0x21;
		PORTC|=(1<<4);//STATE2
		Delay_1_Sec_CTC();
		PORTC&=~(1<<4);
		PORTB=0x09;
		PORTC|=(1<<4);//STATE3
		Delay_1_Sec_CTC();
		PORTC&=~(1<<4);
		PORTB=0x0D;
		PORTC|=(1<<4);//STATE4
		Delay_1_Sec_CTC();
		PORTC&=~(1<<4);
		PORTB=0x0A;
		PORTC|=(1<<5);//STATE5
		Delay_5_Sec_CTC();
		PORTB=0x0C;
		PORTC|=(1<<5);//STATE6
		Blink();
		PORTC^=(1<<5);
		Blink();
		PORTC^=(1<<5);
		Blink();//0.2sec
		PORTC^=(1<<5);
		Blink();//0.2sec
		PORTB=0x09;
		PORTC&=~(1<<5);
		PORTC|=(1<<4);//STATE7
		Delay_1_Sec_CTC();
		PORTC&=~(1<<4);
		PORTB=0x29;
		PORTC|=(1<<4);//STATE8
		Delay_1_Sec_CTC();
	}
}
