#include "adc.h"
#include "delay.h"

#include "stm32f0xx_adc.h"
#include "stm32f0xx_rcc.h"

/**
  * @brief  ADC Configuration
  * @param  None
  * @retval None
  */
void ADC_Config(void)
{
	ADC_InitTypeDef     ADC_InitStructure;
	GPIO_InitTypeDef    GPIO_InitStructure;

	/* GPIOC Periph clock enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	/* ADC1 Periph clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	RCC_ADCCLKConfig(RCC_ADCCLK_PCLK_Div2);//设置分频因子

	/* Configure ADC Channel11 as analog input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 |GPIO_Pin_1 ;	//PA2->NTC；PA1->BAT_DET
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* ADCs DeInit */  
	ADC_DeInit(ADC1);

	/* Initialize ADC structure */
	ADC_StructInit(&ADC_InitStructure);

	/* Configure the ADC1 in continuous mode with a resolution equal to 12 bits  */
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; 
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Backward;
	ADC_Init(ADC1, &ADC_InitStructure); 


	
	/* ADC Calibration */
	ADC_GetCalibrationFactor(ADC1);
	
	ADC_Cmd(ADC1, ENABLE);  
	
	/* Wait the ADRDY flag */
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY)); 

  
}

//获得ADC值
//ch:通道值 0~3
uint16_t Get_Adc(uint8_t ch)   
{
	
	/* Convert the ADC1 Channel 11 with 239.5 Cycles as sampling time */ 
	ADC_ChannelConfig(ADC1, ch , ADC_SampleTime_239_5Cycles);
	
	//设置指定ADC的规则组通道，一个序列，采样时间
//	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
 	
	/* Enable the ADC peripheral */

	
	ADC_StartOfConversion(ADC1);
	
	
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	 

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}

uint16_t Get_Adc_Average(uint8_t ch,uint8_t times)
{
	uint32_t temp_val=0;
	uint32_t temp_min=0;
	uint32_t temp_max=0;
	uint32_t temp_sum=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val=Get_Adc(ch);
		if(t==0)
		{
			temp_min=temp_val;
			temp_max=temp_val;
			
		}
		else if(temp_val<temp_min)
		{
			temp_min=temp_val;
		}
		else if(temp_val>temp_max)
		{
			temp_max=temp_val;
		}
		temp_sum+=temp_val;
		delay_ms(2);
	}
	return (temp_sum-temp_max-temp_min)/(times-2);
} 	 



