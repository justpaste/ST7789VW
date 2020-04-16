#include "sys.h"
#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"  	 
#include "delay.h"
#include "bmp.h"
#include "usart1.h"



uint16_t BACK_COLOR, POINT_COLOR;   //����ɫ������ɫ

uint8_t ref=0;//ˢ����ʾ
uint16_t vx=15542,vy=11165;  //�������ӣ���ֵ����1000֮���ʾ���ٸ�ADֵ����һ�����ص�
uint16_t chx=140,chy=146;//Ĭ�����ص�����Ϊ0ʱ��AD��ʼֵ


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
//	LCD_CSL;        
//	LCD_RDH;
//	SSD1331_Send_Byte(cmd);
	num=cmd;  
	num |=((GPIOB->ODR)&0xFF00);
	(GPIOB->ODR) =num;
	LCD_WRL;
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
//	LCD_CSL; 
//	LCD_RDH; 
//	SSD1331_Send_Byte(data);	
	num=data;  
	num |=((GPIOB->ODR)&0xFF00);
	(GPIOB->ODR) =num;
	LCD_WRL;
	LCD_WRH;    
//	LCD_CSH;
}

void LCD_Data16Write(uint16_t data)		
{
	uint16_t num=0;   
	LCD_RSH; 
//	LCD_CSL; 
//	LCD_RDH; 
//	SSD1331_Send_Byte(data);	
	num=(data&0x00ff);  
	num |=((GPIOB->ODR)&0xFF00);
	(GPIOB->ODR) =num;
	LCD_WRL;
	LCD_WRH;    
//	LCD_CSH;
	
	LCD_RSH; 
//	LCD_CSL; 
//	LCD_RDH; 
//	SSD1331_Send_Byte(data);	
	num=data>>8;  
	num |=((GPIOB->ODR)&0xFF00);
	(GPIOB->ODR) =num;
	LCD_WRL;
	LCD_WRH;    
//	LCD_CSH;
}
/*/////////////////////////////////////////////////////////
void LCD_Writ_Bus(char dat)   //��������д��
{	
	uint8_t i;			  
  

	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();
		if(dat&0x80)
		   OLED_SDIN_Set();
		else 
		   OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat<<=1;   
	}			
}

void LCD_DataWrite8(char da) //��������-8λ����
{	//OLED_CS_Clr();
    OLED_DC_Set();
	LCD_Writ_Bus(da);  
	//OLED_CS_Set();
}  
 void LCD_Data16Write(int da)
{//	OLED_CS_Clr();
    OLED_DC_Set();
	LCD_Writ_Bus(da>>8);
    LCD_Writ_Bus(da);
	//OLED_CS_Set();
}	  
void LCD_CmdWrite(char da)	 
{	//	OLED_CS_Clr();
    OLED_DC_Clr();
	LCD_Writ_Bus(da);
	//OLED_CS_Set();
}
 void LCD_CmdWrite_DATA(int reg,int da)
{	//OLED_CS_Clr();
    LCD_CmdWrite(reg);
	LCD_Data16Write(da);
	//OLED_CS_Set();
}

*//////////////////////////////////////////////////////////

void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{ 
	LCD_CmdWrite(0x2a);
	LCD_DataWrite(x1>>8);
	LCD_DataWrite(x1);
	LCD_DataWrite(x2>>8);
	LCD_DataWrite(x2);

	LCD_CmdWrite(0x2b);
	LCD_DataWrite(y1>>8);
	LCD_DataWrite(y1);
	LCD_DataWrite(y2>>8);
	LCD_DataWrite(y2);

	LCD_CmdWrite(0x2C);					 						 
}

