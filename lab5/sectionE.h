#include "stm32f10x.h"                  // Device header
unsigned int state=0;
void sectionE(void) {
	 SysTick_Config(SystemCoreClock / 1000);
while(1){
GPIO_InitTypeDef GPIO_InitStructure;
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init(GPIOA, &GPIO_InitStructure);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
GPIO_Init(GPIOC, &GPIO_InitStructure);
GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET);

	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)==0){
		state = ~state;
		DelayMs(70);
	}
		if(state==0){
		 GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET);
		}
	  else{
		 GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);
   }
 }
}
