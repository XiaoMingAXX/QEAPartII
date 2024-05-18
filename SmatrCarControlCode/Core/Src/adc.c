/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.c
  * @brief   This file provides code for the configuration
  *          of the ADC instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "adc.h"
#include "main.h"

/* USER CODE BEGIN 0 */
float Voltage,Voltage_Count,Voltage_All; //Variables related to battery voltage sampling //��ص�ѹ������صı���  
const float Revise=1.03;

//CCD��ر���
u16 CCD_Median,CCD_Threshold,ADV[128]={0}; 

//���Ѳ����ر���																										
int Sensor_Left,Sensor_Middle,Sensor_Right,Sensor,sum; 
/* USER CODE END 0 */

ADC_HandleTypeDef hadc1;

/* ADC1 init function */
void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_8;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */
  HAL_ADC_Start(&hadc1);//����adcУ׼
  /* USER CODE END ADC1_Init 2 */

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* ADC1 clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();

//    __HAL_RCC_GPIOA_CLK_ENABLE();
//    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PA4     ------> ADC1_IN4
    PA5     ------> ADC1_IN5
    PC4     ------> ADC1_IN14
    PB0     ------> ADC1_IN8
    PB1     ------> ADC1_IN9
    */
//    GPIO_InitStruct.Pin = GPIO_PIN_4;
//    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//		
//		GPIO_InitStruct.Pin = GPIO_PIN_5;
//    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

//    GPIO_InitStruct.Pin = GPIO_PIN_4;
//    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* ADC1 interrupt Init */
//    HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
//    HAL_NVIC_EnableIRQ(ADC_IRQn);
  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PA4     ------> ADC1_IN4
    PA5     ------> ADC1_IN5
    PC4     ------> ADC1_IN14
    PB0     ------> ADC1_IN8
    PB1     ------> ADC1_IN9
    */
//    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4|GPIO_PIN_5);

//    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_4);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_0|GPIO_PIN_1);

    /* ADC1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(ADC_IRQn);
  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
u16 Get_Adc(u8 ch)   
{
	u16 result;
	ADC_ChannelConfTypeDef sConfig;//ͨ����ʼ��
	sConfig.Channel=ch;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;		//��������239.5����
	sConfig.Rank = 1;
	HAL_ADC_ConfigChannel(&hadc1,&sConfig);		
	
	HAL_ADC_Start(&hadc1);								//����ת��
	HAL_ADC_PollForConversion(&hadc1,30);				//�ȴ�ת������
	if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC))
	{
		result=HAL_ADC_GetValue(&hadc1);	//�������һ��ADC1�������ת�����
	}
	return result;	
}

/**************************************************************************
Function: Collect multiple ADC values to calculate the average function
Input   : ADC channels and collection times
Output  : AD conversion results
�������ܣ��ɼ����ADCֵ��ƽ��ֵ����
��ڲ�����ADCͨ���Ͳɼ�����
�� �� ֵ��ADת�����
**************************************************************************/
u16 Get_adc_Average(u8 chn, u8 times)
{
  u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(chn);
		delay_ms(5);
	}
	return temp_val/times;
}

/**************************************************************************
Function: Read the battery voltage
Input   : none
Output  : Battery voltage in mV
�������ܣ���ȡ��ص�ѹ 
��ڲ�������
����  ֵ����ص�ѹ����λmv
**************************************************************************/
float Get_battery_volt(void)   
{  
		int Volt;
//    HAL_ADC_Start(&hadc1);                                //����ADC
//    HAL_ADC_PollForConversion(&hadc1,10);                 //��ѯת��
	  Volt = Get_Adc(8)*3.3*11*1.03/4096;	//�����ѹ���������ԭ��ͼ�򵥷������Եõ�	
	  return Volt;	                                      	//�������һ��ADC1�������ת�����
}


/**************************************************************************
Function: CCD_ADC_Mode_Config
Input   : none
Output  : none
�������ܣ���ʼ��CCDѲ��ADC
��ڲ���: ��
����  ֵ����
**************************************************************************/	 	
void CCD_ADC_Mode_Config(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = 4;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */
  HAL_ADC_Start(&hadc1);								//����ת��

}

/**************************************************************************
Function: CCD_GPIO_Config
Input   : none
Output  : none
�������ܣ���ʼ��CCDѲ��GPIO
��ڲ���: ��
����  ֵ����
**************************************************************************/	 	
void CCD_GPIO_Config(void)
{
	 GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	// __HAL_RCC_ADC1_CLK_ENABLE();
	// ��CCD�˿�ʱ��
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	// CLK,SI����Ϊ���	
	  GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		
		GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);		
	
//	  HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4|GPIO_PIN_5);

//    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_4);
//	
}

