/***********************************************
��˾����Ȥ�Ƽ�����ݸ�����޹�˾
Ʒ�ƣ�WHEELTEC
������wheeltec.net
�Ա����̣�shop114407458.taobao.com 
����ͨ: https://minibalance.aliexpress.com/store/4455017
�汾��V1.0
�޸�ʱ�䣺2022-9-26

Company: WHEELTEC Co.Ltd
Brand: WHEELTEC
Website: wheeltec.net
Taobao shop: shop114407458.taobao.com 
Aliexpress: https://minibalance.aliexpress.com/store/4455017
Version: V1.0
Update��2022-6-20

All rights reserved
***********************************************/

#include "system.h"

//Robot software fails to flag bits
//���������ʧ�ܱ�־λ
u8 Flag_Stop=0;   

//The ADC value is variable in segments, depending on the number of car models. Currently there are 6 car models
//ADCֵ�ֶα�����ȡ����С���ͺ�������Ŀǰ��6��С���ͺ�
int Divisor_Mode;

// Robot type variable
//�������ͺű���
//0=Mec_Car��1=Omni_Car��2=Akm_Car��3=Diff_Car��4=FourWheel_Car��5=Tank_Car
u8 Car_Mode=4; 

//Servo control PWM value, Ackerman car special
//�������PWMֵ��������С��ר��
int Servo;  

//Default speed of remote control car, unit: mm/s
//ң��С����Ĭ���ٶȣ���λ��mm/s
float RC_Velocity=500; 

//The Tank_Car CCD related variables
//ȫ��С��CCD��ر���
float Tank_Car_CCD_KP=35,Tank_Car_CCD_KI=140;

//The Tank_Car ELE related variables
//ȫ��С��ELE��ر���
float Tank_Car_ELE_KP=25,Tank_Car_ELE_KI=200;


//The Omni_Car CCD related variables
//ȫ��С��CCD��ر���
float Omni_Car_CCD_KP=10,Omni_Car_CCD_KI=110;

//The Omni_Car ELE related variables
//ȫ��С��ELE��ر���
float Omni_Car_ELE_KP=9,Omni_Car_ELE_KI=100;

//The other CCD related variables
//����С��CCD��ر���
float CCD_KP=37,CCD_KI=140;

//The other ELE related variables
//����С��ELE��ر���
float ELE_KP=30,ELE_KI=200;

//The PS2 gamepad controls related variables
//PS2�ֱ�������ر���
int PS2_LX,PS2_LY,PS2_RX,PS2_RY,PS2_KEY; 

//Vehicle three-axis target moving speed, unit: m/s
//С������Ŀ���˶��ٶȣ���λ��m/s
float Move_X, Move_Y, Move_Z;   

//PID parameters of Speed control
//�ٶȿ���PID����
float Velocity_KP=700,Velocity_KI=700; 

//Smooth control of intermediate variables, dedicated to omni-directional moving cars
//ƽ�������м������ȫ���ƶ�С��ר��
Smooth_Control smooth_control;  

//The parameter structure of the motor
//����Ĳ����ṹ��
Motor_parameter MOTOR_A,MOTOR_B,MOTOR_C,MOTOR_D;  

/************ С���ͺ���ر��� **************************/
/************ Variables related to car model ************/
//Encoder accuracy
//����������
float Encoder_precision; 
//Wheel circumference, unit: m
//�����ܳ�����λ��m
float Wheel_perimeter; 
//Drive wheel base, unit: m
//�������־࣬��λ��m
float Wheel_spacing; 
//The wheelbase of the front and rear axles of the trolley, unit: m
//С��ǰ�������࣬��λ��m
float Axle_spacing; 
//All-directional wheel turning radius, unit: m
//ȫ����ת��뾶����λ��m
float Omni_turn_radiaus; 
/************ С���ͺ���ر��� **************************/
/************ Variables related to car model ************/

//PS2 controller, Bluetooth APP, aircraft model controller, CAN communication, serial port 1 communication control flag bit.
//These 5 flag bits are all 0 by default, representing the serial port 3 control mode
//PS2�ֱ�������APP����ģ�ֱ���CANͨ�š�����1ͨ�ſ��Ʊ�־λ����5����־λĬ�϶�Ϊ0��������3����ģʽ
u8 CCD_ON_Flag=0, APP_ON_Flag=0, ELE_ON_Flag=0, Avoid_ON_Flag=0, Follow_ON_Flag=0, Along_wall=0, PS2_ON_Flag=0; 

//Bluetooth remote control associated flag bits
//����ң����صı�־λ
u8 Flag_Left, Flag_Right, Flag_Direction=0, Turn_Flag; 

//Sends the parameter's flag bit to the Bluetooth APP
//������APP���Ͳ����ı�־λ
u8 PID_Send; 

void systemInit(void)
{       
	//Interrupt priority group setting
	//�ж����ȼ���������
	
	//Delay function initialization
	//��ʱ������ʼ��
	delay_init();			                                            
	
	//Initialize the hardware interface connected to the LED lamp
	//��ʼ����LED�����ӵ�Ӳ���ӿ�     
	
	//Initialize the hardware interface connected to the user's key
	//��ʼ�����û��������ӵ�Ӳ���ӿ� to the tap position of the potentiometer, determine which type of car needs to be matched, 
  //and then initialize the corresponding parameters	
  //���ݵ�λ���ĵ�λ�ж���Ҫ���������һ���ͺŵ�С����Ȼ����ж�Ӧ�Ĳ�����ʼ��	
	Robot_Select();                 
	
  /* USER CODE END 2 */
	//Initialize the hardware interface connected to the OLED display
  //��ʼ����OLED��ʾ�����ӵ�Ӳ���ӿ�	
	
//	while(select())	{	}			//���п���ģʽѡ��
//	delay_ms(500);
			                      

	 							
}
