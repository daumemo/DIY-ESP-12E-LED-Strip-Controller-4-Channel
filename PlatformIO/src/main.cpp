#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "ota.h"
#include <EEPROM.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "index.h" //Our HTML webpage contents
#include "setup.h"
#include "reset.h"
#include "clear.h"
#include "reboot.h"
#include "setting.h"

void launchWeb(int webtype);
void handleRoot(void);
void handleSetup(void);
void handleWifiSsids(void);
void handleReset(void);
void handleReboot(void);
void handleClearMem(void);
void handleSetting(void);
void handleChannels(void);

//===============================================================
//  Global Variables
//===============================================================
//Can be changed:
const int outputCount = 4;
const int output[4] = {4, 5, 12, 13}; //output channels 1,2,3,4
const char* ssid = "MC_S1"; //AP SSID
const char* passphrase = "12345678"; //AP Password
volatile int stepDelay[4] = {10, 10, 10, 10}; // delay used between PWM steps.

//Do not change these:
volatile int setValue[4] = {0, 0, 0, 0};
volatile int oldValue[4] = {100, 100, 100, 100};
volatile int groupLastValue[4] = {100, 100, 100, 100};
volatile int tempStepDelay[4] = {0, 0, 0, 0};
volatile int oldSetValue[4] = {0, 0, 0, 0};
String lockMem = "0";
String wifiScanResult = "";
ESP8266WebServer server(80);

//===============================================================
//  Initial startup functions - used to connect to known wifi or 
//  create its own AP
//===============================================================
bool testWifi(void) {
  int c = 0;
  while ( c < 20 ) {
    if (WiFi.status() == WL_CONNECTED) { return true; }
    delay(500);
    c++;
  }
  return false;
}

void setupAP(void) {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  String SSISstr = "\"SSID\":[";
  String RSSIstr = "\"RSSI\":[";
  String Protected = "\"Protected\":[";
  for (int i = 0; i < n; ++i)
    {
      if(i != 0) {
        RSSIstr += ", ";
        SSISstr += ", ";
        Protected += ", ";
      }
      RSSIstr += (WiFi.RSSI(i));
      SSISstr += "\""+ WiFi.SSID(i) + "\"";
      Protected += (WiFi.encryptionType(i) == ENC_TYPE_NONE)?"0":"1";
    }
  RSSIstr += "]";
  SSISstr += "]";
  Protected += "]";
  wifiScanResult = "{ " + RSSIstr +", "+ SSISstr + ", " + Protected +" }";
  delay(100);
  WiFi.softAP(ssid, passphrase, 6, 0);
  launchWeb(1);
}

void createWebServer(int webtype)
{
  if ( webtype == 1 ) {
    server.on("/", handleSetup);
    server.on("/wifissids", handleWifiSsids);
    server.on("/direct", handleRoot);
    server.on("/reset", handleReset);
    server.on("/reboot", handleReboot);
    server.on("/clearmem", handleClearMem);
    server.on("/setting", handleSetting);
    server.on("/channels", handleChannels);
  } else if (webtype == 0) {
    server.on("/", handleRoot);
    server.on("/reset", handleReset);
    server.on("/clearmem", handleClearMem);
    server.on("/reboot", handleReboot);
    server.on("/channels", handleChannels);
  }
}

void launchWeb(int webtype) {
  createWebServer(webtype);
  server.begin();
}

void init_first_boot()
{
  EEPROM.begin(512);
  delay(10);
  String esid;
  for (int i = 0; i < 32; ++i)
    {
      esid += char(EEPROM.read(i));
    }
  String epass = "";
  for (int i = 32; i < 96; ++i)
    {
      epass += char(EEPROM.read(i));
    }
  if ( esid.length() > 1 ) {
      WiFi.mode(WIFI_STA);
      delay(200);
      WiFi.begin(esid.c_str(), epass.c_str());
      if (testWifi()) {
        launchWeb(0);
        return;
      }
  }
  
  if (!testWifi()) {
    setupAP();
  }
}

//===============================================================
//  Routines are executed when you open its IP in browser
//===============================================================
void handleSetting(){
  String qsid = server.arg("ssid");
  String qpass = server.arg("pass");
  if (qsid.length() > 0 && qpass.length() > 0) {
    for (int i = 0; i < 96; ++i) { EEPROM.write(i, 0); }
    for (int i = 0; i < qsid.length(); ++i){
      EEPROM.write(i, qsid[i]);
    }
    for (int i = 0; i < qpass.length(); ++i){
      EEPROM.write(32+i, qpass[i]);
    }
    EEPROM.commit();
    String s = SETTING_page;  
    server.send(200, "text/html", s);
  } else {
    server.send(404, "application/json", "{\"Error\":\"404 not found\"}");
  }
  delay(2000);
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
}
void handleReboot(){
  String s = REBOOT_page;             //Read HTML contents
  server.send(200, "text/html", s);
  delay(2000);
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
}

