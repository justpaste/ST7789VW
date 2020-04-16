#ifndef _ST7789V_H_
#define _ST7789V_H_


/*
**
**************************************************************************
* 文件名：TFT.h
* 作  者：小书童
* 说  明：此文件包含了TFT.c的外部接口函数的声明
* 版本号：V1.1
* 日  期：2012.2.29
**************************************************************************
**
*/
#include "stm32f0xx.h"

#define	BLACK		0x0000
#define	BLUE		0x001F
#define	RED 		0xF800
#define	GREEN 		0x07E0
#define CYAN		0x07FF
#define MAGENTA 	0xF81F
#define YELLOW		0xFFE0
#define WHITE		0xFFFF	
#define BACKCOLOR 	0xFFFF	
#define	WORDCOLOR 	0x0000

void LCDInit(void);
void LCD_Write_Num(uint16_t x, uint16_t y, u32 num, uint16_t wordcolor, uint16_t backcolor);
void LCDDrawFull(void);
void LCD_Clear(uint16_t Color);
void LCDDrawDot(uint16_t xposition, uint16_t yposition, uint16_t color); 
void LCDDrawLine(uint16_t sxp, uint16_t syp, uint16_t exp, uint16_t eyp, uint16_t color);

void LCDDrawFullANDMARK();

void display(uint8_t buff, uint16_t wordcolor, uint16_t backcolor);
                      
void LCD_write_english_string(uint16_t x, uint16_t y, char *str,uint8_t mode);//英文字符串显示
void LCD_write_chinese_string(uint16_t x, uint16_t y,uint16_t address,uint16_t len,uint8_t mode);

void LCD_Picture(uint16_t x,uint16_t y,uint16_t width,uint16_t height, const unsigned char *color);
void LCD_Clear1(uint16_t xStart,uint16_t yStart,uint16_t xlong,uint16_t ylong,uint16_t Color);
void LCD_write_number_string(uint16_t x, uint16_t y,int32_t number,uint8_t mode);
void LCD_ShowPicture(uint16_t x,uint16_t y,uint16_t width,uint16_t heiht,uint16_t point,uint16_t back,const unsigned char *pic,uint8_t mode);
void LCD_Showblank(uint16_t x,uint16_t y,uint16_t width,uint16_t height,const unsigned  char *color);


void SSD1331_Send_Byte(uint8_t chData);
void ssd1331_IOInit(void);

#endif
