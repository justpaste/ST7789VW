#include "stm32f0xx.h"
#include "delay.h"
#include "usart1.h"
#include "stm32f0xx_gpio.h"
#include "adc.h"
#include "stm32f0xx_adc.h"
#include "tim3.h"
#include "cs1237.h"
#include "w25qxx.h" 
#include "oled.h" 
#include "stdbool.h" 
//#include "st7789v.h" 

void OtherIOInit(void);


#define FLASH_SIZE 16*1024*1024

uint8_t TEXT_Buffer[]={"w25q16 test"};
const uint16_t NTCTemp1039[30]=
{
/*10℃-19℃*/	2174 ,2139 ,2104 ,2068 ,2032 ,1996 ,1960 ,1924 ,1887 ,1851 ,
/*20℃-29℃*/	1814 ,1778 ,1741 ,1705 ,1669 ,1633 ,1597 ,1562 ,1526 ,1491 ,
/*30℃-39℃*/	1457 ,1423 ,1389 ,1355 ,1322 ,1289 ,1257 ,1226 ,1194 ,1164 
};

#define ADValueCompensate 658*46
const uint32_t Tobj18[111]=
{
	
//32.0-43.0 
43423,44081,44739,45397,46713,48029,48687,49345,50003,50661,
51318,51976,52634,53292,53950,55266,55924,56582,57240,57898,
58556,59214,59872,60529,61187,61845,62503,63161,63819,65135,
65793,66451,67109,67767,68425,69083,69740,70398,71056,71714,
72372,73030,73688,74346,75004,75662,76320,76978,77636,78294,
78951,79609,80267,80925,81583,82241,82899,83557,84215,84873,
85531,86189,86847,87505,88162,88820,89478,90136,90794,91452,
92110,92768,93426,94084,94742,95400,96058,96716,97373,98031,
98689,99347,100005,100663,101321,101979,102637,103295,103953,104611,
105269,105927,106584,107242,107900,108558,109216,109874,110532,111190,
111848,112506,113164,113822,114480,115138,115796,116453,117111,117769,
118427 

	
					
	
};

#define ADValueMax 	0x7fffff	
#define ADVref 		12.75	//0.5*Vref/Gain->0.5*3266/128
#define Vref		3266

int main(void)
{
	uint8_t Tempi;
	int32_t ADValue;
	float Votage;
	uint16_t VotageTemp;
	uint16_t TobjTemp;
	uint16_t NTCADValue;
	uint8_t NTCTemp;
	uint16_t BATADValue;
	uint16_t NTCVotage;
	bool PowerKeyFalg;
	
	
	
	OtherIOInit();
	SET_Power_H;
	delay_init();
	delay_ms(200);
	USART1_Init(9600);
	printf("Usart Test OK\r\n");
	ADC_Config();
	TIM_Config(59,47);		//0.1M计数频率，1us*60=50us
	Cs1237IO_Init();
//	W25QXX_Init();
	

	Lcd_Init();
	LCD_Clear(LBLUE);
	GPIO_SetBits(GPIOA,LED_Pin);
	//显示buzzer图标
	POINT_COLOR=YELLOW;
//	ShowImage(10,10,34,31,buzzer);
	ShowClourImage(0,0,71,68,ty);
	ShowClourImage(50,80,113,113,windows);
	while(1)
	{
	
	}

}
void OtherIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(	RCC_AHBPeriph_GPIOA, ENABLE );	
	GPIO_InitStructure.GPIO_Pin = POWER_Pin;  				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = KEY_Pin;  				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = Buzzer_Pin;  				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,Buzzer_Pin);
}







