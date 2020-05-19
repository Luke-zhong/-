#include <stdio.h>
#include <string.h>
#include "config.h"
#include "w5500.h"
#include "socket.h"
#include "netinit.h"

uint8 buffer[200];	

void net_init()
{
  uint8 server_ip[4]={192,168,0,101};			// ����Զ�̷�����IP��ַ
  uint16 server_port=8080;								// ����Զ�̷������˿�
  uint16 local_port=6000;									// ��ʼ��һ�����ض˿�
  uint16 len=0;
//  cJSON_Hooks hooks;
	
//  hooks.malloc_fn = pvPortMalloc;
//  hooks.free_fn = vPortFree;
 // cJSON_InitHooks(&hooks);
  
  	 
  switch(getSn_SR(0))
  {	  
	case SOCK_INIT:															// Socket���ڳ�ʼ�����(��)״̬
			connect(0, server_ip,server_port);			// ����Sn_CRΪCONNECT������TCP������������������
	break;
	case SOCK_ESTABLISHED:											// Socket�������ӽ���״̬
			if(getSn_IR(0) & Sn_IR_CON)   					
			{
				setSn_IR(0, Sn_IR_CON);								// Sn_IR��CONλ��1��֪ͨW5500�����ѽ���
			}
			// ���ݻػ����Գ������ݴ���λ������������W5500��W5500���յ����ݺ��ٻظ�������
			len=getSn_RX_RSR(0);										// len=Socket0���ջ������ѽ��պͱ�������ݴ�С
			if(len>0)
			{
//				create_js();
				recv(0,buffer,len);										// W5500�������Է����������ݣ���ͨ��SPI���͸�MCU
				
				//send(0,buffer,len);	
    
			}
	break;
	case SOCK_CLOSE_WAIT:												// Socket���ڵȴ��ر�״̬
			close(0);																// �ر�Socket0
	break;
	case SOCK_CLOSED:														// Socket���ڹر�״̬
			socket(0,Sn_MR_TCP,local_port,Sn_MR_ND);		// ��Socket0��������ΪTCP����ʱģʽ����һ�����ض˿�
	break;
}
}
