#pragma once
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "Config.h"
#include "ConfigServer/WebPages.h"

namespace WebServer
{

    void Initialize();

    void Periodic();
}