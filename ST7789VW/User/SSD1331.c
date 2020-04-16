/**
  ******************************************************************************
  * @file    xxx.c 
  * @author  Waveshare Team
  * @version 
  * @date    xx-xx-2014
  * @brief   xxxxx.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, WAVESHARE SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "SSD1331.h"
#include "Fonts.h"
#include <stdlib.h>
#include "Fonts.h"
#include "delay.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SSD1331_CMD                     0
#define SSD1331_DATA                    1
                 
#define OLED_WIDTH                      96
#define OLED_HEIGHT            			64

/* Private macro -------------------------------------------------------------*/
#define DRAW_LINE                       0x21
#define DRAW_RECTANGLE                  0x22
#define COPY_WINDOW                     0x23
#define DIM_WINDOW                      0x24
#define CLEAR_WINDOW                    0x25
#define FILL_WINDOW                     0x26
#define DISABLE_FILL                    0x00
#define ENABLE_FILL                     0x01
#define CONTINUOUS_SCROLLING_SETUP      0x27
#define DEACTIVE_SCROLLING              0x2E
#define ACTIVE_SCROLLING                0x2F

#define SET_COLUMN_ADDRESS              0x15
#define SET_ROW_ADDRESS                 0x75
#define SET_CONTRAST_A                  0x81
#define SET_CONTRAST_B                  0x82
#define SET_CONTRAST_C                  0x83
#define MASTER_CURRENT_CONTROL          0x87
#define SET_PRECHARGE_SPEED_A           0x8A
#define SET_PRECHARGE_SPEED_B           0x8B
#define SET_PRECHARGE_SPEED_C           0x8C
#define SET_REMAP                       0xA0
#define SET_DISPLAY_START_LINE          0xA1
#define SET_DISPLAY_OFFSET              0xA2
#define NORMAL_DISPLAY                  0xA4
#define ENTIRE_DISPLAY_ON               0xA5
#define ENTIRE_DISPLAY_OFF              0xA6
#define INVERSE_DISPLAY                 0xA7
#define SET_MULTIPLEX_RATIO             0xA8
#define DIM_MODE_SETTING                0xAB
#define SET_MASTER_CONFIGURE            0xAD
#define DIM_MODE_DISPLAY_ON             0xAC
#define DISPLAY_OFF                     0xAE
#define NORMAL_BRIGHTNESS_DISPLAY_ON    0xAF
#define POWER_SAVE_MODE                 0xB0
#define PHASE_PERIOD_ADJUSTMENT         0xB1
#define DISPLAY_CLOCK_DIV               0xB3
#define SET_GRAy_SCALE_TABLE            0xB8
#define ENABLE_LINEAR_GRAY_SCALE_TABLE  0xB9
#define SET_PRECHARGE_VOLTAGE           0xBB
#define SET_V_VOLTAGE                   0xBE

 /**
		dc=1：数据读写
		dc=0：命令读写
		cs=1:不选中
		cs=0:不选中
		res=0:复位
		//6800模式
		RW=1:read
		RW=0:write
 **/

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief 
 * @param 
 * @retval 
 */

 /**
   * @brief  Writes an byte to the display data ram or the command register
   *		 
   * @param  chData: Data to be writen to the display data ram or the command register
   * @param chCmd:	
   *	0: Writes to the command register
   *	1: Writes to the display data ram
		dc=1：数据读写
		dc=0：命令读写
   * @retval None
 **/
void ssd1331_write_byte(uint8_t chData, uint8_t chCmd) 
{
	SET_WR_L;
	delay_us(4);
	if (chCmd) 
	{
		SET_DC_H;
	} 
	else 
	{
		SET_DC_L;
	}
	SSD1331_Send_Byte(chData);
	delay_us(4);
	SET_WR_H;
	delay_us(4);
	SET_DC_H;
	SET_WR_H;
}

