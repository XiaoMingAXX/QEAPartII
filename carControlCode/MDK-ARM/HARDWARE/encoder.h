#ifndef __ENCODER_H
#define __ENCODER_H
#include <sys.h>	 
#include "system.h"

// No larger than 65535, because the timer of STM32F103 is 16 bit
//���ɴ���65535����ΪSTM32F103�Ķ�ʱ����16λ��
#define ENCODER_TIM_PERIOD (u16)(65535)   


int Read_Encoder(u8 TIMX);

#endif
