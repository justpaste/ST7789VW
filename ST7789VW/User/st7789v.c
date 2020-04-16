/*
**
**************************************************************************
* �ļ�����TFT������
* ��  �ߣ�С��ͯ
* ˵  �������ļ���������ILI9328����������TFT���ĸ��ֹ��ܺ���
          ��Ҫʵ��TFT�������ֺ�ͼƬ����ʾ����
* �汾�ţ�V1.1
* ��  �ڣ�2012.2.29
**************************************************************************
  ��������Ҫ˼��������ͨ��IO����ģ��TFT����ʱ����SD������ɶ�TFT���Ķ�д
  ������ʵ�����ֺ�ͼƬ����ʾ
**
*/


//++++++++++++++++++++++++ include +++++++++++++++++++++++++++++++++++++++
#include "delay.h"
#include "st7789v.h"
#include "english_32x16.h"
//+++++++++++++++++++++++++ define +++++++++++++++++++++++++++++++++++++++++


//#define LCD_RSTL   GPIOB->BRR = GPIO_Pin_1  //GPIO_ResetBits( GPIOC, GPIO_Pin_15 )       CSƬѡ WRд RD�� RS���ݡ�ָ��
//#define LCD_RSTH   GPIOB->BSRR = GPIO_Pin_1 //GPIO_SetBits( GPIOC, GPIO_Pin_15 )
//#define LCD_WRL    GPIOB->BRR = GPIO_Pin_12  //GPIO_ResetBits( GPIOC, GPIO_Pin_13 )
//#define LCD_WRH    GPIOB->BSRR = GPIO_Pin_12 //GPIO_SetBits( GPIOC, GPIO_Pin_13 )
//#define LCD_CSL    GPIOB->BRR = GPIO_Pin_14  //GPIO_ResetBits( GPIOC, GPIO_Pin_14 )
//#define LCD_CSH    GPIOB->BSRR = GPIO_Pin_14 //GPIO_SetBits( GPIOC, GPIO_Pin_14 )
//#define LCD_RDL    GPIOB->BRR = GPIO_Pin_13   //GPIO_ResetBits( GPIOE, GPIO_Pin_5 )
//#define LCD_RDH    GPIOB->BSRR = GPIO_Pin_13  //GPIO_SetBits( GPIOE, GPIO_Pin_5 )
//#define LCD_RSL    GPIOB->BRR = GPIO_Pin_15   //GPIO_ResetBits( GPIOE, GPIO_Pin_6 )
//#define LCD_RSH    GPIOB->BSRR = GPIO_Pin_15  //GPIO_SetBits( GPIOE, GPIO_Pin_6 )

//**************************************************************************8
#define	DC_Pin	GPIO_Pin_13		//PB13
#define	RES_Pin	GPIO_Pin_14	//PC14
#define	WR_Pin	GPIO_Pin_13		//PC13->WR

#define	LED_Pin	GPIO_Pin_8		//PA8

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
//******************************************************************************





//+++++++++++++++++++++ static valible +++++++++++++++++++++++++++++++++++++
 //uint16_t backcolor = BLACK;
 //uint16_t temp1=0;
 //uint8_t temp=0;

 extern uint8_t buff[512]={0};
 extern char display_temp[20],display_counter,display_true,BUFF;
 
 
 extern uint8_t displayenable ;
 //extern uint16_t X_center_TFT=160,Y_center_TFT=120;
 #define    X_center_TFT    160
 #define    Y_center_TFT    120
//FRESULT res = FR_OK;
//unsigned char *p1;
extern uint8_t sleep;

//+++++++++++++++++++++++++++++ INTER   FUNCTION +++++++++++++++++++++++++++



/*��������STM32ForLCD
 *��  �ܣ�ΪLCDģ������STM32�ӿ���Դ
 *��  ������
 *����ֵ����
 */
void ssd1331_IOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(	RCC_AHBPeriph_GPIOA, ENABLE );
	RCC_AHBPeriphClockCmd(	RCC_AHBPeriph_GPIOB, ENABLE );

    RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOC|GPIO_Mode_AF,ENABLE );
    RCC_LSEConfig( RCC_LSE_OFF ); /* �ر��ⲿ����ʱ��,PC14+PC15����������ͨIO*/

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