void SSD1331_Send_Byte(uint8_t chData)
{
	(chData>>0 & 0x01) ?	SET_D0_H:SET_D0_L;
	(chData>>1 & 0x01) ?	SET_D1_H:SET_D1_L;
	(chData>>2 & 0x01) ?	SET_D2_H:SET_D2_L;
	(chData>>3 & 0x01) ?	SET_D3_H:SET_D3_L;
	(chData>>4 & 0x01) ?	SET_D4_H:SET_D4_L;
	(chData>>5 & 0x01) ?	SET_D5_H:SET_D5_L;
	(chData>>6 & 0x01) ?	SET_D6_H:SET_D6_L;
	(chData>>7 & 0x01) ?	SET_D7_H:SET_D7_L;
}

void ssd1331_draw_point(uint8_t chXpos, uint8_t chYpos, uint16_t hwColor) 
{
	if (chXpos >= OLED_WIDTH || chYpos >= OLED_HEIGHT) 
	{
		return;
	}

	//set column point
	ssd1331_write_byte(SET_COLUMN_ADDRESS, SSD1331_CMD);
	ssd1331_write_byte(chXpos, SSD1331_CMD);
	ssd1331_write_byte(OLED_WIDTH - 1, SSD1331_CMD);
	//set row point
	ssd1331_write_byte(SET_ROW_ADDRESS, SSD1331_CMD);
	ssd1331_write_byte(chYpos, SSD1331_CMD);
	ssd1331_write_byte(OLED_HEIGHT - 1, SSD1331_CMD);

	//fill 16bit colour
	ssd1331_write_byte(hwColor >> 8, SSD1331_DATA);
	ssd1331_write_byte(hwColor, SSD1331_DATA);   
}

void ssd1331_draw_line(uint8_t chXpos0, uint8_t chYpos0, uint8_t chXpos1, uint8_t chYpos1, uint16_t hwColor) 
{
	uint8_t x = chXpos1 - chXpos0;
	uint8_t y = chYpos1 - chYpos0;
	uint8_t dx = abs(x), sx = chXpos0 < chXpos1 ? 1 : -1;
	uint8_t dy = -abs(y), sy = chYpos0 < chYpos1 ? 1 : -1;
	uint8_t err = dx + dy, e2;

	if (chXpos0 >= OLED_WIDTH || chYpos0 >= OLED_HEIGHT || chXpos1 >= OLED_WIDTH || chYpos1 >= OLED_HEIGHT) 
	{
		return;
	}

	for (;;)
	{
		ssd1331_draw_point(chXpos0, chYpos0 , hwColor);
		e2 = 2 * err;
		if (e2 >= dy) 
		{     
			if (chXpos0 == chXpos1) break;
			err += dy; chXpos0 += sx;
		}
		if (e2 <= dx) 
		{
			if (chYpos0 == chYpos1) break;
			err += dx; chYpos0 += sy;
		}
	}
}

void ssd1331_draw_v_line(uint8_t chXpos, uint8_t chYpos, uint8_t chHeight, uint16_t hwColor)
{	
	uint16_t i, y1 = MIN(chYpos + chHeight, OLED_HEIGHT - 1);

	if (chXpos >= OLED_WIDTH || chYpos >= OLED_HEIGHT) 
	{
		return;
	}
	
    for (i = chYpos; i < y1; i ++) 
	{
        ssd1331_draw_point(chXpos, i, hwColor);
    }
}

void ssd1331_draw_h_line(uint8_t chXpos, uint8_t chYpos, uint8_t chWidth, uint16_t hwColor)
{	
	uint16_t i, x1 = MIN(chXpos + chWidth, OLED_WIDTH- 1);

	if (chXpos >= OLED_WIDTH || chYpos >= OLED_HEIGHT) 
	{
		return;
	}
	
    for (i = chXpos; i < x1; i ++) 
	{
        ssd1331_draw_point(i, chYpos, hwColor);
    }
}

