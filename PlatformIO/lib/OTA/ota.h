#ifndef _OTA_FLASHING_H
#define _OTA_FLASHING_H

#include <include/slist.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
//#include "udpDebug.h"

void OtaSetup(void);
void OtaHandleRequests(void);

#endif
