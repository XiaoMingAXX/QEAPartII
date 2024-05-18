#include "key.h"

/**************************************************************************
Function: Key initialization
Input   : none
Output  : none
�������ܣ�������ʼ��
��ڲ�������
����  ֵ���� 
**************************************************************************/

/**************************************************************************
Function: Buttons to scan
Input   : none
Output  : none
�������ܣ�����ɨ��
��ڲ�������
����  ֵ������״̬ 0���޶��� 1������ 
**************************************************************************/
u8 click(void)
{
	//Press the release sign
	//�������ɿ���־
	static u8 flag_key=1;
	
	if(flag_key&&KEY==0)
	{
	 flag_key=0; //The key is pressed //��������
	 return 1;	
	}
	else if(1==KEY)			
		flag_key=1;
	return 0; //No key is pressed //�ް�������
}


uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{			
	/*����Ƿ��а������� */
	if(KEY == KEY_ON )  
	{	 
		/*�ȴ������ͷ� */
		HAL_Delay(200);
		while(KEY == KEY_ON);   
		return 	KEY_ON;	 
	}
	else
		return KEY_OFF;
}

/**************************************************************************
Function: Delay function
Input   : none
Output  : none
�������ܣ��ӳٺ���
��ڲ�������
�� �� ֵ����
**************************************************************************/
void Delay_ms(void)
{
   int ii,i;    
   for(ii=0;ii<50;ii++)
   {
	   for(i=0;i<50;i++);
	 }	
}
/**************************************************************************
Function: Buttons to scan
Input   : Double click wait time
Output  : Button status: 0- no action, 1- click, 2- double click
�������ܣ�����ɨ��
��ڲ�����˫���ȴ�ʱ��
����  ֵ������״̬: 0-�޶���, 1-����, 2-˫�� 
**************************************************************************/
u8 click_N_Double (u8 time)
{
		static	u8 flag_key,count_key,double_key;	
		static	u16 count_single,Forever_count;
	
	  if(KEY==0)  Forever_count++;   
    else        Forever_count=0;
	
		if(KEY == KEY_ON&&0==flag_key)		flag_key=1;	
	  if(0==count_key)
		{
				if(flag_key==1) 
				{
					double_key++;
					count_key=1;	
				}
				if(double_key==2) 
				{
					double_key=0;
					count_single=0;
					return 2; //Double click //˫��
				}
		}
		if(1==KEY)			flag_key=0,count_key=0;
		
		if(1==double_key)
		{
			count_single++;
			if(count_single>time&&Forever_count<time)
			{
			double_key=0;
			count_single=0;	
			return 1; //Click //����
			}
			if(Forever_count>time)
			{
			double_key=0;
			count_single=0;	
			}
		}	
		return 0;
}
/**************************************************************************
Function: Button scan.Because static variables are used, a function with a different name needs to be defined when the keystroke scan function is used multiple times
Input   : none
Output  : Button status: 0- no action, 1- click, 2- double click
�������ܣ�����ɨ�衣��Ϊʹ�õ��˾�̬���������ദ��Ҫʹ�ð���ɨ�躯��ʱ����Ҫ�ٶ���һ����ͬ������
��ڲ�������
�� �� ֵ������״̬: 0-�޶���, 1-����, 2-˫�� 
**************************************************************************/
u8 click_N_Double_MPU6050 (u8 time)
{
		static	u8 flag_key,count_key,double_key;	
		static	u16 count_single,Forever_count;
	
	  if(KEY==0)  Forever_count++;  
    else        Forever_count=0;
		if(0==KEY&&0==flag_key)		flag_key=1;	
	  if(0==count_key)
		{
				if(flag_key==1) 
				{
					double_key++;
					count_key=1;	
				}
				if(double_key==2) 
				{
					double_key=0;
					count_single=0;
					return 2; //Double click //˫��
				}
		}
		if(1==KEY)			flag_key=0,count_key=0;
		
		if(1==double_key)
		{
			count_single++;
			if(count_single>time&&Forever_count<time)
			{
			double_key=0;
			count_single=0;	
			return 1; //Click //����
			}
			if(Forever_count>time)
			{
			double_key=0;
			count_single=0;	
			}
		}	
		return 0;
}
/**************************************************************************
Function: Long according to the test
Input   : none
Output  : Key state 0: no action 1: long press 3s
�������ܣ��������
��ڲ�������
����  ֵ������״̬ 0���޶��� 1������3s
**************************************************************************/
//u8 Long_Press(void)
//{
//	static u16 Long_Press_count,Long_Press;

//	if(Long_Press==0&&KEY==0)  Long_Press_count++; 
//	else                       Long_Press_count=0;

//	if(Long_Press_count>300)	//3 seconds //3��	
//	{
//		Long_Press=1;	
//		Long_Press_count=0;
//		return 1;
//	}				
//	 if(Long_Press==1) //Long press position 1 //������־λ��1
//	{
//			Long_Press=0;
//	}
//	return 0;
//}


