#ifndef _MYMQTT_H
#define _MYMQTT_H
#include "mqtt_fun.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
typedef struct mqtt_struct {
  
  uint8_t recev[500];
  uint8_t send [500];
  void *lock_recev;
  void *lock_send ;

}mqtt_struct;
//int MQTT_Subscribe(int fd,char *topic,mqtt_struct *mqttstruct);
//int MQTT_Publish(int fd,char *topic,mqtt_struct mqttstruct);
//int MQTT_message_arrive(void);

#endif

