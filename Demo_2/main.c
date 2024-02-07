#include "stm32f10x.h"    
#include "PinMap.h"

int state = 0;

void rightspeed(int speed);
void leftspeed(int speed);
	
int main(void){
	GPIO_init();
	TIM2_CH3_PWM_init();
	TIM3_CH1_PWM_init();
	USART2_init();
	leftspeed(0);
	rightspeed(0);
	
	while(1){
			switch(state){
				case 1:
					USART_SendData(USART2, 'a');
					while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
					state = 0;
					break;
				case 3:
					USART_SendData(USART2, 'c');
					while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
					state = 0;
					break;
				case 5:
					USART_SendData(USART2, 'e');
					while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
					state = 0;
					break;
				default:
					break;
			}
	}
}

void EXTI9_5_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line5) != RESET) {				
			state = 3;
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
	if (EXTI_GetITStatus(EXTI_Line6) != RESET) {				
			state = 4;
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
	if (EXTI_GetITStatus(EXTI_Line7) != RESET) {				
			state = 5;
		EXTI_ClearITPendingBit(EXTI_Line7);
	}
}

void EXTI4_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line4) != RESET) {				
		state = 2;
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}

void EXTI0_IRQHandler(void){
	if (EXTI_GetITStatus(EXTI_Line0) != RESET){
		state = 1;
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}



