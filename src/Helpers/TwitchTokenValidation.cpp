#include "Helpers/TwitchTokenValidation.hpp"
#include "Logger.hpp"

const std::string TWITCH_TOKEN_VALIDATION_URL = "https://id.twitch.tv/oauth2/validate";

size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

using namespace ChatLib::CusLogger;
using namespace ChatLib::Helpers::TwitchTokenValidator;

bool validateToken(std::string token, std::string username) {
    CURL* curl = curl_easy_init();
    if(!curl) return false;

    std::string validationUrl = TWITCH_TOKEN_VALIDATION_URL + "?oauth_token=" + token;
    curl_easy_setopt(curl, CURLOPT_URL, validationUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);

    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        out_severe("Twitch token validation failed. CURL error: " + std::string(curl_easy_strerror(res)));
        curl_easy_cleanup(curl);
        return false;
    }

    long httpCode = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);

    curl_easy_cleanup(curl);

    if (httpCode == 200) {
        out_info("Twitch token validation successful.");
        return true;
    } else {
        out_severe("Twitch token validation failed. HTTP error: " + std::to_string(httpCode));
        return false;
    }
}