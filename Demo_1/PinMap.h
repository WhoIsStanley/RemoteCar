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

// TIM4 CH1 IC1 ** PB6 ** D10
#define TIM4_CH1_IT1_RCC_GPIO 	RCC_APB2Periph_GPIOB
#define TIM4_CH1_IT1_GPIO 			GPIOB
#define TIM4_CH1_IT1_PIN 				GPIO_Pin_6

//Function prototypes
void TIM3_CH1_PWM_init(void);
void TIM2_CH3_PWM_init(void);
void TIM4_CH1_IC1_init(void);
void USART2_init(void);
void USARTSend (char *pucBuffer , unsigned long ulCount);