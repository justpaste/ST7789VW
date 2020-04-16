/*****************************************
*        CS1237 designed by Robert Lee           *
*                                        *
*****************************************/
#include "cs1237.h"
#include "delay.h"


//#ifdef USER_CS1237  

#define ADC_Bit  	24 //ADC��Чλ����������λ ���24λ
#define One_CLK  	SCLout_H;delay_us(30);SCLout_L;delay_us(30);
#define CS_CON  	0X0C   //
//#define CS_CON  	0X02   //�ڲ��¶����
#define Lv_Bo 		0.01  //�˲�ϵ�� С��1

uint32_t AD_Res_Last=0;//��һ�ֵ�ADC��ֵ����

//CS1237����͹���ģʽ
void CS1237_Power_Down(void)
{
	SCLout_L;
	delay_us(10);
	SCLout_H;
	delay_us(200);
	
}
//����CS1237оƬ
void Con_CS1237(void)
{
	uint8_t i;
	uint8_t dat;
	uint16_t count_i=0;		//�����ʱ��
	uint8_t SDAInStatus=1;
	
	GPIO_InitTypeDef    GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	
	dat = CS_CON;				// 0100 1000
	SCLout_L;					//ʱ������
	//оƬ׼�����������  ʱ���Ѿ�Ϊ0������Ҳ��Ҫ��CS1237ȫ������Ϊ0���㶼׼����
	while(SDAInStatus==1)
	{
		SDAInStatus=GPIO_ReadInputDataBit(GPIOB, SDAout_Pin);
		
		delay_ms(1);
		count_i++;
		//��ʱ����ֱ���˳�����
		if(count_i > 1000)
		{
			SCLout_H;
			SDAout_H;
			printf("Config Register error\r\n");
			return;
		}
	}
	//��ȡAD
	for(i=0;i<24;i++)// 1 - 24
	{
		One_CLK;
	}
	//�� 25 ������ 26 �� SCLK ����ȡ�Ĵ���д����״̬
	One_CLK;
	One_CLK;
	//27:�� DRDY / DOUT �������
	One_CLK
	//28 ������ 29 �� SCLK ���л� DRDY / DOUT Ϊ��������
	One_CLK;
	One_CLK;	
	GPIO_InitStructure.GPIO_Pin = SDAout_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	30-36д�������üĴ���������0x65
	SCLout_H;delay_us(30);SDAout_H;SCLout_L;delay_us(30);//30
	SCLout_H;delay_us(30);SDAout_H;SCLout_L;delay_us(30);//30
	SCLout_H;delay_us(30);SDAout_L;SCLout_L;delay_us(30);//30
	SCLout_H;delay_us(30);SDAout_L;SCLout_L;delay_us(30);//30
	SCLout_H;delay_us(30);SDAout_H;SCLout_L;delay_us(30);//30
	SCLout_H;delay_us(30);SDAout_L;SCLout_L;delay_us(30);//30
	SCLout_H;delay_us(30);SDAout_H;SCLout_L;delay_us(30);//30
//	37 
//	�� �� DRDY / DOUT �� �� �� ( �� �� �� д �� �� �� ��
//	DRDY / DOUT Ϊ���룻����Ƕ��Ĵ����� DRDY / DOUT Ϊ���
	One_CLK; 
// 38 - 45�������ˣ�д8λ����
	for(i=0;i<8;i++)
	{
		SCLout_H;
		delay_us(30);
		if(dat&0x80)
			SDAout_H;
		else
			SDAout_L;
		dat <<= 1;
		SCLout_L;
		delay_us(30);
	}
	//46������������������
	One_CLK;
	//����sdaΪ��������������	
	GPIO_InitStructure.GPIO_Pin = SDAout_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
//��ȡоƬ����������
uint8_t Read_CON(void)
{
	uint8_t 	i;
	uint8_t 	dat=0;//��ȡ��������
	uint16_t 	count_i=0;//�����ʱ��
	uint8_t 	SDAInStatus=1;
	
	GPIO_InitTypeDef    GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	
	SCLout_L;//ʱ������
	
	while(SDAInStatus==1)//оƬ׼�����������  ʱ���Ѿ�Ϊ0������Ҳ��Ҫ��CS1237ȫ������Ϊ0���㶼׼����
	{
		SDAInStatus=GPIO_ReadInputDataBit(GPIOB, SDAout_Pin);
		delay_ms(1);
		count_i++;
		if(count_i > 1000)
		{
			SCLout_H;
			SDAout_H;
			printf("Read Register error\r\n");
			return 1;
		}
	}
//	1-24��ȡAD	
	for(i=0;i<24;i++)// 
	{
		One_CLK;
	}
	//�� 25 ������ 26 �� SCLK ����ȡ�Ĵ���д����״̬
	One_CLK;
	One_CLK;
	//27:�� DRDY / DOUT �������
	One_CLK
	//28 ������ 29 �� SCLK ���л� DRDY / DOUT Ϊ��������
	One_CLK;
	One_CLK;	
	GPIO_InitStructure.GPIO_Pin = SDAout_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
//	д���ȡ�Ĵ���������0x56
	SCLout_H;delay_us(30);SDAout_H;SCLout_L;delay_us(30);//30
	SCLout_H;delay_us(30);SDAout_L;SCLout_L;delay_us(30);//30
	SCLout_H;delay_us(30);SDAout_H;SCLout_L;delay_us(30);//30
	SCLout_H;delay_us(30);SDAout_L;SCLout_L;delay_us(30);//30
	SCLout_H;delay_us(30);SDAout_H;SCLout_L;delay_us(30);//30
	SCLout_H;delay_us(30);SDAout_H;SCLout_L;delay_us(30);//30
	SCLout_H;delay_us(30);SDAout_L;SCLout_L;delay_us(30);//30
//	37 
//	�� �� DRDY / DOUT �� �� �� ( �� �� �� д �� �� �� ��
//	DRDY / DOUT Ϊ���룻����Ƕ��Ĵ����� DRDY / DOUT Ϊ���
	One_CLK; 
	//����sdaΪ��������������
	GPIO_InitStructure.GPIO_Pin = SDAout_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	dat=0;
//	38-45�����壬��ȡ����
	for(i=0;i<8;i++)
	{
		One_CLK;
		dat <<= 1;
		SDAInStatus=GPIO_ReadInputDataBit(GPIOB, SDAout_Pin);
		if(SDAInStatus ==1)
		{
			dat++;
		}
	}
	//46������������������
	One_CLK;
	//����sdaΪ��������������	
	GPIO_InitStructure.GPIO_Pin = SDAout_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	return dat;
}
//��ȡADC���ݣ����ص���һ���з�������
uint32_t Read_CS1237(void)
{
	uint8_t 	i;
	int32_t 	dat=0;//��ȡ��������
	uint16_t 	count_i=0;//�����ʱ��
	uint8_t 	SDAInStatus;
	
	//����sdaΪ��������������
	GPIO_InitTypeDef    GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = SDAout_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	
	SCLout_L;//ʱ������
	while(SDAInStatus==1)//оƬ׼�����������  ʱ���Ѿ�Ϊ0������Ҳ��Ҫ��CS1237ȫ������Ϊ0���㶼׼����
	{
		SDAInStatus=GPIO_ReadInputDataBit(GPIOB, SDAout_Pin);
		delay_ms(1);
		count_i++;
		if(count_i > 1000)
		{
			SCLout_H;
			SDAout_H;
			printf("Read AD error\r\n");
			return 1;
		}
	}
//	1-24��ȡAD
	dat=0;
	for(i=0;i<24;i++)//��ȡ24λ��Чת��
	{
		One_CLK;
//		delay_us(30);
		dat <<= 1;
		SDAInStatus=GPIO_ReadInputDataBit(GPIOB, SDAout_Pin);
		if(SDAInStatus ==1)
		{
			dat++;
		}
//		delay_us(30);
	}
	//�� 25 ������ 26 �� SCLK ����ȡ�Ĵ���д����״̬
	One_CLK;
	One_CLK;
	//27:�� DRDY / DOUT �������
	One_CLK
	//28 ������ 29 �� SCLK ���л� DRDY / DOUT Ϊ��������
	One_CLK;
	One_CLK;
	for(i=0;i<22;i++)
	{
		One_CLK
	}

	//46������������������
	One_CLK;
	//����sdaΪ��������������	
	GPIO_InitStructure.GPIO_Pin = SDAout_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//�ȸ��ݺ궨���������Чλ������һЩ����
	i = 24 - ADC_Bit;//i��ʾ��Ҫ������λ��
	dat >>= i;//���������λ��
	return dat;
}
//��ʼ��ADC��ز���
void Init_CS1237(void)
{
	Con_CS1237();//����CS1237
	if(Read_CON() != CS_CON)//�����ȡ��ADC���ó���������
	{
		printf("Init_CS1237 error\r\n");
	}
	//IAP_CONTR = 0x20;
	//AD_Res_Last = Read_CS1237();
	//AD_Res_Last = Read_CS1237();
	//AD_Res_Last = Read_CS1237();
	//printf("AD_Res_Last 0x%x\r\n",AD_Res_Last);
}
//����һ���˲��� �˲�ϵ��A��С��1����һ����ֵB��������ֵC out = b*A + C*(1-A)
//��������������ȡ������ADC����
uint32_t Read_12Bit_AD(void)
{
	float out,c;

	out = AD_Res_Last;
	c = Read_CS1237();
	if(out !=0 && (out<c*0.8 || out>c*1.2))
		c = out;
	if(c!=0) // ������ȷ����
	{
		out = out*Lv_Bo + c*(1-Lv_Bo);
		AD_Res_Last = out;//����εļ������ŵ�ȫ�ֱ������汣��
	}
	//printf("AD_Res_Last 0x%x\r\n",AD_Res_Last);
	return AD_Res_Last;
}

void Cs1237IO_Init(void)
{
	GPIO_InitTypeDef    GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = SCLout_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SDAout_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}
uint32_t Code32bit_conversion(uint32_t CodeInput )
{
	int32_t CodeOutput=0;
	
	CodeOutput=~CodeInput;
	CodeOutput &= 0x00ffffff;
	CodeOutput += 1;
	if(CodeInput & 0x00800000)
	{
		CodeOutput |= 0x80000000;
	}
	CodeOutput &= 0xff7fffff;
	return CodeOutput;
}

//#endif
