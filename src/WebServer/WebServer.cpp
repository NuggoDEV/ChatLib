#include "WebServer/WebServer.hpp"
#include "assets.hpp"
#include "WebServer/ServeAssets.hpp"
#include "PrivateVariables.hpp"

std::string code = "";

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

            serveAssets(server);

            server.Get("/auth", [](const httplib::Request& req, httplib::Response& res) {
                if (req.has_param("token"))
                {
                    code = req.get_param_value("token");
                    res.set_content(code.data(), code.size(), "text/plain");
                }
            });

            server.listen("0.0.0.0", 50009);
        });
    }
}