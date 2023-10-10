namespace Twitch {
    class Message {
    private:

    public:
        std::string content = nullptr;
        std::string author = nullptr;
        std::string channel = nullptr;
        std::string timestamp = nullptr;
    };
}