void handleClearMem(){
  String s = CLEAR_page;             //Read HTML contents
  server.send(200, "text/html", s);
  for (int i = 0; i < 96; ++i) { EEPROM.write(i, 0); }
  EEPROM.commit();
  delay(2000);
  WiFi.disconnect();
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
}

void handleReset(){
  String s = RESET_page;             //Read HTML contents
  server.send(200, "text/html", s); //Send web page
}

String getSsidScan(){
  return wifiScanResult;
}

void handleWifiSsids(void){
  server.send(200, "text/json", getSsidScan());
}

void handleSetup(){
  String s = SETUP_page;             //Read HTML contents
  server.send(200, "text/html", s); //Send web page
}

void handleRoot()
{
  String s = MAIN_page;             //Read HTML contents
  server.send(200, "text/html", s); //Send web page
}

String getChannelsData()
{
  return ("{\"ch1\":" + String(setValue[0]) + ", \"ch2\":" + String(setValue[1]) + ", \"ch3\":" + String(setValue[2]) + ", \"ch4\":" + String(setValue[3]) + ", \"locks\":" + lockMem +"}");
}

void setOutputValue(int outCh, int val)
{
  oldSetValue[outCh] = setValue[outCh];
  setValue[outCh] = val;
}

void setOutputPwm(int chan, int val)
{
  uint32_t mypwm = val * 1023 / 100;
  analogWrite(output[chan], mypwm);
}

void invertChannel(int number)
{
  if (setValue[number] > 0)
  {
    oldValue[number] = setValue[number];
    setOutputValue(number, 0);
  }
  else
  {
    setOutputValue(number, oldValue[number]);
  }
}

void handleChannels()
{
  String ch1(server.arg("ch1"));
  String ch2(server.arg("ch2"));
  String ch3(server.arg("ch3"));
  String ch4(server.arg("ch4"));
  String lcmem(server.arg("locks"));
  bool needToResetGroup = false;

  if (lcmem.length() > 0){
    lockMem = lcmem;
  }

  if ((ch1.length() > 0) && (ch2.length() > 0) && (ch3.length() > 0) && (ch4.length() > 0))
  {
    if ((ch1.toInt() == -1) && (ch2.toInt() == -1) && (ch3.toInt() == -1) && (ch4.toInt() == -1))
    {
      needToResetGroup = true;
      if ((setValue[0] > 0) || (setValue[1] > 0) || (setValue[2] > 0) || (setValue[3] > 0))
      {
        groupLastValue[0] = setValue[0];
        groupLastValue[1] = setValue[1];
        groupLastValue[2] = setValue[2];
        groupLastValue[3] = setValue[3];
        setOutputValue(0, 0);
        setOutputValue(1, 0);
        setOutputValue(2, 0);
        setOutputValue(3, 0);
      }
      else
      {
        setOutputValue(0, groupLastValue[0]);
        setOutputValue(1, groupLastValue[1]);
        setOutputValue(2, groupLastValue[2]);
        setOutputValue(3, groupLastValue[3]);
      }
    }
  }

  if (!needToResetGroup)
  {
    if (ch1.length() > 0)
    {
      if (ch1.toInt() != -1) setOutputValue(0, ch1.toInt());
      else invertChannel(0);
    }
    if (ch2.length() > 0)
    {
      if (ch2.toInt() != -1) setOutputValue(1, ch2.toInt());
      else invertChannel(1);
    }
    if (ch3.length() > 0)
    {
      if (ch3.toInt() != -1) setOutputValue(2, ch3.toInt());
      else invertChannel(2);
    }
    if (ch4.length() > 0)
    {
      if (ch4.toInt() != -1) setOutputValue(3, ch4.toInt());
      else invertChannel(3);
    }
  }
  server.send(200, "text/json", getChannelsData());
}

//==============================================================
//                  SETUP
//==============================================================
void setup()
{

  // Initialize the output variables as outputs
  pinMode(output[0], OUTPUT);
  pinMode(output[1], OUTPUT);
  pinMode(output[2], OUTPUT);
  pinMode(output[3], OUTPUT);
  // Set outputs to LOW
  digitalWrite(output[0], LOW);
  digitalWrite(output[1], LOW);
  digitalWrite(output[2], LOW);
  digitalWrite(output[3], LOW);

  Serial.begin(9600); //maybe is not used...
  init_first_boot();
  OtaSetup();

  server.begin();
}

//==============================================================
//                     LOOP
//==============================================================
void loop()
{
  OtaHandleRequests();

  delay(1);
  for (int i = 0; i < outputCount; i++)
  {
    if (tempStepDelay[i] > 0)
    {
      tempStepDelay[i]--;
    }
    else if (oldSetValue[i] != setValue[i])
    {
      if (oldSetValue[i] < setValue[i])
      {
        oldSetValue[i]++;
      }
      else
      {
        oldSetValue[i]--;
      }
      tempStepDelay[i] = stepDelay[i];
      setOutputPwm(i, oldSetValue[i]);
    }
  }

  server.handleClient();
}
