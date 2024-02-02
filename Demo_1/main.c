#include "stm32f10x.h"                  // Device header
#include "PinMap.h"
#include "stdbool.h"
#include "stdio.h"

int main(void) {

	GPIO_init();
	TIM2_CH3_PWM_init();
	TIM3_CH1_PWM_init();
	USART2_init();
	GPIO_SetBits(Left_wheel_GPIO, Left_wheel_PIN);
	GPIO_ResetBits(Right_wheel_GPIO, Right_wheel_PIN);
	
	while(1) {
		
	}
}

