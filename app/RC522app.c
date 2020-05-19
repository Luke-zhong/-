#include "rc522_config.h"
#include "rc522_function.h"
#include "RC522app.h"
#include "w25qxx.h"
#include <string.h> 
#include <stdio.h>
/******************/
const u8 TEXT_Buffer[]={"ELITE STM32 SPI TEST"};
#define SIZE sizeof(TEXT_Buffer)
static uint8_t buffer[100];
uint8_t buff1[] = {0x50 ,0xBA, 0xA9, 0x89};
uint8_t buff2[]={0xFF ,0xFF, 0xFF, 0xFF, 0xFF, 0xFF};   // ��A��Կ
uint8_t buff3[]={0x55 ,0xBA, 0xA9, 0x89, 0x50 ,0xBA, 0xA9, 0x89, 0x50 ,0xBA, 0xA9, 0x89, 0x50 ,0xBA, 0xA9, 0x89};    // д�������
void IC_CMT ( uint8_t * UID, uint8_t * KEY, uint8_t RW, uint8_t * Dat );


struct Student
 {
     char name[30];
     float fScore[3];
 }student={"dire",98.5,89.0,93.5}; //��ʼ���ṹ����� 
 
 
  void Display(struct Student su) //�β�Ϊͬ���͵Ľṹ��(Student�ṹ) 
 {
     printf("-----Information------\n");
     printf("Name:%s",su.name);
     printf("Chinese:%.2f\n",su.fScore[0]);
     printf("Math:%.2f\n",su.fScore[1]);
     printf("English:%.2f",su.fScore[2]);
     printf("ƽ������Ϊ:%.2f\n",(su.fScore[0]+su.fScore[1],su.fScore[2])/3);
 }
 
// struct CusInfo cusinfo;
 
/****************************/
void  CardHandle(void)
{
  struct CusInfo cusinfo;
  char cStr [ 30 ];
  uint8_t ucArray_ID [ 4 ];    /*�Ⱥ���IC�������ͺ�UID(IC�����к�)*/                                                                                         
  uint8_t ucStatusReturn;      /*����״̬*/                                                                                          
// static uint8_t ucLineCount = 0; 
//  int i;
  
  while ( 1 )
  { 
    /*******************��Ƭ������д����****************************/
//    buff3[0]++;
//    
//    IC_CMT(buff1, buff2, 0, buff3);    // д��

//    IC_CMT(buff1, buff2, 1, buffer);   // ����
//    
//    printf ("����������Ϊ��\n");
//    
//    for( i=0; i<16; i++)
//    {
//      printf ("0x%X\n", buffer[i]);    // ��ӡ����������
//    }
    /*******************��Ƭ������д���� END****************************/  
    
    /*Ѱ��*/
		if ( ( ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID ) ) != MI_OK )  
       /*��ʧ���ٴ�Ѱ��*/
			ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID );		                                                

		if ( ucStatusReturn == MI_OK  )
		{
      /*����ײ�����ж��ſ������д��������Χʱ������ͻ���ƻ������ѡ��һ�Ž��в�����*/
			if ( PcdAnticoll ( ucArray_ID ) == MI_OK )                                                                   
			{
				sprintf ( cStr, "The Card ID is: %02X%02X%02X%02X",
                  ucArray_ID [ 0 ],
                  ucArray_ID [ 1 ],
                  ucArray_ID [ 2 ],
                  ucArray_ID [ 3 ] );
        
        	printf ( "%s\r\n",cStr ); 
			cusinfo.ID[0] = ucArray_ID [ 0 ];
			cusinfo.ID[1] = ucArray_ID [ 1 ];
			cusinfo.ID[2] = ucArray_ID [ 2 ];
			cusinfo.ID[3] = ucArray_ID [ 3 ];
			printf("card id %X",cusinfo.ID[0]);
			printf("%X",cusinfo.ID[1]);
			printf("%X",cusinfo.ID[2]);

		    printf("%X",cusinfo.ID[3]);
				
			INC_CusInfo(cusinfo);
//			printf("add card ok");
//			seek_CusInfo(&cusinfo);

//				if ( ucLineCount == 0 )
      //    LCD_SetTextColor(RED); 	
				
				//ILI9341_DispStringLine_EN(LINE(ucLineCount) , (char* )cStr );
       
				IC_CMT(buff1, buff2, 1, buffer);   // ��Ҫ�ڶ�һ���´�����д��ȥ����֪��Ϊʲô������Ӧ���������ܸı�ĳ��ģʽ�ɣ�
        
//				ucLineCount ++;
				
//				if ( ucLineCount == 17 ) ucLineCount = 0;	    
			}		
		}		
  }	
  
}


