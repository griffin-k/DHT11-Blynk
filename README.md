# DHT11 with Blynk

## Overview
This project demonstrates how to use the DHT11 sensor with Blynk to monitor temperature and humidity. The ESP32 reads data from the DHT11 sensor and sends it to the Blynk app for real-time monitoring.

## Hardware Components
- **DHT11 Sensor:** Measures temperature and humidity.
- **ESP32:** Microcontroller to read sensor data and connect to Blynk.
- **Breadboard and Jumper Wires:** For circuit connections.

## Software Components
- **Blynk App:** For real-time monitoring on your smartphone.
- **Arduino IDE:** For writing and uploading code to ESP32.

## Features
- **Temperature Monitoring:** Real-time temperature data from DHT11.
- **Humidity Monitoring:** Real-time humidity data from DHT11.
- **Blynk Integration:** Data visualization and monitoring on the Blynk app.

## Project Setup
### Hardware Setup
1. Connect the DHT11 sensor to the ESP32:
   - VCC to 3.3V or 5V
   - GND to GND
   - Data to a digital pin (e.g., GPIO 4)

### Software Setup
1. Install the Arduino IDE from [Arduino](https://www.arduino.cc/en/software).
2. Install the Blynk library:
   - Open Arduino IDE
   - Go to `Sketch` > `Include Library` > `Manage Libraries`
   - Search for "Blynk" and install it
3. Install the DHT sensor library:
   - Open Arduino IDE
   - Go to `Sketch` > `Include Library` > `Manage Libraries`
   - Search for "DHT sensor library" and install it

### Blynk Setup
1. Download the Blynk app from the [App Store](https://apps.apple.com/us/app/blynk-iot-for-arduino-esp32/id6443443159) or [Google Play Store](https://play.google.com/store/apps/details?id=cc.blynk&hl=en&gl=US).
2. Create a new project and note the Auth Token sent to your email.
3. Add two Gauge widgets in the Blynk app for temperature and humidity.
4. Set the pin for temperature to V1 and humidity to V2.

### Arduino Code
1. Open Arduino IDE and create a new sketch.
2. Copy and paste the following code:

    ```cpp
    #define BLYNK_PRINT Serial
    #include <WiFi.h>
    #include <BlynkSimpleEsp32.h>
    #include <DHT.h>

    // Replace with your Blynk Auth Token
    char auth[] = "YourAuthToken";

    // Replace with your WiFi credentials
    char ssid[] = "YourNetworkName";
    char pass[] = "YourPassword";

    #define DHTPIN 4          // Digital pin connected to the DHT sensor
    #define DHTTYPE DHT11     // DHT 11

    DHT dht(DHTPIN, DHTTYPE);
    BlynkTimer timer;

    void sendSensorData() {
      float h = dht.readHumidity();
      float t = dht.readTemperature();

      if (isnan(h) || isnan(t)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
      }

      Blynk.virtualWrite(V1, t);
      Blynk.virtualWrite(V2, h);
    }

    void setup() {
      Serial.begin(115200);
      Blynk.begin(auth, ssid, pass);
      dht.begin();
      timer.setInterval(2000L, sendSensorData);
    }

    void loop() {
      Blynk.run();
      timer.run();
    }
    ```

3. Replace `YourAuthToken`, `YourNetworkName`, and `YourPassword` with your Blynk Auth Token and WiFi credentials.
4. Upload the code to your ESP32.

## Usage
1. Power your ESP32.
2. Open the Blynk app to monitor temperature and humidity in real-time.

## Contributing
Contributions are welcome! Please fork the repository and create a pull request with your changes.

## License
This project is licensed under the MIT License.
