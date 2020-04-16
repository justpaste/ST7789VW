#include "tim3.h"
#include "usart1.h"
#include "stdbool.h" 


__IO uint16_t CCR1_Val = 40961;
__IO uint16_t CCR2_Val = 27309;
__IO uint16_t CCR3_Val = 13654;
__IO uint16_t CCR4_Val = 6826;
uint16_t PrescalerValue = 0;

uint16_t PoweroffCount;
uint16_t UsCount;
uint16_t BuzzerCount;
uint8_t BuzzerDriveCount=0;
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */

/**
  * @brief  Configure the TIM IRQ Handler.
  * @param  None
  * @retval None
  */
void TIM_Config(vu16 arr,vu16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


	/* -----------------------------------------------------------------------
	TIM3 Configuration: Output Compare Timing Mode:

	In this example TIM3 input clock (TIM3CLK) is set to APB1 clock (PCLK1),  
	  => TIM3CLK = PCLK1 = SystemCoreClock = 48 MHz
		  
	To get TIM3 counter clock at 6 MHz, the prescaler is computed as follows:
	   Prescaler = (TIM3CLK / TIM3 counter clock) - 1
	   Prescaler = (PCLK1 /6 MHz) - 1
											  
	CC1 update rate = TIM3 counter clock / CCR1_Val = 146.48 Hz
	==> Toggling frequency = 73.24 Hz

	C2 update rate = TIM3 counter clock / CCR2_Val = 219.7 Hz
	==> Toggling frequency = 109.8 Hz

	CC3 update rate = TIM3 counter clock / CCR3_Val = 439.4 Hz
	==> Toggling frequency = 219.7 Hz

	CC4 update rate = TIM3 counter clock / CCR4_Val = 878.9 Hz
	==> Toggling frequency = 439.4 Hz

	Note: 
	 SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f0xx.c file.
	 Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
	 function to update SystemCoreClock variable value. Otherwise, any configuration
	 based on this variable will be incorrect.    
	----------------------------------------------------------------------- */   


	/* Compute the prescaler value */
	PrescalerValue = (uint16_t) (SystemCoreClock  / 6000000) - 1;

	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	//  /* Prescaler configuration */
	//  TIM_PrescalerConfig(TIM3, PrescalerValue, TIM_PSCReloadMode_Immediate);

	//  /* Output Compare Timing Mode configuration: Channel1 */
	//  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
	//  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	//  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
	//  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	//  TIM_OC1Init(TIM3, &TIM_OCInitStructure);

	//  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);

	//  /* Output Compare Timing Mode configuration: Channel2 */
	//  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	//  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;

	//  TIM_OC2Init(TIM3, &TIM_OCInitStructure);

	//  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Disable);

	//  /* Output Compare Timing Mode configuration: Channel3 */
	//  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	//  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;

	//  TIM_OC3Init(TIM3, &TIM_OCInitStructure);

	//  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Disable);

	//  /* Output Compare Timing Mode configuration: Channel4 */
	//  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	//  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;

	//  TIM_OC4Init(TIM3, &TIM_OCInitStructure);

	//  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Disable);

	/* TIM Interrupts enable */
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);

	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/******************************************************************************/
/**
  * @brief  This function handles TIM3 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM3_IRQHandler(void)
{
	
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
			UsCount++;
			if(UsCount>1666)		//60us*1666=100ms
			{
				UsCount=0;
				PoweroffCount++;
				if(BuzzerCount>0)
				{
					BuzzerCount--;
					if(BuzzerCount==0)
					{
						BuzzerDriveCount=0;
						GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)(0x00));
					}
				}					
			}
			if(BuzzerCount>0)
			{
				BuzzerDriveCount++;
				if(BuzzerDriveCount<2)
				{
					GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)(0x01));
				}
				else if(BuzzerDriveCount<4)
				{
					
					GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)(0x00));
				}
				else
				{
					BuzzerDriveCount=0;
				}
				
			}
	}
}


