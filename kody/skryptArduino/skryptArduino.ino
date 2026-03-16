#if defined(ESP32)
  #include <WiFiMulti.h>
  WiFiMulti wifiMulti;
  #define DEVICE "ESP32"
#elif defined(ESP8266)
  #include <ESP8266WiFiMulti.h>
  ESP8266WiFiMulti wifiMulti;
  #define DEVICE "ESP8266"
#endif

#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>
#include "DHT.h"

// ----------------------
// USTAWIENIA WIFI
// ----------------------
#define WIFI_SSID "*"
#define WIFI_PASSWORD "*"

// ----------------------
// USTAWIENIA INFLUXDB
// ----------------------
#define INFLUXDB_URL "-"
#define INFLUXDB_TOKEN "*"
#define INFLUXDB_ORG "*"
#define INFLUXDB_BUCKET "*"

// ----------------------
// USTAWIENIA DHT22
// ----------------------
#define DHTPIN 32
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ----------------------
// USTAWIENIA MQ-135
// ----------------------
#define MQ135_PIN 33     // ADC1 ESP32

// Time zone info
#define TZ_INFO "UTC1"

// Declare InfluxDB client instance with preconfigured InfluxCloud certificate
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);

// ---------------------------------------------------
// POMIAR I WYSYŁKA DANYCH
// ---------------------------------------------------
void handleDHT() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.println(" °C");

  Serial.print("Wilg.: ");
  Serial.print(hum);
  Serial.println(" %");

  Point dhtPoint("dht22"); // measurement name
  dhtPoint.addField("temperature", temp);
  dhtPoint.addField("humidity", hum);

  if (!client.writePoint(dhtPoint)) {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  } else {
    Serial.println("DHT data sent to InfluxDB successfully!");
  }
}

void handleMQ135() {
  int raw = analogRead(MQ135_PIN);

  Serial.print("MQ-135 raw: ");
  Serial.println(raw);

  Point mqPoint("mq135"); // measurement name
  mqPoint.addField("raw", raw);

  if (!client.writePoint(mqPoint)) {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  } else {
    Serial.println("MQ-135 data sent to InfluxDB successfully!");
  }
}

// ---------------------------------------------------
// SETUP
// ---------------------------------------------------
void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to WiFi");
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected! IP: ");
  Serial.println(WiFi.localIP());

  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

  if (client.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }

  // Inicjalizacja DHT
  dht.begin();
}

// ---------------------------------------------------
// LOOP
// ---------------------------------------------------
void loop() {
  handleDHT();
  handleMQ135();

  delay(5000); 
}
