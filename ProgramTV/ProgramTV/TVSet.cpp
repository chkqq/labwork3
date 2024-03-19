#include <utility>
#include "TVSet.h"
#include "ErrorHandler.h"

using namespace std;

CTVSet::CTVSet() : m_isOn(false), m_currentChannel(0), m_previousChannel(0) {}

void CTVSet::TurnOn()
{
    if (!m_isOn)
    {
        m_isOn = true;
        if (m_previousChannel != 0)
        {
            m_currentChannel = m_previousChannel;
        }
        else
        {
            m_previousChannel = 1;
            m_currentChannel = 1;
        }
        cout << "TV was turned on.\n";
    }
    else
    {
        ShowError(cout, "TV is already turned on.");
    }
}

void CTVSet::TurnOff()
{
    if (m_isOn)
    {
        m_isOn = false;
        m_previousChannel = m_currentChannel;
        m_currentChannel = 0;
        cout << "TV was turned off.\n";
    }
    else
    {
        ShowError(cout, "TV is already turned off.");
    }
}

void CTVSet::SelectChannel(int channel)
{
    if (!m_isOn)
    {
        ShowError(cout, "TV must be turned on.");
        return;
    }
    if (!(channel >= 1 && channel <= 99))
    {
        ShowError(cout, "Enter a valid channel number (1 to 99).");
        return;
    }
    m_previousChannel = m_currentChannel;
    m_currentChannel = channel;
    cout << "Channel " << channel << ", has been selected.\n";
}

void CTVSet::SelectChannelByName(const string& name)
{
    for (auto i = m_channelNames.begin(); i != m_channelNames.end(); ++i)
    {
        if (i->second == name)
        {
            m_previousChannel = m_currentChannel;
            m_currentChannel = i->first;
            cout << "Channel " << i->first << ", has been selected.\n";
            return;
        }
    }
    ShowError(cout, "Channel does not exist.");
}


void CTVSet::SelectPreviousChannel()
{
    if (!m_isOn)
    {
        ShowError(cout, "TV must be turned on.");
        return;
    }
    swap(m_currentChannel, m_previousChannel);
    cout << "Previous channel has been selected.\n";
}

void CTVSet::SetChannelName(int channel, const string& name)
{
    if (!m_isOn)
    {
        ShowError(cout, "TV must be turned on.");
        return;
    }
    if (!(channel >= 1 && channel <= 99))
    {
        ShowError(cout, "Enter a valid channel number (1 to 99).");
        return;
    }
    if (name.empty())
    {
        ShowError(cout, "Channel name cannot be empty.");
        return;
    }
    for (auto i = m_channelNames.begin(); i != m_channelNames.end(); ++i)
    {
        if (i->second == name && i->first != channel)
        {
            m_channelNames.erase(i);
            break;
        }
    }
    m_channelNames[channel] = name;
    cout << "Channel name successfully changed.\n";
}

string CTVSet::GetChannelName(int channel) const
{
    auto i = m_channelNames.find(channel);
    if (i != m_channelNames.end())
    {
        return i->second;
    }
    return "";
}

int CTVSet::GetChannelByName(const string& name) const
{
    for (auto i = m_channelNames.begin(); i != m_channelNames.end(); ++i)
    {
        if (i->second == name)
        {
            return i->first;
        }

    }
    return -1;
}

void CTVSet::DeleteChannelName(const string& name)
{
    for (auto i = m_channelNames.begin(); i != m_channelNames.end(); ++i)
    {
        if (i->second == name)
        {
            m_channelNames.erase(i);
            cout << "Channel name successfully delete.\n";
            return;
        }
    }
    ShowError(cout, "Channel does not exist.");
}

void CTVSet::Info()
{
    cout << "TV is " << (m_isOn ? "ON" : "OFF") << "\n";
    cout << "Current channel: " << m_currentChannel << "\n";
    if (m_channelNames.find(m_currentChannel) != m_channelNames.end())
    {
        cout << "Current channel name: ";
        cout << m_channelNames[m_currentChannel] << "\n";
    }
    for (auto i = m_channelNames.begin(); i != m_channelNames.end(); ++i)
    {
        cout << i->first << " - " << i->second << "\n";
    }
}
