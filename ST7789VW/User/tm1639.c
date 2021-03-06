#include "tm1639.h"
#include "sys.h"

////端口位操作全局变量,根据情况修改端口
//BIT16 *bitPort1639     = (BIT16*)P_IOA_Data;
//BIT16 *bitPort_Dir1639 = (BIT16*)P_IOA_Dir;
//BIT16 *bitPort_Att1639 = (BIT16*)P_IOA_Attrib;

////端口设置，根据情况修改端口位
//#define DIO          WRB0(bitPort1639)
//#define DIO_DIR      WRB0(bitPort_Dir1639)
//#define DIO_ATT      WRB0(bitPort_Att1639)

//#define CLK_out          WRB1(bitPort1639)
//#define CLK_DIR      WRB1(bitPort_Dir1639)
//#define CLK_ATT      WRB1(bitPort_Att1639)

//#define STB_out          WRB2(bitPort1639)
//#define STB_DIR      WRB2(bitPort_Dir1639)
//#define STB_ATT      WRB2(bitPort_Att1639)

//工作模式，可以进行|组合
#define MD_WRITE        0x40 //采用地址自动加一方式写显存
#define MD_AUTO         MD_WRITE
#define MD_NORMAL       MD_WRITE

#define MD_READKEY      0x42 //读按键命令
#define MD_FIX          0x44 //采用固定地址方式写显存
#define MD_TEST         0x48 //测试模式


/****************************************************************
初始IC三个端口
DIO,CLK_out,STB全部设置成不带反相器高电平输出
****************************************************************/
void TM1639_Init(void)
{
	//初始化TM1639 IO:PA5,PA6,PA7 
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	ClearAll();
	ICTest();
}


//****************************************************************
// 写入输入1个字节(8bit)到LED_IC程序开始 
//输入8BIT数据
//在时钟的上升沿通过MCU向LED驱动IC——TM16xx写数据
//----------------------------------------------------------------
void TM1639_Write_Byte(unsigned char Byte)
{
	unsigned int i;

	//DIO设为输出
	
	DIO_out_H;;

	STB_out_L;               //保证“STB”为低电平，程序不依赖于之前端口的状态
								//保证程序在实际运行中不会出现“端口迷失”
	for(i=0;i<8;i++) 
	{
		CLK_out_L;              //先将“CLK”清零
		if((Byte & 0x01)!=0)
			DIO_out_H;            //需要传送的数据的低位为“1”，则把“DIO”清零
		else
			DIO_out_L;            //需要传送的数据的低位为“0”，则把“DIO”置高
		CLK_out_H;              //送时钟的上升沿
		Byte=Byte>>1;     		//准备送下一个BIT
	}                     		//送完一个字节后退出循环
}

//****************************************************************
// 写入输入1个字节(8bit)到LED_IC程序开始 
//从LED_IC读入1个字节(8bit)程序开始 
//输出8BIT数据
//在时钟的上升沿通过MCU从LED驱动IC——TM16xx读数据
//----------------------------------------------------------------
unsigned char TM1639_Read_Byte(void)
{
	unsigned char i,Read_Byte=0;    

	//DIO设为上拉输入
//	DIO_DIR = 0;
//	DIO_ATT = 0;
	DIO_in      = 1;

	STB_out_L;                  //保证“STB”为低电平，程序不依赖于之前端口的状态
							  //保证程序在实际运行中不会出现“端口迷失”
	for(i=0;i<8;i++) 
	{
		CLK_out_L;                //先将“CLK”清零
		Read_Byte=Read_Byte>>1;
		if(DIO_in == 0) 
			Read_Byte=Read_Byte & 0x7f;   //如果“DIO”为低电平，则把out的最高位清“0”，其他各位保持不变
		else                  //如果“DIO”为高电平，则把out的最高位置“1”，其他各位保持不变
			Read_Byte=Read_Byte | 0x80; 
		CLK_out_H;                //送时钟的上升沿
	}
	return(Read_Byte);            //返回读到的1字节数据
}

//****************************************************************
//采用固定地址方式传输地址和数据开始
//采用固定地址方式
//----------------------------------------------------------------
/*
void display2(unsigned char adress,unsigned char data)
{
DIO=1;
CLK_out_H;
STB_out_H;                      //通讯开始前通讯端口全部初始化为“1”

TM1639_Write_Byte(MD_FIX);             //数据设置命令
STB_out_H;
TM1639_Write_Byte(adress);             //传显示数据对应的地址
TM1639_Write_Byte(data);               //保持“STB”=“0”，传1BYTE显示数据
STB_out_H;                      //传完显示数据后将“STB”置“1”
}
*/

