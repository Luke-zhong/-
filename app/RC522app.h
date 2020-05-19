#ifndef _RC522_H
#define _RC522_H

typedef struct CusInfo {
	
  //uint8_t name[20];
  uint8_t ID  [4];
  //uint8_t num [8];
  //uint8_t StartTime[8];
 // uint8_t EndTine  [8];
 // uint8_t state;
  
}CusInfo;

void  CardHandle(void);
int seek_CusInfo(struct CusInfo *p);
int INC_CusInfo(struct CusInfo p);

#endif

