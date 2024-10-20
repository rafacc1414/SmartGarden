#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>

#include <DHT11.h>

#include "config.h"  // Replace with your network data
#include "ESP8266_Utils.hpp"
#include "ESP8266_Utils_OTA.hpp"
#include "ESP8266_Utils_mDNS.hpp"
#include "ESP8266_Utils_ADS.hpp"

#define ANALOGPIN A0  // Analog Pin
#define DHTPIN D4     // Digital Pin connected to the DHT sensor
#define RELAY_PIN D7  // Relay Pin D7 for water motor

// Analag Sensors
#define SOIL_MOSTURE_STEEL_SENSOR 0
#define SOIL_MOSTURE_SENSOR 1
#define LDR 3

bool static_ip = true;

DHT11 dht11(DHTPIN);

Adafruit_ADS1115 ads;
const float multiplier = 0.1875F;

void setup() {

  Serial.begin(9600);

  ConnectWiFi_STA(static_ip);

  InitOTA();

  InitMDNS();

  // ADS
  ads.setGain(GAIN_ONE);
  ads.begin();

  pinMode(RELAY_PIN, OUTPUT);     // Initialize the relay pin as output
  digitalWrite(RELAY_PIN, HIGH);  // Initially turn off the relay (assuming active-low relay)
}

void loop() {
  ArduinoOTA.handle();

  SensorMessage msg{};

  // Read Temperature and humidity
  {
    int temperature, humidity;
    int result = dht11.readTemperatureHumidity(temperature, humidity);
    if (result == 0) {
      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.print(" °C\tHumidity: ");
      Serial.print(humidity);
      Serial.println(" %");
    } else {
      // Print error message based on the error code.
      Serial.println(DHT11::getErrorString(result));
    }

    // Store data
    msg.air_temperature = temperature;
    msg.air_humidity = humidity;
  }

  // Read Analog Sensors
  {
    int16_t values[4];
    if (!ads_read_all(&ads, values))
      Serial.println("ERROR: ADS115 could not read Analog Inputs");

    // Read Light (LDR)
    int luminosity = values[LDR];

    // Map the luminosity to a percentage
    int luminosity_percentage = map(luminosity, 600, 24000, 0, 100);

    // Print the mapped percentage
    Serial.print("Mapped Luminosity Percentage: ");
    Serial.println(100 - luminosity_percentage);

    // Soil Mosture steel alone
    // 13253 Seco
    // 8860 Humedad

    // Ideal tras riego ambos sensores juntos:
    //   Soil mosture steel: 18500
    //   Soil mosture: 7400
    int soilMoistureSteelValue = values[SOIL_MOSTURE_STEEL_SENSOR];
    int soil_moistureSteel_percentaje = map(soilMoistureSteelValue, 6000, 25000, 0, 100);

    int soilMoistureValue = values[SOIL_MOSTURE_SENSOR];
    int soil_moisture_percentaje = map(soilMoistureValue, 1000, 14000, 0, 100);

    Serial.print("SOIL_MOISTURE_STEEL_SENSOR: ");
    Serial.print(soil_moistureSteel_percentaje);
    Serial.println("%");

    Serial.print("SOIL_MOISTURE_SENSOR: ");
    Serial.print(soil_moisture_percentaje);
    Serial.println("%");

    delay(2000);


    // Store data
    msg.luminosity = luminosity;
    msg.soil_moisture = soilMoistureValue;
    msg.soil_moisture_steel = soilMoistureSteelValue;
  }

  // Send Data To Server
  SendData2Server(&msg);
}

void BumpWater() {
  digitalWrite(RELAY_PIN, LOW);   // Relay on
  delay(2000);                    // Pump runs for 2 seconds
  digitalWrite(RELAY_PIN, HIGH);  // Relay off
}

void SendData2Server(const SensorMessage *msg) {

  if (WiFi.status() != WL_CONNECTED)
    return;

  WiFiClient wifiClient;
  HTTPClient http;

  // Iniciar la conexión al servidor
  http.begin(wifiClient, serverUrl);
  http.addHeader("Content-Type", "application/json");  // Cabecera del tipo de contenido

  // Crear el JSON con los datos
  String jsonPayload = "{\"soil_moisture\":" + String(msg->soil_moisture) + ", \"soil_moisture_steel\":" + String(msg->soil_moisture_steel) + ", \"luminosity\":" + String(msg->luminosity) + ", \"temperature\":" + String(msg->air_temperature) + ", \"humidity\":" + String(msg->air_humidity) + "}";

  Serial.println(jsonPayload);

  // Enviar la solicitud POST
  int httpResponseCode = http.POST(jsonPayload);

  // Imprimir la respuesta del servidor
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("Respuesta del servidor: " + response);
  } else {
    Serial.println("Error en la conexión: " + String(httpResponseCode));
  }

  // Finalizar la conexión
  http.end();
}
