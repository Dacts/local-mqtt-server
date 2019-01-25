/* 
App connection instruction:
Step 1 :
1.Open the app and create a new project.Note the auth key in project menu page.
2.Note the ip address of the Mobile which is running Dacts : mqtt server.
3.Create buttons or slider by clicking Add Device button in home page.
4.If you create PinButton named as D1 the output from the server wil be {"D1":1} or {"D1":0} (ON or OFF respectively).
For Rgb Slider the output will be :
{"Rgb_name":{"r":10,"g":20,"b":30}}
For Slider the output will be :
{"Slider_name":555}
For imageButton the output will be:
{"image_name":0} or {"image_name":1} (OFF or ON)
......................................................

Step 2 :
1.Edit auth below.
2.Edit wifiname and wifipassword
3.Edit ip address.
4.Edit port. below.

......................................................
Step 3 :
1.Open the arduino ide and paste the below code .
2 Edit the code in setup PinMode .
3.Edit the code after json phrase with your name of button or slider. 
4.Edit delay as you want.
5.Update the code to Esp8266 or your arduino.
.................................................................

IMPORTANT NOTE:
Both the mobile and devboards should be connected to the same network either 
your Router or to your mobile hotspot.
Because it runs a local server.

Another Note:
Make sure your Ide have the required library for your boards.
Below code is for Node Mcu8266.
The library used :
1.Esp8266
2.Arduino Json 

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
String auth="Athp21R1aW1917I40N38mu296Oth345";//your auth key in app
int port = 8080;// port number in settings in the app
String output;
void setup(){
  pinMode(D2,OUTPUT); // Rgb -- red
  pinMode(D3,OUTPUT); // Rgb -- green
  pinMode(D4,OUTPUT); // Rgb -- blue
  pinMode(D5,OUTPUT); // Slider value
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
          int slider = root["Pwm SLider"];
          analogWrite(D2,r*4);
          analogWrite(D3,g*4);
          analogWrite(D4,b*4);
          analogWrite(D5,slider); // slider value 0 to 1024
          delay(200);

}
String serverData(){
  String out;
  String link = "http://"+ip+":"+port+"/?auth="+auth;
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

