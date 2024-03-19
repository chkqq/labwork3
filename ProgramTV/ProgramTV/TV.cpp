#include <iostream>
#include <string>
#include <sstream>
#include "TVSet.h"

using namespace std;

void displayMenu()
{
    cout << "=== TV Control Menu ===\n"
        << "1. turn_on\n"
        << "2. turn_off\n"
        << "3. select_channel <channel_number>\n"
        << "4. select_channel_by_name <channel_name>\n"
        << "5. select_previous_channel\n"
        << "6. set_channel_name <channel_number> <channel_name>\n"
        << "7. get_channel_name <channel_number>\n"
        << "8. get_channel_by_name <channel_name>\n"
        << "9. delete_channel_name <channel_name>\n"
        << "10. TV_info\n"
        << "11. exit\n"
        << "=======================\n";
}

void PrintError(const string& error)
{
    cout << error << endl;
}

void PrintMissingParameterError(const string& parameter)
{
    PrintError("Missing parameter. Enter " + parameter + ".");
}

void PrintInvalidParameterError(const string& parameter)
{
    PrintError("Invalid " + parameter + ".");
}

void processCommand(CTVSet& tv, const string& command)
{
    istringstream iss(command);
    string cmd, param1, param2;
    iss >> cmd >> param1 >> param2;

    if (cmd.empty()) {
        PrintError("Invalid command. Type 'help' for the list of commands.");
        return;
    }

    if (cmd == "turn_on" || cmd == "1")
    {
        tv.TurnOn();
    }
    else if (cmd == "turn_off" || cmd == "2")
    {
        tv.TurnOff();
    }
    else if (cmd == "select_channel" || cmd == "3")
    {
        if (param1.empty())
        {
            PrintMissingParameterError("channel number");
            return;
        }
        int channel;
        if (!(istringstream(param1) >> channel))
        {
            PrintInvalidParameterError("channel number");
            return;
        }
        tv.SelectChannel(channel);
    }
    else if (cmd == "select_channel_by_name" || cmd == "4")
    {
        if (param1.empty())
        {
            PrintMissingParameterError("channel name");
            return;
        }
        tv.SelectChannelByName(param1);
    }
    else if (cmd == "select_previous" || cmd == "5")
    {
        tv.SelectPreviousChannel();
    }
    else if (cmd == "set_channel_name" || cmd == "6")
    {
        if (param1.empty() || param2.empty())
        {
            PrintMissingParameterError("channel number and name.");
            return;
        }
        int channel;
        if (!(istringstream(param1) >> channel))
        {
            PrintInvalidParameterError("channel number");
            return;
        }
        tv.SetChannelName(channel, param2);
    }
    else if (cmd == "get_channel_name" || cmd == "7")
    {
        if (param1.empty())
        {
            PrintMissingParameterError("channel number");
            return;
        }
        int channel;
        if (!(istringstream(param1) >> channel))
        {
            PrintInvalidParameterError("channel number");
            return;
        }
        string channelName = tv.GetChannelName(channel);
        if (channelName.empty())
        {
            cout << "No channel name\n";
        }
        else
        {
            cout << "Channel name: " << channelName << "\n";
        }
    }
    else if (cmd == "get_channel_by_name" || cmd == "8")
    {
        if (param1.empty())
        {
            PrintMissingParameterError("channel name");
            return;
        }
        int channelNumber = tv.GetChannelByName(param1);
        if (channelNumber == -1)
        {
            cout << "No channel with this name";
        }
        else
        {
            cout << "Channel Number: " << channelNumber << "\n";
        }
    }
    else if (cmd == "delete_channel_name" || cmd == "9")
    {
        if (param1.empty())
        {
            PrintMissingParameterError("channel name");
            return;
        }
        tv.DeleteChannelName(param1);
    }
    else if (cmd == "TV_info" || cmd == "10")
    {
        tv.Info();
    }
    else if (cmd == "exit" || cmd == "11")
    {
        cout << "Exiting...\n";
        exit(0);
    }
    else if (cmd == "help" || cmd == "0")
    {
        displayMenu();
    }
    else
    {
        PrintError("Invalid command. Type 'help' or '0' for the list of commands.");
    }
}


void TVRun()
{
    CTVSet tv;
    cout << "Welcome to TV Control!\n";
    string command;
    while (true)
    {
        cout << "> ";
        getline(cin, command);
        processCommand(tv, command);
    }
}