void Lcd_Init(void)
{
	St7789v_IOInit();
	LCD_Reset();
	
	//************* Start Initial Sequence **********// 
	LCD_CmdWrite(0x36); 
	LCD_DataWrite(0x00);

	LCD_CmdWrite(0x3A); 
	LCD_DataWrite(0x05);

	LCD_CmdWrite(0xB2);
	LCD_DataWrite(0x0C);
	LCD_DataWrite(0x0C);
	LCD_DataWrite(0x00);
	LCD_DataWrite(0x33);
	LCD_DataWrite(0x33);

	LCD_CmdWrite(0xB7); 
	LCD_DataWrite(0x35);  

	LCD_CmdWrite(0xBB);
	LCD_DataWrite(0x19);

	LCD_CmdWrite(0xC0);
	LCD_DataWrite(0x2C);

	LCD_CmdWrite(0xC2);
	LCD_DataWrite(0x01);

	LCD_CmdWrite(0xC3);
	LCD_DataWrite(0x12);   

	LCD_CmdWrite(0xC4);
	LCD_DataWrite(0x20);  

	LCD_CmdWrite(0xC6); 
	LCD_DataWrite(0x0F);    

	LCD_CmdWrite(0xD0); 
	LCD_DataWrite(0xA4);
	LCD_DataWrite(0xA1);

	LCD_CmdWrite(0xE0);
	LCD_DataWrite(0xD0);
	LCD_DataWrite(0x04);
	LCD_DataWrite(0x0D);
	LCD_DataWrite(0x11);
	LCD_DataWrite(0x13);
	LCD_DataWrite(0x2B);
	LCD_DataWrite(0x3F);
	LCD_DataWrite(0x54);
	LCD_DataWrite(0x4C);
	LCD_DataWrite(0x18);
	LCD_DataWrite(0x0D);
	LCD_DataWrite(0x0B);
	LCD_DataWrite(0x1F);
	LCD_DataWrite(0x23);

	LCD_CmdWrite(0xE1);
	LCD_DataWrite(0xD0);
	LCD_DataWrite(0x04);
	LCD_DataWrite(0x0C);
	LCD_DataWrite(0x11);
	LCD_DataWrite(0x13);
	LCD_DataWrite(0x2C);
	LCD_DataWrite(0x3F);
	LCD_DataWrite(0x44);
	LCD_DataWrite(0x51);
	LCD_DataWrite(0x2F);
	LCD_DataWrite(0x1F);
	LCD_DataWrite(0x1F);
	LCD_DataWrite(0x20);
	LCD_DataWrite(0x23);

	LCD_CmdWrite(0x21); 

	LCD_CmdWrite(0x11); 
	//Delay (120); 

	LCD_CmdWrite(0x29);
	
} 


/*LCD_Clear
 *��  �ܣ�����
 *����ֵ����
 *��  ����uint16_t Color ��������ɫ
 */
void LCD_Clear(uint16_t Color)
{
	uint16_t i,j;  	
	Address_set(0,0,LCD_W-1,LCD_H-1);
    for(i=0;i<LCD_W;i++)
	 {
	  for (j=0;j<LCD_H;j++)
	   	{
        	LCD_Data16Write(Color);	 			 
	    }

	  }
}

/*LCD_Clearpart
 *��  �ܣ�ָ����������
 *����ֵ����
 *��  ����x1,y1,x2,y2;ָ������;Color ��������ɫ
 */

void LCD_Clearpart(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint16_t Color)
{
	uint16_t i,j;  	
	Address_set(x1,y1,x2-1,y2-1);
	for(i=0;i<x2;i++)
	{
		for (j=0;j<y2;j++)
		{
			LCD_Data16Write(Color);	 			 
		}
	}
}

/*ShowChinese
 *��  �ܣ�ָ����������
 *����ֵ����
 *��  ����x,y��ʾ��ʼλ��;w,h��ʾ���ֵĿ�ȸ߶�;index �����������
 */

