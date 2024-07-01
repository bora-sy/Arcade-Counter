#include <Arduino.h>
#include "Pages.h"
#include "Config.h"




void setup() {
  Serial.begin(921600);

  Serial.println("Begin");
  
  Serial.printf("Config init suc: %d\n", Config::Initialize());
  Serial.printf("Network: (SSID: %s) (PW: %s)\n", (char*)Config::Network.SSID, (char*)Config::Network.Password);
  Serial.printf("User:    (SlackID: %s) (AirtableID: %s)\n", (char*)Config::User.SlackMemberID, (char*)Config::User.UserAirtableID);

  PagedView::Begin();
  Pages::Initialize();
  
  Pages::startupPage->Show();

}

void loop() {
  PagedView::Periodic();
}