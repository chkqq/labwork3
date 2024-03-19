#ifndef TVSET_H
#define TVSET_H

#include <iostream>
#include <map>
#include <string>

using namespace std;

class CTVSet
{
public:
    CTVSet();
    void TurnOn();
    void TurnOff();
    void SelectChannel(int channel);
    void SelectChannelByName(const string& name);
    void SelectPreviousChannel();
    void SetChannelName(int channel, const string& name);
    string GetChannelName(int channel) const;
    int GetChannelByName(const string& name) const;
    void DeleteChannelName(const string& name);
    void Info();

private:
    bool m_isOn;
    int m_currentChannel;
    int m_previousChannel;
    map<int, string> m_channelNames;
};

#endif
