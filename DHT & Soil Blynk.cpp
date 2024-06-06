#define BLYNK_TEMPLATE_ID "TMPL000000000"
#define BLYNK_TEMPLATE_NAME "DHT & Soil Blynk"
#define BLYNK_AUTH_TOKEN  "YourAuthToken"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>


#define DHTPIN   D5 
#define DHTTYPE DHT11


DHT dht(DHTPIN, DHTTYPE);


#define SOIL_MOISTURE_PIN A0


char ssid[] = "YourSSID";
char pass[] = "YourPassword";


char auth[] = BLYNK_AUTH_TOKEN;


BlynkTimer timer;

void sendSensorData()
{

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }


  Blynk.virtualWrite(V5, t); // V5 is the virtual pin for temperature
  Blynk.virtualWrite(V6, h); // V6 is the virtual pin for humidity
  Blynk.virtualWrite(V7, soilMoistureValue); // V7 is the virtual pin for soil moisture


  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" °C    Humidity: ");
  Serial.print(h);
  Serial.print(" %    Soil Moisture: ");
  Serial.println(soilMoistureValue);
}

void setup()
{

  Serial.begin(115200);

  dht.begin();


  WiFi.begin(ssid, pass);
  int wifiAttempts = 0;
  while (WiFi.status() != WL_CONNECTED && wifiAttempts < 20) {
    delay(1000);
    Serial.print(".");
    wifiAttempts++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi connected");
  } else {
    Serial.println("Failed to connect to WiFi");
    return;
  }


  Blynk.begin(auth, ssid, pass);


  timer.setInterval(2000L, sendSensorData);
}

void loop()
{

  Blynk.run();

  timer.run();
}
