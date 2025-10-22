/*
 * ESP8266 NodeMCU - Wireless Access Point Mode
 * Two LED Control via Web Server with LittleFS
 * Author: Ahmed Walid
 * Date: October, 2025
 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>

// Access Point Configuration
const char* ap_ssid = "ESP8266 LED Control";
const char* ap_password = "Password 5ateer";

// Static IP Configuration
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// Create a Web Server on port 80
ESP8266WebServer server(80);

// LED Pin Definitions
const int LED1_PIN = 5;  // D1 on NodeMCU
const int LED2_PIN = 4;  // D2 on NodeMCU

// LED Status Variables
bool led1_status = LOW;
bool led2_status = LOW;

// Function Prototypes
void handle_root();
void handle_style_css();
void handle_script_js();
void handle_favicon();
void handle_favicon_png();
void handle_status();
void handle_led1_on();
void handle_led1_off();
void handle_led2_on();
void handle_led2_off();
void handle_both_on();
void handle_both_off();
void handle_not_found();
String get_status_json();

void setup() {
  // Initialize Serial Communication
  Serial.begin(115200);
  delay(100);
  Serial.println("\n\n=== ESP8266 AP Mode Controling 2 LEDs ===");
  
  // Initialize LittleFS
  Serial.println("Mounting LittleFS...");
  if (!LittleFS.begin()) {
    Serial.println("Failed to mount LittleFS!");
    Serial.println("Please upload filesystem image using: pio run -t uploadfs");
  } else {
    Serial.println("LittleFS mounted successfully!");
    
    // List files in LittleFS (for debugging)
    Dir dir = LittleFS.openDir("/");
    Serial.println("Files in LittleFS:");
    while (dir.next()) {
      Serial.print("  ");
      Serial.print(dir.fileName());
      Serial.print(" - ");
      Serial.print(dir.fileSize());
      Serial.println(" bytes");
    }
  }
  
  // Configure LED Pins as Output
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  
  // Initialize LEDs to OFF state
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  
  // Configure ESP8266 as Access Point
  Serial.println("\nConfiguring Access Point...");
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  
  bool ap_status = WiFi.softAP(ap_ssid, ap_password);
  
  if (ap_status) {
    Serial.println("Access Point Created Successfully!");
    Serial.print("SSID: ");
    Serial.println(ap_ssid);
    Serial.print("Password: ");
    Serial.println(ap_password);
    Serial.print("AP IP Address: ");
    Serial.println(WiFi.softAPIP());
  } else {
    Serial.println("Failed to create Access Point!");
  }
  
  // Configure Web Server Routes
  server.on("/", HTTP_GET, handle_root);
  server.on("/style.css", HTTP_GET, handle_style_css);
  server.on("/script.js", HTTP_GET, handle_script_js);
  server.on("/favicon.ico", HTTP_GET, handle_favicon);
  server.on("/favicon.png", HTTP_GET, handle_favicon_png);
  server.on("/status", HTTP_GET, handle_status);
  
  // LED control endpoints returns JSON
  server.on("/led1/on", HTTP_GET, handle_led1_on);
  server.on("/led1/off", HTTP_GET, handle_led1_off);
  server.on("/led2/on", HTTP_GET, handle_led2_on);
  server.on("/led2/off", HTTP_GET, handle_led2_off);
  server.on("/both/on", HTTP_GET, handle_both_on);
  server.on("/both/off", HTTP_GET, handle_both_off);
  
  // Fallback for any other request
  server.onNotFound(handle_not_found);
  
  // Start Web Server
  server.begin();
  Serial.println("\nHTTP Web Server Started");
  Serial.println("Connect to WiFi and navigate to: http://192.168.1.1");
  Serial.println("==========================================\n");
}

void loop() {
  // Handle incoming client requests
  server.handleClient();
  
  // Update LED states
  digitalWrite(LED1_PIN, led1_status ? HIGH : LOW);
  digitalWrite(LED2_PIN, led2_status ? HIGH : LOW);
}

// ============================================================
// Route Handlers
// ============================================================

void handle_root() {
  Serial.println("Request: GET /");
  if (LittleFS.exists("/index.html")) {
    File file = LittleFS.open("/index.html", "r");
    server.streamFile(file, "text/html");
    file.close();
  } else {
    server.send(404, "text/plain", "index.html not found");
  }
}

void handle_style_css() {
  Serial.println("Request: GET /style.css");
  if (LittleFS.exists("/style.css")) {
    File file = LittleFS.open("/style.css", "r");
    server.streamFile(file, "text/css");
    file.close();
  } else {
    server.send(404, "text/plain", "style.css not found");
  }
}

void handle_script_js() {
  Serial.println("Request: GET /script.js");
  if (LittleFS.exists("/script.js")) {
    File file = LittleFS.open("/script.js", "r");
    server.streamFile(file, "application/javascript");
    file.close();
  } else {
    server.send(404, "text/plain", "script.js not found");
  }
}

void handle_favicon() {
  Serial.println("Request: GET /favicon.ico");
  if (LittleFS.exists("/favicon.ico")) {
    File file = LittleFS.open("/favicon.ico", "r");
    server.sendHeader("Cache-Control", "public, max-age=86400");
    server.streamFile(file, "image/x-icon");
    file.close();
  } else {
    server.send(404, "text/plain", "favicon.ico not found");
  }
}

void handle_favicon_png() {
  Serial.println("Request: GET /favicon.png");
  if (LittleFS.exists("/favicon.png")) {
    File file = LittleFS.open("/favicon.png", "r");
    server.sendHeader("Cache-Control", "public, max-age=86400");
    server.streamFile(file, "image/png");
    file.close();
  } else {
    server.send(404, "text/plain", "favicon.png not found");
  }
}

void handle_status() {
  Serial.println("Request: GET /status");
  server.send(200, "application/json", get_status_json());
}

void handle_led1_on() {
  led1_status = HIGH;
  Serial.println("LED 1 → ON");
  server.send(200, "application/json", get_status_json());
}

void handle_led1_off() {
  led1_status = LOW;
  Serial.println("LED 1 → OFF");
  server.send(200, "application/json", get_status_json());
}

void handle_led2_on() {
  led2_status = HIGH;
  Serial.println("LED 2 → ON");
  server.send(200, "application/json", get_status_json());
}

void handle_led2_off() {
  led2_status = LOW;
  Serial.println("LED 2 → OFF");
  server.send(200, "application/json", get_status_json());
}

void handle_both_on() {
  led1_status = HIGH;
  led2_status = HIGH;
  Serial.println("Both LEDs → ON");
  server.send(200, "application/json", get_status_json());
}

void handle_both_off() {
  led1_status = LOW;
  led2_status = LOW;
  Serial.println("Both LEDs → OFF");
  server.send(200, "application/json", get_status_json());
}

void handle_not_found() {
  String message = "404: Not Found\n\n";
  message += "URI: " + server.uri() + "\n";
  message += "Method: " + String((server.method() == HTTP_GET) ? "GET" : "POST") + "\n";
  Serial.println("404 - " + server.uri());
  server.send(404, "text/plain", message);
}

String get_status_json() {
  String json = "{";
  json += "\"led1\":" + String(led1_status ? "true" : "false") + ",";
  json += "\"led2\":" + String(led2_status ? "true" : "false");
  json += "}";
  return json;
}
