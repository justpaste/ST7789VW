/**
  ******************************************************************************
  * @file    xxx.h
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


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SSD1331_H_
#define _SSD1331_H_

/* Includes ------------------------------------------------------------------*/
#include "MacroAndConst.h"
#include <math.h>
#include <stdlib.h>
#include "stm32f0xx.h" 

#define FONT_1206    12
#define FONT_1608    16



#define	DC_Pin	GPIO_Pin_13		//PB13
#define	RES_Pin	GPIO_Pin_13		//PC14
#define	WR_Pin	GPIO_Pin_15		//PC13->WR

#define	LED_Pin	GPIO_Pin_8		//PA8

#define	D0_Pin	GPIO_Pin_0		//PB0
#define	D1_Pin	GPIO_Pin_1		//PB1
#define	D2_Pin	GPIO_Pin_2		//PB2
#define	D3_Pin	GPIO_Pin_3		//PB3
#define	D4_Pin	GPIO_Pin_4		//PB4
#define	D5_Pin	GPIO_Pin_5		//PB5
#define	D6_Pin	GPIO_Pin_6		//PB6
#define	D7_Pin	GPIO_Pin_7		//PB7


#define SET_DC_H    GPIO_WriteBit(GPIOB,DC_Pin,(BitAction)(0x01))
#define SET_DC_L    GPIO_WriteBit(GPIOB,DC_Pin,(BitAction)(0x00))

#define SET_LED_H    GPIO_WriteBit(GPIOA,LED_Pin,(BitAction)(0x01))
#define SET_LED_L    GPIO_WriteBit(GPIOA,LED_Pin,(BitAction)(0x00))

#define SET_RES_H   GPIO_WriteBit(GPIOC,RES_Pin,(BitAction)(0x01))
#define SET_RES_L   GPIO_WriteBit(GPIOC,RES_Pin,(BitAction)(0x00))

#define SET_WR_H    GPIO_WriteBit(GPIOC,WR_Pin,(BitAction)(0x01))
#define SET_WR_L    GPIO_WriteBit(GPIOC,WR_Pin,(BitAction)(0x00))

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




#define RGB(R,G,B)  (((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3))
enum Color{
    BLACK     = RGB(  0,  0,  0), // black
    GREY      = RGB(192,192,192), // grey
    WHITE     = RGB(255,255,255), // white
    RED       = RGB(255,  0,  0), // red
    PINK      = RGB(255,192,203), // pink
    YELLOW    = RGB(255,255,  0), // yellow
    GOLDEN    = RGB(255,215,  0), // golden
    BROWN     = RGB(128, 42, 42), // brown
    BLUE      = RGB(  0,  0,255), // blue
    CYAN      = RGB(  0,255,255), // cyan
    GREEN     = RGB(  0,255,  0), // green
    PURPLE    = RGB(160, 32,240), // purple
};


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/                    

/* Exported functions ------------------------------------------------------- */
extern void ssd1331_draw_point(uint8_t chXpos, uint8_t chYpos, uint16_t hwColor);
extern void ssd1331_draw_line(uint8_t chXpos0, uint8_t chYpos0, uint8_t chXpos1, uint8_t chYpos1, uint16_t hwColor);
extern void ssd1331_draw_v_line(uint8_t chXpos, uint8_t chYpos, uint8_t chHeight, uint16_t hwColor);
extern void ssd1331_draw_h_line(uint8_t chXpos, uint8_t chYpos, uint8_t chWidth, uint16_t hwColor);
extern void ssd1331_draw_rect(uint8_t chXpos, uint8_t chYpos, uint8_t chWidth, uint8_t chHeight, uint16_t hwColor);
extern void ssd1331_fill_rect(uint8_t chXpos, uint8_t chYpos, uint8_t chWidth, uint8_t chHeight, uint16_t hwColor);
extern void ssd1331_draw_circle(uint8_t chXpos, uint8_t chYpos, uint8_t chRadius, uint16_t hwColor);
extern void ssd1331_display_char(uint8_t chXpos, uint8_t chYpos, uint8_t chChr, uint8_t chSize, uint16_t hwColor);
extern void ssd1331_display_num(uint8_t chXpos, uint8_t chYpos, uint32_t chNum, uint8_t chLen, uint8_t chSize, uint16_t hwColor);
extern void ssd1331_display_string(uint8_t chXpos, uint8_t chYpos, const char *pchString, uint8_t chSize, uint16_t hwColor);
extern void ssd1331_draw_1616char(uint8_t chXpos, uint8_t chYpos, uint8_t chChar, uint16_t hwColor);
extern void ssd1331_draw_3216char(uint8_t chXpos, uint8_t chYpos, uint8_t chChar, uint16_t hwColor);
extern void ssd1331_draw_bitmap(uint8_t chXpos, uint8_t chYpos, const uint8_t *pchBmp, uint8_t chWidth, uint8_t chHeight, uint16_t hwColor);
extern void ssd1331_clear_screen(uint16_t hwColor);

extern void ssd1331_init(void);

void SSD1331_Send_Byte(uint8_t chData);
void ssd1331_IOInit(void);
void ssd1331_write_byte(uint8_t chData, uint8_t chCmd);


void address(void);
void fillcolor(unsigned char dat1,unsigned char dat2);



#endif
/*-------------------------------END OF FILE-------------------------------*/

