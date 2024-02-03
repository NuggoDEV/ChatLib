#include "Helpers/TwitchTokenValidation.hpp"
#include "Logger.hpp"

// Twitch OAuth2 token validation endpoint
const std::string TWITCH_TOKEN_VALIDATION_URL = "https://id.twitch.tv/oauth2/validate";

/**
 * @brief Callback function for libcurl to handle HTTP response.
 * @param contents The received data.
 * @param size The size of each data element.
 * @param nmemb The number of data elements.
 * @param output The output string to store the received data.
 * @return The total size of the received data.
 */
size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

using namespace ChatLib::CusLogger;
using namespace ChatLib::Helpers::TwitchTokenValidator;

/**
 * @brief Validates a Twitch OAuth2 token for a given account.
 * @param token The Twitch authentication token to be validated.
 * @param username The Twitch account name associated with the token.
 * @return True if the token is valid for the specified account, otherwise false.
 */
bool validateToken(std::string token, std::string username) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        return false;
    }

    // Construct the validation URL with the provided token
    std::string validationUrl = TWITCH_TOKEN_VALIDATION_URL + "?oauth_token=" + token;

    // Set libcurl options
    curl_easy_setopt(curl, CURLOPT_URL, validationUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);

    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        // Log an error message if Twitch token validation fails
        out_severe("Twitch token validation failed. CURL error: " + std::string(curl_easy_strerror(res)));
        curl_easy_cleanup(curl);
        return false;
    }

    long httpCode = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);

    curl_easy_cleanup(curl);

    if (httpCode == 200) {
        // Log an info message if Twitch token validation is successful
        out_info("Twitch token validation successful.");
        return true;
    } else {
        // Log an error message if Twitch token validation fails
        out_severe("Twitch token validation failed. HTTP error: " + std::to_string(httpCode));
        return false;
    }
}
