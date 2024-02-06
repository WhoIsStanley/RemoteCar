#include "stm32f10x.h"                  // Device header
#include "PinMap.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char buffer[50], coor[50];
char *numx, *numy;
int x, y = 50;
int leftwheel, rightwheel;
int i, state, start = 0;

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
	memset(buffer, 0, sizeof(buffer));
	rightspeed(0);
	leftspeed(0);
	while(1) {
		if(state == 2){
		//USARTSend(buffer, sizeof(buffer));
		numx = strchr(buffer, 'X');
		x = atoi(numx + 1);
		numy = strchr(numx + 1, 'Y');
		y = atoi(numy + 1);
		memset(buffer, 0, sizeof(buffer));
		i = 0;
		USART_SendData(USART2, 'd');
		state = 1;
		//
		
		}
		if(40<=y && y<=60){
			leftspeed(0);
			rightspeed(0);
		}else if(y<40){
			GPIO_ResetBits(Left_wheel_GPIO, Left_wheel_PIN);
			GPIO_SetBits(Right_wheel_GPIO, Right_wheel_PIN);
			leftwheel = (y+10)*2;
			rightwheel = (y+10)*2;
			leftspeed(leftwheel);
			rightspeed(rightwheel);
		}else if(60<y){
			GPIO_SetBits(Left_wheel_GPIO, Left_wheel_PIN);
			GPIO_ResetBits(Right_wheel_GPIO, Right_wheel_PIN);
			rightwheel = (y-50)*2;
			leftwheel = (y-50)*2;
			leftspeed(leftwheel);
			rightspeed(rightwheel);
		}
		//left
//		if(x<20){
//			GPIO_ResetBits(Left_wheel_GPIO, Left_wheel_PIN);
//			leftwheel = (100-x*5);
//			leftspeed(leftwheel);
//		}else if(x <= 40){
//		
//		}
//		//right
//		else if(x>=60){
//			
//		}else if(x>80){
//		}
	}
}

void USART2_IRQHandler() {
	if(start == 0){
		USART_SendData(USART2, 'd');
		if(USART_GetITStatus(USART2, USART_IT_RXNE)){
		buffer[0] = USART_ReceiveData(USART2);
		if(buffer[0] == 'Z'){
			start = 1;
			state = 2;
		}
	}
	}
	if(state == 1){
	if(USART_GetITStatus(USART2, USART_IT_RXNE)){
		buffer[i] = USART_ReceiveData(USART2);
		if(buffer[i] == 'Z'){
			state = 2;
		}
		i++;
	}
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