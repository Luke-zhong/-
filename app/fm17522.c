struct CusInfo {
	
  uint8_t name[20];
  uint8_t ID  [4];
  uint8_t num [8];
  uint8_t StartTime[8];
  uint8_t EndTine  [8];
  uint8_t state;
  
};

typedef struct CusInfo CusInfo;

CusInfo CUS_INFO; 
int Fm17522app()
{
  if (TypeA_CardActivate(PICC_ATQA,PICC_UID,PICC_SAK)==OK) {
    
	Init_Cuninfo(&CUS_INFO);
	
	W25Q64_ReadData(4096*5,4,SuperCard);
	memcmp(CUS_INFO.ID,PICC_UID,sizeof(CUS_INFO.ID));	
    if (memcmp(superCard,CUS_INFO,4)) {
		LOCK_ON;
		...;
	}
	else {
      if(!Seek_Customer(&CUS_INFO)) {
	    LOCK_ON;
	  }
	  else {
	    //报警；
	  }
	}  	
  }
} 

int Seek_Customer(CusInfo *CUS_INFO)
{
  
  CusInfo buff;
  W25Q64_ReadData(门卡数量,1,cnt);
  for(i=0; i<cnt; i++)
  {
    W25Q64_ReadData(CusAddrBase+i*sizeof(CusInfo),sizeof(CusInfo),buff);
	
    if (memcmp(buff.ID,CUS_INFO.ID,sizeof(CUS_INFO.ID))) {
	  if (memcmp(buff.EndTine,CUS_INFO.EndTine,sizeof(CusInfo.EndTine))) {
	    return OK;
	  }
	  
	  else {
		buff.state = -1;
	    W25Q64_WriteData(CusAddrBase+i*sizeof(CusInfo),sizeof(CusInfo),buff)
		return false;
	  }
	  
	}	
  }
  
  
  
}

void Init_Cuninfo(CusInfo * cusinfo)
{
  memcpy(cusinfo->ID,PICC_UID,4);
  memcpy(cusinfo->EndTine,RTCtime,6);
}