void ShowChinese(uint16_t x,uint16_t y,uint8_t w,uint8_t h,uint8_t index)	
{  
	uint8_t t;
	uint8_t x0=x;
	uint8_t temp;
	uint16_t pos;
	uint16_t posnum =(w/8+(w%8?1:0))*h;
	uint16_t colortemp=POINT_COLOR;
    Address_set(x,y,x+w-1,y+h-1); //�������� 
	printf("index=%d\n",index);
	for(pos=0;pos<posnum;pos++)
	{ 
		
		temp=Chinese32[(uint32_t)index*posnum+pos];
		for(t=0;t<8;t++)
		{                 
			if(temp&0x01)POINT_COLOR=colortemp;
			else POINT_COLOR=BACK_COLOR;
			LCD_Data16Write(POINT_COLOR);	
			temp>>=1; 
			x++;
		}
		x=x0;
		y++;
	}
	POINT_COLOR=colortemp;	    	
}

void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t Size,const uint8_t *Charasc,uint8_t mode)
{
    uint8_t temp;
    uint8_t t;
    uint16_t pos;
    uint16_t posnum=(Size*Size/2)/8;
	uint16_t x0=x;
	uint16_t x1=0;
	uint16_t y1=0;
	uint16_t colortemp=POINT_COLOR;
    if(x>LCD_W-(Size/2)||y>LCD_H-Size)return;	    
	//���ô���		   
//	num=num-' ';//�õ�ƫ�ƺ��ֵ
	Address_set(x,y,x+Size/2-1,y+Size-1);      //���ù��λ�� 
	if(!mode) //�ǵ��ӷ�ʽ
	{
		for(pos=0;pos<posnum;pos++)
		{ 
			temp=Charasc[(uint32_t)num*posnum+pos];
			for(t=0;t<8;t++)
			{                 
				if(temp&0x01)POINT_COLOR=colortemp;
				else POINT_COLOR=BACK_COLOR;
				LCD_Data16Write(POINT_COLOR);	
				temp>>=1; 
				x++;
			}
			x=x0;
			y++;
		}	
	}
	else//���ӷ�ʽ
	{
		for(pos=0;pos<posnum;pos++)
		{
		    temp=Charasc[(uint32_t)num*posnum+pos];		 //����1608����
			for(t=0;t<8;t++)
		    {                 
		        if(temp&0x01)LCD_DrawPoint(x+x1,y+y1);//��һ���� 
				x1++;		
				if(x1>(Size/2-1))
				{
					x1=0;
					y1++;
				}
		        temp>>=1; 
		    }
		}
	}
	POINT_COLOR=colortemp;	    	   	 	  
} 

void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t Size,const uint8_t *Charasc,uint8_t len,uint8_t mode)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;
	num=(uint16_t)num;
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+Size/2*t,y,' ',Size,Charasc32,mode);
				continue;
			}else enshow=1; 
		 	 
		}
		LCD_ShowChar(x+Size/2*t,y,temp,Size,Charasc,mode);
	}
} 
/*mypow
 *��  �ܣ�m^n����
 *����ֵ����
 *��  ����m^n
 */
uint32_t mypow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}	

/*LCD_DrawPoint
 *��  �ܣ�ָ��λ�û���
 *����ֵ����
 *��  ����x,y����λ��;
 */
void LCD_DrawPoint(uint16_t x,uint16_t y)
{
	Address_set(x,y,x,y);//���ù��λ�� 
	LCD_Data16Write(POINT_COLOR); 	    
} 	 
/*LCD_DrawPoint_big
 *��  �ܣ�ָ��λ�û����
 *����ֵ����
 *��  ����x,y����λ��;
 */
void LCD_DrawPoint_big(uint16_t x,uint16_t y)
{
	LCD_Fill(x-5,y-5,x+5,y+5,POINT_COLOR);
}
/*LCD_Fill
 *��  �ܣ�ָ�����������ɫ
 *����ֵ����
 *��  ����xsta,ysta��xend��yendָ������color��ָ����ɫ
 */

void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color)
{          
	uint16_t i,j; 
	Address_set(xsta,ysta,xend,yend);      //���ù��λ�� 
	for(i=ysta;i<=yend;i++)
	{													   	 	
		for(j=xsta;j<=xend;j++)
		LCD_Data16Write(color);//���ù��λ�� 	    
	} 					  	    
}  

