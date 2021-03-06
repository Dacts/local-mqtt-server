// change ssid , password 
/* 
1.Also change the user key .. The user key will be in the project menu on the top right corner 
of your project home page.(Line 21)
2.Change the ip value to your mobile ip from your mobile settings 
( Settings -> About phone - > Status ->IPaddress ) and paste it here in 20 th line.
3.Upload.
4.Create a pin button named ad D1.
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
HTTPClient http;
// Name of the wifi
char* ssid = "Your wifi or hotspot ID"; // both mobile and Esp should be connected to the same network 
// Password of the same wifi
char* password = "Your wifi or hotspot password";

String ip = "192.168.1.3";//Ip address of android device running Dacts
String userkey="Athp27R1aW1917I25N37mu486Oth615";//"Athp24R1aW1922I28N9mu432Oth46";//"Athp23R1aW1923I17N26mu822Oth143";//"Athp21R1aW1917I40N38mu296Oth345";//"Athp22R1aW1916I40N42mu639Oth654";//"Athp21R1aW1917I40N38mu296Oth345";//your auth key in app
int port = 8080;// port number in settings in the app
String output;
void setup(){
  pinMode(D1,OUTPUT);

  
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue 
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  Serial.begin(115200);
  Serial.println("setup...");
  while(WiFi.status() != WL_CONNECTED)
  { Serial.print("..");
    delay(500);    
    }
   Serial.println("ipAddress:");
   Serial.print(WiFi.localIP());   
}
void loop(){
          output = serverData();
          //StaticJsonBuffer<600> jsonBuffer;
          Serial.println(output);
          DynamicJsonBuffer jsonBuf;         
          JsonObject &root = jsonBuf.parseObject(output);//
          if (!root.success())
          {
            Serial.println("parseObject() failed");
          }
          Serial.println(".............................");
          int d1 = root["D1"];
          digitalWrite(D1,d1);          
          delay(400);
          
}
String serverData(){
  String out;
  String link = "http://"+ip+":"+port+"/?auth="+userkey;
    http.begin(link);
    int Code = http.GET();
     if (Code > 0) {
       // HTTP header has been send and Server response header has been handled
        if (Code == HTTP_CODE_OK || Code == HTTP_CODE_MOVED_PERMANENTLY) {
          out = http.getString();
          http.end();   
          return out;                       
          }
          else{
            out = "{'Error':1}";
            http.end(); 
            delay(500);
            return out; 
          }
        }
     else{
      Serial.println("con -------- failed");
      out = "{'Error':1}";
      http.end(); 
      return out; 
      }
      
}

