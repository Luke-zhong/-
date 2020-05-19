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
uint8_t buff2[]={0xFF ,0xFF, 0xFF, 0xFF, 0xFF, 0xFF};   // 卡A密钥
uint8_t buff3[]={0x55 ,0xBA, 0xA9, 0x89, 0x50 ,0xBA, 0xA9, 0x89, 0x50 ,0xBA, 0xA9, 0x89, 0x50 ,0xBA, 0xA9, 0x89};    // 写入的数据
void IC_CMT ( uint8_t * UID, uint8_t * KEY, uint8_t RW, uint8_t * Dat );


struct Student
 {
     char name[30];
     float fScore[3];
 }student={"dire",98.5,89.0,93.5}; //初始化结构体变量 
 
 
  void Display(struct Student su) //形参为同类型的结构体(Student结构) 
 {
     printf("-----Information------\n");
     printf("Name:%s",su.name);
     printf("Chinese:%.2f\n",su.fScore[0]);
     printf("Math:%.2f\n",su.fScore[1]);
     printf("English:%.2f",su.fScore[2]);
     printf("平均分数为:%.2f\n",(su.fScore[0]+su.fScore[1],su.fScore[2])/3);
 }
 
// struct CusInfo cusinfo;
 
/****************************/
void  CardHandle(void)
{
  struct CusInfo cusinfo;
  char cStr [ 30 ];
  uint8_t ucArray_ID [ 4 ];    /*先后存放IC卡的类型和UID(IC卡序列号)*/                                                                                         
  uint8_t ucStatusReturn;      /*返回状态*/                                                                                          
// static uint8_t ucLineCount = 0; 
//  int i;
  
  while ( 1 )
  { 
    /*******************卡片扇区读写测试****************************/
//    buff3[0]++;
//    
//    IC_CMT(buff1, buff2, 0, buff3);    // 写卡

//    IC_CMT(buff1, buff2, 1, buffer);   // 读卡
//    
//    printf ("读到的数据为：\n");
//    
//    for( i=0; i<16; i++)
//    {
//      printf ("0x%X\n", buffer[i]);    // 打印读到的数据
//    }
    /*******************卡片扇区读写测试 END****************************/  
    
    /*寻卡*/
		if ( ( ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID ) ) != MI_OK )  
       /*若失败再次寻卡*/
			ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID );		                                                

		if ( ucStatusReturn == MI_OK  )
		{
      /*防冲撞（当有多张卡进入读写器操作范围时，防冲突机制会从其中选择一张进行操作）*/
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
       
				IC_CMT(buff1, buff2, 1, buffer);   // 需要在读一次下次再能写进去（不知道为什么这样，应该是这样能改变某种模式吧）
        
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
  W25QXX_Read((u8 *)q,32*1024*1024-100,sizeof(struct CusInfo));//为什么不能传入这个指针
	printf("seek card == %X",q->ID[0]);
	printf("%X",q->ID[1]);
	printf("%X",q->ID[2]);
	printf("%X",q->ID[3]);
//	W25QXX_Write((u8*)TEXT_Buffer,FLASH_SIZE-100,SIZE);		//从倒数第100个地址处开始,写入SIZE长度的数据
//	W25QXX_Read(datatemp,FLASH_SIZE-100,SIZE);					//从倒数第100个地址处开始,读出SIZE个字节
//			printf("11%s",datatemp);
  CusCnt++;

//  buff[0]=CusCnt>>8;
//  buff[1]=CusCnt&0xFF;
//  W25QXX_Write((uint8_t *)buff,2,100);
	

  return 1;
}
 


 