/*LCD_DrawLine
 *��  �ܣ�ָ��������
 *����ֵ����
 *��  ����x1,y1,x2,y2���������յ�
 */

void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		LCD_DrawPoint(uRow,uCol);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 

/*LCD_DrawRectangle
 *��  �ܣ�ָ�����򻭾���
 *����ֵ����
 *��  ����x1,y1,x2,y2���������յ�
 */
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}

/*Draw_Circle
 *��  �ܣ�ָ��λ�û�ָ����С��Բ
 *����ֵ����
 *��  ����x0,y0ָ��Բ����λ�ã�Բ�뾶
 */
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		LCD_DrawPoint(x0-b,y0-a);             //3           
		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0-a,y0+b);             //1       
		LCD_DrawPoint(x0-b,y0-a);             //7           
		LCD_DrawPoint(x0-a,y0-b);             //2             
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0-b);             //5
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-b,y0+a);             
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 
		LCD_DrawPoint(x0+a,y0+b);
	}
} 

void St7789v_IOInit(void)
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
	
	
	GPIO_InitStructure.GPIO_Pin = D0_Pin|D1_Pin|D2_Pin|D3_Pin|D4_Pin|D5_Pin|D6_Pin|D7_Pin ;  				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,D0_Pin|D1_Pin|D2_Pin|D3_Pin|D4_Pin|D5_Pin|D6_Pin|D7_Pin);
}

/*��������LCD_Reset
 *��  �ܣ���λTFT��
 *��  ������
 *����ֵ����
 */
void LCD_Reset(void)
{
  //************* Reset LCD Driver ****************// 
    LCD_RSTH;    
    delay_ms(1);  			
    LCD_RSTL;  
    delay_ms(10); 			//This delay time is necessary 
    LCD_RSTH;    
    delay_ms(120); 			
}

void showimage(void) //��ʾ40*40ͼƬ
{
  	int i,j,k; 
	//k:��ʾ�У�j��ʾ��

	for(k=2;k<6;k++)
	{
	   	for(j=0;j<6;j++)
		{	
			Address_set(40*j,40*k,40*j+39,40*k+39);		//��������
			Address_set(40,40,40+39,40+39);		//��������
		    for(i=0;i<1600;i++)
			 { 	
				 		
			  	 LCD_DataWrite(image[i*2+1]);	 
				 LCD_DataWrite(image[i*2]);				
			 }	
		 }
	}
	ref=0;				
}
void ShowClourImage(uint16_t x,uint16_t y,uint8_t l,uint8_t h,const uint8_t *Charasc) 
{
	uint16_t i; 
	uint16_t charnum=l*h*2;
	Address_set(x,y,x+l-1,y+h-1);		
	for(i=0;i<charnum/2;i++)
	{ 	
		 LCD_DataWrite(Charasc[i*2+1]);	 
		 LCD_DataWrite(Charasc[i*2]);				
	}	
	ref=0;				
}



void ShowImage(uint16_t x,uint16_t y,uint8_t l,uint8_t h,const uint8_t *Charasc)
{
    uint8_t temp;
    uint8_t t;
    uint16_t pos;
	uint16_t x0=x;
	uint16_t colortemp=POINT_COLOR;
	uint16_t charnum=(h/8+(h%8?1:0))*l;
    
	//���ô���		   
	Address_set(x,y,x+l-1,y+h-1);      //���ù��λ�� 
	for(pos=0;pos<charnum;pos++)
	{ 
		temp=Charasc[pos];		 //
		for(t=0;t<8;t++)
		{                 
			if(temp&0x01)POINT_COLOR=colortemp;
			else POINT_COLOR=BACK_COLOR;
			LCD_Data16Write(POINT_COLOR);	
			temp>>=1; 
			x++;
			if(x-x0==l)
			{
				x=x0;
				y++;
				break;
			}
		}
	}
	POINT_COLOR=colortemp;	
}































