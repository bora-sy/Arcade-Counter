#pragma once
#include <Arduino.h>
#include <DataSaving.h>

#define MAX_SSID_LENGTH 32
#define MAX_PASSWORD_LENGTH 32

#define MAX_SLACK_MEMBER_ID_LENGTH 32
#define MAX_USER_AIRTABLE_ID_LENGTH 32

#define CONFIGFILE_NETWORK "/network.config"
#define CONFIGFILE_USER "/user.config"

struct NetworkConfig
{
    char SSID[MAX_SSID_LENGTH + 1];
    char Password[MAX_PASSWORD_LENGTH + 1];

    NetworkConfig(const char* _ssid, const char* _password);
    NetworkConfig();
};

struct UserConfig
{
    char SlackMemberID[MAX_SLACK_MEMBER_ID_LENGTH + 1];
    char UserAirtableID[MAX_USER_AIRTABLE_ID_LENGTH + 1];

    UserConfig(const char* _slackid, const char* _airtableid);
    UserConfig();
};


namespace Config
{
    extern NetworkConfig Network;
    extern UserConfig User; 

    bool Initialize();

    bool SetUser(UserConfig _user);
    
    bool SetNetwork(NetworkConfig _network);
}


