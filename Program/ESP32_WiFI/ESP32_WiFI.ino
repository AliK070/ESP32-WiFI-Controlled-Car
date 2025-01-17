#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// Wi-Fi credentials
const char *ssid = "";
const char *password = "";

// Motor control pins
#define ain1 14  // Front wheelss
#define ain2 12  // Front wheels
#define bin1 26  // Back wheels
#define bin2 27  // Back wheels
#define pwmM 13
#define pwmM_2 25

#define ain1_2 32  // Front wheels
#define ain2_2 33  // Front wheels
#define bin1_2 18  // Back wheels
#define bin2_2 19  // Back wheels

// Fixed speed for the motors
const int fixedSpeed = 200;

// Create AsyncWebServer object
AsyncWebServer server(80);

void setMotorSpeed(int speed) {
  analogWrite(pwmM, speed);
  analogWrite(pwmM_2, speed);
}

void stopMotors() {
  digitalWrite(ain1, LOW);
  digitalWrite(ain2, LOW);
  digitalWrite(bin1, LOW);
  digitalWrite(bin2, LOW);

  digitalWrite(ain1_2, LOW);
  digitalWrite(ain2_2, LOW);
  digitalWrite(bin1_2, LOW);
  digitalWrite(bin2_2, LOW);
  setMotorSpeed(0);
}

void setup() {
  Serial.begin(115200);

  // Initialize Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Initialize pins
  pinMode(ain1, OUTPUT);
  pinMode(ain2, OUTPUT);
  pinMode(bin1, OUTPUT);
  pinMode(bin2, OUTPUT);
  pinMode(pwmM, OUTPUT);
  pinMode(pwmM_2, OUTPUT);

  pinMode(ain1_2, OUTPUT);
  pinMode(ain2_2, OUTPUT);
  pinMode(bin1_2, OUTPUT);
  pinMode(bin2_2, OUTPUT);

  stopMotors();

  // Serve HTML page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    String html = "<html><head><style>";
    html += "body { font-family: Arial, sans-serif; text-align: center; background-color: #f0f0f0; margin: 0; padding: 0; height: 100%; overflow: hidden; display: flex; justify-content: center; align-items: center; }";
    html += "h1 { color: #4CAF50; margin-bottom: 20px; user-select: none; }";
    html += ".joystick-container { display: flex; flex-direction: column; align-items: center; justify-content: center; }";
    html += ".button { padding: 20px; border: none; border-radius: 50%; cursor: pointer; background-color: #4CAF50; color: white; font-size: 24px; width: 80px; height: 80px; display: flex; justify-content: center; align-items: center; margin: 10px; }";
    html += ".button:hover { background-color: #45a049; }";
    html += ".button:active { background-color: #388e3c; }";
    html += ".button:focus { outline: none; }";
    html += ".button i { font-size: 40px; }";  
    html += ".joystick-container { display: flex; flex-direction: column; align-items: center; justify-content: center; }";
    html += "body { user-select: none; }"; 
    html += "</style><link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.4/css/all.min.css'></head><body>";
    html += "<h1>Motor Control</h1>";
    html += "<div class='joystick-container'>";
    html += "<button class='button' ontouchstart=\"startMove('forward')\" ontouchend=\"stopMove()\" onmousedown=\"startMove('forward')\" onmouseup=\"stopMove()\"><i class='fas fa-arrow-up'></i></button><br>";
    html += "<div style='display: flex; justify-content: center;'>";
    html += "<button class='button' ontouchstart=\"startMove('left')\" ontouchend=\"stopMove()\" onmousedown=\"startMove('left')\" onmouseup=\"stopMove()\"><i class='fas fa-arrow-left'></i></button>";
    html += "<button class='button' ontouchstart=\"startMove('right')\" ontouchend=\"stopMove()\" onmousedown=\"startMove('right')\" onmouseup=\"stopMove()\"><i class='fas fa-arrow-right'></i></button>";
    html += "</div>";
    html += "<button class='button' ontouchstart=\"startMove('backward')\" ontouchend=\"stopMove()\" onmousedown=\"startMove('backward')\" onmouseup=\"stopMove()\"><i class='fas fa-arrow-down'></i></button><br>";
    html += "</div>";
    html += "<script>";
    html += "function startMove(direction) { fetch('/startMove?direction=' + direction); }";
    html += "function stopMove() { fetch('/stopMove'); }";
    html += "</script>";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  server.on("/startMove", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam("direction")) {
      String direction = request->getParam("direction")->value();
      if (direction == "forward") {
        // Front and back wheels forward


        //Back Wheel to the right
        digitalWrite(ain1, HIGH);
        digitalWrite(ain2, LOW);
        //Back Wheel to the left
        digitalWrite(bin1, LOW);
        digitalWrite(bin2, HIGH);
        //Front wheel left
        digitalWrite(ain1_2, HIGH);
        digitalWrite(ain2_2, LOW);
        //Front wheel right
        digitalWrite(bin1_2, HIGH);
        digitalWrite(bin2_2, LOW);



      } else if (direction == "backward") {
        // Front and back wheels backward

        //Back Wheel to the right
        digitalWrite(ain1, LOW);
        digitalWrite(ain2, HIGH);
        //Back Wheel to the left
        digitalWrite(bin1, HIGH);
        digitalWrite(bin2, LOW);
        //Front wheel left
        digitalWrite(ain1_2, LOW);
        digitalWrite(ain2_2, HIGH);
        //Front wheel right
        digitalWrite(bin1_2, LOW);
        digitalWrite(bin2_2, HIGH);
      } else if (direction == "right") {
        // Disable right wheels, enable left wheels
        //Back Wheel to the right
        digitalWrite(ain1, HIGH);
        digitalWrite(ain2, LOW);
        //Back Wheel to the left
        digitalWrite(bin1, HIGH);
        digitalWrite(bin2, LOW);
        //Front wheel left
        digitalWrite(ain1_2, LOW);
        digitalWrite(ain2_2, HIGH);
        //Front wheel right
        digitalWrite(bin1_2, HIGH);
        digitalWrite(bin2_2, LOW);
      } else if (direction == "left") {
        //Back Wheel to the right
        digitalWrite(ain1, LOW);
        digitalWrite(ain2, HIGH);
        //Back Wheel to the left
        digitalWrite(bin1, LOW);
        digitalWrite(bin2, HIGH);
        //Front wheel left
        digitalWrite(ain1_2, HIGH);
        digitalWrite(ain2_2, LOW);
        //Front wheel right
        digitalWrite(bin1_2, LOW);
        digitalWrite(bin2_2, HIGH);
      }
      setMotorSpeed(fixedSpeed);
    }
    request->send(200, "text/plain", "Moving");
  });

  server.on("/stopMove", HTTP_GET, [](AsyncWebServerRequest *request) {
    stopMotors();
    request->send(200, "text/plain", "Stopped");
  });

  server.begin();
}

void loop() {
}
