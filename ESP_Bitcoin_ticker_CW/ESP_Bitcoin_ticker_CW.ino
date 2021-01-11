#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// WiFi Parameters
const char* ssid = "Access Point";
const char* password = "NbyCy4Q3RKhk";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
}

void loop() {
  // Check WiFi Status
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;  //Object of class HTTPClient

    // Connect to server
    http.begin("http://api.coindesk.com/v1/bpi/currentprice.json");
    int httpCode = http.GET();
    //Check the returning code                                                                  
    if (httpCode > 0) {
      
      // Parsing
      const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
      DynamicJsonBuffer jsonBuffer(bufferSize);
      JsonObject& root = jsonBuffer.parseObject(http.getString());
      
      // JSON Parameters
      JsonObject& bpi = root["bpi"];
      
      JsonObject& ap_time = root["time"];
      const char* time_updated = ap_time["updated"]; // "Jun 12, 2020 01:36:00 UTC"
      const char* time_updatedISO = ap_time["updatedISO"]; // "2020-06-12T01:36:00+00:00"
      const char* time_updateduk = ap_time["updateduk"]; // "Jun 12, 2020 at 02:36 BST"
      
      const char* disclaimer = root["disclaimer"]; // "This data was produced from the CoinDesk Bitcoin Price Index (USD). Non-USD currency data converted using hourly conversion rate from openexchangerates.org"
      const char* chartName = root["chartName"]; // "Bitcoin"

      JsonObject& bpi_USD = bpi["USD"];
      const char* bpi_USD_code = bpi_USD["code"]; // "USD"
      const char* bpi_USD_symbol = bpi_USD["symbol"]; // "$"
      const char* bpi_USD_rate = bpi_USD["rate"]; // "9,325.8542"
      const char* bpi_USD_description = bpi_USD["description"]; // "United States Dollar"
      float bpi_USD_rate_float = bpi_USD["rate_float"]; // 9325.8542
      
      JsonObject& bpi_GBP = bpi["GBP"];
      const char* bpi_GBP_code = bpi_GBP["code"]; // "GBP"
      const char* bpi_GBP_symbol = bpi_GBP["symbol"]; // "£"
      const char* bpi_GBP_rate = bpi_GBP["rate"]; // "7,354.6111"
      const char* bpi_GBP_description = bpi_GBP["description"]; // "British Pound Sterling"
      float bpi_GBP_rate_float = bpi_GBP["rate_float"]; // 7354.6111
      
      JsonObject& bpi_EUR = bpi["EUR"];
      const char* bpi_EUR_code = bpi_EUR["code"]; // "EUR"
      const char* bpi_EUR_symbol = bpi_EUR["symbol"]; // "€"
      const char* bpi_EUR_rate = bpi_EUR["rate"]; // "8,207.0781"
      const char* bpi_EUR_description = bpi_EUR["description"]; // "Euro"
      float bpi_EUR_rate_float = bpi_EUR["rate_float"]; // 8207.0781

      // Output to serial monitor
      Serial.print("BTC/USD: $"); 
      Serial.println(bpi_USD_rate);
    }
    http.end();   //Close connection
  }
  // Delay
  delay(60000);
}
