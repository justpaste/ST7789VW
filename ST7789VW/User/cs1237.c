/*****************************************
*        CS1237 designed by Robert Lee           *
*                                        *
*****************************************/
#include "cs1237.h"
#include "delay.h"


//#ifdef USER_CS1237  

#define ADC_Bit  	24 //ADC有效位数，带符号位 最高24位
#define One_CLK  	SCLout_H;delay_us(30);SCLout_L;delay_us(30);
#define CS_CON  	0X0C   //
//#define CS_CON  	0X02   //内部温度输出
#define Lv_Bo 		0.01  //滤波系数 小于1

uint32_t AD_Res_Last=0;//上一轮的ADC数值保存

//CS1237进入低功耗模式
void CS1237_Power_Down(void)
{
	SCLout_L;
	delay_us(10);
	SCLout_H;
	delay_us(200);
	
}
//配置CS1237芯片
void Con_CS1237(void)
{
	uint8_t i;
	uint8_t dat;
	uint16_t count_i=0;		//溢出计时器
	uint8_t SDAInStatus=1;
	
	GPIO_InitTypeDef    GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	
	dat = CS_CON;				// 0100 1000
	SCLout_L;					//时钟拉低
	//芯片准备好数据输出  时钟已经为0，数据也需要等CS1237全部拉低为0才算都准备好
	while(SDAInStatus==1)
	{
		SDAInStatus=GPIO_ReadInputDataBit(GPIOB, SDAout_Pin);
		
		delay_ms(1);
		count_i++;
		//超时，则直接退出程序
		if(count_i > 1000)
		{
			SCLout_H;
			SDAout_H;
			printf("Config Register error\r\n");
			return;
		}
	}
	//读取AD
	for(i=0;i<24;i++)// 1 - 24
	{
		One_CLK;
	}
	//第 25 个到第 26 个 SCLK ，读取寄存器写操作状态
	One_CLK;
	One_CLK;
	//27:把 DRDY / DOUT 输出拉高
	One_CLK
	//28 个到第 29 个 SCLK ，切换 DRDY / DOUT 为输入或输出
	One_CLK;
	One_CLK;	
	GPIO_InitStructure.GPIO_Pin = SDAout_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	30-36写入了配置寄存器命令字0x65
	SCLout_H;delay_us(30);SDAout_H;SCLout_L;delay_us(30);//30
	SCLout_H;delay_us(30);SDAout_H;SCLout_L;delay_us(30);//30
	SCLout_H;delay_us(30);SDAout_L;SCLout_L;delay_us(30);//30
	SCLout_H;delay_us(30);SDAout_L;SCLout_L;delay_us(30);//30
	SCLout_H;delay_us(30);SDAout_H;SCLout_L;delay_us(30);//30
	SCLout_H;delay_us(30);SDAout_L;SCLout_L;delay_us(30);//30
	SCLout_H;delay_us(30);SDAout_H;SCLout_L;delay_us(30);//30
//	37 
//	切 换 DRDY / DOUT 的 方 向 ( 如 果 是 写 寄 存 器 ，
//	DRDY / DOUT 为输入；如果是读寄存器， DRDY / DOUT 为输出
	One_CLK; 
// 38 - 45个脉冲了，写8位数据
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
	//46个脉冲拉高数据引脚
	One_CLK;
	//配置sda为输入且上拉输入	
	GPIO_InitStructure.GPIO_Pin = SDAout_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
//读取芯片的配置数据
uint8_t Read_CON(void)
{
	uint8_t 	i;
	uint8_t 	dat=0;//读取到的数据
	uint16_t 	count_i=0;//溢出计时器
	uint8_t 	SDAInStatus=1;
	
	GPIO_InitTypeDef    GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	
	SCLout_L;//时钟拉低
	
	while(SDAInStatus==1)//芯片准备好数据输出  时钟已经为0，数据也需要等CS1237全部拉低为0才算都准备好
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
//	1-24读取AD	
	for(i=0;i<24;i++)// 
	{
		One_CLK;
	}
	//第 25 个到第 26 个 SCLK ，读取寄存器写操作状态
	One_CLK;
	One_CLK;
	//27:把 DRDY / DOUT 输出拉高
	One_CLK
	//28 个到第 29 个 SCLK ，切换 DRDY / DOUT 为输入或输出
	One_CLK;
	One_CLK;	
	GPIO_InitStructure.GPIO_Pin = SDAout_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
//	写入读取寄存器命令字0x56
	SCLout_H;delay_us(30);SDAout_H;SCLout_L;delay_us(30);//30
	SCLout_H;delay_us(30);SDAout_L;SCLout_L;delay_us(30);//30
	SCLout_H;delay_us(30);SDAout_H;SCLout_L;delay_us(30);//30
	SCLout_H;delay_us(30);SDAout_L;SCLout_L;delay_us(30);//30
	SCLout_H;delay_us(30);SDAout_H;SCLout_L;delay_us(30);//30
	SCLout_H;delay_us(30);SDAout_H;SCLout_L;delay_us(30);//30
	SCLout_H;delay_us(30);SDAout_L;SCLout_L;delay_us(30);//30
//	37 
//	切 换 DRDY / DOUT 的 方 向 ( 如 果 是 写 寄 存 器 ，
//	DRDY / DOUT 为输入；如果是读寄存器， DRDY / DOUT 为输出
	One_CLK; 
	//配置sda为输入且上拉输入
	GPIO_InitStructure.GPIO_Pin = SDAout_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	dat=0;
//	38-45个脉冲，读取数据
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
	//46个脉冲拉高数据引脚
	One_CLK;
	//配置sda为输入且上拉输入	
	GPIO_InitStructure.GPIO_Pin = SDAout_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	return dat;
}
//读取ADC数据，返回的是一个有符号数据
uint32_t Read_CS1237(void)
{
	uint8_t 	i;
	int32_t 	dat=0;//读取到的数据
	uint16_t 	count_i=0;//溢出计时器
	uint8_t 	SDAInStatus;
	
	//配置sda为输入且上拉输入
	GPIO_InitTypeDef    GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = SDAout_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	
	SCLout_L;//时钟拉低
	while(SDAInStatus==1)//芯片准备好数据输出  时钟已经为0，数据也需要等CS1237全部拉低为0才算都准备好
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
//	1-24读取AD
	dat=0;
	for(i=0;i<24;i++)//获取24位有效转换
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
	//第 25 个到第 26 个 SCLK ，读取寄存器写操作状态
	One_CLK;
	One_CLK;
	//27:把 DRDY / DOUT 输出拉高
	One_CLK
	//28 个到第 29 个 SCLK ，切换 DRDY / DOUT 为输入或输出
	One_CLK;
	One_CLK;
	for(i=0;i<22;i++)
	{
		One_CLK
	}

	//46个脉冲拉高数据引脚
	One_CLK;
	//配置sda为输入且上拉输入	
	GPIO_InitStructure.GPIO_Pin = SDAout_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//先根据宏定义里面的有效位，丢弃一些数据
	i = 24 - ADC_Bit;//i表示将要丢弃的位数
	dat >>= i;//丢弃多余的位数
	return dat;
}
//初始化ADC相关参数
void Init_CS1237(void)
{
	Con_CS1237();//配置CS1237
	if(Read_CON() != CS_CON)//如果读取的ADC配置出错，则重启
	{
		printf("Init_CS1237 error\r\n");
	}
	//IAP_CONTR = 0x20;
	//AD_Res_Last = Read_CS1237();
	//AD_Res_Last = Read_CS1237();
	//AD_Res_Last = Read_CS1237();
	//printf("AD_Res_Last 0x%x\r\n",AD_Res_Last);
}
//数字一阶滤波器 滤波系数A，小于1。上一次数值B，本次数值C out = b*A + C*(1-A)
//下面这个程序负责读取出最终ADC数据
uint32_t Read_12Bit_AD(void)
{
	float out,c;

	out = AD_Res_Last;
	c = Read_CS1237();
	if(out !=0 && (out<c*0.8 || out>c*1.2))
		c = out;
	if(c!=0) // 读到正确数据
	{
		out = out*Lv_Bo + c*(1-Lv_Bo);
		AD_Res_Last = out;//把这次的计算结果放到全局变量里面保护
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
