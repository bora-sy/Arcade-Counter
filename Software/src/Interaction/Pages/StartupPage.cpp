#include "Pages.h"
#include <ESP8266WiFi.h>
#include "Config.h"

void Disp(String text, uint8_t textSize = 2)
{
    Pages::startupPage->ShowInfo(text, textSize);
}
void NoDisp()
{
    Pages::startupPage->ClearInfo();
}

void SetupAP()
{
    const char* ssid = "ArcadeCounter";
    const char* password = "hackclub";

    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);

    Serial.println("Switched to AP Mode");


    
}

void SetupSTA()
{
    WiFi.mode(WIFI_STA);
    
    wl_status_t status = WiFi.begin(Config::Network.SSID + String("a"), Config::Network.Password);
    String cnctowifi = "Connecting\nto WiFi";
    
    const char* dots[] = {"",".", "..", "..."};

    Disp(cnctowifi);

    Serial.print("Connecting to WiFi");

    int timeoutRemaining = 10;
    int doti = 0;

    while (status != WL_CONNECTED && timeoutRemaining > 0)
    {
        status = WiFi.status();
        Serial.print(".");
        Disp(cnctowifi + dots[doti++ % 4]);
        delay(500);
        esp_yield();
        timeoutRemaining--;
    }

    if(status == WL_CONNECTED)
    {
        Serial.println("\nConnected to WiFi");
        Disp("Connected\n\nIP ADDR\n" + WiFi.localIP().toString(), 1);
        delay(4000);
    }
    else
    {
        Serial.println("\nFailed to connect to WiFi, switching to AP mode");
        Disp("Connection\nFailed\nSwitching\nTo AP Mode");
        delay(3000);
        SetupAP();
    }

}

void Startup()
{
      
    Serial.printf("Config init suc: %d\n", Config::Initialize());
    Serial.printf("Network: (SSID: %s) (PW: %s)\n", (char*)Config::Network.SSID, (char*)Config::Network.Password);
    Serial.printf("User:    (SlackID: %s) (AirtableID: %s)\n", (char*)Config::User.SlackMemberID, (char*)Config::User.UserAirtableID);

    if(!Config::networkInit) SetupAP();
    else SetupSTA();
}


void StartupPage::OnLoad()
{
    Startup();
}

void StartupPage::OnExit()
{
    
}

void StartupPage::OnInput(BtnInput input){}

void StartupPage::Periodic()
{
    
}

void StartupPage::ShowInfo(String info, uint8_t textSize)
{
    this->ToggleAllVisible(false, false);

    this->labelInfo.UpdateTextSize(textSize, false);
    this->labelInfo.UpdateText(info, false);
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