#include "WebServer/WebServer.hpp"
#include "assets.hpp"
#include "WebServer/ServeAssets.hpp"


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

            server.Get("/authorization", [](const httplib::Request& req, httplib::Response& res) {
                std::string params = "";
                params = req.get_param_value("access_token");
                //params = req.params;
                //for (auto value : req.params)
                //    params.append(value.first + " " + value.second + "\n");

                res.set_content(params.data(), params.size(), "text/plain");
            });

            server.listen("0.0.0.0", 50009);
        });
    }
}