/*��������LCD_CmdWrite
 *��  �ܣ���LCD������д�����
 *����ֵ����
 *��  ����uint8_t cmd�����
 */
 void LCD_CmdWrite(uint8_t cmd)			   
{
	uint16_t num=0;   
	LCD_RSL;
	delay_us(4);
//	LCD_CSL;        
//	LCD_RDH;
	SSD1331_Send_Byte(cmd);
//	num=cmd;  
//	num |=((GPIOB->ODR)&0xFF00);
//	(GPIOB->ODR) =num;
	delay_us(4);	
	LCD_WRL;
	delay_us(4);	
	LCD_WRH;    
//	LCD_CSH;
	LCD_RSH;
}

/*��������LCD_DataWrite
 *��  �ܣ���LCD������д�������
 *����ֵ����
 *��  ����uint8_t data Ҫд�������
 */
 void LCD_DataWrite(uint8_t data)		
{
	uint16_t num=0;   
	LCD_RSH; 
	delay_us(4);
//    LCD_CSL; 
//    LCD_RDH; 
	SSD1331_Send_Byte(data);	
//	num=data;  
//	num |=((GPIOB->ODR)&0xFF00);
//	(GPIOB->ODR) =num;
	delay_us(4); 
	LCD_WRL;
	delay_us(4);    
	LCD_WRH;    
	//    LCD_CSH;
}

/*����������
 *��  �ܣ���TFT�е�index�Ĵ�����ֵʵ�ֲ�ͬ����
 *��  ����uint8_t index�Ĵ��������� uint8_t data�Ĵ���ֵ
 *����ֵ����

static void LCD_CmdWrite(uint8_t index, uint8_t data)
{
    LCD_CmdWrite(index);
    LCD_DataWrite(data);
}
 */
/*��������LCD_Reset
 *��  �ܣ���λTFT��
 *��  ������
 *����ֵ����
 */
static void LCD_Reset(void)
{
  //************* Reset LCD Driver ****************// 
    LCD_RSTH;    
    delay_ms(1);  // delay_ms 1ms 
    LCD_RSTL;  
    delay_ms(10); // delay_ms 10ms               // This delay time is necessary 
    LCD_RSTH;    
    delay_ms(120); // delay_ms 120 ms   	  
}

/*************************************************
��������Lcd�����㶨λ����
���ܣ�ָ��320240Һ���ϵ�һ����Ϊд���ݵ���ʼ��
��ڲ�����x ���� 0~239
          y ���� 0~319
����ֵ����
*************************************************/
/*static void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
    LCD_CmdWrite(0x20, Xpos);
    LCD_CmdWrite(0x21, Ypos);
}
*/

void LCD_WriteOneDot(uint16_t color)
{ 
    LCD_DataWrite(color>>8);
    LCD_DataWrite(color);
}
/**********************************************
��������Lcd��ѡ����
���ܣ�ѡ��Lcd��ָ���ľ�������
ע�⣺xStart�� yStart������Ļ����ת���ı䣬λ���Ǿ��ο���ĸ���
��ڲ�����xStart x�������ʼ��
          ySrart y�������ʼ��
          xlong  x������յ�
          ylong  y������յ�
����ֵ����
***********************************************/
void Lcd_SetBox(uint16_t xStart,uint16_t yStart,uint16_t xlong,uint16_t ylong)
{
        uint16_t xEnd=0, yEnd=0;
        xEnd=xStart+xlong-1;
        yEnd=yStart+ylong-1;
        
        LCD_CmdWrite(0x2a);   
	LCD_DataWrite(xStart>>8);
	LCD_DataWrite(xStart);
	LCD_DataWrite(xEnd>>8);
	LCD_DataWrite(xEnd);

	LCD_CmdWrite(0x2b);   
	LCD_DataWrite(yStart>>8);
	LCD_DataWrite(yStart);
	LCD_DataWrite(yEnd>>8);
	LCD_DataWrite(yEnd);

	LCD_CmdWrite(0x2c);                                    

    	
}

