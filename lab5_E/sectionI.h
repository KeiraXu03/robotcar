#include "stm32f10x.h" // Device header
#include "string.h"
char msg[] = "We are ready!";
//char bye[] = "Bye!";
uint8_t msg_i=0;
int state6=0;
unsigned char character;
unsigned char ch;
int sendtimes=0;
void sectionI(void) {
msg_i=0;
//USART2 TX RX
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
GPIO_InitTypeDef GPIO_InitStructure;
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
GPIO_Init(GPIOA, &GPIO_InitStructure);
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
GPIO_Init(GPIOA, &GPIO_InitStructure);
//USART2 ST-LINK USB
RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
USART_InitTypeDef USART_InitStructure;
USART_InitStructure.USART_BaudRate = 9600;
USART_InitStructure.USART_WordLength = USART_WordLength_8b;
USART_InitStructure.USART_StopBits = USART_StopBits_1;
USART_InitStructure.USART_Parity = USART_Parity_No;
USART_InitStructure.USART_HardwareFlowControl =
USART_HardwareFlowControl_None;
USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
USART_Init(USART2, &USART_InitStructure);
USART_Cmd(USART2, ENABLE);
NVIC_InitTypeDef NVIC_InitStructure;
// Enable the USART2 TX Interrupt
USART_ITConfig(USART2, USART_IT_TC, ENABLE );
NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);
// Enable the USART2 RX Interrupt
USART_ITConfig(USART2, USART_IT_RXNE, ENABLE );
NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);
while(1) {
}
}
void USART2_IRQHandler() {
if(USART_GetITStatus(USART2, USART_IT_TC) != RESET) {
if(state6==0) {
USART_SendData(USART2, 'a');
}
else if(state6==1){
	sendtimes+=1;
	USART_SendData(USART2, ch);
	if(sendtimes==10){
	sendtimes=0;
		state6=2;
	}
}
//USART_ClearITPendingBit(USART2, USART_IT_TC);
}
if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
	if(state6==0){
		ch = (unsigned char) USART_ReceiveData(USART2);
		state6=1;
	}
	else if(state6==2){
		//USART_SendData(USART2, 'F');
		character = (unsigned char) USART_ReceiveData(USART2); 
		if(character==ch){
			state6=0;
		}
	}

	
//USART_SendData(USART2, character);
}
}