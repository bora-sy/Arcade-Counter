#include "ConfigServer/WebServer.h"

ESP8266WebServer server(80);


namespace WebServer
{

    void mainPage()
    {
        server.send(200, "text/html", "<h1>Hello World</h1>");
    }

    void SetNetworkConfig()
    {
        String ssid = server.arg("ssid");
        String password = server.arg("password");
        
        bool suc = Config::SetNetwork(NetworkConfig(ssid.c_str(), password.c_str()));
        Serial.printf("Networkconfig set suc: %d\n", suc);

        server.send(suc ? 200 : 500, "text/plain", suc ? "1" : "0");
        
    }

    void SetUserConfig()
    {
        String slackID = server.arg("slackid");
        String airtableID = server.arg("userairtableid");
        
        bool suc = Config::SetUser(UserConfig(slackID.c_str(), airtableID.c_str()));
        Serial.printf("Userconfig set suc: %d\n", suc);
        
        server.send(suc ? 200 : 500, "text/plain", suc ? "1" : "0");
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
        server.on("/api/restart", HTTP_POST, restart);
    }

    void Periodic()
    {
        server.handleClient();
    }
}