#include "WebServer/WebServer.hpp"
#include "assets.hpp"
#include "WebServer/ServeAssets.hpp"
#include "Logger.hpp"

#include "safestorage/shared/interface.hpp"

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

                if (req.has_param("token"))
                {
                    SafeStorage::Interface::remove(GetModInfo(), "Token");
                    SafeStorage::Interface::insert(GetModInfo(), "Token", req.get_param_value("Token"));
                }
            });

            serveAssets(server);

            server.listen("0.0.0.0", 50009);
        });
    }
}