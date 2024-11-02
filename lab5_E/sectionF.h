#include "stm32f10x.h"	// Device header 
#include "stdbool.h"
#include "stm32f10x_exti.h" 
int timecount=0;
int statef=0;
void clear(void);
void sectionF(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	
	////GPIO set up for PB8 (G)
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	////GPIO set up for PB9 (Y)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	//GPIO set up for PA5 (R)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
///GPIO set up for PA6 (Y)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	////GPIO set up for PA7 (G)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	////GPIO set up for PB6 (R)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	////GPIO set up for PC7 (R)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	////GPIO set up for PA9 (G)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//Timer 2 set up 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseInitTypeDef timerInitStructure;
	timerInitStructure.TIM_Prescaler = 18000 - 1;	
	timerInitStructure.TIM_Period = 400 - 1;
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &timerInitStructure);
	TIM_Cmd(TIM2, ENABLE);
	//Enable update event for Timer2
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	NVIC_EnableIRQ(TIM2_IRQn);
	while(1){
			if(timecount<50){
				clear();
				GPIO_SetBits(GPIOA, GPIO_Pin_5); 		
				GPIO_SetBits(GPIOA, GPIO_Pin_7); 		
				GPIO_SetBits(GPIOC, GPIO_Pin_7); 		
			}
			//state 2
			else if(timecount>=50&&timecount<60){
				clear();
				GPIO_SetBits(GPIOA, GPIO_Pin_5);
				GPIO_SetBits(GPIOA, GPIO_Pin_6); 		
				GPIO_SetBits(GPIOC, GPIO_Pin_7); 	
			}
						//state 3
			else if(timecount>=60&&timecount<70){
				clear();
				GPIO_SetBits(GPIOA, GPIO_Pin_5);
				GPIO_SetBits(GPIOB, GPIO_Pin_6); 		
				GPIO_SetBits(GPIOC, GPIO_Pin_7); 	
			}
							//state 4
			else if(timecount>=70&&timecount<80){
				clear();
				GPIO_SetBits(GPIOA, GPIO_Pin_5);
				GPIO_SetBits(GPIOB, GPIO_Pin_9); 		
				GPIO_SetBits(GPIOB, GPIO_Pin_6); 		
				GPIO_SetBits(GPIOC, GPIO_Pin_7); 	
			}	
			//state 5
			else if(timecount>=80&&timecount<130){
				clear();
				GPIO_SetBits(GPIOB, GPIO_Pin_8); 		
				GPIO_SetBits(GPIOB, GPIO_Pin_6); 		
				GPIO_SetBits(GPIOA, GPIO_Pin_9); 	
			}					
			//state 6
			else if(timecount>=130&&timecount<140){
				clear();
				if(timecount%2==0)GPIO_SetBits(GPIOB, GPIO_Pin_8); 
				else GPIO_ResetBits(GPIOB, GPIO_Pin_9); 		
				GPIO_SetBits(GPIOB, GPIO_Pin_6); 		
				GPIO_SetBits(GPIOA, GPIO_Pin_9); 	
			}		
			//state 7
			else if(timecount>=140&&timecount<150){
				clear();
				GPIO_SetBits(GPIOA, GPIO_Pin_5); 		
				GPIO_SetBits(GPIOB, GPIO_Pin_6); 		
				GPIO_SetBits(GPIOC, GPIO_Pin_7); 	
			}	
			//state 8
			else if(timecount>=150&&timecount<160){
				clear();
				GPIO_SetBits(GPIOA, GPIO_Pin_5); 		
				GPIO_SetBits(GPIOB, GPIO_Pin_6); 
				GPIO_SetBits(GPIOA, GPIO_Pin_6); 
				GPIO_SetBits(GPIOC, GPIO_Pin_7); 	
			}
			else{
			timecount=0;
			}
	}
}
//Interrupt Subroutine
void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
		timecount+=1;
TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}
}
void clear(void){
	GPIO_Write(GPIOA,RESET);
	GPIO_Write(GPIOB,RESET);
	GPIO_Write(GPIOC,RESET);
	GPIO_Write(GPIOD,RESET);
}
