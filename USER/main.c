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
/*****程序构思*******
MQTT用一个结构体描述

struct mqtt {
uint8 recev[1024];
uint8 send [1024];
void *lock_recev;
void *lock_send ;

}
*******************/
/************************************************
 ALIENTEK 精英STM32F103开发板 FreeRTOS实验2-1
 FreeRTOS移植实验-库函数版本
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		128  
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);

//任务优先级
#define LED0_TASK_PRIO		2
//任务堆栈大小	
#define LED0_STK_SIZE 		1000  
//任务句柄
TaskHandle_t LED0Task_Handler;
//任务函数
void led0_task(void *pvParameters);

////任务优先级
//#define LED1_TASK_PRIO		2
////任务堆栈大小	
//#define LED1_STK_SIZE 		50  
////任务句柄
//TaskHandle_t MqttSubTask_Handler;
////任务函数
//void MqttSubscribe_task(void *pvParameters);

////任务优先级
//#define LED2_TASK_PRIO		3
////任务堆栈大小	
//#define LED2_STK_SIZE 		50  
////任务句柄
//TaskHandle_t MqttPubTask_Handler;
////任务函数
//void MqttPuslish_task(void *pvParameters);

////任务优先级
//#define TEST_TASK_PRIO		3
////任务堆栈大小	
//#define TEST_STK_SIZE 		1500  
////任务句柄
//TaskHandle_t TestTask_Handler;
////任务函数
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
	
    HAL_Init();                    	 	//初始化HAL库    
	Stm32_Clock_Init(RCC_PLL_MUL9);   	//设置时钟,72M
	delay_init();	    				//延时函数初始化	
	uart_init(115200);					//初始化串口
//	W25QXX_Init();
	GPIO_Configuration();			
	WIZ_SPI_Init();
	Reset_W5500();
	set_default(); 														// 设置默认MAC、IP、GW、SUB、DNS
	set_network();		// 配置初始化IP信息并打印，初始化8个Socket
	//net_init();
//	RC522_Init ();  
//	PcdReset ();
//	M500PcdConfigISOType ( 'A' );
  
	//printf("start"); 


	LED_Init();		  					//初始化LED
	//创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
    vTaskStartScheduler();          //开启任务调度
}

//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
    //创建LED0任务
    xTaskCreate((TaskFunction_t )led0_task,     	
                (const char*    )"led0_task",   	
                (uint16_t       )LED0_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED0_TASK_PRIO,	
                (TaskHandle_t*  )&LED0Task_Handler);   
    //创建LED1任务
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
 
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

//LED0任务函数 

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

////LED1任务函数
//void MqttSubscribe_task(void *pvParameters)
//{
//    while(1)
//    {
//       ulTaskNotifyTake( pdTRUE, portMAX_DELAY);
//       //订阅任务	   
//    }
//}

//void MqttPuslish_task(void *pvParameters)
//{
//    while(1)
//    {
//       ulTaskNotifyTake( pdTRUE, portMAX_DELAY); 
//		//推送任务
//    }
//}
