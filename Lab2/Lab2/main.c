#include <avr/io.h>
void Section_A_normal();
void Section_A_CTC();
void Delay_1_Sec();
void Delay_5_Sec();
void Delay_1_Sec_CTC();
void Delay_5_Sec_CTC();
void Section_B_normal();
void Section_B_CTC();
void Section_C();
int main(void)
{
	//Section_A_normal();
	//Section_A_CTC();
	//Section_B_normal();
	//Section_B_CTC();
	Section_C();
}
void Section_A_normal(void){
	DDRB|=(1<<0);
	while (1){
		PORTB^=(1<<0);//toggle PB0
		TCNT1H = 0xC2;//TCNT1=49911,65536-16M*1/1024
		TCNT1L = 0xF7;
		TCCR1A = 0x00;//normal mode
		TCCR1B = 0x05;//pre-scaler 1024
		while((TIFR1&(1<<TOV1))==0);
		TCCR1B = 0;//stop
		TIFR1 = 0x01<<TOV1;//clear
	}
}
void Section_A_CTC(void){
	DDRB|=(1<<0);
	while (1){
		PORTB^=(1<<0);//toggle PB0
		OCR1A = 15624;//16M*1/1024-1
		TCCR1A = 0x00;//normal mode
		TCCR1B = 0x0D;//pre-scaler 1024
		while((TIFR1&(1<<OCF1A))==0);
		TCCR1B = 0;//stop
		TIFR1 = 0x01<<OCF1A;//clear
	}
}
void Delay_1_Sec(void){//delay 1 sec use normal mode
	TCNT1H = 0xC2;//TCNT1=49911,65536-16M*1/1024
	TCNT1L = 0xF7;
	TCCR1A = 0x00;//normal mode
	TCCR1B = 0x05;//pre-scaler 1024
	while((TIFR1&(1<<TOV1))==0);
	TCCR1B = 0;//stop
	TIFR1 = 0x01<<TOV1;//clear
}
void Delay_5_Sec(void){//delay 5 sec use normal mode
	for(int i=1;i<=5;i++){
		TCNT1H = 0xC2;//TCNT1=49911,65536-16M*1/1024
		TCNT1L = 0xF7;
		TCCR1A = 0x00;//normal mode
		TCCR1B = 0x05;//pre-scaler 1024
		while((TIFR1&(1<<TOV1))==0);
		TCCR1B = 0;//stop
		TIFR1 = 0x01<<TOV1;//clear
	}
}
void Delay_1_Sec_CTC(void){//delay 1 sec use CTC mode
		OCR1A = 15624;//16M*1/1024-1
		TCCR1A = 0x00;//normal mode
		TCCR1B = 0x0D;//pre-scaler 1024
		while((TIFR1&(1<<OCF1A))==0);
		TCCR1B = 0;//stop
		TIFR1 = 0x01<<OCF1A;//clear
}
void Delay_5_Sec_CTC(void){//delay 5 sec use CTC mode
	for(int i=1;i<=5;i++){
		OCR1A = 15624;//16M*1/1024-1
		TCCR1A = 0x00;//normal mode
		TCCR1B = 0x0D;//pre-scaler 1024
		while((TIFR1&(1<<OCF1A))==0);
		TCCR1B = 0;//stop
		TIFR1 = 0x01<<OCF1A;//clear
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
void Section_B_normal(void){
	DDRB=0xFF;
	DDRC=0xFF;
	while(1){
		PORTB=0x11;//STATE1
		PORTC=0x10;
		Delay_5_Sec();
		PORTB=0x21;
		PORTC=0x10;//STATE2
		Delay_1_Sec();
		PORTB=0x09;
		PORTC=0x10;//STATE3
		Delay_1_Sec();
		PORTB=0x0D;
		PORTC=0x10;//STATE4
		Delay_1_Sec();
		PORTB=0x0A;
		PORTC=0x20;;//STATE5
		Delay_5_Sec();
		PORTB=0x0C;
		PORTC=0x00;//STATE6
		Blink();
		PORTC=0x20;
		Blink();
		PORTC=0x00;
		Blink();
		PORTC=0x20;
		Blink();
		PORTB=0x09;
		PORTC=0x10;//STATE7
		Delay_1_Sec();
		PORTB=0x29;
		PORTC=0x10;//STATE8
		Delay_1_Sec();
	}
}
void Section_B_CTC(void){
	DDRB=0xFF;
	DDRC=0xFF;
	while(1){
		PORTB=0x11;//STATE1
		PORTC=0x10;
		Delay_5_Sec_CTC();
		PORTB=0x21;
		PORTC=0x10;//STATE2
		Delay_1_Sec_CTC();
		PORTB=0x09;
		PORTC=0x10;//STATE3
		Delay_1_Sec_CTC();
		PORTB=0x0D;
		PORTC=0x10;//STATE4
		Delay_1_Sec_CTC();
		PORTB=0x0A;
		PORTC=0x20;;//STATE5
		Delay_5_Sec_CTC();
		PORTB=0x0C;
		PORTC=0x00;//STATE6
		Blink();
		PORTC=0x20;
		Blink();
		PORTC=0x00;
		Blink();//0.2sec
		PORTC=0x20;
		Blink();//0.2sec
		PORTB=0x09;
		PORTC=0x10;//STATE7
		Delay_1_Sec_CTC();
		PORTB=0x29;
		PORTC=0x10;//STATE8
		Delay_1_Sec_CTC();
	}
}
void Section_C(void){
	//DDRD=0x00;
	DDRC|=(1<<0);//output
	PORTC=(0<<0);//low
	while(1){
		OCR1A=0x02;//3 times
		TCCR1A=0x00;
		TCCR1B=0x0F;//rising edge CTC mode
		while((TIFR1 & (1<<OCF1A))==0){
		}
		TCCR1B = 0;//stop
		TIFR1=0x01<<OCF1A;//clear
		PORTC^=(1<<0);//toggle
	}
}
