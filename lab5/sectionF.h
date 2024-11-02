#include "stm32f10x.h"                  // Device header

#define sw GPIO_Pin_1 //A
#define LED GPIO_Pin_0 //B


int main(void){
	
	
	GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef timerInitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
   
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 
  	timerInitStructure.TIM_Prescaler = 0;
  	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  	timerInitStructure.TIM_Period = 2;
  	timerInitStructure.TIM_ClockDivision = 0;
  	timerInitStructure.TIM_RepetitionCounter = 0;
  	TIM_TimeBaseInit(TIM2, &timerInitStructure);
  	TIM_Cmd(TIM2, ENABLE);
	
		TIM_TIxExternalClockConfig(TIM2, TIM_TIxExternalCLK1Source_TI2, TIM_ICPolarity_Rising, 0);
	
	//Enable update event for Timer2
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	NVIC_EnableIRQ(TIM2_IRQn);
		
	while(1){
			
	}
	
	
}

int state = 0;

void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
		if(state == 0) {
			GPIO_ResetBits(GPIOB, LED);		
			state = 1;
			
		} 
		else if(state == 1){
			GPIO_SetBits(GPIOB, LED);
			state = 0;
		}
		
	  
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}
	}