/*
   Copyright (c) 2015, Majenko Technologies
   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:

 * * Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.

 * * Redistributions in binary form must reproduce the above copyright notice, this
     list of conditions and the following disclaimer in the documentation and/or
     other materials provided with the distribution.

 * * Neither the name of Majenko Technologies nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
   ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>

#ifndef STASSID
#define STASSID "Access Point"
#define STAPSK  "NbyCy4Q3RKhk"
#endif

const char *ssid = STASSID;
const char *password = STAPSK;
const char* price;
int lastprice[39];

ESP8266WebServer server(80);

const int led = 13;

void handleRoot() {
  digitalWrite(led, 1);
  char temp[400];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  snprintf(temp, 400,

           "<html>\
  <head>\
    <meta http-equiv='refresh' content='5'/>\
    <title>ESP8266 Demo</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Hello from ESP8266!</h1>\
    <p>Uptime: %02d:%02d:%02d</p>\
    <p>Bitcoin Price: $ %s</p>\
    <img src=\"/test.svg\" />\
  </body>\
</html>",

           hr, min % 60, sec % 60, price
          );
  server.send(200, "text/html", temp);
  digitalWrite(led, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void drawGraph() {
  String out;
  out.reserve(2600);
  char temp[70];
  out += "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"400\" height=\"150\">\n";
  out += "<rect width=\"400\" height=\"150\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n";
  out += "<g stroke=\"black\">\n";
  int y = rand() % 130;
  int c = 0;
  for (int x = 10; x < 390; x += 10) {
    int y2 = rand() % 130;
    Serial.println(String(x) + " " + String(map(lastprice[x / 10], (lastprice[0] - 1000), lastprice[0] + 1000, 10, 140)) + " " + String( x + 10) + " " + String(map(lastprice[(x / 10) + 1], (lastprice[0] - 1000), lastprice[0] + 1000, 10, 140)));
    sprintf(temp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"1\" />\n", x, map(lastprice[x / 10], (lastprice[0] - 1000), lastprice[0] + 1000, 10, 140), x + 10, map(lastprice[(x / 10) + 1], (lastprice[0] - 1000), lastprice[0] + 1000, 10, 140));
    //    sprintf(temp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"1\" />\n", x, 140 - y , x + 10, 140 - y2);
    out += temp;
    //    y = y2;
  }
  out += "</g>\n</svg>\n";

  server.send(200, "image/svg+xml", out);
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/test.svg", drawGraph);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
  for (int i = 0; i >= 39; i++) {
    lastprice[i] = 1000;
  }

}

void loop(void) {
  int x = 1;
  if (x >= 39) {
    x = 0;
  }
  server.handleClient();
  MDNS.update();

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

      int rf = int(bpi_USD_rate_float);
      if (lastprice[x - 1] != rf ) {
        lastprice[x] = rf;
        x++;
      }
      price = bpi_USD_rate;

      delay(5000);
    }
    http.end();   //Close connection
  }
}
