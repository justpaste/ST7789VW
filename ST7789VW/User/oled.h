//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2014-0101
//  ����޸�   : 
//  ��������   : OLED 4�ӿ���ʾ����(51ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              CLK   ��PA5��SCL��
//              MOSI   ��PA7��SDA��
//              RES  ��PB0
//              DC   ��PB1  
//							BLK  ��PA4 ��������
//							MISO ���Բ���
//              ----------------------------------------------------------------
// �޸���ʷ   :
// ��    ��   : 
// ��    ��   : HuangKai
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2014/3/16
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

//OLEDģʽ����
//0:4�ߴ���ģʽ
//1:����8080ģʽ
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED�˿ڶ���----------------  
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

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

extern  uint16_t BACK_COLOR, POINT_COLOR;   //����ɫ������ɫ

void Lcd_Init(void); 
void LCD_Clear(uint16_t Color);
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
//void LCD_WR_DATA8(char da); //��������-8λ����
//void LCD_WR_DATA(int da);
//void LCD_WR_REG(char da);

void LCD_DrawPoint(uint16_t x,uint16_t y);//����
void LCD_DrawPoint_big(uint16_t x,uint16_t y);//��һ�����
uint16_t  LCD_ReadPoint(uint16_t x,uint16_t y); //����
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r);
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);		   
void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color);
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t Size,const uint8_t *Charasc,uint8_t mode);
void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t Size,const uint8_t *Charasc,uint8_t len,uint8_t mode);
void LCD_ShowString(uint16_t x,uint16_t y,const uint8_t *p);		 //��ʾһ���ַ���,16����
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

//������ɫ
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
//#define BROWN 			 0XBC40 //��ɫ
//#define BRRED 			 0XFC07 //�غ�ɫ
//#define GRAY  			 0X8430 //��ɫ

#define WHITE         	 0xFFFF	//��ɫ
#define BLACK         	 0x0000	//��ɫ  
#define LGREEN         	 0x001F //ǳ��ɫ 
#define GREEN            0XF81F	//��ɫ
#define PURPLE 			 0XFFE0	//��ɫ
#define YELLOW			 0X07FF	//��ɫ
#define LBLUE            0xF800	//ǳ��ɫ
#define RED         	 0x07E0	//��ɫ
#define LWHITE           0x7FFF	//ǳ��
#define BLUE 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ

//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)


					  		 
#endif  
	 
	 