void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{
  Lcd_SetBox(x,y,1,1);
  LCD_WriteOneDot(color);
  
}
/**********************************************
��������LCD_write_english
���ܣ�ѡ��Lcd��дһ��Ӣ�Ļ�����
��ڲ�����data Ҫд���ַ�
          color �ַ�����ɫ
          xcolor �ַ��ı���ɫ
          size  ����Ĵ�С
����ֵ����
***********************************************/
static void LCD_write_english(uint8_t data,uint16_t color,uint16_t xcolor ,uint8_t mode)//д�ַ�
{
  uint8_t i=0,j=0,n=0;
  uint8_t avl=0;
  data -=32;                      
  for (i=0;i<120;i++) //Ϊ 20x40�ֿ�       
  {     
    avl=english[data][i];         
    for (j=0;j<8;j++)           
    {
      n++;
      if(avl&0x80)LCD_WriteOneDot(color);        
      else if(mode==0) LCD_WriteOneDot(xcolor);
      avl<<=1;
      if(n>19) {
        n=0;
        break;
      }//����������Ӣ��20*40���γɵ��ֿ�3��8λһ�飬ÿһ�����4λ����ʾ���ø��������ж��м�λ����Ҫ��ʾ
    }     
   }
}


static void LCD_write_chinese(uint16_t data, uint16_t color, uint16_t xcolor,uint8_t mode )//д�ַ�
{
  uint8_t i=0,j=0;
  u32 avl=0;
  //data -=' ';                      //��ASCII��- 32 = �ֿ���������
 //===========Ϊ 48x24�ֿ�       32*16=512�����ص㱣����ʽΪ8λ���ݹ���512/8=64�� ÿһλ�����֡��򡰱�����Ȼ���ٰ�ÿ���������ɫ��ʾ����==========  Ҫ����ʾ��ʲôλ�� ��ʾ�Ĵ�СΪʲô��32X16��LCD_write_english_string����  �����и�Lcd_SetBox
  for (i=0;i<128;i++)
  {     
    avl=Chinese[data][i];         //ȡ��һ��8λ
    for (j=0;j<8;j++)            //����8λ���һ��16λѭ��16�����16������ж� ÿ����ʾ�������ص��ɺ���LCD_write_english_string�����������
    {
      if(avl&0x80)LCD_WriteOneDot(color);        
      else if(mode==0) LCD_WriteOneDot(xcolor);     //��0����ʾΪ�������� �� ������ɫ     
      avl<<=1;
    }
  }
}

static void LCD_write_number(uint8_t data,uint16_t color,uint16_t xcolor,uint8_t mode)//д�ַ�
{
  uint8_t i=0,j=0,n=0;
  uint8_t avl=0;
  data +=16;                      
 //===========Ϊ 20x40�ֿ�       
  for (i=0;i<120;i++)
  {     
    avl=english[data][i]; 
    
    for (j=0;j<8;j++)            
    {
      n++;
      if(avl&0x80)LCD_WriteOneDot(color);        
      else if(mode==0) LCD_WriteOneDot(xcolor);
      avl<<=1;
      if(n>19) {//����������Ӣ��20*40���γɵ��ֿ�3��8λһ�飬ÿһ�����4λ����ʾ���ø��������ж��м�λ����Ҫ��ʾ
        n=0;
        break;
      }

    }     
   }
}
/*
************************************************************************|
**************************** ���º�����ʹ���ߵ���***********************|
************************************************************************|
*/
/*��������LCD_Clear
 *��  �ܣ��Ը�����ɫ��TFT��
 *��  ����color ����Ҫ����ɫֵ
 *����ֵ����
 */
void LCD_Clear(uint16_t Color)
{
   u32 i;  
   Lcd_SetBox(0,0,320,240);  
   for(i=0;i<78900;i++){       
       LCD_WriteOneDot(Color); 
  }
}

void LCD_Clear1(uint16_t xStart,uint16_t yStart,uint16_t xlong,uint16_t ylong,uint16_t Color)
{
   u32 i,j;  
   j=xlong*ylong;
   Lcd_SetBox(xStart,yStart,xlong,ylong);  
   for(i=0;i<j;i++){       
       LCD_WriteOneDot(Color); 
  }
}

/*��������LCDInit
 *��  �ܣ���ʼ��TFT��
 *��  ������
 *����ֵ����
 */

