#include "stm32f10x.h"                  // Device header
static __IO uint32_t msTicks;

void DelayMs(uint32_t ms)
{
 msTicks = ms; // Reload us value
 while (msTicks); // Wait until usTick reach zero
}

// SysTick_Handler function will be called every 1 ms
void SysTick_Handler()
{
 if (msTicks != 0) msTicks--;
}

void sectionC(void) {
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
 GPIO_InitTypeDef  GPIO_InitStructure;
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 GPIO_Init(GPIOA, &GPIO_InitStructure);
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // Enable APB2
 SystemCoreClockUpdate(); // Update SystemCoreClock value
	
	// Configure the SysTick timer to overflow every 1 ms
 SysTick_Config(SystemCoreClock / 1000);
    while(1) {
     GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);
     DelayMs(1000);
     GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET);
     DelayMs(1000);
     }
}
