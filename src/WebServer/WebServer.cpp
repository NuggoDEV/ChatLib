#include "WebServer/WebServer.hpp"
#include "assets.hpp"


namespace WebServer {
    void start() {
        if (running) return;
        running = true;
        new std::thread([]() {
            httplib::Server server;

            server.Get("/", [](const httplib::Request& req, httplib::Response& res) {
                const std::string_view htmlContent = static_cast<std::string_view>(IncludedAssets::index_html);
                res.set_content(htmlContent.data(), htmlContent.size(), "text/html");
            });

            server.listen("0.0.0.0", 50009);
        });
    }
}