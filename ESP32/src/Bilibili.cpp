#include "Bilibili.h"
#include <ArduinoJson.h>
#include "GUI_Paint.h"
#include "DEV_Config.h"
#include <Wire.h>
#include <string.h>
String NAME = "DaqoLee";  //�ĳ��Լ�������
String QiUID  = "19577966";  //�ĳ��Լ���UID 19577966  435162639 483818980
String MyUID = "483818980";
String QiFollowerUrl = "http://api.bilibili.com/x/relation/stat?vmid=" + QiUID;   // ��˿��
String MyFollowerUrl = "http://api.bilibili.com/x/relation/stat?vmid=" + MyUID;   // ��˿��
String ViewAndLikesUrl = "http://api.bilibili.com/x/space/upstat?mid=" + MyUID; // ��������������
String WeatherUrl = "http://api.seniverse.com/v3/weather/now.json?key=**************=guangzhou&language=zh-Hans&unit=c";   //����Լ���key



long Follower = 0;   // ��˿��
long View = 0;       // ������
long Likes = 0;      // ������
int WeatherCode=0;
int Temperature=0;

DynamicJsonBuffer jsonBuffer(256); // ArduinoJson V5
// ��ȡ B վ�������������
void getViewAndLikes(String url)
{
  HTTPClient http;
  http.begin(url);

  int httpCode = http.GET();
  Serial.printf("[HTTP] GET... code: %d\n", httpCode);

  if (httpCode == 200)
  {
    Serial.println("Get OK");
    String resBuff = http.getString();
   

    JsonObject &root = jsonBuffer.parseObject(resBuff);

    if (!root.success())
    {
      Serial.println("parseObject() failed");
      return;
    }
    JsonObject& results_0 = root["results"][0];
    Likes = root["data"]["likes"];
    View = root["data"]["archive"]["view"];
    Serial.print("Likes: ");
    Serial.println(Likes);
    Serial.print("View: ");
    Serial.println(View);
  }
  else
  {
    Serial.printf("[HTTP] GET... failed, error: %d\n", httpCode);
  }

  http.end();
}

// ��ȡ B վ��˿��������֮ǰʱ����˻Ῠ����Json���������ʱ����һ����������
int getFollower(String url)
{
  HTTPClient http;
  http.begin(url);
  char *buff=NULL;
	uint32_t mid;
  uint32_t following;
	uint32_t whisper;
	uint32_t black;
  int httpCode = http.GET();
  Serial.printf("[HTTP] GET... code: %d\n", httpCode);

  if (httpCode == 200)
  {
    Serial.println("Get OK");
    String resBuff = http.getString();

    // Serial.println(resBuff);
    //  Serial.printf("\n");
		buff=(char*)resBuff.c_str();
		buff = strstr((char *)buff, "mid");
    //  Serial.println(buff);
		//  Serial.printf("\n");
		//sscanf(buff,"\"follower\":%d", &Follower);
    // ---------- ArduinoJson V5 ----------
    //  JsonObject &root = jsonBuffer.parseObject(resBuff);
    
    // if (!root.success())
    // {
    //   Serial.println("parseObject() failed");
    // //  return;
    // }
    // Follower = root["data"]["follower"];

  if(buff!=NULL)
	{	
		sscanf(buff,"mid\":%d,\"following\":%d,\"whisper\":%d,\"black\":%d,\"follower\":%d", 
		      &mid, &following, &whisper, &black, &Follower);
	}
	else
	{
		 Serial.printf("err\n");
		 return 0;
	}
	
    Serial.print("Fans: ");
    Serial.println(Follower);
  }
  else
  {
    Serial.printf("[HTTP] GET... failed, error: %d\n", httpCode);
		return 0;
  }

  http.end();

	return 1;
}


void getWeather(String url)
{
  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();
  Serial.printf("[HTTP] GET... code: %d\n", httpCode);
  if (httpCode == 200)
  {
    Serial.println("Get OK");
    String resBuff = http.getString();
  //   Serial.println(resBuff);
    // ---------- ArduinoJson V5 ----------
    JsonObject &root = jsonBuffer.parseObject(resBuff);
    if (!root.success())
    {
      Serial.println("parseObject() failed");
      return;
    }
   // JsonObject& results_0 = root["results"][0];
    WeatherCode = root["results"][0]["now"]["code"];
    Temperature = root["results"][0]["now"]["temperature"];
     Serial.println(Temperature);
  }
  else
  {
    Serial.printf("[HTTP] GET... failed, error: %d\n", httpCode);
  }

  http.end();
}
