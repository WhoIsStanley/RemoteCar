#include "stm32f10x.h"    
#include "PinMap.h"
#include "string.h"
#include "stdio.h"
#include "stdbool.h"

int state,count,lspeed,rspeed,doonce = 0;
unsigned char lintk[7] = "00000\r\n";
unsigned int pevstate,storestate = 0;
unsigned char str[50] = "";
static __IO uint32_t msTicks;

int ignore = 0;
int chanmode=0;

void DelayMs(uint32_t ms){
	msTicks = ms;
	while (msTicks);
}

void rightspeed(int speed);
void leftspeed(int speed);
void xlinecheck(void);
void intclinecheck(void);
void linecheck(void);
	
int main(void){
	GPIO_init();
	TIM2_CH3_PWM_init();
	TIM3_CH1_PWM_init();
//	TIM2_CH2_IC2_init();
	TIM4_CH1_IC1_init();
	USART2_init();
	leftspeed(0);
	rightspeed(0);
	SystemCoreClockUpdate();
	
	SysTick_Config(SystemCoreClock / 1000);
	
	//default Forward
	GPIO_SetBits(Left_wheel_GPIO, Left_wheel_PIN);
	GPIO_ResetBits(Right_wheel_GPIO, Right_wheel_PIN);
	while(1){
		if(!(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13))){
			leftspeed(8000);
			rightspeed(8000);
			DelayMs(20);
			state = 1;
			count = 0;
			lspeed = 2000;
			rspeed = 3500;
		}

		//ok
		
		//Sending//
//		USARTSend(lintk, sizeof(lintk));
		memset(str, 0, sizeof(str));
		sprintf(str, "state:%d pevstate:%d storestate:%d\r\n", state, pevstate, storestate);
		USARTSend(str, sizeof(str));	
		memset(str, 0, sizeof(str));
		sprintf(str, "Left:%d Right:%d\r\n", lspeed, rspeed);
		USARTSend(str, sizeof(str));
		
		//pevstate 
		//0=centre
		//1=left
		//2=right
		//3=out		
		
		
		if(state != 0){
			chanmode=0;
			leftspeed(5000);
			rightspeed(5000);
			DelayMs(10);
			
			switch(state){
				case 1:
					if(count<20)
						intclinecheck();
					else{
						linecheck();
					}
					break;
					
				case 2:
					if(count<80)
						linecheck();
					else{
						intclinecheck();
					}
					break;
					
				case 3:
					if(count<20)
						intclinecheck();
					else{
						linecheck();
					}
					break;
					
				case 4:
					if(count<140)
						intclinecheck();
					else{
						xlinecheck();
					}
					break;
					
				case 5:
						xlinecheck();
					break;
					
				case 6:
					if(count<20)
						intclinecheck();
					else{
						linecheck();
					}
					break;
			}
			leftspeed(lspeed*1.075);
			rightspeed(rspeed*1.175);
			if((lintk[4] == '0'||lintk[3] == '0') && lintk[2] == '0' && (lintk[0] == '0'||lintk[1] == '0') && count > 10){
				state++;
				count = 0;
				doonce = 0;
			}
		}
		
		DelayMs(100);
		//while_end
	}
}
void intclinecheck(void){
	//11111
	if(lintk[2] == '1' && lintk[4] == '1' && lintk[0] == '1' && lintk[1] == '1' && lintk[3] == '1'){
		if(pevstate != 3){
			switch(pevstate){
				//pev r
				case 2:
					lspeed = 1300;
					rspeed = 1400;
					storestate = 2;
					break;
			}
			pevstate = 3;
			
		}else{
			if(storestate == 2){
			lspeed = 1300;
			rspeed = 1400;}
		}
	}
	
	//little right
	else if(lintk[3] == '0'){
		//11101
		if(lintk[4] == '0'){
			lspeed = 1200;
			rspeed = 1400;
		}
		else if(pevstate == 0 || pevstate == 1){
			lspeed = 1200;
			rspeed = 1400;
			storestate = 0;
		}else{
			if(storestate == 0){
				lspeed = 1200;
				rspeed = 1400;}
		}
	}
	//Right//
	if(lintk[4] == '0'){
		//11110
		if(pevstate != 1){
			switch(pevstate){
				case 0:
					lspeed = 1300;
					rspeed = 1400;
					storestate = 0;
					break;
				case 2:
					break;
				case 3:
					lspeed = 1300;
					rspeed = 1400;
					storestate = 3;
					break;
			}
			pevstate = 1;
		}else{
			if(storestate == 0){
			lspeed = 1300;
			rspeed = 1400;}
			else if(storestate == 3){
			lspeed = 1300;
			rspeed = 1400;}
		}
	}
	
	//Center//
	else if(lintk[2] == '0'){
		if(pevstate != 0){
			lspeed = 1125;
			rspeed = 1475;
			pevstate = 0;
		}
		else{
			lspeed = 1125;
			rspeed = 1475;
		}
	}
}
void xlinecheck(void){
	//11111
	if(lintk[2] == '1' && lintk[4] == '1' && lintk[0] == '1' && lintk[1] == '1' && lintk[3] == '1'){
		if(pevstate != 3){
			switch(pevstate){
				case 0:
					break;
				//pev l
				case 1:
					lspeed = 1350;
					rspeed = 0;
					storestate = 1;
					break;
				//pev r
				case 2:
					lspeed = 1350;
					rspeed = 0;
					storestate = 2;
					break;
			}
			pevstate = 3;
		}else{
			if(storestate == 1){
			lspeed = 1350;
			rspeed = 0;}
			else if(storestate == 2){
			lspeed = 0;
			rspeed = 1350;}
		}
	}
	//little left
	if(lintk[1] == '0'){
		//10111
		if(lintk[0] == '0'){
			lspeed = 1125;
			rspeed = 1275;
		}
		else if(pevstate == 0 || pevstate == 2){
			lspeed = 1125;
			rspeed = 1275;
			storestate = 0;
		}else{
			if(storestate == 0){
				lspeed = 1125;
				rspeed = 1275;}
		}
	}
	
	//little right
	else if(lintk[3] == '0'){
		//11101
		if(lintk[4] == '0'){
			lspeed = 1125;
			rspeed = 1275;
		}
		else if(pevstate == 0 || pevstate == 1){
			lspeed = 1275;
			rspeed = 1125;
			storestate = 0;
		}else{
			if(storestate == 0){
				lspeed = 1275;
				rspeed = 1125;}
		}
	}
	//Right//
	if(lintk[4] == '0'){
		//11110
		if(pevstate != 1){
			switch(pevstate){
				case 0:
					lspeed = 1350;
					rspeed = 0;
					storestate = 0;
					break;
				case 2:
					break;
				case 3:
					lspeed = 1350;
					rspeed = 1100;
					storestate = 3;
					break;
			}
			pevstate = 1;
		}else{
			if(storestate == 0){
			lspeed = 1350;
			rspeed = 0;}
			else if(storestate == 3){
			lspeed = 1350;
			rspeed = 1100;}
		}
	}
	
	//Left//
	else if(lintk[0] == '0'){
		//01111
		if(pevstate != 2){
			switch(pevstate){
				case 0:
					lspeed = 0;
					rspeed = 1350;
					storestate = 0;
					break;
				case 1:
					break;
				case 3:
					lspeed = 1100;
					rspeed = 1350;
					break;
			}
			pevstate = 2;
		}else{
			if(storestate == 0){
			lspeed = 0;
			rspeed = 1350;}
			else if(storestate == 3){
			lspeed = 1100;
			rspeed = 1350;}
		}
	}
	
	//Center//
	else if(lintk[2] == '0'){
		if(pevstate != 0){
			lspeed = 1225;
			rspeed = 1275;
			pevstate = 0;
		}
		else{
			lspeed = 1225;
			rspeed = 1275;
		}
	}
}


