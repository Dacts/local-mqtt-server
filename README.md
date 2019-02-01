# local-mqtt-server

The Dacts:Local Mqtt Srever is an app which runs a server in your mobile.

To get started 
Install the esp8266 library.
Install arduino Json library
Now you are ready to go.


To connect it to your Esp8266.Use the following instructions.

1.Mobile and the Esp should be connected to the same wifi or hotspot.
2.The data recieved by the esp will be on json formate.
3.So if you name a pin button name as "D1" then you can get the value by root["D1"] in the loop function.
Other Button Outputs:

Pin Button 
name : D1
output :  {"D1":0} or {"D1":1} ( ON or OFF)
To get value root["D1"]

Image button:
name : Bulb
output :  {"Bulb":0} or {"Bulb":1} ( ON or OFF)
To get value root["Bulb"]

Rgb button :
name : Test Rgb
output : {"Test Rgb" : {"r":255,"g":255,"b":255}}
to get value :
Red - > root["Test Rgb"]["r"]
Greed - > root["Test Rgb"]["g"]
Blue - > root["Test Rgb"]["b"]

Slider Button
name : Slider
Output : {"Slider":1024}
to get value
root["Slider"]
