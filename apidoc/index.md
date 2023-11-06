# ChatLib API Doc

ChatLib provides an api which can be accessed by anyone on the local network on port ``50009``.
The API can be used to manage accounts, execute actions of the mod and more.

Additionally, ChatLib provides a websocket server on port ``50010`` where you can hook onto channels
and receive messages. 

> [!IMPORTANT]
> If you're developing a beatsaber mod, please **do not use** these endpoints. Instead, install the libary
> using Quest Package Manager (qpm) into your project and use the provided API in the shared files.

### Here is a simple overview of all the endpoints:

| Endpoint | Description              | Format   | ApiDoc                |
| -------- |--------------------------|----------|-----------------------|
| ``/api/accounts`` | List and manage accounts | ``JSON`` | [Link](./accounts.md) |