void linecheck(void){
	//11111
	if(lintk[2] == '1' && lintk[4] == '1' && lintk[0] == '1' && lintk[1] == '1' && lintk[3] == '1'){
		if(pevstate != 3){
			switch(pevstate){
				case 0:
					break;
				//pev l
				case 1:
					lspeed = 1550;
					rspeed = 1100;
					storestate = 1;
					break;
				//pev r
				case 2:
					lspeed = 1200;
					rspeed = 1550;
					storestate = 2;
					break;
			}
			pevstate = 3;
		}else{
			if(storestate == 1){
			lspeed = 1550;
			rspeed = 1100;}
			else if(storestate == 2){
			lspeed = 1200;
			rspeed = 1550;}
		}
	}
	//little left
	if(lintk[1] == '0'){
		//10111
		if(lintk[0] == '0'){
			lspeed = 1400;
			rspeed = 1500;
		}
		else if(pevstate == 0 || pevstate == 2){
			lspeed = 1400;
			rspeed = 1500;
			storestate = 0;
		}else{
			if(storestate == 0){
				lspeed = 1400;
				rspeed = 1500;}
		}
	}
	
	//little right
	else if(lintk[3] == '0'){
		//11101
		if(lintk[4] == '0'){
			lspeed = 1350;
			rspeed = 1500;
		}
		else if(pevstate == 0 || pevstate == 1){
			lspeed = 1500;
			rspeed = 1350;
			storestate = 0;
		}else{
			if(storestate == 0){
				lspeed = 1500;
				rspeed = 1350;}
		}
	}
	//Right//
	if(lintk[4] == '0'){
		//11110
		if(pevstate != 1){
			switch(pevstate){
				case 0:
					lspeed = 1575;
					rspeed = 1100;
					storestate = 0;
					break;
				case 2:
					break;
				case 3:
					lspeed = 1575;
					rspeed = 1200;
					storestate = 3;
					break;
			}
			pevstate = 1;
		}else{
			if(storestate == 0){
			lspeed = 1575;
			rspeed = 1100;}
			else if(storestate == 3){
			lspeed = 1575;
			rspeed = 1200;}
		}
	}
	
	//Left//
	else if(lintk[0] == '0'){
		//01111
		if(pevstate != 2){
			switch(pevstate){
				case 0:
					lspeed = 1200;
					rspeed = 1575;
					storestate = 0;
					break;
				case 1:
					break;
				case 3:
					lspeed = 1300;
					rspeed = 1575;
					break;
			}
			pevstate = 2;
		}else{
			if(storestate == 0){
			lspeed = 1200;
			rspeed = 1575;}
			else if(storestate == 3){
			lspeed = 1300;
			rspeed = 1575;}
		}
	}
	
	//Center//
	else if(lintk[2] == '0'){
		if(pevstate != 0){
			lspeed = 1425;
			rspeed = 1475;
			pevstate = 0;
		}
		else{
			lspeed = 1425;
			rspeed = 1475;
		}
	}
}
	
