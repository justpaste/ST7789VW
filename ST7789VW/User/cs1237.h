#ifndef __CS1237_H__
#define __CS1237_H__

#include "stdio.h"
#include "sys.h"

#define SCLout_H GPIO_WriteBit(GPIOB,SCLout_Pin,(BitAction)(0x01))
#define SDAout_H GPIO_WriteBit(GPIOB,SDAout_Pin,(BitAction)(0x01))

#define SCLout_L GPIO_WriteBit(GPIOB,SCLout_Pin,(BitAction)(0x00))
#define SDAout_L GPIO_WriteBit(GPIOB,SDAout_Pin,(BitAction)(0x00))

#define SCLout_Pin GPIO_Pin_11
#define SDAout_Pin GPIO_Pin_10


//配置CS1237芯片
void Con_CS1237(void);
//读取芯片的配置数据
unsigned char Read_CON(void);
//读取ADC数据
uint32_t Read_CS1237(void);
//初始化ADC相关参数
void Init_CS1237(void);
//下面这个程序负责读取出最终ADC数据
uint32_t Read_18Bit_AD(void);
//CS1237进入低功耗模式
void CS1237_Power_Down(void);
//配置IO
void Cs1237IO_Init(void);

uint32_t Read_12Bit_AD(void);
//补码与原码转换
uint32_t Code32bit_conversion(uint32_t CodeInput );


#endif
