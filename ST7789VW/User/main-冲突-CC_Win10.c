#include "stm32f0xx.h"
#include "delay.h"
#include "power.h"
#include "tm1639.h"
#include "usart1.h"
#include "stm32f0xx_gpio.h"
#include "adc.h"
#include "stm32f0xx_adc.h"
#include "tim3.h"

#define VDDA 3300

unsigned char Table0[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00};
					/*  0    1    2    3    4    5    6    7    8    9    不显示    */
unsigned char Table1[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,0x00};
					/*  0.   1.   2.   3.   4.   5.   6.   7.   8.   9.   不显示    */
unsigned char Table2[]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};	//8
unsigned char Table3[8];	
unsigned char Table4[8];	

vu8 Time_sec;
vu8 Time_min;
vu8 Time_hou;
vu16 Ad_buf[];


int main(void)
{
	vu16 ADV_Value=0;
	vu16 ADI_Value=0;
	vu16 ADNTC_Value=0;
	vu16 ADV_Voltage=0;
	vu16 ADI_Voltage=0;
	vu8 i=0;
	vu16 Sum=0;
	vu16 Sum_buf[12];
	vu8 Sum_buf_i;
	vu8	first_cycle;
	vu16 Ave_voltage;
		
	delay_init();
	USART1_Init(115200);
	ADC_Config();
//	TIM_Config(999,47990);//1k计数频率，1ms*3000=3s
	IO_Init();
	TM1639_Init();
	TM1639_Write_Series_Byte(DIG0,Table2,8,LEVEL_10);
	delay_ms(300);
	
	while(1)
	{
//		delay_ms(500);
//		delay_ms(500);
		//ADV=PA0,ADI=PA1,ADNTC=PA2
		ADV_Value =Get_Adc_Average(ADC_Channel_0,10);
		ADI_Value =Get_Adc_Average(ADC_Channel_1,10);
		ADNTC_Value =Get_Adc_Average(ADC_Channel_2,10);
		printf("%d\r\n",ADV_Value);
//		printf("ADI_Value=%d\r\n",ADI_Value);
//		printf("ADNTC_Value=%d\r\n",ADNTC_Value);
		ADI_Voltage=(VDDA*ADI_Value*100)/(4095*47);			//I=U*(1/R),R=0.47
		Table3[4]=ADI_Voltage/1000;
		Table3[5]=ADI_Voltage/100%10;
		Table3[6]=ADI_Voltage/10%10;
		Table3[7]=ADI_Voltage%10;
		
		ADV_Value =Get_Adc_Average(ADC_Channel_0,4);
		
		Sum_buf_i++;		
		if(first_cycle==1)
		{
			Sum_buf[Sum_buf_i]=ADV_Value;
			Sum+=Sum_buf[Sum_buf_i];
			ADV_Value=Sum/Sum_buf_i;
		}
		if(Sum_buf_i>11)
		{
			first_cycle=0;
			Sum_buf_i=0;
		}
		if(first_cycle==0)
		{
			Sum=Sum-Sum_buf[Sum_buf_i]+ADV_Value;
			ADV_Value=Sum/12;
			Sum_buf[Sum_buf_i]=ADV_Value;
		}
		
		ADV_Value=ADV_Value*10;
		ADV_Value=ADV_Value-ADI_Value;
		ADV_Voltage=(VDDA*ADV_Value)/(4095);
		Table3[0]=ADV_Voltage/10000;
		Table3[1]=ADV_Voltage/1000%10;
		Table3[2]=ADV_Voltage/100%10;
		Table3[3]=ADV_Voltage/10%10;
		for( i=0;i<8;i++)
		{
			Table4[i]=Table0[Table3[i]];
			if(i==1||i==4)
			{
				Table4[i]=Table4[i]+0x80;
			}
			
		}
		
		TM1639_Write_Series_Byte(DIG0,Table4,8,LEVEL_10);
		
//		printf("STM32F030F4P6 USART TEST\r\n");
//		printf("	ADV_Value=%d,	ADI_Value=%d\r\n",ADV_Value,ADI_Value);
		
//		GPIO_WriteBit(GPIOB,GPIO_Pin_1,(BitAction)(0x00));
		
		
	}

	
}





