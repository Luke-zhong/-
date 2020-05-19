//#include "sys.h"
//#include "delay.h"
//#include "usart.h"
//#include "led.h"
//#include "FreeRTOS.h"
//#include "task.h"
//#include "device.h"
//#include "w5500.h"
#include "socket.h"
//#include "string.h"
//#include "spi.h"
////#include "tcp_client.h"
////#include "dns.h"
//#include "dev_sign_api.h"
//#include "mqtt_api.h"
#include "mymqtt.h"
#include "MQTTPacket.h"
#include "delay.h"

//uint8 SUB_FLAG = 1;

int MQTT_Subscribe(int fd,char *topic,struct mqtt_struct *mqttstruct)
{
	
 
	memset(mqttstruct->send,0,sizeof(mqttstruct->send));  
	
	make_sub_msg(topic,mqttstruct->send,sizeof(mqttstruct->send));
	send(0,mqttstruct->send,sizeof(mqttstruct->send));
   // delay_ms(500);

	memset(mqttstruct->recev,0,sizeof(mqttstruct->recev));
	recv(0,mqttstruct->recev,sizeof(mqttstruct->recev));
	
	while(mqtt_decode_msg(mqttstruct->recev)!=SUBACK)//判断是不是SUBACK
	{
	 // delay_ms(500);
	  printf("wait suback\r\n");
	  //memset(mqttstruct.recev,0,sizeof(mqttstruct.recev)); 
	  //send(0,mqttstruct.send,sizeof(mqttstruct.send));
	}
	printf("sub over\r\n");
	printf("Subscibe topic is %s\r\n",topic);
	//    while(mqtt_decode_msg(msgbuf)!=SUBACK)//判断是不是SUBACK
	//    {
	//      printf("wait suback\r\n");
	//    }
//	SUB_FLAG = 0;
//   printf("222222");
//  memset(msgbuf,0,sizeof(msgbuf));					 
//	make_sub_msg(topic,msgbuf,sizeof(msgbuf));
//		// make_pub_msg(topic,msgbuf,sizeof(msgbuf),"hello");
//		 send(0,msgbuf,sizeof(msgbuf));// 接收到数据后再回给服务器，完成数据回环
//		 SUB_FLAG = 0;
//		 printf("444444");
////		  Delay_s(2);
//		  printf("3333333");
//		 while((len=getSn_RX_RSR(0))==0)
//		 {
////			 Delay_s(2);	
//			  send(0,msgbuf,sizeof(msgbuf));
//		  }
//		 printf("%s",topic);
//		  while(1);
//		 recv(0,msgbuf,len);
//		 
//		 do{
//			printf("wait suback\r\n");
//		 }while(mqtt_decode_msg(msgbuf)!=SUBACK);
//	//					 while(mqtt_decode_msg(msgbuf)!=SUBACK)//判断是不是SUBACK
//	//					{
//	//					  delay_ms(500);
//	//					  printf("22222\r\n");
//	//					}
//	//					  TIM_Cmd(TIM2, ENABLE);
//		  printf("send sub\r\n");	
//		
//		

//  return 1;

}

int MQTT_Publish(int fd,char *topic,struct mqtt_struct mqttstruct)
{
  memset(mqttstruct.send,0,sizeof(mqttstruct.send));
  make_pub_msg(topic,mqttstruct.send,sizeof(mqttstruct.send),"hellow");
  send(0,mqttstruct.send,sizeof(mqttstruct.send));
	
  return 1;
}

int MQTT_message_arrive(void)
{  
	
    uint8  msgbuf[1024];
    unsigned char dup;
	int qos = 0;
	unsigned char retained;
	unsigned short mssageid;
	int payloadlen_in;
	unsigned char* payload_in;
	MQTTString receivedTopic;


	
  memset(msgbuf,0,sizeof(msgbuf));
  recv(0,msgbuf,sizeof(msgbuf));
  
	
  if ((getSn_RX_RSR(0))>0) {
	  printf("2222");
  switch (mqtt_decode_msg(msgbuf)) {
  
	  case 3 :
		   MQTTDeserialize_publish(&dup, &qos, &retained, &mssageid, &receivedTopic,&payload_in, &payloadlen_in, msgbuf,sizeof(msgbuf));  
		   printf("message arrived %d: %s\n\r", payloadlen_in, payload_in);
		   break;
	  }
  return 1;
  }	  
}