void LCDInit(void)
{
//************* Reset LCD Driver ****************// 
    
	LCD_Reset();
	ssd1331_IOInit();
	
//++++++++++ initializing funciton 1 +++++++++++++++++ 
    LCD_CmdWrite(0x11); 
    delay_ms(120);         //Delay 120ms 

    LCD_CmdWrite(0x36); 
    LCD_DataWrite(0x60); //a0��������00:������60����������
    LCD_CmdWrite(0x3a); 
    LCD_DataWrite(0x05); 

    LCD_CmdWrite(0xb2); 
    LCD_DataWrite(0x0c); 
    LCD_DataWrite(0x0c); 
    LCD_DataWrite(0x00); 
    LCD_DataWrite(0x33); 
    LCD_DataWrite(0x33); 
    LCD_CmdWrite(0xb7); 
    LCD_DataWrite(0x35); 
   
    //24��2.4������ʼ������
    LCD_CmdWrite(0xbb); 
    LCD_DataWrite(0x2b); 
    LCD_CmdWrite(0xc0); 
    LCD_DataWrite(0x2c); 
    LCD_CmdWrite(0xc2); 
    LCD_DataWrite(0x01); 
    LCD_CmdWrite(0xc3); 
    LCD_DataWrite(0x11); 
    LCD_CmdWrite(0xc4); 
    //ST7789V 54
    LCD_DataWrite(0x20); 
    LCD_CmdWrite(0xc6); 
    LCD_DataWrite(0x0f); 
    LCD_CmdWrite(0xd0); 
    LCD_DataWrite(0xa4); 
    LCD_DataWrite(0xa1); 

    LCD_CmdWrite(0xe0); 
    LCD_DataWrite(0xd0); 
    LCD_DataWrite(0x00); 
    LCD_DataWrite(0x05); 
    LCD_DataWrite(0x0e); 
    LCD_DataWrite(0x15); 
    LCD_DataWrite(0x0d); 
    LCD_DataWrite(0x37); 
    LCD_DataWrite(0x43); 
    LCD_DataWrite(0x47); 
    LCD_DataWrite(0x09); 
    LCD_DataWrite(0x15); 
    LCD_DataWrite(0x12); 
    LCD_DataWrite(0x16); 
    LCD_DataWrite(0x19); 
    LCD_CmdWrite(0xe1); 
    LCD_DataWrite(0xd0); 
    LCD_DataWrite(0x00); 
    LCD_DataWrite(0x05); 
    LCD_DataWrite(0x0d); 
    LCD_DataWrite(0x0c); 
    LCD_DataWrite(0x06); 
    LCD_DataWrite(0x2d); 
    LCD_DataWrite(0x44); 
    LCD_DataWrite(0x40); 
    LCD_DataWrite(0x0e); 
    LCD_DataWrite(0x1c); 
    LCD_DataWrite(0x18); 
    LCD_DataWrite(0x16); 
    LCD_DataWrite(0x19); 
    LCD_CmdWrite(0xe7); 
    LCD_DataWrite(0x10);
    LCD_CmdWrite(0x29); //display on
//***************************************************************
//	LCD_CmdWrite(0x11);     //
//	delay_ms(120);
//	LCD_CmdWrite(0x36);     //MX, MY, RGB mode
//	LCD_DataWrite(0x00);   	//c0

//	LCD_CmdWrite(0x3A);     //MX, MY, RGB mode
//	LCD_DataWrite(0x05);   	//c0

//	LCD_CmdWrite(0x21);

//	LCD_CmdWrite(0xB2);
//	LCD_DataWrite(0x05);   
//	LCD_DataWrite(0x05);       
//	LCD_DataWrite(0x00);   
//	LCD_DataWrite(0x33);   
//	LCD_DataWrite(0x33);   

//	LCD_CmdWrite(0xB7);     
//	LCD_DataWrite(0x23);   
//	 

//	LCD_CmdWrite(0xBB);    
//	LCD_DataWrite(0x22);   

//	LCD_CmdWrite(0xC0);     
//	LCD_DataWrite(0x2C);   


//	LCD_CmdWrite(0xC2);     
//	LCD_DataWrite(0x01);   


//	LCD_CmdWrite(0xC3);     
//	LCD_DataWrite(0x13);   


//	LCD_CmdWrite(0xC4);     
//	LCD_DataWrite(0x20); 

//	LCD_CmdWrite(0xC6);    
//	LCD_DataWrite(0x0F);


//	LCD_CmdWrite(0xD0);    
//	LCD_DataWrite(0xA4);
//	LCD_DataWrite(0xA1);

//	LCD_CmdWrite(0xD6);    
//	LCD_DataWrite(0xA1);
//	  
//	LCD_CmdWrite(0xE0);     
//	LCD_DataWrite(0x70);   
//	LCD_DataWrite(0x06);   
//	LCD_DataWrite(0x0C);   
//	LCD_DataWrite(0x08);   
//	LCD_DataWrite(0x09);   
//	LCD_DataWrite(0x27);   
//	LCD_DataWrite(0x2E);   
//	LCD_DataWrite(0x34);   
//	LCD_DataWrite(0x46);   
//	LCD_DataWrite(0x37);   
//	LCD_DataWrite(0x13);   
//	LCD_DataWrite(0x13);   
//	LCD_DataWrite(0x25);   
//	LCD_DataWrite(0x2A);
//	 

//	LCD_CmdWrite(0xE1);     
//	LCD_DataWrite(0x70);   
//	LCD_DataWrite(0x04);   
//	LCD_DataWrite(0x08);   
//	LCD_DataWrite(0x09);   
//	LCD_DataWrite(0x07);   
//	LCD_DataWrite(0x03);   
//	LCD_DataWrite(0x2C);   
//	LCD_DataWrite(0x42);   
//	LCD_DataWrite(0x42);   
//	LCD_DataWrite(0x38);   
//	LCD_DataWrite(0x14);   
//	LCD_DataWrite(0x14);   
//	LCD_DataWrite(0x27);   
//	LCD_DataWrite(0x2C); 

//	LCD_CmdWrite(0x21); 

//	LCD_CmdWrite(0x11); 
//	delay_ms (120); 

//	LCD_CmdWrite(0x29);     //Display on
//*********************************************************
//************* Start Initial Sequence **********// 
//	LCD_CmdWrite(0x36); 
//	LCD_DataWrite(0x00);

//	LCD_CmdWrite(0x3A); 
//	LCD_DataWrite(0x05);

//	LCD_CmdWrite(0xB2);
//	LCD_DataWrite(0x0C);
//	LCD_DataWrite(0x0C);
//	LCD_DataWrite(0x00);
//	LCD_DataWrite(0x33);
//	LCD_DataWrite(0x33);

//	LCD_CmdWrite(0xB7); 
//	LCD_DataWrite(0x35);  

//	LCD_CmdWrite(0xBB);
//	LCD_DataWrite(0x19);

//	LCD_CmdWrite(0xC0);
//	LCD_DataWrite(0x2C);

//	LCD_CmdWrite(0xC2);
//	LCD_DataWrite(0x01);

//	LCD_CmdWrite(0xC3);
//	LCD_DataWrite(0x12);   

//	LCD_CmdWrite(0xC4);
//	LCD_DataWrite(0x20);  

//	LCD_CmdWrite(0xC6); 
//	LCD_DataWrite(0x0F);    

//	LCD_CmdWrite(0xD0); 
//	LCD_DataWrite(0xA4);
//	LCD_DataWrite(0xA1);

//	LCD_CmdWrite(0xE0);
//	LCD_DataWrite(0xD0);
//	LCD_DataWrite(0x04);
//	LCD_DataWrite(0x0D);
//	LCD_DataWrite(0x11);
//	LCD_DataWrite(0x13);
//	LCD_DataWrite(0x2B);
//	LCD_DataWrite(0x3F);
//	LCD_DataWrite(0x54);
//	LCD_DataWrite(0x4C);
//	LCD_DataWrite(0x18);
//	LCD_DataWrite(0x0D);
//	LCD_DataWrite(0x0B);
//	LCD_DataWrite(0x1F);
//	LCD_DataWrite(0x23);

//	LCD_CmdWrite(0xE1);
//	LCD_DataWrite(0xD0);
//	LCD_DataWrite(0x04);
//	LCD_DataWrite(0x0C);
//	LCD_DataWrite(0x11);
//	LCD_DataWrite(0x13);
//	LCD_DataWrite(0x2C);
//	LCD_DataWrite(0x3F);
//	LCD_DataWrite(0x44);
//	LCD_DataWrite(0x51);
//	LCD_DataWrite(0x2F);
//	LCD_DataWrite(0x1F);
//	LCD_DataWrite(0x1F);
//	LCD_DataWrite(0x20);
//	LCD_DataWrite(0x23);

//	LCD_CmdWrite(0x21); 

//	LCD_CmdWrite(0x11); 
//	//Delay (120); 

//	LCD_CmdWrite(0x29); 
}


