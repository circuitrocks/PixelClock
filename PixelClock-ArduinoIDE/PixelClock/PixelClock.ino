#include "main.h"

uint8_t noAPfound = 0;

void setup()
{
  Serial.begin(115200);

  initWiFi();

  initNTP();

  initClock();
}

void loop()
{
  uint8_t multiResult = wifiMulti.run(15000U);
  if (multiResult != WL_CONNECTED)
  {
    if (multiResult == WL_NO_SSID_AVAIL)
    {
      noAPfound++;
      if (noAPfound >= 50)
      {
        myLog_d("WiFi not connected! Error %d", multiResult);
        myLog_e("No WiFi AP found");
        noAPfound = 0;
      }
    }
    else
    {
      // retry in a second
      delay(1000);
    }
  }
  else
  {
    if (connStatusChanged)
    {
      startOTA();
      connStatusChanged = false;
    }

    ArduinoOTA.handle();

    if (otaStarted)
    {
      return;
    }
  }

  // Update the time
  time_t now;
  time(&now);					  // get time (as epoch)
  localtime_r(&now, &timeinfo); // update tm struct with current time

  // DateTime nowTime = rtc.now();

  setDay(timeinfo.tm_wday == 0 ? 7 : timeinfo.tm_wday);

  uint8_t nowHour = timeinfo.tm_hour;
  uint8_t nowMinute = timeinfo.tm_min;
  setNumber(nowHour / 10, 0);
  setNumber(nowHour - (nowHour / 10 * 10), 1);
  setNumber(nowMinute / 10, 2);
  setNumber(nowMinute - (nowMinute / 10 * 10), 3);

  if (nowHour >= 22)
  {
    setBrightness(0);
  }
  else if (nowHour > 7)
  {
    setBrightness(16);
  }
  updateClock();
  delay(15000);
}
