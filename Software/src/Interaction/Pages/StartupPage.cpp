#include "Pages.h"
#include <ESP8266WiFi.h>
#include "Config.h"

void StartupPage::OnLoad()
{
    wl_status_t status = WiFi.begin(Config::Network.SSID, Config::Network.Password);
    ShowInfo("Connecting\nto WiFi");

    Serial.print("Connecting to WiFi");

    int timeoutRemaining = 40;
    while (status != WL_CONNECTED && timeoutRemaining > 0)
    {
        status = WiFi.status();
        Serial.print(".");
        delay(500);
        esp_yield();
        timeoutRemaining--;
    }

    if(status)
    {
        Serial.println("\nConnected to WiFi");
        ShowInfo("Connected\n\nIP ADDRESS\n" + WiFi.localIP().toString());
        delay(2000);
    }
    else
    {
        Serial.println("\nFailed to connect to WiFi");
        ShowInfo("Failed to\nconnect to\nWiFi\n\nRestart\nRequired");
        while (true);
    }



    ClearInfo();
    
}

void StartupPage::OnExit()
{
    
}

void StartupPage::OnInput(BtnInput input){}

void StartupPage::Periodic()
{
    
}

void StartupPage::ShowInfo(String info)
{
    this->ToggleAllVisible(false, false);

    this->labelInfo.UpdateText(info);
    this->labelInfo.SetVisible(true, false);
    this->DrawIfShown();
}

void StartupPage::ClearInfo()
{
    this->ToggleAllVisible(true, false);

    this->labelInfo.SetVisible(false, false);
    
    this->DrawIfShown();
}


StartupPage::StartupPage()
{
    this->labelInfo = Label(RelativePoint(0, 0.5), "", 2, Color::White, RelativePoint(0, 0.5));
    labelInfo.SetVisible(false, false);

    this->AddComponent(&labelInfo);
}