/**********************************************
��������LCD_write_english_string
���ܣ�ѡ��Lcd��дһ��Ӣ�Ļ�����
��ڲ�����x �ַ������Ͻ������е�ˮƽλ�ã��������Ͻ�Ϊ0ֵ��
          y �ַ������Ͻ������е���ֱλ�ã��������Ͻ�Ϊ0ֵ��
          *s Ҫд���ַ���ָ��
          wordcolor �ַ�������ɫ
          backcolor �ַ����ı���ɫ
          scale ����Ĵ�С�������С��8*16����*scale��
����ֵ����
***********************************************/
void LCD_write_english_string(uint16_t x, uint16_t y, char *str,uint8_t mode)//Ӣ���ַ�����ʾ
{
 uint16_t k = 0;
  while ((*str<='~')&&(*str>=' ')) 
  {
     Lcd_SetBox(x+k,y,20,40);
     LCD_write_english( *str,WORDCOLOR,BACKCOLOR, mode);
     k+=20;
     str++;      
  }
}  

void LCD_write_chinese_string(uint16_t x, uint16_t y,uint16_t address,uint16_t len,uint8_t mode)
{
  int i;
  uint16_t k = 0;
  for(i=0;i<len;i++)
  {
     Lcd_SetBox(x+k,y,32,32);
     LCD_write_chinese(address,WORDCOLOR,BACKCOLOR, mode);
     k+=32;
     address++;
     
  }
}


