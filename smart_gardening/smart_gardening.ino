#include <Adafruit_SGP30.h>
#include <DHT.h>
#include <WiFiNINA.h>

#include "wifi_connection.h"

const uint8_t soilMoisture01Pin = A1;
const uint8_t soilMoisture02Pin = A2;
const uint8_t soilMoisture03Pin = A3;
const uint8_t tempHumidityPin = 2;

DHT dht(tempHumidityPin, DHT11);
Adafruit_SGP30 sgp;

/* return absolute humidity [mg/m^3] with approximation formula
* @param temperature [°C]
* @param humidity [%RH]
*/
uint32_t getAbsoluteHumidity(float temperature, float humidity) {
    // approximation formula from Sensirion SGP30 Driver Integration chapter 3.15
    const float absoluteHumidity = 216.7f * ((humidity / 100.0f) * 6.112f * exp((17.62f * temperature) / (243.12f + temperature)) / (273.15f + temperature)); // [g/m^3]
    const uint32_t absoluteHumidityScaled = static_cast<uint32_t>(1000.0f * absoluteHumidity); // [mg/m^3]
    return absoluteHumidityScaled;
}

void setup()
{
  Serial.begin(9600);

  pinMode(soilMoisture01Pin, INPUT);
  pinMode(soilMoisture02Pin, INPUT);
  pinMode(soilMoisture03Pin, INPUT);
  dht.begin();
   if (!sgp.begin()) {
    Serial.println("CO2 sensor not found :(");
  }

  connectToWiFi();
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connection lost, trying to reconnect");
    connectToWiFi();
  }
  float humidity = dht.readHumidity();
  float tempCelsius = dht.readTemperature();

  int soilMoisture01 = analogRead(soilMoisture01Pin);
  int soilMoisture02 = analogRead(soilMoisture02Pin);
  int soilMoisture03 = analogRead(soilMoisture03Pin);

  sgp.setHumidity(getAbsoluteHumidity(tempCelsius, humidity));

  sendSensorData("airHumidity01", humidity);
  sendSensorData("airTemp01", tempCelsius);

  sendSensorData("soilMoisture01", soilMoisture01);
  sendSensorData("soilMoisture02", soilMoisture02);
  sendSensorData("soilMoisture03", soilMoisture03);

  if (sgp.IAQmeasure()) {
    sendSensorData("airQuality01", sgp.eCO2);
    Serial.print("CO2: ");
    Serial.println(sgp.eCO2);
  } else {
    Serial.println("Measurement failed");
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%\tTemperature: ");
  Serial.print(tempCelsius);
  Serial.print(" *C\tSoil 1: ");
  Serial.print(soilMoisture01);
  Serial.print("\tSoil 2: ");
  Serial.print(soilMoisture02);
  Serial.print("\tSoil 3: ");
  Serial.print(soilMoisture03);
  Serial.println();

  delay(10000);
}
