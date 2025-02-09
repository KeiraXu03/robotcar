#include "stm32f10x.h" // Device header
#include "stdbool.h"
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
void sectionG(void) {
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

GPIO_SetBits(L3_GPIO, L3_R_PIN);
while(1) {
if(state4==0)	{
GPIO_SetBits(L3_GPIO, L3_R_PIN);
} 
else {
GPIO_ResetBits(L3_GPIO, L3_R_PIN);
}
}
}void EXTI15_10_IRQHandler(void) {
if (EXTI_GetITStatus(EXTI_Line13) != RESET) {
INT_times+=1;
if(INT_times%3==0){
	state4=1-state4;
}
EXTI_ClearITPendingBit(EXTI_Line13);
}
}
