// 8266_epp.cpp header with global variables and function Prototypes

#ifndef _8266_EPP_H
#define _8266_EPP_H

//#ifdef __cplusplus
//extern "C" {
//#endif

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

// Global variables:
/*extern ESP8266WebServer server(80);
extern const char* ssid = "test";
extern const char* passphrase = "test";
extern String st;
extern String content;
extern int statusCode;*/

bool testWifi(void);
void launchWeb(int webtype);
void setupAP(void);
void createWebServer(int webtype);
void init_8266_ep(void);
void LoopWork8266EEP(void);

//#ifdef __cplusplus
//}
//#endif

#endif
