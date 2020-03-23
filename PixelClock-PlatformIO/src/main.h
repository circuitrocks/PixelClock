#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <Ticker.h>
#include <ArduinoOTA.h>
#include <WiFiUdp.h>
#include <ESPmDNS.h>

// Choose a log level to show app specific log output 
#define MYLOG_LOG_LEVEL MYLOG_LOG_LEVEL_VERBOSE

#include "myLog.h"

#include <NeoPixelBus.h>

void initWiFi(void);
extern WiFiMulti wifiMulti;
extern bool connStatusChanged;

void startOTA(void);
extern boolean otaStarted;

/** WiFiUDP class for NTP server */
extern WiFiUDP ntpUDP;
bool initNTP(void);
void tryGetTime(void);
extern struct tm timeinfo;

void initClock(void);
void updateClock(void);
void setNumber(uint8_t value, uint8_t digit);
void setDay(uint8_t day);
void setColon(void);
void setBrightness(uint8_t newBrightness);
