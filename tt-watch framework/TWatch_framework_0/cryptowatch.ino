//#include "config.h"
//#include <WiFi.h>
//
//#include <WiFiClientSecure.h>
//#include "CoinMarketCapApi.h"
//#include "alert.h"
//#include "info.h"
//#include "btc_icon.h"
//#include "btc_icon2.h"
//
//#define APIKEY "fe231f8e-6d40-49c8-a22b-231123a7543a"
//
//WiFiClientSecure client;
//CoinMarketCapApi api(client, APIKEY);
//
//// CoinMarketCap's limit is "no more than 10 per minute"
//// Make sure to factor in if you are requesting more than one coin.
//unsigned long api_mtbs = 60000; //mean time between api requests
//unsigned long api_due_time = 0;
//int16_t x, y;
//
//TFT_eSPI *tft = nullptr;
//TTGOClass *ttgo = nullptr;
//
//AXP20X_Class *power;
//bool irq = false;
////---------------------------------------//
//
//// edit this for your network
//#define wifi_ssid "BTHub6-W7TF"
//#define wifi_password "NbyCy4Q3RKhk"
//
////---------------------------------------//
//#define TFT_AQUA  0x04FF
//#define TFT_GRAY  0x8410
//unsigned long last_active(){
//  la = millis();
//}
//
//
//
//void printTickerData(String ticker)
//{
//    Serial.println("---------------------------------");
//    Serial.println("Getting ticker data for " + ticker);
//
//
//    //For the new API, you can use the currency ID or abbreviated name, such as
//    //Bitcoin, you can view the letter after Circulating Supply at https://coinmarketcap.com/, it is BTC
//
//    CMCTickerResponse response = api.GetTickerInfo(ticker, "USD");
//    if (response.error == "") {
//        Serial.print("ID: ");
//        Serial.println(response.id);
//        Serial.print("Name: ");
//        Serial.println(response.name);
//        Serial.print("Symbol: ");
//        Serial.println(response.symbol);
//
//        Serial.print("Rank: ");
//        Serial.println(response.cmc_rank);
//
//        Serial.print("Price: ");
//        Serial.println(response.price);
//
//        Serial.print("24h Volume: ");
//        Serial.println(response.volume_24h);
//        Serial.print("Market Cap: ");
//        Serial.println(response.market_cap);
//
//        Serial.print("Circulating Supply: ");
//        Serial.println(response.circulating_supply);
//        Serial.print("Total Supply: ");
//        Serial.println(response.total_supply);
//
//        Serial.print("Percent Change 1h: ");
//        Serial.println(response.percent_change_1h);
//        Serial.print("Percent Change 24h: ");
//        Serial.println(response.percent_change_24h);
//        Serial.print("Percent Change 7d: ");
//        Serial.println(response.percent_change_7d);
//        Serial.print("Last Updated: ");
//        Serial.println(response.last_updated);
//
//        tft->setTextColor(TFT_GRAY);
//        tft->drawString(response.symbol, 100, 11, 2);
//        tft->drawString("/USD", 125, 11, 2);
//
//        tft->setTextColor(TFT_WHITE);
//
//        tft->fillRect(0, 120, 300, 38, TFT_BLACK); //price
//        tft->fillRect(185, 40, 55, 20, TFT_BLACK); //rank
//
//        tft->fillRect(100, 60, 100, 20, TFT_BLACK); //Volume
//        tft->fillRect( 95, 70, 100, 20, TFT_BLACK); //Marketcap
//
//
//        tft->setTextColor(TFT_YELLOW);
//
//        if (response.percent_change_1h < 0) {
//            tft->setTextColor(TFT_RED);
//        }
//        if (response.percent_change_1h > 0) {
//            tft->setTextColor(TFT_GREEN);
//        }
//
//
//        tft->drawString("$", 10, 100, 6);
//        tft->drawString(String(response.price).c_str(), 30, 120, 6);
//
//        tft->setTextColor(TFT_GRAY);
//        tft->drawString("Rank:", 105, 40, 4);
//        tft->drawString(String(response.cmc_rank).c_str(), 175, 40, 4);
//        tft->drawString(String(response.volume_24h).c_str(), 100, 60, 2);
//        tft->drawString(String(response.market_cap).c_str(), 95, 75, 2);
//
//        tft->drawLine(11, 166, 229, 166, TFT_GRAY);
//
//        // hours change
//        tft->fillRect(10, 200, 210, 25, TFT_BLACK);
//        tft->setTextColor(TFT_YELLOW);
//
//        if (response.percent_change_1h < 0) {
//            tft->setTextColor(TFT_RED);
//        }
//        if (response.percent_change_1h > 0) {
//            tft->setTextColor(TFT_GREEN);
//        }
//        tft->drawString("% Delta 1h:", 11, 200, 4);
//        tft->drawString(String(response.percent_change_1h).c_str(), 156, 200, 4);
//        delay(20000);
//
//
//        // 24 hours change
//        tft->fillRect(10, 200, 210, 25, TFT_BLACK);
//        tft->setTextColor(TFT_YELLOW);
//
//        if (response.percent_change_24h < 0) {
//            tft->setTextColor(TFT_RED);
//        }
//        if (response.percent_change_24h > 0) {
//            tft->setTextColor(TFT_GREEN);
//        }
//        tft->drawString("% Delta 24h:", 11, 200, 4);
//        tft->drawString(String(response.percent_change_24h).c_str(), 156, 200, 4);
//        delay(20000);
//
//
//        // 7d hours change
//        tft->fillRect(10, 200, 210, 25, TFT_BLACK);
//        tft->setTextColor(TFT_YELLOW);
//
//        if (response.percent_change_7d < 0) {
//            tft->setTextColor(TFT_RED);
//        }
//        if (response.percent_change_7d > 0) {
//            tft->setTextColor(TFT_GREEN);
//        }
//        tft->drawString("% Delta 7d:", 11, 200, 4);
//        tft->drawString(String(response.percent_change_7d).c_str(), 156, 200, 4);
//        delay(20000);
//
//
//    }
//
//    else {
//        Serial.print("Error getting data: ");
//        Serial.println(response.error);
//        tft->fillRect(200, 2, 40, 32, TFT_BLACK); //wifi RSSI and alert
//        tft->pushImage(203, 2, alertWidth, alertHeight, alert);
//    }
//    Serial.println("---------------------------------");
//
//
//
//}
//
//float RSSI = 0.0;
//unsigned long la;
//
//void bitcoin()
//{
//  
//    uint16_t time = millis();
//    time = millis() - time;
//    tft->fillScreen(TFT_BLACK);
//    tft->setSwapBytes(true);
//    tft->pushImage(75, 75, btc_icon_width, btc_icon_height, btc_icon);
//    delay(3000);
//
//    // Starup
//    tft->fillScreen(TFT_BLACK);
//    Serial.print("Connecting to ");
//    tft->drawString("Connecting to ", 15, 10, 2);;
//    Serial.println(wifi_ssid);
//    tft->drawString(wifi_ssid, 15, 25, 2);
//    tft->pushImage(200, 2, infoWidth, infoHeight, info);
//    delay(1000);
//
//    WiFi.begin(wifi_ssid, wifi_password);
//
//    while (WiFi.status() != WL_CONNECTED) {
//        delay(500);
//        Serial.print(".");
//    }
//
//    Serial.println("");
//    Serial.println("WiFi connected");
//    tft->setTextColor(TFT_GREEN);
//    tft->drawString("WiFi connected", 15, 40, 2);
//    tft->setTextColor(TFT_WHITE);
//    Serial.println("IP address: ");
//    Serial.println(WiFi.localIP());
//    delay(1000);
//    tft->fillRect(0, 0, 240, 135, TFT_BLACK);
//
//    tft->pushImage(0, 0, btc_icon2_width, btc_icon2_height, btc_icon2);
//
//    unsigned long timeNow = millis();
//      if ((timeNow > api_due_time))  {
//        // int signal bars
//        Serial.println(timeNow);
//        Serial.println(la);
//        Serial.println(timeout);
//        Serial.print(WiFi.RSSI());
//        tft->fillRect(200, 2, 40, 32, TFT_BLACK); //wifi RSSI and alert
//
//
//        int bars;
//        RSSI = WiFi.RSSI();
//
//        if (RSSI >= -55) {
//            bars = 5;
//            Serial.println(" 5 bars");
//        } else if (RSSI < -55 & RSSI >= -65) {
//            bars = 4;
//            Serial.println(" 4 bars");
//        } else if (RSSI < -65 & RSSI >= -70) {
//            bars = 3;
//            Serial.println(" 3 bars");
//        } else if (RSSI < -70 & RSSI >= -78) {
//            bars = 2;
//            Serial.println(" 2 bars");
//        } else if (RSSI < -78 & RSSI >= -82) {
//            bars = 1;
//            Serial.println(" 1 bars");
//        } else {
//            bars = 0;
//            Serial.println(" 0 bars");
//        }
//
//        // signal bars
//        for (int b = 0; b <= bars; b++) {
//            tft->fillRect(202 + (b * 6), 23 - (b * 4), 5, b * 4, TFT_GRAY);
//        }
//        printTickerData("BTC");
//        api_due_time = timeNow + api_mtbs;
//    }   
//}