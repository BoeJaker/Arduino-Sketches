/*
 *  This sketch demonstrates how to scan WiFi networks.
 *  The API is almost the same as with the WiFi Shield library,
 *  the most obvious difference being the different file you need to include:
 */
#include "WiFi.h"
#define LILYGO_WATCH_2020_V1                  // To use T-Watch2020 , please uncomment this line
#include <LilyGoWatch.h>

//TFT Color Definitions
#define TFT_AQUA  0x04FF
#define TFT_GRAY  0x8410
#define ERROR_COLOR 0xF000
#define TEXT_COLOR 0x4F40

TFT_eSPI *tft = nullptr;
TTGOClass *ttgo = nullptr;

void setup()
{
  
    Serial.begin(115200);
    ttgo = TTGOClass::getWatch();
    ttgo->begin();
    ttgo->openBL();
    tft = ttgo->tft;
    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    tft->fillRect(0, 0, 240, 240, TFT_BLACK);
    Serial.println("Setup done");
}

void loop()
{
    tft->setTextColor(TFT_GREEN);
    Serial.println("scan start");

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        tft->drawString("Networks Found", 60, 1, 2);
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            if (WiFi.encryptionType(i) == WIFI_AUTH_OPEN){
              tft->setTextColor(TFT_RED);
            }
            tft->fillRect(0, 20*(i+1), 240, 18, TFT_BLACK);
            tft->drawString(WiFi.SSID(i)+" "+String(WiFi.RSSI(i))+" "+String((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*"), 10, 20*(i+1), 2);
            tft->drawLine(0,20*(i+1)+18,240+int(WiFi.RSSI(i)),20*(i+1)+18,TFT_WHITE);
            tft->setTextColor(TFT_GREEN);
            delay(10);
            
        }
    }
    Serial.println("");

    // Wait a bit before scanning again
    delay(500);
}
