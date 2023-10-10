
#include "Logger.hpp"
#include "Services/IRC/TestClient.hpp"
#include "socket_lib/shared/ClientSocket.hpp"
#include "socket_lib/shared/ServerSocket.hpp"
#include "socket_lib/shared/SocketHandler.hpp"
#include "socket_lib/shared/Socket.hpp"
#include "socket_lib/shared/SocketLogger.hpp"

void Test()
{
    SocketLib::SocketHandler& handler = SocketLib::SocketHandler::getCommonSocketHandler();
    SocketLib::ClientSocket *socket = handler.createClientSocket("irc.chat.twitch.tv", 6667);
    socket->connect();
    getLogger().info("Connected!");
}