int seek_CusInfo(struct CusInfo *p)
{
	
	
  struct CusInfo q;
  uint8_t cnt;
  uint16_t CusCnt=0,i=0;
 // uint8_t j,k,l;
	
//  W25QXX_Read(&cnt,100,1);
//  CusCnt = cnt;
//  W25QXX_Read(&cnt,100+1,1);
//  CusCnt=(CusCnt<<8)|cnt;
	
 // for(i=0; i<CusCnt; i++)
 // {
	W25QXX_Read((uint8_t *)&q,100+1*sizeof(CusInfo),sizeof(CusInfo));
	printf("seek card == %X",q.ID[0]);
	printf("%X",q.ID[1]);
	printf("%X",q.ID[2]);
	printf("%X",q.ID[3]);
	
    if (memcmp(q.ID,p->ID,sizeof(q.ID))) {
		
		printf("seek ok");
	 // if (memcmp(buff.EndTine,CUS_INFO.EndTine,sizeof(CusInfo.EndTine))) {
	    return 1;
	  }
	  
//	  else {
//		buff.state = -1;
//	    W25Q64_WriteData(CusAddrBase+i*sizeof(CusInfo),sizeof(CusInfo),buff)
//		return false;
//	  }
	  
//	}	
  return 1;
}

int INC_CusInfo(struct CusInfo p)
{
	
  uint8_t buff[10];
  uint16_t CusCnt=0;
  uint8_t cnt=0;
  struct CusInfo *q;
  u32 FLASH_SIZE;
	u8 datatemp[SIZE];
FLASH_SIZE=32*1024*1024;	

	
//	 Display(student);
//	
	printf("income card == %X",p.ID[0]);
	printf("%X",p.ID[1]);
	printf("%X",p.ID[2]);
	printf("%X",p.ID[3]);
//  W25QXX_Read(&cnt,100,1);
//  CusCnt = cnt;
//	printf("2");
//  W25QXX_Read(&cnt,100+1,1);
 // CusCnt=(CusCnt<<8)|cnt;

	printf("3");
  W25QXX_Write((u8 *)&p,32*1024*1024-100,sizeof(struct CusInfo));
//	printf("income card == %X",p->ID[0]);
//	printf("%X",p->ID[1]);
//	printf("%X",p->ID[2]);
//	printf("%X",p->ID[3]);
  W25QXX_Read((u8 *)q,32*1024*1024-100,sizeof(struct CusInfo));//Ϊʲô���ܴ������ָ��
	printf("seek card == %X",q->ID[0]);
	printf("%X",q->ID[1]);
	printf("%X",q->ID[2]);
	printf("%X",q->ID[3]);
//	W25QXX_Write((u8*)TEXT_Buffer,FLASH_SIZE-100,SIZE);		//�ӵ�����100����ַ����ʼ,д��SIZE���ȵ�����
//	W25QXX_Read(datatemp,FLASH_SIZE-100,SIZE);					//�ӵ�����100����ַ����ʼ,����SIZE���ֽ�
//			printf("11%s",datatemp);
  CusCnt++;

//  buff[0]=CusCnt>>8;
//  buff[1]=CusCnt&0xFF;
//  W25QXX_Write((uint8_t *)buff,2,100);
	

  return 1;
}
 


 

