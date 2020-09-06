#ifndef __BILIBILI_H
#define __BILIBILI_H

#include <WiFi.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

extern String NAME ;  //�ĳ��Լ�������
extern String QiUID ;  //�ĳ��Լ���UID 19577966  435162639 483818980
extern String MyUID  ;
extern String QiollowerUrl ;   // ��˿��
extern String MyFollowerUrl ;   // ��˿��
extern String ViewAndLikesUrl ; // ��������������
extern String WeatherUrl ;   // ʱ������

extern long Follower ;   // ��˿��
extern long View ;       // ������
extern long Likes ;      // ������
extern int WeatherCode;
extern int Temperature;

void getViewAndLikes(String url);
int getFollower(String url);
void getWeather(String url);

#endif 

