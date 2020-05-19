

struct CusInfo {
	
  uint8_t name[20];
  uint8_t ID  [4];
  uint8_t num [8];
  uint8_t StartTime[8];
  uint8_t EndTine  [8];
  uint8_t state;
  
};
typedef struct CusInfo CusInfo
int AddCusInfo(CusInfo *CUS_INFO)
{
  W25Q64_ReadData(门卡数量,1,cnt);
  //关中断
  W25Q64_WriteData(CusAddrBase+cnt*sizeof(CusInfo),sizeof(CusInfo),&CUS_INFO);
  cnt++;
  W25Q64_WriteData(门卡数量,1,cnt);
  
  return 1;
}

void GetCusInfo();
{
  root=cJSON_CreateObject();
  char *cusinfo;
  for(i=0; i<cnt; i++)
  {
    W25Q64_ReadData(CusAddrBase+cnt*sizeof(CusInfo),sizeof(CusInfo),buff);
	cJSON_AddStringToObject(root, "name", buff.name);
	cJSON_AddStringToObject(root, "ID", buff.ID);
	cJSON_AddStringToObject(root, "num", buff.num);
	cJSON_AddStringToObject(root, "StartTime", buff.StartTime);
	cJSON_AddStringToObject(root, "EndTine", buff.EndTine);
	cJSON_AddStringToObject(root, "state", buff.state);
	cusinfo = cJSON_Print(root);   // 将 root 转化为普通字符串，并返回指针	
	cJSON_Delete(root); 
	send(TCPC,sizeof(CusInfo),cusinfo);
  }
}