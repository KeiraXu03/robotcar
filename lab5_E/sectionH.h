#include "stm32f10x.h" // Device header
#include "stdbool.h"
int timecount=0;
int statef=0;
void clear(void);
//PC13
#define BUTTON_RCC_GPIO RCC_APB2Periph_GPIOC
#define BUTTON_GPIO GPIOC
#define BUTTON_GPIO_PIN GPIO_Pin_13
#define BUTTON_EXTI_LINE EXTI_Line13
#define BUTTON_GPIO_PORTSOURCE GPIO_PortSourceGPIOC
#define BUTTON_GPIO_PINSOURCE GPIO_PinSource13
#define L3_RCC_GPIO RCC_APB2Periph_GPIOB
#define L3_GPIO GPIOB
#define L3_R_PIN GPIO_Pin_8
#define L3_G_PIN GPIO_Pin_9
int state4=1;
int INT_times=0;
bool state3 = false;
bool state3_changed = false;
void sectionH(void) {
GPIO_InitTypeDef GPIO_InitStruct;
// GPIO clock for I/O
RCC_APB2PeriphClockCmd(BUTTON_RCC_GPIO, ENABLE); // GPIOC
RCC_APB2PeriphClockCmd(L3_RCC_GPIO, ENABLE); //GPIOB
RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); //AFIO
// Configure I/O for L3
GPIO_InitStruct.GPIO_Pin = L3_R_PIN | L3_G_PIN;
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
GPIO_Init(L3_GPIO, &GPIO_InitStruct);
// Configure I/O for EXTI13
GPIO_InitStruct.GPIO_Pin = BUTTON_GPIO_PIN;
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
GPIO_Init(BUTTON_GPIO, &GPIO_InitStruct);
// EXTI Configuration, GPIOC, Pin 13
GPIO_EXTILineConfig(BUTTON_GPIO_PORTSOURCE, BUTTON_GPIO_PINSOURCE);
EXTI_InitTypeDef EXTI_InitStruct;
EXTI_InitStruct.EXTI_Line = BUTTON_EXTI_LINE;
EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
EXTI_InitStruct.EXTI_LineCmd = ENABLE;
EXTI_Init(&EXTI_InitStruct);
// Enable Interrupt
NVIC_InitTypeDef NVIC_InitStruct;
NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x02;
NVIC_Init(&NVIC_InitStruct);

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
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &timerInitStructure);
	TIM_Cmd(TIM2, ENABLE);
	//Enable update event for Timer2
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	NVIC_EnableIRQ(TIM2_IRQn);
while(1) {
if(state4==0)	{
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
else {
clear();
	timecount=0;
}
}
}void EXTI15_10_IRQHandler(void) {
if (EXTI_GetITStatus(EXTI_Line13) != RESET) {
INT_times+=1;
	state4=1-state4;

EXTI_ClearITPendingBit(EXTI_Line13);
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

