# ChatLib API Doc

## Quickstart

ChatLib provides both a Shared API (used in BeatSaber mods) and an HTTP / Websocket API (used in external programs).

### Shared API

Make sure to install ChatLib using Quest Package Manager (qpm) into your project.

> [!NOTE]
>Documentation for the Header API coming soon.


### HTTP / Websocket API

ChatLib provides an api which can be accessed by anyone on the local network on port ``50009``.
The API can be used to manage accounts, execute actions of the mod and more.

Additionally, ChatLib provides a websocket server on port ``50010`` where you can hook onto channels
and receive / send messages. 

> [!IMPORTANT]
> If you're developing a Beat Saber mod, please **do not use** these endpoints. Instead, install the libary
> using Quest Package Manager (qpm) into your project and use shared api (header files in the shared folder).

### Here is a simple overview of all the endpoints:

| Endpoint | Description              | Format   | ApiDoc                |
| -------- |--------------------------|----------|-----------------------|
| ``/api/accounts`` | List and manage accounts | ``JSON`` | [Link](./accounts.md) |