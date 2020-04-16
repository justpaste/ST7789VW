//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2014-0101
//  最近修改   : 
//  功能描述   : OLED 4接口演示例程(51系列)
//              说明: 
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              CLK   接PA5（SCL）
//              MOSI   接PA7（SDA）
//              RES  接PB0
//              DC   接PB1  
//							BLK  接PA4 可以悬空
//							MISO 可以不接
//              ----------------------------------------------------------------
// 修改历史   :
// 日    期   : 
// 作    者   : HuangKai
// 修改内容   : 创建文件
//版权所有，盗版必究。
//Copyright(C) 中景园电子2014/3/16
//All rights reserved
//******************************************************************************/
#ifndef __OLED_H
#define __OLED_H			  	 
#include "stdlib.h"	 

#define LCD_W 240
#define LCD_H 240
#define	uint8_t unsigned char
#define	uint16_t unsigned int
#define	uint32_t unsigned long
	

extern const uint8_t Chinese32[];
extern const uint8_t Charasc16[];
extern const uint8_t Charasc24[];
extern const uint8_t Charasc32[];
extern const uint8_t Charasc48[];
extern const uint8_t Charasc64[];
extern const uint8_t Charasc96[];
extern const uint8_t Charasc128[];
extern const uint8_t buzzer[];
extern const uint8_t bat[];
extern const uint8_t image[];
extern const uint8_t ty[9656]; 
extern const uint8_t windows[25538];

//OLED模式设置
//0:4线串行模式
//1:并行8080模式
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED端口定义----------------  
//**************************************************************************8
#define	DC_Pin	GPIO_Pin_13		//PB13
#define	RES_Pin	GPIO_Pin_14		//PC14
#define	WR_Pin	GPIO_Pin_13		//PC13->WR

#define	LED_Pin		GPIO_Pin_8		//PA8
#define	POWER_Pin	GPIO_Pin_11		//PA11
#define	KEY_Pin		GPIO_Pin_15		//PA15
#define	Buzzer_Pin	GPIO_Pin_4		//PA4


#define	D0_Pin	GPIO_Pin_0		//PB0
#define	D1_Pin	GPIO_Pin_1		//PB1
#define	D2_Pin	GPIO_Pin_2		//PB2
#define	D3_Pin	GPIO_Pin_3		//PB3
#define	D4_Pin	GPIO_Pin_4		//PB4
#define	D5_Pin	GPIO_Pin_5		//PB5
#define	D6_Pin	GPIO_Pin_6		//PB6
#define	D7_Pin	GPIO_Pin_7		//PB7


#define LCD_RSH    GPIO_WriteBit(GPIOB,DC_Pin,(BitAction)(0x01))
#define LCD_RSL    GPIO_WriteBit(GPIOB,DC_Pin,(BitAction)(0x00))

#define LCD_RSTH   GPIO_WriteBit(GPIOC,RES_Pin,(BitAction)(0x01))
#define LCD_RSTL   GPIO_WriteBit(GPIOC,RES_Pin,(BitAction)(0x00))

#define LCD_WRH    GPIO_WriteBit(GPIOC,WR_Pin,(BitAction)(0x01))
#define LCD_WRL    GPIO_WriteBit(GPIOC,WR_Pin,(BitAction)(0x00))

#define SET_LED_H    GPIO_WriteBit(GPIOA,LED_Pin,(BitAction)(0x01))
#define SET_LED_L    GPIO_WriteBit(GPIOA,LED_Pin,(BitAction)(0x00))


#define SET_D0_H   GPIO_WriteBit(GPIOB,D0_Pin,(BitAction)(0x01))
#define SET_D0_L   GPIO_WriteBit(GPIOB,D0_Pin,(BitAction)(0x00))

#define SET_D1_H   GPIO_WriteBit(GPIOB,D1_Pin,(BitAction)(0x01))
#define SET_D1_L   GPIO_WriteBit(GPIOB,D1_Pin,(BitAction)(0x00))

#define SET_D2_H   GPIO_WriteBit(GPIOB,D2_Pin,(BitAction)(0x01))
#define SET_D2_L   GPIO_WriteBit(GPIOB,D2_Pin,(BitAction)(0x00))

#define SET_D3_H   GPIO_WriteBit(GPIOB,D3_Pin,(BitAction)(0x01))
#define SET_D3_L   GPIO_WriteBit(GPIOB,D3_Pin,(BitAction)(0x00))

