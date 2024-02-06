#include "stm32f10x.h"                  // Device header
#include "PinMap.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

unsigned char buffer[50], coor[50];
char *numx, *numy;
unsigned char key;
int leftwheel, rightwheel;
int state, start = 0;

void rightspeed(int speed);
void leftspeed(int speed);

int main(void) {

	GPIO_init();
	TIM2_CH3_PWM_init();
	TIM3_CH1_PWM_init();
	USART2_init();
	//default Forward
	GPIO_SetBits(Left_wheel_GPIO, Left_wheel_PIN);
	GPIO_ResetBits(Right_wheel_GPIO, Right_wheel_PIN);
	rightspeed(0);
	leftspeed(0);
	while(1) {
		
		switch(key){
			case 'a':
				GPIO_SetBits(Left_wheel_GPIO, Left_wheel_PIN);
				GPIO_ResetBits(Right_wheel_GPIO, Right_wheel_PIN);
				rightspeed(67);
				leftspeed(58);
				break;
			case 'b':
				GPIO_ResetBits(Left_wheel_GPIO, Left_wheel_PIN);
				GPIO_ResetBits(Right_wheel_GPIO, Right_wheel_PIN);
				rightspeed(35);
				leftspeed(40);
				break;
			case 'c':
				GPIO_ResetBits(Left_wheel_GPIO, Left_wheel_PIN);
				GPIO_SetBits(Right_wheel_GPIO, Right_wheel_PIN);
				rightspeed(67);
				leftspeed(58);
				break;
			case 'd':
				GPIO_SetBits(Left_wheel_GPIO, Left_wheel_PIN);
				GPIO_SetBits(Right_wheel_GPIO, Right_wheel_PIN);
				rightspeed(40);
				leftspeed(35);
				break;
			case 'e':
				rightspeed(0);
				leftspeed(0);
				break;
		}
	}
}

void USART2_IRQHandler() {
	if(USART_GetITStatus(USART2, USART_IT_RXNE)){
		key = USART_ReceiveData(USART2);
		start = 1;
	}
}

void rightspeed(int speed){
	TIM_OCInitTypeDef outputChannelInit;
	outputChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
	outputChannelInit.TIM_Pulse = speed; // set duty cycle
	outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
	outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &outputChannelInit);
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
}

void leftspeed(int speed){
	TIM_OCInitTypeDef outputChannelInit;
	outputChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
	outputChannelInit.TIM_Pulse = speed; // set duty cycle
	outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
	outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM2, &outputChannelInit);
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
}