bool pulseHigh = false;

void TIM4_IRQHandler(void) {
if(TIM_GetITStatus(TIM4,TIM_IT_CC1) != RESET) {
	if(!pulseHigh) {
		pulseHigh = true; //pulse starts
		//change to detect falling
		TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Falling);
	} else {
		count++;
		//change to detect raising
		TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Rising);
		//
		sprintf(str, "Count: %d\r\n", count);
		USARTSend(str, sizeof(str));
		pulseHigh = false;
	}
}
//Clear interrupt flag
TIM_ClearITPendingBit(TIM4,TIM_IT_Update|TIM_IT_CC1);
}

void EXTI9_5_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line5) != RESET) {		
		if(lintk[2] == '0')
			lintk[2] = '1';
		else
			lintk[2] = '0';
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
	if (EXTI_GetITStatus(EXTI_Line6) != RESET) {	
		if(lintk[3] == '0')
			lintk[3] = '1';
		else
			lintk[3] = '0';
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
	if (EXTI_GetITStatus(EXTI_Line7) != RESET) {
		if(lintk[4] == '0')
			lintk[4] = '1';
		else
			lintk[4] = '0';
		EXTI_ClearITPendingBit(EXTI_Line7);
	}
}

void EXTI4_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line4) != RESET) {	
		if(lintk[1] == '0')		
			lintk[1] = '1';
		else
			lintk[1] = '0';
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}

void EXTI0_IRQHandler(void){
	if (EXTI_GetITStatus(EXTI_Line0) != RESET){
		if(lintk[0] == '0')
			lintk[0] = '1';
		else
			lintk[0] = '0';
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void SysTick_Handler(){
	if (msTicks != 0)
		msTicks--;
}