/****************************************************************
连续传递数据，数据最多16byte
statAddr：起始地址
data：    连续写入数据的起始数据地址
len：     连续写入数据的长度，len*2+DIG0 < DIG7
leve：    亮度级别
注：如果len*2+DIG0地址>DIG7那么，多出来的地址返回到DIG0，如此循环。
本函数可以防止上电后马上传显示数据，会出现乱码。
****************************************************************/
void TM1639_Write_Series_Byte(unsigned char starAddr,unsigned char *Byte,unsigned char len,unsigned char level)
{
	int i;

	//通讯开始前通讯端口全部初始化为“1”
	DIO_out_H;
	CLK_out_H;
	STB_out_H;                      

	TM1639_Write_Byte(MD_AUTO);                 //传数据设置命令，设置采用地址自动加1方式写显示数据，
	STB_out_H;                          //数据设置命令传完后需要将“STB”置“1”
	TM1639_Write_Byte(starAddr);               //传起始地址

	//关键部分（数据分两次传递到两个地址里面去）
	for(i = 0;i < len;++i) 
	{
		TM1639_Write_Byte(*Byte & 0x0f);         //低地址
		TM1639_Write_Byte(*Byte >> 4 & 0x0f);    //高地址
		++Byte;
	}

	STB_out_H;                      //传完所有的显示数据后（最多14BYTE）后，将“STB置“1”
	TM1639_Write_Byte(level);
	STB_out_H;                      //显示控制命令传完后将“STB”置“1”
}

/****************************************************************
连续一位数码管数据
statAddr：起始地址
data：    连续写入数据的起始数据地址
leve：    亮度级别
注：本质上这个函数也是使用连续模式写入的，非连续模式我写不进去。
这个函数可以防止由于使用SeriesInData函数导致写入长度越界
****************************************************************/
void TM1639_Write_One_Byte(unsigned char starAddr,unsigned char Byte,unsigned char level)
{
	DIO_out_H;
	CLK_out_H;
	STB_out_H;                      //通讯开始前通讯端口全部初始化为“1”

	TM1639_Write_Byte(MD_AUTO);            //传数据设置命令，设置采用地址自动加1方式写显示数据，
	STB_out_H;                      //数据设置命令传完后需要将“STB”置“1”
	TM1639_Write_Byte(starAddr);           //传起始地址

	//关键部分（数据分两次传递到两个地址里面去）
	TM1639_Write_Byte(Byte & 0x0f);       //低地址
	TM1639_Write_Byte(Byte >> 4 & 0x0f); //高地址

	STB_out_H;                      //传完所有的显示数据后（最多14BYTE）后，将“STB置“1”
	TM1639_Write_Byte(level);
	STB_out_H;                      //显示控制命令传完后将“STB”置“1
}

/****************************************************************
清除所有数据
从第一位数码管(地址DIG0)开始连续清除8位数码管数据，并且关闭显示。
调用情况1：
由于上点过程中数码管显示的数据是随机的，可以先调用此函数对数码管清屏。
调用情况2：
如果系统运行过程当中显示的位数不一定（有时显示3位有时显示5位），
那么当从高位切换到低位的时候需要对多余的几位进行清显操作，
可一直接调用此ClearAll函数，也可以调用OneByteInData函数逐位写0清显
****************************************************************/
void ClearAll(void)
{
	unsigned int i;             //i——控制本次需要传多少个字节显示数据
		
	//通讯开始前通讯端口全部初始化为“1”
	DIO_out_H;
	CLK_out_H;
	STB_out_H;                      

	TM1639_Write_Byte(MD_AUTO);            //传数据设置命令，设置采用地址自动加1方式写显示数据，
	STB_out_H;                      //数据设置命令传完后需要将“STB”置“1”
	TM1639_Write_Byte(DIG0);               //传起始地址
								  //地址命令传完后，“STB”保持为“0”继续传需要显示的数据
	for(i=0;i<16;i++)           //datacount=2*grid=2*5=10???
		  TM1639_Write_Byte(0);              //在连续传显示的数据过程中，“STB”一直保持为”0“
		  
	STB_out_H;                      //传完所有的显示数据后（最多14BYTE）后，将“STB置“1”
	TM1639_Write_Byte(0x80);               //传显示控制命令
	STB_out_H;                      //显示控制命令传完后将“STB”置“1
}

/****************************************************************
按键扫描程序
key:存储按键按下的信息int形数据，最多一次可以得到两个按键按下的结果
key1或key2：4、8、64、128，每个变量可以指示4个按键按下，key1或key2里面允许组合两个按键，
****************************************************************/

void KeyRead(int *key)
{
	unsigned char key1,key2;
	STB_out_H;

	TM1639_Write_Byte(MD_READKEY);         //传数据设置命令，设置为读按键    
								  //“STB”保持为“0”，读键值
	key1 = TM1639_Read_Byte();
	key2 = TM1639_Read_Byte();
	*key = key1 | (key2 << 8);

	STB_out_H;                      //读键结束将“STB”置“1”
//	*P_IOA_Dir = 0xffff;
}

/****************************************************************
测试模式，内部使用，检验硬件完整性
****************************************************************/
void ICTest(void)
{
	STB_out_H;
	TM1639_Write_Byte(MD_TEST);
	STB_out_H;
	TM1639_Write_Byte(0x8c); 
	STB_out_H;
}
