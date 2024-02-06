# Description
It use STM32F103TBT6 and ATmega328p.
## Demo_1
1. init.c(Timer setting)
  ~~~~~
  timerInitStructure.TIM_Prescaler = 1440-1; // (72Mhz/144)=50000Hz
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 100-1;
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &timerInitStructure);
	TIM_Cmd(TIM2,ENABLE);
  ~~~~~
TIM_Prescaler: 1440 = 500Hz  
TIM_Period: 100 = 0-100  
***
2. init.c(PWM setting)
  ~~~~~
	TIM_OCInitTypeDef outputChannelInit;
	outputChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
	outputChannelInit.TIM_Pulse = 50; // set duty cycle
	outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
	outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM2, &outputChannelInit);
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
  ~~~~~
TIM_Pulse[^1]: Set the how much power you need  
Set which Timer chanel to output PWM:  
> TIM_OCnInit(TIMx, &outputChannelInit);  
> TIM_OCnPreloadConfig(TIMx, &outputChannelInit);
***
3. init.c(USART2 setting)
  ~~~~~
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
	USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  ~~~~~
USART_BaudRate[^2]: 115200
  ~~~~~
	NVIC_InitTypeDef NVIC_InitStructure;
	// Enable the USART2 RX Interrupt
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
  ~~~~~
NVIC: Set RX interrupt only (because TX using polling is enough).
***
4. main.c(Remapping pin)[^3]
  ~~~~~
  // Timer 3 code
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
  GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);

  // Timer 2 code
  GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);
  ~~~~~
This may not need in your board.
***
5. main.c(Receive direction command)
  ~~~~~
  void USART2_IRQHandler() {
  	if(USART_GetITStatus(USART2, USART_IT_RXNE)){
  		key = USART_ReceiveData(USART2);
  		start = 1;
  	}
  }
  ~~~~~
***
6. main.c(changing wheel speed)
  ~~~~~
  void rightspeed(int speed){
  	TIM_OCInitTypeDef outputChannelInit;
  	outputChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
  	outputChannelInit.TIM_Pulse = speed; // set duty cycle
  	outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
  	outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_High;
  	TIM_OC1Init(TIM3, &outputChannelInit);
  	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
  }
  ~~~~~
Set the Pulse can change from 0% to 100%
## Demo_1(Remote)
1. main.c(delay)
~~~~~
 void delay()
 {
	 TCCR1A = 0b00000000;
	 TCCR1B = 0b00001011; // Prescaler = 64
	 OCR1A = 12500; // 1 / (16 MHz / 64) = 0.004 ms,  50ms / 0.004 ms = 12500
	 
	 unsigned char count = 0;
	 while (count < 5) // 20 x 50 ms = 1 s
	 {
		 while(!(TIFR1 & (1<<OCF1A))) ;
		 TIFR1 = (1<<OCF1A);
		 count++;
	 }
 }
~~~~~
It is suggested to set a delay. Unless you sure that sending too fast will not crash the Car recevier code

[^1]:Because my period set as 100. Pulse set 100 to be 100% output and  set 0 to be 0% output.  
[^2]:Because my HC05 & HC06 BaudRate is setted to 115200. Setting go to these website to check AT command https://swf.com.tw/?p=335 (Chinese), https://www.instructables.com/AT-command-mode-of-HC-05-Bluetooth-module/ (English)  
[^3]:Go this datasheet to check the remapping pin is which one https://www.st.com/resource/en/datasheet/stm32f103c8.pdf
