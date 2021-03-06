/* 
1.Create A rgb slider in your project with name Test RGB
2.Now edit the ssid , password 
3.Change the userkey to your prokect user key .(line 23. )
4.Change ip address.( line 22)
5.Connect RGb led as follow :
PIN D2 as Red
PIN D3 as Green
PIN D4 as Red
now upload.
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
HTTPClient http;
// Name of the wifi
char* wifiName = "Your Wifi Name";
// Password of the same wifi
char* wifiPass = "Your wifi password";

String ip = "192.168.1.3";//Ip address of android device running Dacts
String userkey="Athp21R1aW1917I40N38mu296Oth345";//your user key in app
int port = 8080;// port number in settings in the app
String output;
void setup(){
  pinMode(D2,OUTPUT); // Rgb -- red
  pinMode(D3,OUTPUT); // Rgb -- green
  pinMode(D4,OUTPUT); // Rgb -- blue
  
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue 
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifiName,wifiPass);
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
          StaticJsonBuffer<600> jsonBuffer;
          DynamicJsonBuffer jsonBuf;
          Serial.println(output);
          JsonObject &root = jsonBuf.parseObject(output);//
          if (!root.success())
          {
            Serial.println("parseObject() failed");
          }
          int r = root["Test RGB"]["r"];//name you registered for the rgb light here "Test RGB" is used change the name
          int g = root["Test RGB"]["g"];
          int b = root["Test RGB"]["b"];
          
          analogWrite(D2,r*4); // multiplied by 4 because the value will be of range 0 -255 to increase
          analogWrite(D3,g*4); // brightness it is multiplied by 4.
          analogWrite(D4,b*4); // 
          
          delay(200);

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