void LCD_write_number_string(uint16_t x, uint16_t y,int number,uint8_t mode)
{
   uint8_t temp[6]={0},i=0,j=0,k=0;
   
   if(number >= 0)
   {
     Lcd_SetBox(x+k,y,20,40);
     LCD_write_english(32,WORDCOLOR,BACKCOLOR,mode);    
   }
   else
   {
     number = 0-number;
     Lcd_SetBox(x+k,y,20,40);
     LCD_write_english(45,WORDCOLOR,BACKCOLOR,mode);
   }
    k+=20;
   if(number != 0)
   { 
     for(i=0; i<6; i++)
     {
       temp[i]=(uint8_t)(number % 10);//��λ��ǰ����λ�ں�
       number /=10;
     } 
     i=0;
     j=5;
     while(temp[5-i] == 0)
     {
       i++;
       j--;       
     }
     for(; i<6; i++)
     {
       Lcd_SetBox(x+k,y,20,40);
       LCD_write_number(temp[5-i],WORDCOLOR,BACKCOLOR,mode);
       k+=20;
       if(i==5){
         for(; j>0;j--){
           Lcd_SetBox(x+k,y,20,40);
           LCD_write_english(32,WORDCOLOR,BACKCOLOR,mode);
           k+=20;
         }
       }
           
     }
     
   }
   else
   {
     Lcd_SetBox(x+k,y,20,40);
     LCD_write_number(0,WORDCOLOR,BACKCOLOR,mode);
   }
}

void LCD_Picture(uint16_t x,uint16_t y,uint16_t width,uint16_t height,const unsigned  char *color)
{  
	uint16_t i,j,temp;
        j=width*height;
        Lcd_SetBox(x,y,width,height);
     	
 	for(i=0;i<j;i++)
	{ 
          temp=color[i*2]<<8&0xFF00;
          temp+=color[i*2+1];
          LCD_WriteOneDot(temp);
	}	  
}
/*��������LCD_ShowPicture
 *��  �ܣ���ָ��λ����ʾ��ɫͼƬ������ʾ�ַ�ԭ��һ�£��ɸı���ɫ
 *����ֵ����
 *��  ����
*/
void LCD_ShowPicture(uint16_t x,uint16_t y,uint16_t width,uint16_t heiht,uint16_t point,uint16_t back,const unsigned char *pic,uint8_t mode)
{  							  
        uint16_t temp,t1,t;
	uint16_t x0=x,data=0;
          data=(width/8+((width%8)?1:0))*heiht;
	for(t=0;t<data;t++)
	{   	temp=pic[t]; 						
		for(t1=0;t1<8;t1++)
		{	    
			if(temp&0x80)LCD_DrawPoint(x,y,point);
			else if(mode==0)LCD_DrawPoint(x,y,back);
			temp<<=1;
			x++;
			if((x-x0)==width)
			{
				x=x0;
				y++;
				break;
			}
		}  	 
	}  	    	   	 	  
}

void LCD_Showblank(uint16_t x,uint16_t y,uint16_t width,uint16_t height,const unsigned  char *color)
{  
	u32 data;
        uint16_t
		i,j,temp;
        data=y*240+x;
        Lcd_SetBox(x,y,width,height);    	
 	for(i=0;i<height;i++)
	{ 
          for(j=0;j<width;j++){
            temp=color[data*2]<<8&0xFF00;
            temp+=color[data*2+1];
            LCD_WriteOneDot(temp); 
            data+=1;
	}	
         data+=(240-width);
     }
}