void ssd1331_draw_rect(uint8_t chXpos, uint8_t chYpos, uint8_t chWidth, uint8_t chHeight, uint16_t hwColor)
{
	if (chXpos >= OLED_WIDTH || chYpos >= OLED_HEIGHT) 
	{
		return;
	}

	ssd1331_draw_h_line(chXpos, chYpos, chWidth, hwColor);
	ssd1331_draw_h_line(chXpos, chYpos + chHeight, chWidth, hwColor);
	ssd1331_draw_v_line(chXpos, chYpos, chHeight, hwColor);
	ssd1331_draw_v_line(chXpos + chWidth, chYpos, chHeight + 1, hwColor);
}

void ssd1331_fill_rect(uint8_t chXpos, uint8_t chYpos, uint8_t chWidth, uint8_t chHeight, uint16_t hwColor)
{
	uint16_t i, j;

	if (chXpos >= OLED_WIDTH || chYpos >= OLED_HEIGHT) 
	{
		return;
	}
	
	for(i = 0; i < chHeight; i ++)
	{
		for(j = 0; j < chWidth; j ++)
		{
			ssd1331_draw_point(chXpos + j, chYpos + i, hwColor);
		}
	}
}

void ssd1331_draw_circle(uint8_t chXpos, uint8_t chYpos, uint8_t chRadius, uint16_t hwColor)
{
	int x = -chRadius, y = 0, err = 2 - 2 * chRadius, e2;

	if (chXpos >= OLED_WIDTH || chYpos >= OLED_HEIGHT) 
	{
		return;
	}
	
    do 
	{
        ssd1331_draw_point(chXpos - x, chYpos + y, hwColor);
        ssd1331_draw_point(chXpos + x, chYpos + y, hwColor);
        ssd1331_draw_point(chXpos + x, chYpos - y, hwColor);
        ssd1331_draw_point(chXpos - x, chYpos - y, hwColor);
        e2 = err;
        if (e2 <= y) 
		{
            err += ++ y * 2 + 1;
            if(-x == y && e2 <= x) e2 = 0;
        }
        if(e2 > x) err += ++ x * 2 + 1;
    } 
	while(x <= 0);
}

/**
  * @brief Displays one character at the specified position    
  *         
  * @param  chXpos: Specifies the X position
  * @param  chYpos: Specifies the Y position
  * @param  chSize: 
  * @param  chMode
  * @retval 
**/
void ssd1331_display_char(uint8_t chXpos, uint8_t chYpos, uint8_t chChr, uint8_t chSize, uint16_t hwColor)
{      	
	uint8_t i, j, chTemp;
	uint8_t chYpos0 = chYpos;

	if (chXpos >= OLED_WIDTH || chYpos >= OLED_HEIGHT) 
	{
		return;
	}
					   
    for (i = 0; i < chSize; i ++) 
	{   
		if (FONT_1206 == chSize) 
		{
			chTemp = c_chFont1206[chChr - 0x20][i];  
		} 
		else if (FONT_1608 == chSize) 
		{ 
			chTemp = c_chFont1608[chChr - 0x20][i];
		}
		
        for (j = 0; j < 8; j ++) 
		{
    		if (chTemp & 0x80) 
			{
				ssd1331_draw_point(chXpos, chYpos, hwColor);
    		}			
			chTemp <<= 1;
			chYpos ++;
			if ((chYpos - chYpos0) == chSize) 
			{
				chYpos = chYpos0;
				chXpos ++;
				break;
			}
		}  	 
    } 
}

static uint32_t _pow(uint8_t m, uint8_t n)
{
	uint32_t result = 1;
	
	while(n --) result *= m;    
	return result;
}


