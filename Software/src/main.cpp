#include <Arduino.h>
#include "Pages.h"




void setup() {
  Serial.begin(921600);

  Serial.println("Begin");

  PagedView::Begin();
  Pages::Initialize();

  Pages::mainPage->Show();
}

void loop() {
  PagedView::Periodic();
}
