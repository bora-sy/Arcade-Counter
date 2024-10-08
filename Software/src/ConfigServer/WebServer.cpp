#include "ConfigServer/WebServer.h"

ESP8266WebServer server(80);


namespace WebServer
{

    void mainPage()
    {
        WiFiMode_t mode = WiFi.getMode();

        switch (mode)
        {
        case WiFiMode_t::WIFI_OFF:
            server.send(200, "text/plain", "WiFi is off (somehow?)");
            break;
        case WiFiMode_t::WIFI_STA:
            server.send(200, "html", (const char*)PAGE_STA);
            break;

        case WiFiMode_t::WIFI_AP:
            server.send(200, "text/html", (const char*)PAGE_AP);
            break;
        
        default:
            server.send(200, "text/plain", "Something went wrong..");
            break;
        }
    }

    void SetNetworkConfig()
    {
        String ssid = server.arg("ssid");
        String password = server.arg("password");
        
        ssid.trim();
        password.trim();

        if(ssid == "" || password == ""){server.send(400, "text/plain", "0"); return;}
        
        bool suc = Config::SetNetwork(NetworkConfig(ssid.c_str(), password.c_str()));
        Serial.printf("Networkconfig set suc: %d\n", suc);

        server.send(suc ? 200 : 500, "text/plain", suc ? "1" : "0");
        
    }

    void SetUserConfig()
    {
        String slackID = server.arg("slackmemberid");
        String airtableID = server.arg("userairtableid");

        slackID.trim();
        airtableID.trim();

        if(slackID == "" || airtableID == ""){server.send(400, "text/plain", "0"); return;}
        
        bool suc = Config::SetUser(UserConfig(slackID.c_str(), airtableID.c_str()));
        Serial.printf("Userconfig set suc: %d\n", suc);
        
        server.send(suc ? 200 : 500, "text/plain", suc ? "1" : "0");
    }    
    
    void GetNetworkConfig()
    {
        char buf[128];
        
        sprintf(buf, "{\"ssid\":\"%s\",\"password\":\"%s\"}", Config::Network.SSID, Config::Network.Password);

        server.send(200, "application/json", buf);
    }

    void GetUserConfig()
    {
        char buf[128];
        
        sprintf(buf, "{\"slackmemberid\":\"%s\",\"userairtableid\":\"%s\"}", Config::User.SlackMemberID, Config::User.UserAirtableID);

        server.send(200, "application/json", buf);
    }

    void restart()
    {
        server.send(200, "text/plain", "ok");
        delay(1000);
        ESP.restart();
    }

    void Initialize()
    {
        server.begin(80);

        server.on("/", HTTP_GET, mainPage);
        server.on("/api/config/network", HTTP_POST, SetNetworkConfig);
        server.on("/api/config/user", HTTP_POST, SetUserConfig);
        server.on("/api/config/network", HTTP_GET, GetNetworkConfig);
        server.on("/api/config/user", HTTP_GET, GetUserConfig);
        server.on("/api/restart", HTTP_POST, restart);
    }

    void Periodic()
    {
        server.handleClient();
    }
}