#define SET_D4_H   GPIO_WriteBit(GPIOB,D4_Pin,(BitAction)(0x01))
#define SET_D4_L   GPIO_WriteBit(GPIOB,D4_Pin,(BitAction)(0x00))

#define SET_D5_H   GPIO_WriteBit(GPIOB,D5_Pin,(BitAction)(0x01))
#define SET_D5_L   GPIO_WriteBit(GPIOB,D5_Pin,(BitAction)(0x00))

#define SET_D6_H   GPIO_WriteBit(GPIOB,D6_Pin,(BitAction)(0x01))
#define SET_D6_L   GPIO_WriteBit(GPIOB,D6_Pin,(BitAction)(0x00))

#define SET_D7_H   GPIO_WriteBit(GPIOB,D7_Pin,(BitAction)(0x01))
#define SET_D7_L   GPIO_WriteBit(GPIOB,D7_Pin,(BitAction)(0x00))

#define SET_Power_H   GPIO_WriteBit(GPIOA,POWER_Pin,(BitAction)(0x01))
#define SET_Power_L   GPIO_WriteBit(GPIOA,POWER_Pin,(BitAction)(0x00))

#define SET_Buzzer_H   GPIO_WriteBit(GPIOA,Buzzer_Pin,(BitAction)(0x01))
#define SET_Buzzer_L   GPIO_WriteBit(GPIOA,Buzzer_Pin,(BitAction)(0x00))

#define ReadKey    GPIO_ReadInputDataBit(GPIOA, KEY_Pin)
//******************************************************************************

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

extern  uint16_t BACK_COLOR, POINT_COLOR;   //背景色，画笔色

void Lcd_Init(void); 
void LCD_Clear(uint16_t Color);
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
//void LCD_WR_DATA8(char da); //发送数据-8位参数
//void LCD_WR_DATA(int da);
//void LCD_WR_REG(char da);

void LCD_DrawPoint(uint16_t x,uint16_t y);//画点
void LCD_DrawPoint_big(uint16_t x,uint16_t y);//画一个大点
uint16_t  LCD_ReadPoint(uint16_t x,uint16_t y); //读点
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r);
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);		   
void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color);
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t Size,const uint8_t *Charasc,uint8_t mode);
void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t Size,const uint8_t *Charasc,uint8_t len,uint8_t mode);
void LCD_ShowString(uint16_t x,uint16_t y,const uint8_t *p);		 //显示一个字符串,16字体
void ShowChinese(uint16_t x,uint16_t y,uint8_t w,uint8_t h,uint8_t index);
void ShowImage(uint16_t x,uint16_t y,uint8_t l,uint8_t h,const uint8_t *Charasc);
void ShowClourImage(uint16_t x,uint16_t y,uint8_t l,uint8_t h,const uint8_t *Charasc); 




uint32_t mypow(uint8_t m,uint8_t n);

void St7789v_IOInit(void);
void LCD_Reset(void);
void LCD_DataWrite(uint8_t data);
void LCD_CmdWrite(uint8_t cmd);			   
void LCD_Data16Write(uint16_t data);		
void SSD1331_Send_Byte(uint8_t chData);
void showimage(void);
void showbattery(void);
void LCD_Clearpart(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint16_t Color);
void batteryupdate(uint16_t ADvalue);
void showbuzzer(void) ;
void tempupdate(uint16_t TobjADvalue);

//画笔颜色
//#define WHITE         	 0xFFFF
//#define BLACK         	 0x0000	  
//#define BLUE         	 0x001F  
//#define BRED             0XF81F
//#define GRED 			 0XFFE0
//#define GBLUE			 0X07FF
//#define RED           	 0xF800
//#define MAGENTA       	 0xF81F
//#define GREEN         	 0x07E0
//#define CYAN          	 0x7FFF
//#define YELLOW        	 0xFFE0
//#define BROWN 			 0XBC40 //棕色
//#define BRRED 			 0XFC07 //棕红色
//#define GRAY  			 0X8430 //灰色

#define WHITE         	 0xFFFF	//白色
#define BLACK         	 0x0000	//黑色  
#define LGREEN         	 0x001F //浅绿色 
#define GREEN            0XF81F	//绿色
#define PURPLE 			 0XFFE0	//紫色
#define YELLOW			 0X07FF	//黄色
#define LBLUE            0xF800	//浅蓝色
#define RED         	 0x07E0	//红色
#define LWHITE           0x7FFF	//浅白
#define BLUE 			 0XBC40 //蓝色
#define BRRED 			 0XFC07 //棕红色

//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)


					  		 
#endif  
	 
	 



