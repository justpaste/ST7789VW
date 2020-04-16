#ifndef __CS1237_H__
#define __CS1237_H__

#include "stdio.h"
#include "sys.h"

#define SCLout_H GPIO_WriteBit(GPIOB,SCLout_Pin,(BitAction)(0x01))
#define SDAout_H GPIO_WriteBit(GPIOB,SDAout_Pin,(BitAction)(0x01))

#define SCLout_L GPIO_WriteBit(GPIOB,SCLout_Pin,(BitAction)(0x00))
#define SDAout_L GPIO_WriteBit(GPIOB,SDAout_Pin,(BitAction)(0x00))

#define SCLout_Pin GPIO_Pin_11
#define SDAout_Pin GPIO_Pin_10


//����CS1237оƬ
void Con_CS1237(void);
//��ȡоƬ����������
unsigned char Read_CON(void);
//��ȡADC����
uint32_t Read_CS1237(void);
//��ʼ��ADC��ز���
void Init_CS1237(void);
//��������������ȡ������ADC����
uint32_t Read_18Bit_AD(void);
//CS1237����͹���ģʽ
void CS1237_Power_Down(void);
//����IO
void Cs1237IO_Init(void);

uint32_t Read_12Bit_AD(void);
//������ԭ��ת��
uint32_t Code32bit_conversion(uint32_t CodeInput );


#endif
