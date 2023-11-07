#pragma once

#include "Services/IRC/TwitchIRCSocket.hpp"
#include <string>

namespace ChatLib
{
    class ChatLibClient
    {
        public:
        const char *address = "irc.chat.twitch.tv";
        const int port = 6667;

        //bool CreateClient();
        int CreateSocketAndConnect();
        bool AuthenticateWithTwitch(int sockfd, const char* accessToken, const char* username);
        void JoinChannel(int sockfd, const char* channel);
        void ReceiveAndPrintMessages(int sockfd);

        //bool Login();
        //void Connect(std::string channel);
        //void Disconnect();
        
        //bool SendData(std::string data);
        //bool IsTokenValid(std::string token);

        private:
        int _socket;
        bool _connected = false;
        //Services::TwitchIRCSocket socket;
    };
}