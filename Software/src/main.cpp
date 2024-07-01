#include <Arduino.h>
#include "Pages.h"
#include "Config.h"




void setup() {
  Serial.begin(921600);
  bool pvb = PagedView::Begin();
  if(!pvb)
  {
    Serial.println("Display init failed");
    delay(2000);
    ESP.restart();
    return;
  }

  Pages::Initialize();
  Serial.println("Begin");
  
  Pages::startupPage->Show();

}

void loop() {
  PagedView::Periodic();
}