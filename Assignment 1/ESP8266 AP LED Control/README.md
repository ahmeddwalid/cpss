# ESP8266 NodeMCU LED Control System

## Overview

This project implements a wireless LED control system using ESP8266 NodeMCU operating in Access Point (AP) mode. The system creates its own WiFi network and hosts a web server that allows users to control two LEDs through a responsive web interface.

![webpage.png](/home/ahmed/Documents/Koleya/7th%20Term/CPSS/Section/Assignments/Assignment%201/ESP8266%20AP%20LED%20Control/assets/screenshots/webpage.png)

## Hardware

### Components

- ESP8266 NodeMCU Development Board
- 2x LEDs (any color)
- 2x 330Ω Resistors
- Breadboard
- Jumper Wires
- USB Cable

### Pin Configuration

| Component | NodeMCU Pin |
| --------- | ----------- |
| LED 1     | D1          |
| LED 2     | D2          |
| GND       | GND         |

## Wiring

![circuit wiring.png](./assets/images/circuit%20wiring.png)

#### LEDs OFF

![LEDs OFF.jpg](./assets/images/LEDs%20OFF.jpg)

#### LEDs ON

![LEDs ON.jpg](./assets/images/LEDs%20ON.jpg)

## Network Configuration

### Software Requirements

1. PlatformIO

### Installation Steps

1. **Install PlatformIO:**

2. **Build and Upload:**
   
   ```bash
   pio run --target upload && pio run --target uploadfs
   ```

## Usage Instructions

### Connecting to the Access Point

1. Power on the NodeMCU
2. On your device:
   - Open WiFi settings
   - Look for network: **ESP8266 LED Control**
   - Connect using password: **Password 5ateer**
3. Open a web browser
4. Navigate to: **http://192.168.1.1**

### Controlling the LEDs

- Click **Turn ON** button to turn LED on (green status)
- Click **Turn OFF** button to turn LED off (red status)
- Use **Turn Both ON/OFF** buttons to control both LEDs simultaneously
- Status updates immediately on each button click.
- Each LED can be controlled independently

## Code Explanation

### Changing Access Point Credentials

```cpp
const char* ap_ssid = "YourCustomSSID";
const char* ap_password = "YourPassword";
```

You can also change the IP address:

```cpp
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
```

### Libraries and Dependencies

```cpp
#include <ESP8266WiFi.h>        // WiFi functionality for ESP8266
#include <ESP8266WebServer.h>   // Web server implementation
#include <LittleFS.h>          // File system for storing web assets
```

The code uses three main libraries:

- **ESP8266WiFi**: Handles WiFi operations including Access Point mode
- **ESP8266WebServer**: Creates and manages the HTTP web server
- **LittleFS**: Provides file system access for serving CSS and other static files

### Configuration Constants

```cpp
// Access Point Configuration
const char* ap_ssid = "ESP8266 LED Control";
const char* ap_password = "Password 5ateer";

// Static IP Configuration
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
```

These constants define the WiFi network settings. The ESP8266 creates its own network with the specified SSID and password using a static IP configuration.

### Hardware Pin Mapping

```cpp
const int LED1_PIN = 5;  // D1 on NodeMCU
const int LED2_PIN = 4;  // D2 on NodeMCU

bool led1_status = LOW;
bool led2_status = LOW;
```

The code maps NodeMCU pins D1 and D2 to GPIO pins 5 and 4 respectively. Boolean variables track the current state of each LED.

### Setup Function Flow

1. **Serial Communication**: Initializes debugging output at 115200 baud
2. **File System**: Mounts LittleFS and lists available files for debugging
3. **GPIO Configuration**: Sets LED pins as outputs and initializes them to OFF
4. **Access Point Setup**: Configures ESP8266 as a WiFi Access Point
5. **Route Registration**: Maps URL endpoints to handler functions
6. **Server Start**: Begins listening for HTTP requests on port 80

### Web Server Route Handlers

The code implements a RESTful API with the following endpoints:

```cpp
server.on("/", HTTP_GET, handle_root);              // Main page
server.on("/style.css", HTTP_GET, handle_style_css); // CSS file
server.on("/script.js", HTTP_GET, handle_script_js); // JavaScript file
server.on("/status", HTTP_GET, handle_status);      // JSON status
server.on("/led1/on", HTTP_GET, handle_led1_on);    // LED 1 ON
server.on("/led1/off", HTTP_GET, handle_led1_off);  // LED 1 OFF
// ... etc for each LED
```

Each LED control handler function:

1. Updates the corresponding LED status variable
2. Logs the action to Serial monitor
3. Returns JSON status of both LEDs

