#include "stm32f10x.h"                  // Device header


void delay(int t) {
int i;
for(i = 0; i < t; i++) 
	GPIOB->BSRR |= 0x10;
}
void sectionB(){
RCC->APB2ENR |= RCC_APB2Periph_GPIOA; //PA5, enable APB2 peripheral clock
GPIOA->CRL &= 0xFF0FFFFF; //clear the setting
GPIOA->CRL |= 0 << 22 | 2 << 20; //GPIO_Mode_Out_PP, GPIO_Speed_2MHz
while(1) {
GPIOA->BSRR |= 0x20;
delay(5000000);
GPIOA->BRR |= 0x20;
delay(5000000);
}
}
