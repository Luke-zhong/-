#include <stdio.h>
#include <string.h>
#include "config.h"
#include "w5500.h"
#include "socket.h"
#include "netinit.h"

uint8 buffer[200];	

void net_init()
{
  uint8 server_ip[4]={192,168,0,101};			// 配置远程服务器IP地址
  uint16 server_port=8080;								// 配置远程服务器端口
  uint16 local_port=6000;									// 初始化一个本地端口
  uint16 len=0;
//  cJSON_Hooks hooks;
	
//  hooks.malloc_fn = pvPortMalloc;
//  hooks.free_fn = vPortFree;
 // cJSON_InitHooks(&hooks);
  
  	 
  switch(getSn_SR(0))
  {	  
	case SOCK_INIT:															// Socket处于初始化完成(打开)状态
			connect(0, server_ip,server_port);			// 配置Sn_CR为CONNECT，并向TCP服务器发出连接请求
	break;
	case SOCK_ESTABLISHED:											// Socket处于连接建立状态
			if(getSn_IR(0) & Sn_IR_CON)   					
			{
				setSn_IR(0, Sn_IR_CON);								// Sn_IR的CON位置1，通知W5500连接已建立
			}
			// 数据回环测试程序：数据从上位机服务器发给W5500，W5500接收到数据后再回给服务器
			len=getSn_RX_RSR(0);										// len=Socket0接收缓存中已接收和保存的数据大小
			if(len>0)
			{
//				create_js();
				recv(0,buffer,len);										// W5500接收来自服务器的数据，并通过SPI发送给MCU
				
				//send(0,buffer,len);	
    
			}
	break;
	case SOCK_CLOSE_WAIT:												// Socket处于等待关闭状态
			close(0);																// 关闭Socket0
	break;
	case SOCK_CLOSED:														// Socket处于关闭状态
			socket(0,Sn_MR_TCP,local_port,Sn_MR_ND);		// 打开Socket0，并配置为TCP无延时模式，打开一个本地端口
	break;
}
}