/**************************************************************************
Function: CCD_Init
Input   : none
Output  : none
�������ܣ���ʼ��CCDѲ��
��ڲ���: ��
����  ֵ����
**************************************************************************/	 	
void CCD_Init(void)
{
	CCD_GPIO_Config();
	CCD_ADC_Mode_Config();

}


/**************************************************************************
Function: ELE_ADC_Mode_Config
Input   : none
Output  : none
�������ܣ���ʼ�����Ѳ��ADC
��ڲ���: ��
����  ֵ����
**************************************************************************/	 	

void ELE_ADC_Mode_Config(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = 4;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	
	sConfig.Channel = 5;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	
	sConfig.Channel = 14;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */
  HAL_ADC_Start(&hadc1);								//����ת��
}


void ELE_GPIO_Config(void)
{
		GPIO_InitTypeDef GPIO_InitStruct = {0};
		
		//__HAL_RCC_ADC1_CLK_ENABLE();
		// ��CCD�˿�ʱ��
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();
		
	  GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		
		GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

//    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4|GPIO_PIN_5);

//    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_4);

}

/**************************************************************************
Function: ELE_ADC_Init
Input   : none
Output  : none
�������ܣ���ʼ�����Ѳ��ADC
��ڲ���: ��
����  ֵ����
**************************************************************************/	 	
//���Ѳ�߳�ʼ��
void ELE_ADC_Init(void)
{
	ELE_GPIO_Config();
	//ELE_ADC_Mode_Config();
}

/**************************************************************************
�������ܣ���ʱ
��ڲ�������
����  ֵ����
**************************************************************************/
void Dly_us(void)
{
   int ii;    
   for(ii=0;ii<30;ii++); 
}
/**************************************************************************
�������ܣ�CCD���ݲɼ�
��ڲ�������
����  ֵ����
**************************************************************************/
 void RD_TSL(void) 
{
  u8 i=0,tslp=0;
  TSL_CLK=0;
  TSL_SI=0; 
  Dly_us();
      
  TSL_SI=1;
  Dly_us();	
	
  TSL_CLK=0;
  Dly_us();
	
      
  TSL_CLK=1;
	Dly_us(); 
	
  TSL_SI=0;
  Dly_us();
  for(i=0;i<128;i++)
  { 
    TSL_CLK=0; 
    Dly_us();  //�����ع�ʱ��

    ADV[tslp]=(Get_Adc(4))>>4;
    ++tslp;
    TSL_CLK=1;
     Dly_us();

  }  
}
/**************************************************************************
�������ܣ�����CCDȡ��ֵ
��ڲ�������
����  ֵ����
**************************************************************************/
void  Find_CCD_Median (void)
{ 
	 static u16 i,j,Left,Right,Last_CCD_Median;
	 static u16 value1_max,value1_min;
	 //��ֵ˵����CCD�ɼ�������128�����ݣ�ÿ�����ݵ�������ֵ���бȽϣ�����ֵ��Ϊ��ɫ������ֵСΪ��ɫ
	 //��̬��ֵ�㷨����ȡÿ�βɼ����ݵ�������Сֵ��ƽ������Ϊ��ֵ 
	 value1_max=ADV[0];  
   for(i=5;i<123;i++)   //���߸�ȥ��5����
     {
       if(value1_max<=ADV[i])
       value1_max=ADV[i];
     }
	  value1_min=ADV[0];  //��Сֵ
    for(i=5;i<123;i++) 
     {
       if(value1_min>=ADV[i])
       value1_min=ADV[i];
     }
   CCD_Threshold =(value1_max+value1_min)/2;	  //���������������ȡ����ֵ
		 
	 for(i = 5;i<118; i++)   //Ѱ����������أ��������������غ����������������ж����������
	 {
		 if(ADV[i]>CCD_Threshold &&ADV[i+1]>CCD_Threshold &&ADV[i+2]>CCD_Threshold &&ADV[i+3]<CCD_Threshold &&ADV[i+4]<CCD_Threshold &&ADV[i+5]<CCD_Threshold )
		 {	
			 Left=i+2;
			 break;	
		 }
	 }
	 for(j = 118;j>5; j--)//Ѱ���ұ������أ��������������غ����������������ж��ұ�������
   {
		if(ADV[j]<CCD_Threshold &&ADV[j+1]<CCD_Threshold &&ADV[j+2]<CCD_Threshold &&ADV[j+3]>CCD_Threshold &&ADV[j+4]>CCD_Threshold &&ADV[j+5]>CCD_Threshold )
		 {	
		   Right=j+2;
		   break;	
		 }
   }
	CCD_Median =(Right+Left)/2;//��������λ��
	if(myabs(CCD_Median-Last_CCD_Median)>90)   //�������ߵ�ƫ����̫��
	CCD_Median=Last_CCD_Median;    //��ȡ��һ�ε�ֵ
	Last_CCD_Median=CCD_Median;  //������һ�ε�ƫ��
} 

/* USER CODE END 1 */
