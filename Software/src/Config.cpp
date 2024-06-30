#include "Config.h"

namespace Config
{
    NetworkConfig Network;
    UserConfig User; 

    bool InitializeNetwork()
    {
        if (!DataSaving::FileExists(CONFIGFILE_NETWORK))
            return false;
        uint16_t configsize = sizeof(Network);
        return DataSaving::ReadData(CONFIGFILE_NETWORK, (uint8_t *)&Network, configsize) == configsize;
    }

    bool InitializeUser()
    {
        if (!DataSaving::FileExists(CONFIGFILE_USER))
            return false;
        uint16_t configsize = sizeof(User);
        return DataSaving::ReadData(CONFIGFILE_USER, (uint8_t *)&User, configsize) == configsize;
    }

    bool Initialize()
    {
        if (!DataSaving::Initialize())
            return false;
        return InitializeNetwork() && InitializeUser();
    }

    bool SetUser(UserConfig _user)
    {
        uint16_t configsize = sizeof(User);
        if (sizeof(_user) != configsize)
            return false;

        bool writesuc = DataSaving::WriteData(CONFIGFILE_USER, (uint8_t *)&_user, configsize) == configsize;
        if (!writesuc)
            return false;

        User = _user;
        return true;
    }

    bool SetNetwork(NetworkConfig _network)
    {
        uint16_t configsize = sizeof(Network);
        if (sizeof(_network) != configsize)
            return false;

        bool writesuc = DataSaving::WriteData(CONFIGFILE_NETWORK, (uint8_t *)&_network, configsize) == configsize;
        if (!writesuc)
            return false;

        Network = _network;
        return true;
    }
}

NetworkConfig::NetworkConfig(){}
NetworkConfig::NetworkConfig(const char *_ssid, const char *_password)
{
    strncpy(SSID, _ssid, MAX_SSID_LENGTH);
    strncpy(Password, _password, MAX_PASSWORD_LENGTH);
}

UserConfig::UserConfig(){}
UserConfig::UserConfig(const char *_slackid, const char *_airtableid)
{
    strncpy(SlackMemberID, _slackid, MAX_SLACK_MEMBER_ID_LENGTH);
    strncpy(UserAirtableID, _airtableid, MAX_USER_AIRTABLE_ID_LENGTH);
}
