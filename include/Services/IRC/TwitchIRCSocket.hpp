#pragma once

#include <iostream>
#include <sstream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "netdb.h"


#define closesocket(s) close(s)
#define close(s)
#define SOCKET_ERROR -1
#define INVALID_SOCKET = -1

namespace ChatLib::Services
{
    class TwitchIRCSocket
    {
        public:
        bool Init();

        bool Connect(char const *host, int port);
        void Disconnect();

        bool Connected() { return _connected; }

        bool SendData(char const *data);
        std::string RecieveData();

        private:
        int _socket;
        bool _connected = false;
    };
}