void ssd1331_display_num(uint8_t chXpos, uint8_t chYpos, uint32_t chNum, uint8_t chLen, uint8_t chSize, uint16_t hwColor)
{         	
	uint8_t i;
	uint8_t chTemp, chShow = 0;

	if (chXpos >= OLED_WIDTH || chYpos >= OLED_HEIGHT) 
	{
		return;
	}
	
	for(i = 0; i < chLen; i ++) 
	{
		chTemp = (chNum / _pow(10, chLen - i - 1)) % 10;
		if(chShow == 0 && i < (chLen - 1)) 
		{
			if(chTemp == 0) 
			{
				ssd1331_display_char(chXpos + (chSize / 2) * i, chYpos, ' ', chSize, hwColor);
				continue;
			} 
			else 
			{
				chShow = 1;
			}	 
		}
	 	ssd1331_display_char(chXpos + (chSize / 2) * i, chYpos, chTemp + '0', chSize, hwColor); 
	}
} 


/**
  * @brief  Displays a string on the screen
  *         
  * @param  chXpos: Specifies the X position
  * @param  chYpos: Specifies the Y position
  * @param  pchString: Pointer to a string to display on the screen 
  *         
  * @retval  None
**/
void ssd1331_display_string(uint8_t chXpos, uint8_t chYpos, const char *pchString, uint8_t chSize, uint16_t hwColor)
{
	if (chXpos >= OLED_WIDTH || chYpos >= OLED_HEIGHT) 
	{
		return;
	}
	
    while (*pchString != '\0') 
	{       
        if (chXpos > (OLED_WIDTH - chSize / 2)) 
		{
			chXpos = 0;
			chYpos += chSize;
			if (chYpos > (OLED_HEIGHT - chSize)) 
			{
				chYpos = chXpos = 0;
				ssd1331_clear_screen(0x00);
			}
		}
		
        ssd1331_display_char(chXpos, chYpos, *pchString, chSize, hwColor);
        chXpos += chSize / 2;
        pchString ++;
    } 
}

void ssd1331_draw_1616char(uint8_t chXpos, uint8_t chYpos, uint8_t chChar, uint16_t hwColor)
{
	uint8_t i, j;
	uint8_t chTemp = 0, chYpos0 = chYpos;

	for (i = 0; i < 32; i ++) 
	{
		chTemp = c_chFont1612[chChar - 0x30][i];
		for (j = 0; j < 8; j ++) 
		{
			if (chTemp & 0x80) 
			{
				ssd1331_draw_point(chXpos, chYpos, hwColor);
    		}
			chTemp <<= 1;
			chYpos ++;
			if ((chYpos - chYpos0) == 16) 
			{
				chYpos = chYpos0;
				chXpos ++;
				break;
			}
		}
	}
}

void ssd1331_draw_3216char(uint8_t chXpos, uint8_t chYpos, uint8_t chChar, uint16_t hwColor)
{
	uint8_t i, j;
	uint8_t chTemp = 0, chYpos0 = chYpos;

	for (i = 0; i < 64; i ++) 
	{
		chTemp = c_chFont3216[chChar - 0x30][i];
		for (j = 0; j < 8; j ++) 
		{
			if (chTemp & 0x80) 
			{
				ssd1331_draw_point(chXpos, chYpos, hwColor);
    		}
			chTemp <<= 1;
			chYpos ++;
			if ((chYpos - chYpos0) == 32) 
			{
				chYpos = chYpos0;
				chXpos ++;
				break;
			}
		}
	}
}

void ssd1331_draw_bitmap(uint8_t chXpos, uint8_t chYpos, const uint8_t *pchBmp, uint8_t chWidth, uint8_t chHeight, uint16_t hwColor)
{
	uint16_t i, j, byteWidth = (chWidth + 7) / 8;
	
    for(j = 0; j < chHeight; j ++)
	{
        for(i = 0; i < chWidth; i ++ ) 
		{
            if(*(pchBmp + j * byteWidth + i / 8) & (128 >> (i & 7))) 
			{
                ssd1331_draw_point(chXpos + i, chYpos + j, hwColor);
            }
        }
    }
}

