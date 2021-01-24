#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// WiFi settings
#define WIFI_MODE           2                     // 1 = AP mode, 2 = STA mode
#define SSID_AP             "NodeMCU_WiFi_Boat"    // for AP mode
#define PASSWORD_AP         "12345678"            // for AP mode
#define SSID_STA            "hu"      // for STA mode
#define PASSWORD_STA        "magicstar"  // for STA mode

// motor settings
#define RIGHT_MOTOR_PIN    4                     // pin of right motor (D2)
#define RIGHT_MOTOR_PIN    5                     // pin of right motor (D1)
#define RIGHT_MOTOR_SPEED   1023                  //speed for right motor (0-1023)
#define LEFT_MOTOR_SPEED    1023                  //speed for left motor (0-1023)

IPAddress local_ip(192, 168, 4, 1); //IP for AP mode
IPAddress gateway(192, 168, 4, 1); //IP for AP mode
IPAddress subnet(255, 255, 255, 0); //IP for AP mode
ESP8266WebServer server(80);
int car_mode = 0; // set car drive mode (0 = stop)

// motor driver
const int motor_pin = 5;
int power = 500;
// initialize
void setup() {
  Serial.begin(115200);
  Serial.println("NodeMCU Wifi Car");
  //pinMode(motor_pin, OUTPUT); //digital write
  
  boat_control();

  if (WIFI_MODE == 1) { // AP mode
    WiFi.softAP(SSID_AP, PASSWORD_AP);
    WiFi.softAPConfig(local_ip, gateway, subnet);
  } else { // STA mode
    WiFi.begin(SSID_STA, PASSWORD_STA);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
      Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected! IP: ");
    Serial.println(WiFi.localIP()); //the IP is needed for connection in STA mode
  }

  // setup web server to handle specific HTTP requests
  server.on("/", HTTP_GET, handle_OnConnect);
  server.on("/forward", HTTP_GET, handle_forward);
  server.on("/backward", HTTP_GET, handle_backward);
  server.on("/left", HTTP_GET, handle_left);
  server.on("/right", HTTP_GET, handle_right);
  server.on("/stop", HTTP_GET, handle_stop);
  server.onNotFound(handle_NotFound);

  //start server
  server.begin();
  Serial.println("NodeMCU web server started.");
}

// handle HTTP requests and control car
void loop() { 
  server.handleClient();
  boat_control();
}

// HTTP request: on connect
void handle_OnConnect() {
  car_mode = 0;
  Serial.println("Client connected");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: stop boat
void handle_stop() {
  car_mode = 0;
  Serial.println("Stopped");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: go forward
void handle_forward() {
  car_mode = 1;
  Serial.println("Go forward...");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: go backward
void handle_backward() {
  car_mode = 2;
  Serial.println("Go backward...");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: turn left
void handle_left() {
  car_mode = 3;
  Serial.println("Turn left...");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: turn right
void handle_right() {
  car_mode = 4;
  Serial.println("Turn right...");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: other
void handle_NotFound() {
  car_mode = 0;
  Serial.println("Page error");
  server.send(404, "text/plain", "Not found");
}

// control boat movement
void boat_control() {
  switch (car_mode) {
    case 0: // stop boat
      analogWrite(motor_pin, 0);
      yield();
      break;
    case 1: // go forward
      analogWrite(motor_pin, power);
      yield();
      break;
    case 2: // go backward
      analogWrite(motor_pin, 0);
      yield();
      break;
    case 3: // turn left
      if (power + 200 < 1024) power += 200;
      car_mode = 0;
      break;
    case 4: // turn right
      if (power - 200 > 0) power -= 200;
      car_mode = 0;
      break;
  }
}

// output HTML web page for user
String SendHTML() {
  String html = "<!DOCTYPE html>\n";
  html += "<html>\n";
  html += "<head>\n";
  html += "<title>NodeMCU Wifi boat</title>\n";
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
  html += "</head>\n";
  html += "<body>\n";
  html += "<div align=\"center\">\n";
  html += "<h1>NodeMCU Wifi boat</h1>\n";
  html += "<br>\n";
  html += "<form method=\"GET\">\n";
  html += "<input type=\"button\" value=\"Go forward\" onclick=\"window.location.href='/forward'\">\n";
  html += "<br><br>\n";
  html += "<input type=\"button\" value=\"power up\" onclick=\"window.location.href='/left'\">\n";
  html += "<br><br>\n";
  html += "<input type=\"button\" value=\"power down\" onclick=\"window.location.href='/right'\">\n";
  html += "<br><br>\n";
  html += "<input type=\"button\" value=\"boat stop\" onclick=\"window.location.href='/stop'\">\n";
  html += "</form>\n";
  html += "</div>\n";
  html += "</body>\n";
  html += "</html>\n";
  return html;
}
