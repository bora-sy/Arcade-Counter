#include "Pages.h"
#include <ESP8266WiFi.h>
#include "Config.h"

const char* hostname = "arcadecounter.local";
const char* ap_ssid = "ArcadeCounter";
const char* ap_password = "hackclub";
IPAddress IPAddr;
bool hostnameSuc = false;

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

    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(IPAddress(192, 168, 1, 1), IPAddress(192, 168, 1, 1), IPAddress(255, 255, 255, 0));
    WiFi.softAP(ap_ssid, ap_password);
    hostnameSuc = WiFi.setHostname(hostname);
    IPAddr = WiFi.softAPIP();
    Serial.println("Switched to AP Mode");

    Disp("(AP Mode)\nWaiting for\nconnection...\n\nSSID: " + String(ap_ssid) + "\nPASSWORD: " + String(ap_password), 1);

    while(WiFi.softAPgetStationNum() == 0) delay(100);

    Disp("STA\nConnected",2);
    delay(2000);
}

void SetupSTA()
{
    WiFi.mode(WIFI_STA);
    
    wl_status_t status = WiFi.begin(Config::Network.SSID, Config::Network.Password);
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
        timeoutRemaining--;
    }

    if(status == WL_CONNECTED)
    {
        hostnameSuc = WiFi.setHostname(hostname);
        IPAddr = WiFi.localIP();
        Serial.println("\nConnected to WiFi");
        Disp("Connected", 2);
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

void SetupConfigServer()
{
    WebServer::Initialize();

    if(!Config::networkInit || !Config::userInit)
    {
        Serial.printf("Hostname suc: %d", hostnameSuc);
        Disp("-Missing Config-\n\nGo to\n\n" + String(hostname) + "\nor\nhttp://" + IPAddr.toString() + "/", 1);
        while (true)
        {
            WebServer::Periodic();
            yield();
            esp_yield();
        }
    }


}

void Startup()
{
      
    Serial.printf("Config init suc: %d\n", Config::Initialize());
    Serial.printf("Network: (SSID: %s) (PW: %s)\n", (char*)Config::Network.SSID, (char*)Config::Network.Password);
    Serial.printf("User:    (SlackID: %s) (AirtableID: %s)\n", (char*)Config::User.SlackMemberID, (char*)Config::User.UserAirtableID);

    if(!Config::networkInit) SetupAP();
    else SetupSTA();

    SetupConfigServer();
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