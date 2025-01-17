## ESP32 WiFi Controlled Car

## The project itself: 

I gathred all my knowledge to do with Arduinos and motors and created a new car based on WiFi control using the ESP32. The ESP32 has a slightly larger learning curve than an Arduino, but once you get used to the diffrences it's a way better system than an Arduino, as it is overall a significantly better mcu than an ATmega328.

## Materials needed:

- An ESP32 (I used an ESP32-D0WDQ6)
- Jumper wires, 22 awg solid core wire, and two breadboards (I used a mini breadboard for the GPIO pins)
- Two H-Bridges (TB6612FNG H-Bridge preferably) 
- Two sets of motors (four hobbyist motors or any two motors 6V~8VDC≤150mA)
- A battery bank for the ESP32 and motors
- Some type of case for the final product (I used carboard for prototpying)
  
Hopefully I'll get a 3D printer soon and move on from carboard! 

## The circuit Diagram 

The circuit diagram for the wiring of the ESP32 alongside four motors and a battery.

![Image](https://github.com/user-attachments/assets/c873739e-3bfd-482f-a9e9-8ba16bd83d94)

## The code and how it works: 

You will first need to install the ESPAsyncWebServer library and you'll need to include the WiFi library as well. Next when using the code in the program file, you will have to input your WiFis SSID and password, this is quite an unsafe way of doing this as you are hard coding both of these elements into the code, thus instead try to see a way in which you can dynamically and safely input this data. 

Change these fields to your own SSID and password:
```c++
// Wi-Fi credentials
const char *ssid = "";
const char *password = "";
```

## Conclusion: 
