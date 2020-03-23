#include "main.h"

WiFiMulti wifiMulti;

/** Connection change status */
bool connStatusChanged = false;

/**
   @briefCallback for WiFi events
*/
void wifiEventCb(WiFiEvent_t event)
{
  myLog_d("[WiFi-event] event: %d", event);
  IPAddress localIP;
  switch (event)
  {
    case SYSTEM_EVENT_STA_GOT_IP:
      connStatusChanged = true;

      localIP = WiFi.localIP();
      myLog_d("Connected to AP: %s with IP: %d.%d.%d.%d RSSI: %d",
              WiFi.SSID().c_str(),
              localIP[0], localIP[1], localIP[2], localIP[3],
              WiFi.RSSI());
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      connStatusChanged = true;
      myLog_e("WiFi lost connection");
      break;
    default:
      break;
  }
}

/**
   Initialize WiFi
   - Check if WiFi credentials are stored in the preferences
   - Create unique device name
   - Register WiFi event callback function
   - Try to connect to WiFi if credentials are available
*/
void initWiFi(void)
{
  WiFi.disconnect(true);
  delay(100);
  WiFi.enableSTA(true);
  delay(100);
  WiFi.mode(WIFI_STA);
  delay(100);
  WiFi.onEvent(wifiEventCb);

  // Using WiFiMulti to connect to best AP
  wifiMulti.addAP("FIRST_AP_NAME", "FIRST_AP_PASSWORD");
  wifiMulti.addAP("SECOND_AP_NAME", "SECOND_AP_PASSWORD");
  // wifiMulti.addAP("THIRD_AP_NAME", "THIRD_AP_PASSWORD");}
}
