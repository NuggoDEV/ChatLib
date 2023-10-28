#include <cstring>
#include <fcntl.h>
#include <linux/in.h>
#include "Services/IRC/TwitchIRCSocket.hpp"

#define MAXDATASIZE 4096

namespace ChatLib::Services
{
    bool TwitchIRCSocket::Init()
    {
        if ((_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
            return false;

        int on = 1;

        if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, (char const*)&on, sizeof(on)) == 1)
            return false;
        return true;
    }

    bool TwitchIRCSocket::Connect(char const *host, int port)
    {
        hostent *he;

        if (!(he = gethostbyname(host)))
            return false;

        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr = *((const in_addr*)he->h_addr);
        memset(&(addr.sin_zero), '\0', 8);

        if (connect(_socket, (sockaddr*)&addr, sizeof(addr)) == -1)
        {
            closesocket(_socket);
            return false;
        }

        fcntl(_socket, F_SETFL, fcntl(_socket, F_GETFL, 0) | O_NONBLOCK);
        _connected = true;
        return true;
    }

    void TwitchIRCSocket::Disconnect()
    {
        if (_connected)
        {
            closesocket(_socket);
            _connected = false;
        }
    }

    bool TwitchIRCSocket::SendData(const char* data)
    {
        if (_connected)
            if (send(_socket, data, strlen(data), 0) == -1)
                return false;
        return true;
    }

    std::string TwitchIRCSocket::RecieveData()
    {
        if (_connected)
        {
            char buffer[MAXDATASIZE];
            memset(buffer, 0, MAXDATASIZE);

            int bytes = recv(_socket, buffer, MAXDATASIZE - 1, 0);
            auto err = errno;


            if (bytes > 0)
                return std::string(buffer);
            else if (err != EWOULDBLOCK)
                Disconnect();
        }
        return "";
    }
}