void ssd1331_clear_screen(uint16_t hwColor)  
{
	uint16_t i, j;
	
	for(i = 0; i < OLED_HEIGHT; i ++)
	{
		for(j = 0; j < OLED_WIDTH; j ++)
		{
			ssd1331_draw_point(j, i, hwColor);
		}
	}
}


void ssd1331_init(void)
{
	
	SET_RES_H;
	delay_ms(100);
	SET_RES_L;
	delay_ms(100);
	SET_RES_H;
	
	ssd1331_write_byte(0x11,SSD1331_CMD);     //Sleep out
	delay_ms(200);
	
	ssd1331_write_byte(0x36,SSD1331_CMD);     //MX, MY, RGB mode
	ssd1331_write_byte(0x00,SSD1331_DATA);    //c0

	ssd1331_write_byte(0x3A,SSD1331_CMD);     //MX, MY, RGB mode
	ssd1331_write_byte(0x05,SSD1331_DATA);   	//c0

	ssd1331_write_byte(0x21,SSD1331_CMD);

	ssd1331_write_byte(0xB2,SSD1331_CMD);
	ssd1331_write_byte(0x05,SSD1331_DATA);   
	ssd1331_write_byte(0x05,SSD1331_DATA);       
	ssd1331_write_byte(0x00,SSD1331_DATA);   
	ssd1331_write_byte(0x33,SSD1331_DATA);   
	ssd1331_write_byte(0x33,SSD1331_DATA);   

	ssd1331_write_byte(0xB7,SSD1331_CMD);     
	ssd1331_write_byte(0x23,SSD1331_DATA);   
	 

	ssd1331_write_byte(0xBB,SSD1331_CMD);    
	ssd1331_write_byte(0x22,SSD1331_DATA);   

	ssd1331_write_byte(0xC0,SSD1331_CMD);     
	ssd1331_write_byte(0x2C,SSD1331_DATA);   


	ssd1331_write_byte(0xC2,SSD1331_CMD);     
	ssd1331_write_byte(0x01,SSD1331_DATA);   


	ssd1331_write_byte(0xC3,SSD1331_CMD);     
	ssd1331_write_byte(0x13,SSD1331_DATA);   


	ssd1331_write_byte(0xC4,SSD1331_CMD);     
	ssd1331_write_byte(0x20,SSD1331_DATA); 

	ssd1331_write_byte(0xC6,SSD1331_CMD);    
	ssd1331_write_byte(0x0F,SSD1331_DATA);


	ssd1331_write_byte(0xD0,SSD1331_CMD);    
	ssd1331_write_byte(0xA4,SSD1331_DATA);
	ssd1331_write_byte(0xA1,SSD1331_DATA);

	ssd1331_write_byte(0xD6,SSD1331_CMD);    
	ssd1331_write_byte(0xA1,SSD1331_DATA);
	  
	ssd1331_write_byte(0xE0,SSD1331_CMD);     
	ssd1331_write_byte(0x70,SSD1331_DATA);   
	ssd1331_write_byte(0x06,SSD1331_DATA);   
	ssd1331_write_byte(0x0C,SSD1331_DATA);   
	ssd1331_write_byte(0x08,SSD1331_DATA);   
	ssd1331_write_byte(0x09,SSD1331_DATA);   
	ssd1331_write_byte(0x27,SSD1331_DATA);   
	ssd1331_write_byte(0x2E,SSD1331_DATA);   
	ssd1331_write_byte(0x34,SSD1331_DATA);   
	ssd1331_write_byte(0x46,SSD1331_DATA);   
	ssd1331_write_byte(0x37,SSD1331_DATA);   
	ssd1331_write_byte(0x13,SSD1331_DATA);   
	ssd1331_write_byte(0x13,SSD1331_DATA);   
	ssd1331_write_byte(0x25,SSD1331_DATA);   
	ssd1331_write_byte(0x2A,SSD1331_DATA);
	 

	ssd1331_write_byte(0xE1,SSD1331_CMD);     
	ssd1331_write_byte(0x70,SSD1331_DATA);   
	ssd1331_write_byte(0x04,SSD1331_DATA);   
	ssd1331_write_byte(0x08,SSD1331_DATA);   
	ssd1331_write_byte(0x09,SSD1331_DATA);   
	ssd1331_write_byte(0x07,SSD1331_DATA);   
	ssd1331_write_byte(0x03,SSD1331_DATA);   
	ssd1331_write_byte(0x2C,SSD1331_DATA);   
	ssd1331_write_byte(0x42,SSD1331_DATA);   
	ssd1331_write_byte(0x42,SSD1331_DATA);   
	ssd1331_write_byte(0x38,SSD1331_DATA);   
	ssd1331_write_byte(0x14,SSD1331_DATA);   
	ssd1331_write_byte(0x14,SSD1331_DATA);   
	ssd1331_write_byte(0x27,SSD1331_DATA);   
	ssd1331_write_byte(0x2C,SSD1331_DATA); 

	ssd1331_write_byte(0x21,SSD1331_CMD); 

	ssd1331_write_byte(0x11,SSD1331_CMD); 
	delay_ms(120); 

	ssd1331_write_byte(0x29,SSD1331_CMD);     //Display on	
	
	
	
//*********************************************************************************	
//	ssd1331_write_byte(DISPLAY_OFF, SSD1331_CMD);          //Display Off
//    ssd1331_write_byte(SET_CONTRAST_A, SSD1331_CMD);       //Set contrast for color A
//    ssd1331_write_byte(0xFF, SSD1331_CMD);                     //145 0x91
//    ssd1331_write_byte(SET_CONTRAST_B, SSD1331_CMD);       //Set contrast for color B
//    ssd1331_write_byte(0xFF, SSD1331_CMD);                     //80 0x50
//    ssd1331_write_byte(SET_CONTRAST_C, SSD1331_CMD);       //Set contrast for color C
//    ssd1331_write_byte(0xFF, SSD1331_CMD);                     //125 0x7D
//    ssd1331_write_byte(MASTER_CURRENT_CONTROL, SSD1331_CMD);//master current control
//    ssd1331_write_byte(0x06, SSD1331_CMD);                     //6
//    ssd1331_write_byte(SET_PRECHARGE_SPEED_A, SSD1331_CMD);//Set Second Pre-change Speed For ColorA
//    ssd1331_write_byte(0x64, SSD1331_CMD);                     //100
//    ssd1331_write_byte(SET_PRECHARGE_SPEED_B, SSD1331_CMD);//Set Second Pre-change Speed For ColorB
//    ssd1331_write_byte(0x78, SSD1331_CMD);                     //120
//    ssd1331_write_byte(SET_PRECHARGE_SPEED_C, SSD1331_CMD);//Set Second Pre-change Speed For ColorC
//    ssd1331_write_byte(0x64, SSD1331_CMD);                     //100
//    ssd1331_write_byte(SET_REMAP, SSD1331_CMD);            //set remap & data format
//    ssd1331_write_byte(0x72, SSD1331_CMD);                     //0x72              
//    ssd1331_write_byte(SET_DISPLAY_START_LINE, SSD1331_CMD);//Set display Start Line
//    ssd1331_write_byte(0x0, SSD1331_CMD);
//    ssd1331_write_byte(SET_DISPLAY_OFFSET, SSD1331_CMD);   //Set display offset
//    ssd1331_write_byte(0x0, SSD1331_CMD);
//    ssd1331_write_byte(NORMAL_DISPLAY, SSD1331_CMD);       //Set display mode
//    ssd1331_write_byte(SET_MULTIPLEX_RATIO, SSD1331_CMD);  //Set multiplex ratio
//    ssd1331_write_byte(0x3F, SSD1331_CMD);
//    ssd1331_write_byte(SET_MASTER_CONFIGURE, SSD1331_CMD); //Set master configuration
//    ssd1331_write_byte(0x8E, SSD1331_CMD);
//    ssd1331_write_byte(POWER_SAVE_MODE, SSD1331_CMD);      //Set Power Save Mode
//    ssd1331_write_byte(0x00, SSD1331_CMD);                     //0x00
//    ssd1331_write_byte(PHASE_PERIOD_ADJUSTMENT, SSD1331_CMD);//phase 1 and 2 period adjustment
//    ssd1331_write_byte(0x31, SSD1331_CMD);                     //0x31
//    ssd1331_write_byte(DISPLAY_CLOCK_DIV, SSD1331_CMD);    //display clock divider/oscillator frequency
//    ssd1331_write_byte(0xF0, SSD1331_CMD);
//    ssd1331_write_byte(SET_PRECHARGE_VOLTAGE, SSD1331_CMD);//Set Pre-Change Level
//    ssd1331_write_byte(0x3A, SSD1331_CMD);
//    ssd1331_write_byte(SET_V_VOLTAGE, SSD1331_CMD);        //Set vcomH
//    ssd1331_write_byte(0x3E, SSD1331_CMD);
//    ssd1331_write_byte(DEACTIVE_SCROLLING, SSD1331_CMD);   //disable scrolling
//    ssd1331_write_byte(NORMAL_BRIGHTNESS_DISPLAY_ON, SSD1331_CMD);//set display on
//    //ssd1331_fill_rect(0, 0, 96, 64, 0x0000);
//    ssd1331_clear_screen(0x0000);
	
}
void ssd1331_IOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(	RCC_AHBPeriph_GPIOA, ENABLE );
	RCC_AHBPeriphClockCmd(	RCC_AHBPeriph_GPIOB, ENABLE );

    RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOC|GPIO_Mode_AF,ENABLE );
    RCC_LSEConfig( RCC_LSE_OFF ); /* 关闭外部低速时钟,PC14+PC15可以用作普通IO*/

    GPIO_InitStructure.GPIO_Pin = RES_Pin |WR_Pin ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;          
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOC, RES_Pin | WR_Pin);
	

	
	
	GPIO_InitStructure.GPIO_Pin = DC_Pin ;  				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,DC_Pin);
	
	GPIO_InitStructure.GPIO_Pin = LED_Pin ;  				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,LED_Pin);
		
	GPIO_InitStructure.GPIO_Pin = D0_Pin|D1_Pin|D2_Pin|D3_Pin|D4_Pin|D5_Pin|D6_Pin|D7_Pin ;  				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,D0_Pin|D1_Pin|D2_Pin|D3_Pin|D4_Pin|D5_Pin|D6_Pin|D7_Pin);
}

void address(void)
{             
	ssd1331_write_byte(0x2A,SSD1331_CMD);       
	ssd1331_write_byte(0x00,SSD1331_DATA);  
	ssd1331_write_byte(0x34,SSD1331_DATA); //52 
	ssd1331_write_byte(0x00,SSD1331_DATA);
	ssd1331_write_byte(0xBa,SSD1331_DATA);  //186

	ssd1331_write_byte(0x2B,SSD1331_CMD);       
	ssd1331_write_byte(0x00,SSD1331_DATA);
	ssd1331_write_byte(0x28,SSD1331_DATA);  //40
	ssd1331_write_byte(0x01,SSD1331_DATA);
	ssd1331_write_byte(0x17,SSD1331_DATA);  //279
				   
	ssd1331_write_byte(0x2C,SSD1331_CMD);
 }	

void fillcolor(unsigned char dat1,unsigned char dat2)
{
    unsigned char i,j;

    address();
    
    for (i=0;i<240;i++)
        for (j=0;j<135;j++)
         {
           ssd1331_write_byte(dat1,SSD1331_DATA);
           ssd1331_write_byte(dat2,SSD1331_DATA);
         }
}

 


