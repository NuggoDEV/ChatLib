#include "WebServer/WebServer.hpp"
#include "assets.hpp"


namespace WebServer {
    bool wsrunning = false;

    void start() {
        if (wsrunning) return;
        wsrunning = true;
        new std::thread([]() {
            httplib::Server server;

            server.Get("/", [](const httplib::Request& req, httplib::Response& res) {
                const std::string_view htmlContent = static_cast<std::string_view>(IncludedAssets::index_html);
                res.set_content(htmlContent.data(), htmlContent.size(), "text/html");
            });

            server.Get("/api", [](const httplib::Request& req, httplib::Response& res) {

            });

            server.listen("0.0.0.0", 50009);
        });
    }
}