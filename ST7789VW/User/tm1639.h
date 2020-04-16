#ifndef _TM1639_H
#define _TM1639_H
#include "stm32f0xx_gpio.h"
#include "stm32f0xx.h"
#include "delay.h"


#define STB_pin  GPIO_Pin_5
#define CLK_pin  GPIO_Pin_6
#define DIO_pin  GPIO_Pin_7


#define	STB_out_H  GPIO_WriteBit(GPIOA,STB_pin,(BitAction)(0x01))
#define	STB_out_L  GPIO_WriteBit(GPIOA,STB_pin,(BitAction)(0x00))

#define	CLK_out_H  GPIO_WriteBit(GPIOA,CLK_pin,(BitAction)(0x01))
#define	CLK_out_L  GPIO_WriteBit(GPIOA,CLK_pin,(BitAction)(0x00))

#define	DIO_out_H  GPIO_WriteBit(GPIOA,DIO_pin,(BitAction)(0x01))
#define	DIO_out_L  GPIO_WriteBit(GPIOA,DIO_pin,(BitAction)(0x00))



#define DIO_in   PAin(7)

//位使能
#define DIG0 0xc0
#define DIG1 0xc2
#define DIG2 0xc4
#define DIG3 0xc6
#define DIG4 0xc8
#define DIG5 0xca
#define DIG6 0xcc
#define DIG7 0xce

//显示亮度级别
#define LEVEL_OFF   0x80
#define LEVEL_1     0x88
#define LEVEL_2     0x89
#define LEVEL_4     0x8a
#define LEVEL_10    0x8b
#define LEVEL_11    0x8c
#define LEVEL_12    0x8d
#define LEVEL_13    0x8e
#define LEVEL_14    0x8f


//初始化IC端口
void TM1639_Init(void);
//连续传送多个数据
void TM1639_Write_Series_Byte(unsigned char starAddr,unsigned char *Byte,unsigned char len,unsigned char level);
//传送一个数据（本质是连续模式）
void TM1639_Write_One_Byte(unsigned char starAddr,unsigned char Byte,unsigned char level);
//清楚所有显示数据
void ClearAll(void);
//读取按键键值
void KeyRead(int *key);
//测试模式，内部使用，检验硬件完整性
void ICTest(void);

#endif