### Main Loop

```cpp
void loop() {
  server.handleClient();  // Process incoming HTTP requests

  // Update physical LED states based on status variables
  digitalWrite(LED1_PIN, led1_status ? HIGH : LOW);
  digitalWrite(LED2_PIN, led2_status ? HIGH : LOW);
}
```

The main loop continuously:

- Processes incoming web requests
- Updates the physical LED states based on the status variables

### Static File Serving with JSON API

The code uses a clean separation between frontend and backend:

**Static Files from LittleFS**:

```cpp
void handle_root() {
  if (LittleFS.exists("/index.html")) {
    File file = LittleFS.open("/index.html", "r");
    server.streamFile(file, "text/html");
    file.close();
  }
}
```

**JSON API Endpoints**: All LED control endpoints return JSON status instead of HTML:

```cpp
void handle_led1_on() {
  led1_status = HIGH;
  server.send(200, "application/json", get_status_json());
}

String get_status_json() {
  String json = "{";
  json += "\"led1\":" + String(led1_status ? "true" : "false") + ",";
  json += "\"led2\":" + String(led2_status ? "true" : "false");
  json += "}";
  return json;
}
```

**JavaScript Frontend**: The `script.js` file contains all client-side functionality that makes AJAX calls to update the UI without page reloads:

```javascript
function controlLED(ledNum, action) {
  fetch(`/led${ledNum}/${action}`)
    .then(response => response.json())
    .then(data => {
      updateStatus(1, data.led1);
      updateStatus(2, data.led2);
    });
}
```

**Static File Serving**: The server handles all static assets from LittleFS:

```cpp
server.on("/", HTTP_GET, handle_root);           // index.html
server.on("/style.css", HTTP_GET, handle_style_css);   // CSS file
server.on("/script.js", HTTP_GET, handle_script_js);   // JavaScript file
server.on("/favicon.ico", HTTP_GET, handle_favicon);   // Favicon ICO
server.on("/favicon.png", HTTP_GET, handle_favicon_png); // Favicon PNG
```

## API Endpoints

### GET /

Returns the main HTML interface for controlling the LEDs.

**Response:** HTML page with interactive LED controls

### GET /style.css

Returns the CSS stylesheet for the web interface.

**Response:** CSS file with styling and layout

### GET /script.js

Returns the JavaScript file containing client-side functionality.

**Response:** JavaScript file with AJAX functions and UI updates

### GET /favicon.ico

Returns the website favicon icon in ICO format.

**Response:** ICO file for browser tab icon

### GET /favicon.png

Returns the website favicon icon in PNG format.

**Response:** PNG file for browser tab icon

### GET /status

Returns the current status of both LEDs in JSON format.

**Response:** `{"led1": true/false, "led2": true/false}`

### GET /led1/on

Turns LED 1 ON.

**Response:** JSON status `{"led1": true, "led2": current_status}`

### GET /led1/off

Turns LED 1 OFF.

**Response:** JSON status `{"led1": false, "led2": current_status}`

### GET /led2/on

Turns LED 2 ON.

**Response:** JSON status `{"led1": current_status, "led2": true}`

### GET /led2/off

Turns LED 2 OFF.

**Response:** JSON status `{"led1": current_status, "led2": false}`

### GET /both/on

Turns both LEDs ON.

**Response:** JSON status `{"led1": true, "led2": true}`

### GET /both/off

Turns both LEDs OFF.

**Response:** JSON status `{"led1": false, "led2": false}`

This architecture provides:

- **Faster UI updates**: No full page reloads
- **Better user experience**: Smooth interactions
- **Cleaner code separation**: HTML/CSS/JS in files, C++ handles hardware
- **Smaller memory footprint**: No HTML strings in program memory

### Error Handling

The code includes several error handling mechanisms:

- **File System**: Checks if LittleFS mounts successfully
- **Access Point**: Verifies AP creation status
- **404 Handler**: Provides informative error messages for invalid URLs
- **File Existence**: Checks if CSS file exists before serving

### Serial Debugging

Serial.println() statements provide debugging information:

- System initialization status
- File system contents
- Network configuration details
- Incoming request logging
- LED state changes

## References & Acknowledgments

- [PlatformIO Documentation](https://docs.platformio.org/)
- [ESP8266WiFi Library](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html)
- [ESP8266WebServer Library](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer)
- [LittleFS Documentation](https://arduino-esp8266.readthedocs.io/en/latest/filesystem.html)
- [NodeMCU GPIO Pin Reference](https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/)
- [Favicon created by Smashicons - Flaticon](https://www.flaticon.com/free-icons/led-lighting)
