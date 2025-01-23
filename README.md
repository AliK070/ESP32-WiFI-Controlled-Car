## ESP32 WiFi Controlled Car

## The project itself: 

I gathered all my knowledge to do with Arduinos and motors and created a new car based on WiFi control using the ESP32. The ESP32 has a slightly larger learning curve than an Arduino, but once you get used to the differences it's a way better system than an Arduino, as it is overall a significantly better mcu than an ATmega328.

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

The two primary functions that take care of the motors are (with one extra being the server functionality): 

```c++

void stopMotors(); // Stops all motors
void setup(); // Initialzing all the pins for the motors
server.on(); // Serves the HTML page, you are able to fully edit it.

```

## Pictures and Demo: 

Pictures: 

Ariel-ish view:

![Image](https://github.com/user-attachments/assets/a6332a1a-b934-473b-8b6d-49d62898255c)

View from afar: 

![Image](https://github.com/user-attachments/assets/8a81a950-6793-4dba-b2f3-622543e3a3fe)

## Conclusion: 

The ESP32 WiFi-controlled car is a fascinating project that combines skills in electronics, coding, and prototyping to create a functional and interactive device. By leveraging the ESP32's advanced capabilities over traditional Arduino boards, such as built-in WiFi and Bluetooth, this project showcases how modern microcontrollers can take DIY projects to the next level.

One of the key takeaways from this project is the importance of prototyping. Using cardboard as a preliminary material for the car body allowed for iterative testing and design improvements without incurring high costs. However, upgrading to a 3D-printed case in the future will provide durability, precision, and aesthetics.

Another significant point is the flexibility and scalability of the ESP32. Beyond controlling the motors, it opens up possibilities for integrating additional features such as real-time telemetry, sensors (e.g., ultrasonic or IR for obstacle detection), or even a camera module for remote surveillance. Furthermore, the use of web server control provides a versatile and user-friendly way to interact with the car from any device with a browser.

Lastly, this project highlights the importance of security when handling sensitive data like WiFi credentials. While the current approach involves hardcoding these credentials, future improvements could include implementing a more secure and dynamic way to configure WiFi settings, such as using a captive portal or storing credentials in encrypted EEPROM.

In summary, this project not only demonstrates the potential of the ESP32 in robotics and IoT applications but also underscores the value of continuous learning, prototyping, and attention to security and design. The skills and knowledge gained here can easily be applied to more advanced projects, paving the way for even more creative and innovative designs in the future.
