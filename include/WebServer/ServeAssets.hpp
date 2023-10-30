#pragma once

#include "httplib/httplib.h"
#include "assets.hpp"


void serveAssets(httplib::Server& server) {
    server.Get("/header-background.jpg", [](const httplib::Request& req, httplib::Response& res) {
        const std::string_view jpgContent = static_cast<std::string_view>(IncludedAssets::header_background_jpg);
        res.set_content(jpgContent.data(), jpgContent.size(), "image/jpeg");
    });
};