#include <avr/io.h>
int state=0;
void delay_1_second(void);
void lab_1(void);
void Section_B_1(void);
void Section_B_2(void);
int main(void)
{
	while(1){
	//lab_1();
	Section_B_1();	
	//Section_B_2();	
	}

}
void delay_1_second(void){
	for(unsigned int i=1;i<=1600;i++){
		for(int j=1;j<=1000;j++){			
		}
	}
}
void lab_1(void){
		DDRD = 0xFF;
		while(1)
		{
			PORTD = 0xFF;
			delay_1_second();
			PORTD = 0x55;
			delay_1_second();
		}
}
void Section_B_1(void){
	DDRB &=(~(1<<0));
	PORTB |=(1<<0);
	if(PINB&(1<<0)){
		DDRD |=(1<<2);
		PORTD|=(1<<2);
	}
	else{
		PORTD &=(~(1<<2));
	}
}
void Section_B_2(void){
	DDRB &=(~(1<<0));
	PORTB |=(1<<0);
	if(PINB&(1<<0)&&state==0){
		DDRD = 0xFF;
		PORTD = 0xFF;
		state=1;
	}
	if(PINB&(1<<0)&&state==1){
			DDRD = 0xFF;
			PORTD = 0x00;
			state=0;
		}
}

