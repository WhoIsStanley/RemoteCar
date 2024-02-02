#include "stm32f10x.h"                  // Device header
#include "PinMap.h"

void GPIO_init(void){
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	
	//GPIO set up
	GPIO_InitTypeDef GPIO_InitStructureA, GPIO_InitStructureB;
	
		GPIO_InitStructureA.GPIO_Pin   = Left_wheel_PIN;
		GPIO_InitStructureA.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructureA.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructureA);
	
		GPIO_InitStructureB.GPIO_Pin   = Right_wheel_PIN;
		GPIO_InitStructureB.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructureB.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructureB);
}


//left speed
void TIM2_CH3_PWM_init(void) {
//#define TIM2_CH3_PWM_RCC_GPIO 	RCC_APB2Periph_GPIOB
//#define TIM2_CH3_PWM_GPIO 			GPIOB ** 
//#define TIM2_CH3_PWM_PIN 				GPIO_Pin_10 ** datasheet TM3 CH1 partial ** => rightC
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(TIM2_CH3_PWM_RCC_GPIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);
	TIM2->CCR3 &= ~(TIM_CR1_CEN);
	//
	GPIO_InitTypeDef GPIO_InitStructure;
	// Configure I/O for Tim2 Ch3 PWM pin
	GPIO_InitStructure.GPIO_Pin = TIM2_CH3_PWM_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(TIM2_CH3_PWM_GPIO, &GPIO_InitStructure);
		
	// Tim2 set up
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		
	TIM_TimeBaseInitTypeDef timerInitStructure;
	timerInitStructure.TIM_Prescaler = 1440-1; // (72Mhz/144)=50000Hz
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 100-1;
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &timerInitStructure);
	TIM_Cmd(TIM2,ENABLE);

	//Enable Tim2 Ch3 PWM
	TIM_OCInitTypeDef outputChannelInit;
	outputChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
	outputChannelInit.TIM_Pulse = 50; // set duty cycle
	outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
	outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM2, &outputChannelInit);
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
}

//Right speed
void TIM3_CH1_PWM_init(void) {
//#define TIM3_CH1_PWM_RCC_GPIO 	RCC_APB2Periph_GPIOB
//#define TIM3_CH1_PWM_GPIO 			GPIOB
//#define TIM3_CH1_PWM_PIN 				GPIO_Pin_4 ** datasheet TM2 CH3 Full ** => right
	
	RCC_APB2PeriphClockCmd(TIM3_CH1_PWM_RCC_GPIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
	//
	GPIO_InitTypeDef GPIO_InitStructure;
	// Configure I/O for Tim3 Ch1 PWM pin
	GPIO_InitStructure.GPIO_Pin = TIM3_CH1_PWM_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(TIM3_CH1_PWM_GPIO, &GPIO_InitStructure);
		
	// Tim3 set up
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		
	TIM_TimeBaseInitTypeDef timerInitStructure;
	timerInitStructure.TIM_Prescaler = 1440-1; // (72Mhz/144)=50000Hz
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 100-1;
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &timerInitStructure);
	TIM_Cmd(TIM3,ENABLE);

	//Enable Tim3 Ch1 PWM
	TIM_OCInitTypeDef outputChannelInit;
	outputChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
	outputChannelInit.TIM_Pulse = 50; // set duty cycle
	outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
	outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &outputChannelInit);
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
}

void TIM4_CH1_IC1_init(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	// Configure I/O for IC1
	GPIO_InitStruct.GPIO_Pin = TIM4_CH1_IT1_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(TIM4_CH1_IT1_GPIO, &GPIO_InitStruct);

	//Tim4 set up
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_TimeBaseInitTypeDef timerInitStructure;
	timerInitStructure.TIM_Prescaler = 144-1;		// 1/(72Mhz/720)=0.01ms
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 1000-1;		// 0.01ms*200= 2ms
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &timerInitStructure);
	TIM_Cmd(TIM4, ENABLE);

	//Enable Tim4 Ch1 Input Capture
	TIM_ICInitTypeDef InputCaptureInitStructure;
	InputCaptureInitStructure.TIM_Channel = TIM_Channel_1; //Seclect IC1
	InputCaptureInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	//Capture rising
	InputCaptureInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	//Map to TI1
	InputCaptureInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	//Configure input frequency
	InputCaptureInitStructure.TIM_ICFilter = 0; //no filter
	TIM_ICInit(TIM4, &InputCaptureInitStructure);

	//Enable Input Capture Interrupt
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; //TIM4 interrupt
	//Preemptive priority level 2
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	//From the priority level 0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	//The IRQ channel is enabled
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//Allow updates to interrupt, allows the CC1IE to capture interrupt
	TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC1,ENABLE);
}

void USART2_init(void) {
	//USART2 TX RX
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure );
		
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
}

void USARTSend(char *pucBuffer, unsigned long ulCount){
	//
	// Loop while there are more characters to send.
	//
	while(ulCount--){
		USART_SendData(USART2, *pucBuffer++);
		/* Loop until the end of transmission */
		while(USART_GetFlagStatus (USART2, USART_FLAG_TC) == RESET){}
	}
}