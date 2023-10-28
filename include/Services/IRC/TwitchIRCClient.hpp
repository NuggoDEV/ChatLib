#include <string>
#include <vector>
#include <list>
#include "Services/IRC/TwitchIRCSocket.hpp"

namespace ChatLib::Services
{
    class TwitchIRCClient;

    extern std::vector<std::string> split(std::string const&, char);

    struct IRCCommandPrefix
    {
        void Parse(std::string data)
        {
            if (data == "")
                return;

            prefix = data.substr(1, data.find(" ") - 1);
            std::vector<std::string> tokens;

            if (prefix.find("@") != std::string::npos)
            {
                tokens = split(prefix, '@');
                nick = tokens.at(0);
                user = tokens.at(1);
            }
            if (nick != "" && nick.find("!") != std::string::npos)
            {
                tokens = split(nick, '!');
                nick = tokens.at(0);
                user = tokens.at(1);
            }
        }

        std::string prefix;
        std::string nick;
        std::string user;
        std::string host;
    };

    struct IRCMessage
    {
        IRCMessage();
        IRCMessage(std::string cmd, IRCCommandPrefix p, std::vector<std::string> params) : command(cmd), prefix(p), parameters(params) {};
        std::string command;
        IRCCommandPrefix prefix;
        std::vector<std::string> parameters;
    };

    struct IRCCommandHook
    {
        IRCCommandHook() : function(NULL) {};

        std::string command;
        void (*function)(IRCMessage /*message*/, TwitchIRCClient* /*client*/);
    };

    class TwitchIRCClient
    {
        public:
        TwitchIRCClient() {};

        bool InitSocket();
        bool Connect();
        void Disconnect();
        bool Connected() { return _socket.Connected(); }

        bool SendIRC(std::string data);

        bool Login(std::string nickname, std::string oauth = std::string());

        bool JoinChannel(std::string channel);

        bool LeaveChannel();

        bool SendChatMessage(std::string message);

        void ReceiveData();

        void HookIRCCommand(std::string command, void (*function)(IRCMessage message, TwitchIRCClient *client));

        void Parse(std::string data);

        private:
        void HandleCommand(IRCMessage message);
        void CallHook(std::string command, IRCMessage message);

        TwitchIRCSocket _socket;
        std::list<IRCCommandHook> _hooks;
        std::string _currentChannel;
    };
}