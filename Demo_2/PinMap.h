// Pin Usage
// Function ** Pin Name ** Board Pin Out
// TIM4 CH1 IC1 ** PB6 ** D10
// TIM3 CH1 PWM ** PA6 ** D12

// Left wheel ** PA8 ** D
#define Left_wheel_RCC_GPIO 		RCC_APB2Periph_GPIOA
#define Left_wheel_GPIO 				GPIOA
#define Left_wheel_PIN 					GPIO_Pin_8

// Right wheel ** PB5 ** D
#define Right_wheel_RCC_GPIO 		RCC_APB2Periph_GPIOB
#define Right_wheel_GPIO 				GPIOB
#define Right_wheel_PIN 				GPIO_Pin_5

//Right
// TIM3 CH1 PWM ** PB4 ** D
#define TIM3_CH1_PWM_RCC_GPIO 	RCC_APB2Periph_GPIOB
#define TIM3_CH1_PWM_GPIO 			GPIOB
#define TIM3_CH1_PWM_PIN 				GPIO_Pin_4

//Left
// TIM2 CH3 PWM ** PB10 ** D
#define TIM2_CH3_PWM_RCC_GPIO 	RCC_APB2Periph_GPIOB
#define TIM2_CH3_PWM_GPIO 			GPIOB
#define TIM2_CH3_PWM_PIN 				GPIO_Pin_10

// Lin Trk ** PB0 ** D
#define Lin1_RCC_GPIO 		RCC_APB2Periph_GPIOB
#define Lin1_GPIO 				GPIOB
#define Lin1_PIN 					GPIO_Pin_0
#define Lin1_EXTI_LINE    EXTI_Line0
#define Lin1_GPIO_PORTSOURCE 	GPIO_PortSourceGPIOB
#define Lin1_GPIO_PINSOURCE  	GPIO_PinSource0

// Lin Trk ** PA4 ** D
#define Lin2_RCC_GPIO 		RCC_APB2Periph_GPIOA
#define Lin2_GPIO 				GPIOA
#define Lin2_PIN 					GPIO_Pin_4
#define Lin2_EXTI_LINE    EXTI_Line4
#define Lin2_GPIO_PORTSOURCE 	GPIO_PortSourceGPIOA
#define Lin2_GPIO_PINSOURCE  	GPIO_PinSource4

// Lin Trk ** PA5 ** D
#define Lin3_RCC_GPIO 		RCC_APB2Periph_GPIOA
#define Lin3_GPIO 				GPIOA
#define Lin3_PIN 					GPIO_Pin_5
#define Lin3_EXTI_LINE    EXTI_Line5
#define Lin3_GPIO_PORTSOURCE 	GPIO_PortSourceGPIOA
#define Lin3_GPIO_PINSOURCE  	GPIO_PinSource5

// Lin Trk ** PA6 ** D
#define Lin4_RCC_GPIO 		RCC_APB2Periph_GPIOA
#define Lin4_GPIO 				GPIOA
#define Lin4_PIN 					GPIO_Pin_6
#define Lin4_EXTI_LINE    EXTI_Line6
#define Lin4_GPIO_PORTSOURCE 	GPIO_PortSourceGPIOA
#define Lin4_GPIO_PINSOURCE  	GPIO_PinSource6

// Lin Trk ** PA7 ** D
#define Lin5_RCC_GPIO 		RCC_APB2Periph_GPIOA
#define Lin5_GPIO 				GPIOA
#define Lin5_PIN 					GPIO_Pin_7
#define Lin5_EXTI_LINE    EXTI_Line7
#define Lin5_GPIO_PORTSOURCE 	GPIO_PortSourceGPIOA
#define Lin5_GPIO_PINSOURCE  	GPIO_PinSource7

//Function prototypes
void GPIO_init(void);
void TIM3_CH1_PWM_init(void);
void TIM2_CH3_PWM_init(void);
void USART2_init(void);
void USARTSend (char *pucBuffer , unsigned long ulCount);
void rightspeed(int speed);
void leftspeed(int speed);