/*************************************************************************
Function:User_Key_Scan
Input:None
Output:Key_status
�������ܣ��û��������
��ڲ�������
����ֵ  ������״̬
**************************************************************************/
//����5ms�ж��е���
uint8_t User_Key_Scan(void)
{
	static u16 count_time = 0;					//���㰴�µ�ʱ�䣬ÿ5ms��1
	static u8 key_step = 0;						//��¼��ʱ�Ĳ���
	switch(key_step)
	{
		case 0:
			if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_0) == KEY_ON )
				key_step++;						//��⵽�а������£�������һ��
			break;
		case 1:
			if((++count_time) == 5)				//��ʱ����
			{
				if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_0) == KEY_ON )//����ȷʵ������
					key_step++,count_time = 0;	//������һ��
				else
					count_time = 0,key_step = 0;//����λ
			}
			break;
		case 2:
			if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_0) == KEY_ON )
				count_time++;					//���㰴�µ�ʱ��
			else 								//��ʱ���ɿ���
				key_step++;						//������һ��
			break;
		case 3:									//��ʱ�����µ�ʱ�䣬���ж��ǳ������Ƕ̰�
			if(count_time > 200)				//��5ms�ж��е��ã��ʰ���ʱ��������400*5 = 2000ms�����ֵ��
			{							
				key_step = 0;					//��־λ��λ
				count_time = 0;
				return Long_Press;				//���� ���� ��״̬ 
 			}
			else if(count_time > 5)				//��ʱ�ǵ�����һ��
			{
				key_step++;						//��ʱ������һ�����ж��Ƿ���˫��
				count_time = 0;					//���µ�ʱ������
			}
			else
			{
				key_step = 0;
				count_time = 0;	
			}
			break;
		case 4:									//�ж��Ƿ���˫���򵥻�
			if(++count_time > 30)				//5*50= 250ms���жϰ����Ƿ���
			{
				if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_0) == KEY_ON )	//����ȷʵ������
				{																	//����˫�����ܰ�̫�죬��ʶ��ɵ���
					key_step++;														//������һ������Ҫ�����ֲ����ͷ�״̬
					count_time = 0;
				}
				else																//190ms���ް������£���ʱ�ǵ�����״̬
				{
					key_step = 0;				//��־λ��λ
					count_time = 0;					
					return Click;				//���ص�����״̬
				}
			}
			break;
		case 5:
			if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_0) == KEY_ON )//�������ڰ���
			{
				count_time++;
			}
			else								//�����Ѿ�����
			{
//				if(count_time>400)				//����ڶ��εĵ���Ҳ�����ж�ʱ��ģ�Ĭ�ϲ��ж�ʱ�䣬ȫ��������˫��
//				{
//				}
				count_time = 0;
				key_step = 0;
				return Double_Click;
			}
			break;
		default:break;
	}
	return No_Action;							//�޶���
}
/**************************************************************************
�������ܣ�ѡ�����е�ģʽ
��ڲ�������
����  ֵ����
**************************************************************************/
//u8  select(void)
//{
//	  int Flag_Next=0;
//	  static u8 flag=1;
//	
//	  oled_show_once();  //OLED��ʾ
//	  if(click_N_Double(150) == 1)
//		{
//			Move+=1;
//			if(Move>6)
//				Move=0;
//		}
//	  if(Move==0)			 ELE_ON_Flag=0,CCD_ON_Flag=1,APP_ON_Flag=0,Along_wall=0,Follow_ON_Flag=0,Avoid_ON_Flag=0,PS2_ON_Flag=0;  //CCDң��ģʽ 
//		else if(Move==1) ELE_ON_Flag=1,CCD_ON_Flag=0,APP_ON_Flag=0,Along_wall=0,Follow_ON_Flag=0,Avoid_ON_Flag=0,PS2_ON_Flag=0;  //ELEң��ģʽ
//		else if(Move==2) ELE_ON_Flag=0,CCD_ON_Flag=0,APP_ON_Flag=1,Along_wall=0,Follow_ON_Flag=0,Avoid_ON_Flag=0,PS2_ON_Flag=0;	//othģʽ
//	  else if(Move==3) ELE_ON_Flag=0,CCD_ON_Flag=0,APP_ON_Flag=0,Along_wall=1,Follow_ON_Flag=0,Avoid_ON_Flag=0,PS2_ON_Flag=0;  //��ֱ��ģʽ
//	  else if(Move==4) ELE_ON_Flag=0,CCD_ON_Flag=0,APP_ON_Flag=0,Along_wall=0,Follow_ON_Flag=1,Avoid_ON_Flag=0,PS2_ON_Flag=0;  //����ģʽ
//	  else if(Move==5) ELE_ON_Flag=0,CCD_ON_Flag=0,APP_ON_Flag=0,Along_wall=0,Follow_ON_Flag=0,Avoid_ON_Flag=1,PS2_ON_Flag=0;  //����ģʽ
//		else if(Move==6) ELE_ON_Flag=0,CCD_ON_Flag=0,APP_ON_Flag=0,Along_wall=0,Follow_ON_Flag=0,Avoid_ON_Flag=0,PS2_ON_Flag=1;  //ps2ģʽ
//    if(Long_Press())Flag_Next=1;//��������3���������ģʽ
//	  if(Flag_Next==1)OLED_Clear(),flag=0;  //���OLED��Ļ ������������
//	  return flag;	  
//}
