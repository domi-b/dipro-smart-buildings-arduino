#include <WiFiNINA.h>

// login.h is excluded from the repository as it defines username and password for the wifi
#include "login.h"

WiFiClient client;

void sendSensorData(String sensorId, float value) {
  if (!client.connected() && !client.connectSSL("dipro-h22-dburger.enterpriselab.ch", 443)) {
    Serial.println("connection failed");
    return;
  }

  Serial.println("connected");

  String json = String("{\"sensor_id\": \"") + sensorId + String("\", \"value\": ") + value + String("}");

  client.println("POST /sensors HTTP/1.1");
  client.println("Host: dipro-h22-dburger.enterpriselab.ch");
  client.println("Connection: keep-alive");
  client.println("Content-Type: application/json");
  client.print("Content-Length: ");
  client.println(json.length());
  client.println();
  client.println(json);

  delay(500);

  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
}

void connectToWiFi() {
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);
    status = WiFi.beginEnterprise(ssid, username, password);
    delay(2000);
  }
}
