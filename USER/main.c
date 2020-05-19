#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"
#include "device.h"
#include "w5500.h"
#include "socket.h"
#include "string.h"
#include "spi.h"
#include <cJSON.h>
#include <stdlib.h> 
//#include "rc522_config.h"
//#include "rc522_function.h"
//#include "RC522app.h"
//#include "netinit.h"
#include "tcp_client.h"
#include "mymqtt.h"
/*****����˼*******
MQTT��һ���ṹ������

struct mqtt {
uint8 recev[1024];
uint8 send [1024];
void *lock_recev;
void *lock_send ;

}
*******************/
/************************************************
 ALIENTEK ��ӢSTM32F103������ FreeRTOSʵ��2-1
 FreeRTOS��ֲʵ��-�⺯���汾
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		128  
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);

//�������ȼ�
#define LED0_TASK_PRIO		2
//�����ջ��С	
#define LED0_STK_SIZE 		1000  
//������
TaskHandle_t LED0Task_Handler;
//������
void led0_task(void *pvParameters);

////�������ȼ�
//#define LED1_TASK_PRIO		2
////�����ջ��С	
//#define LED1_STK_SIZE 		50  
////������
//TaskHandle_t MqttSubTask_Handler;
////������
//void MqttSubscribe_task(void *pvParameters);

////�������ȼ�
//#define LED2_TASK_PRIO		3
////�����ջ��С	
//#define LED2_STK_SIZE 		50  
////������
//TaskHandle_t MqttPubTask_Handler;
////������
//void MqttPuslish_task(void *pvParameters);

////�������ȼ�
//#define TEST_TASK_PRIO		3
////�����ջ��С	
//#define TEST_STK_SIZE 		1500  
////������
//TaskHandle_t TestTask_Handler;
////������
//void test_task(void *pvParameters);
/******private code**********/


/****************************/
//void MQTT_Subscribe(void)
//{
//  //if (RTC.Hour == 3 && RTC.Min == 2) {
//   if(0)
//   xTaskNotifyGive(MqttSubscribe_task);  
//	  
//  //}
//}

//void MQTT_Puslish(void)
//{
//  // if (RTC.Hour == 3 && RTC.Min == 2) {
//   if(0)
//   xTaskNotifyGive(MqttPuslish_task); 
//	   
//  //}
//}


int main(void)
{
	
    HAL_Init();                    	 	//��ʼ��HAL��    
	Stm32_Clock_Init(RCC_PLL_MUL9);   	//����ʱ��,72M
	delay_init();	    				//��ʱ������ʼ��	
	uart_init(115200);					//��ʼ������
//	W25QXX_Init();
	GPIO_Configuration();			
	WIZ_SPI_Init();
	Reset_W5500();
	set_default(); 														// ����Ĭ��MAC��IP��GW��SUB��DNS
	set_network();		// ���ó�ʼ��IP��Ϣ����ӡ����ʼ��8��Socket
	//net_init();
//	RC522_Init ();  
//	PcdReset ();
//	M500PcdConfigISOType ( 'A' );
  
	//printf("start"); 


	LED_Init();		  					//��ʼ��LED
	//������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������              
    vTaskStartScheduler();          //�����������
}

//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
    //����LED0����
    xTaskCreate((TaskFunction_t )led0_task,     	
                (const char*    )"led0_task",   	
                (uint16_t       )LED0_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED0_TASK_PRIO,	
                (TaskHandle_t*  )&LED0Task_Handler);   
    //����LED1����
//    xTaskCreate((TaskFunction_t )MqttSubscribe_task,     
//                (const char*    )"MqttSubscribe_task",   
//                (uint16_t       )LED1_STK_SIZE, 
//                (void*          )NULL,
//                (UBaseType_t    )LED1_TASK_PRIO,
//                (TaskHandle_t*  )&MqttSubTask_Handler);  
//				
//	 xTaskCreate((TaskFunction_t )MqttPuslish_task,     
//                (const char*    )"MqttPuslish_task",   
//                (uint16_t       )LED2_STK_SIZE, 
//                (void*          )NULL,
//                (UBaseType_t    )LED2_TASK_PRIO,
//                (TaskHandle_t*  )&MqttPubTask_Handler);     
 
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

//LED0������ 

extern uint8 SUB_FLAG;

void led0_task(void *pvParameters)
{
 // struct mqtt_struct mqttstruct;

//  char *topic = "/a1ZCY7ACE5k/FY-STM32/user/get";
  while(1)
  {
//	  printf("1111");
//    CardHandle();

	MQTT_CON_ALI();
//	if (getSn_SR(0) == 0x17) {
//    MQTT_Subscribe(0,topic,&mqttstruct);
//	if (SUB_FLAG == 0) {
//	MQTT_message_arrive();
}
//	MQTT_Puslish();
 //   }
//  }
}   

////LED1������
//void MqttSubscribe_task(void *pvParameters)
//{
//    while(1)
//    {
//       ulTaskNotifyTake( pdTRUE, portMAX_DELAY);
//       //��������	   
//    }
//}

//void MqttPuslish_task(void *pvParameters)
//{
//    while(1)
//    {
//       ulTaskNotifyTake( pdTRUE, portMAX_DELAY); 
//		//��������
//    }
//}
