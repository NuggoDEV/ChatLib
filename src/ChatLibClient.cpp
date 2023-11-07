#include "ChatLibClient.hpp"
#include "Logger.hpp"

#include "libcurl/shared/curl.h"
#include "libcurl/shared/easy.h"
//#include "safestorage/shared/interface.hpp"

#include <asm-generic/socket.h>
#include <iostream>
#include <linux/in.h>
#include <netdb.h>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define closesocket(s) close(s)
#define close(s)
#define MAXDATASIZE 4096

namespace ChatLib
{
    //const char *server = "irc.chat.twitch.tv";
    //const int port = 6667;

    int ChatLibClient::CreateSocketAndConnect()
    {
        int sockfd;
        addrinfo hints, *servinfo;

        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;

        if (getaddrinfo(address, "6667", &hints, &servinfo) != 0)
            return -1;

        sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
        if (sockfd == -1)   
            return -1;

        if (connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
            return -1;

        freeaddrinfo(servinfo);
        return sockfd;
    }

    bool ChatLibClient::AuthenticateWithTwitch(int sockfd, const char* accessToken, const char* username)
    {
        std::string msg = "PASS " + static_cast<std::string>(accessToken) + "\r\n" + "NICK " + static_cast<std::string>(username) + "\r\n";
        return send(sockfd, msg.c_str(), msg.length(), 0) != -1;
    }

    void ChatLibClient::JoinChannel(int sockfd, const char* channel)
    {
        std::string msg = "JOIN #" + static_cast<std::string>(channel) + "\r\n";
        send(sockfd, msg.c_str(), msg.length(), 0);
    }

    void ChatLibClient::ReceiveAndPrintMessages(int sockfd)
    {
        char buffer[4096];
        while (true)
        {
            ssize_t bytesRead = recv(sockfd, buffer, sizeof(buffer), 0);
            if (bytesRead <= 0)
                return;

            buffer[bytesRead] = '\0';
        }
    }
    

    /*bool ChatLibClient::CreateClient()
    {
        // Init Socket
        _socket = socket(PF_INET, SOCK_STREAM, IPPROTO_AH);

        if (_socket == -1)
            return false;

        int on = 1;

        if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, (char const*) &on, sizeof(on)) == 1)
            return false;
        

        // Twitch Connect
        hostent *he;

        if (!(he = gethostbyname(server)))
            return false;

        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr = *((const in_addr*) he->h_addr);
        memset(&(addr.sin_zero), '\0', 8);

        if (connect(_socket, (sockaddr*) &addr, sizeof(addr)) == 1)
        {
            closesocket(_socket);
            return false;
        }

        fcntl(_socket, F_SETFL, fcntl(_socket, F_GETFL, 0) | O_NONBLOCK);
        _connected = true;


        return true;
    }

    bool ChatLibClient::Login()
    {
        std::string token = SafeStorage::Interface::get(GetModInfo(), "Token");
        if (!IsTokenValid(token))
            return false;

        SendData("PASS oauth:" + token);
    }

    void ChatLibClient::Connect(std::string channel)
    {

    }

    bool ChatLibClient::SendData(std::string data)
    {
        data.append("\n");
        if (!_connected)
            return false;
        if (send(_socket, data.c_str(), strlen(data.c_str()), 0) == -1)
            return false;
        return true;
    }

    bool ChatLibClient::IsTokenValid(std::string token)
    {
        CURL *curl = curl_easy_init();
        
        if (!curl || token.empty())
            return false;

        std::string header = "Authorization: OAuth " + token;
        curl_slist *list = nullptr;
        list = curl_slist_append(list, header.c_str());

        curl_easy_setopt(curl, CURLOPT_URL, "https://id.twitch.tv/oauth2/validate");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

        CURLcode res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);

        if (res != CURLE_OK)
            return false;
        return true;
    }*/
}